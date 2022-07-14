//
//  ASR.ino
//  智能用纸管理系统
//
//  Created by peler on 2022/7/6.
//  Copyright © 2022 peler. All rights reserved.
//

#include "ASR.h"  //语音识别
#include "hongwai.hpp"  //红外测距
#include "duoji.hpp"  //舵机控制
#include <LiquidCrystal.h>  //LCD显示

#define MAXPAPER 10   //用纸阈值

//#define DEBUG   //DEBUG模式

//初始化硬件对象
Hongwai *hongwai;
Duoji *duoji;
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

int times = 0;  //用纸数
int overTimes = 0;  //超出的纸数

//抽纸盒盖板状态
bool isOpen = 1;
bool isClose = 0;

void setup() {
  /*
   * 以下为语音识别初始化代码，语音识别模块官方提供
   */
  unsigned char cleck = 0xff;
  unsigned char asr_version = 0;
  Wire.begin();
  Wire.setClock(100000);
  Serial.begin(115200);  //串口波特率设置


  WireReadData(FIRMWARE_VERSION, &asr_version, 1);
  Serial.print("asr_version is ");
  Serial.println(asr_version);
#if 1
  I2CWrite(ASR_CLEAR_ADDR, 0x40); //清除掉电保存区,录入前需要清除掉电保存区
  BusyWait();
  Serial.println("clear flash is ok");
  I2CWrite(ASR_MODE_ADDR, 1); //设置检测模式
  BusyWait();
  Serial.println("mode set is ok");
  AsrAddWords(0, "xiao mu");
  BusyWait();
  AsrAddWords(1, "hong deng");
  BusyWait();
  AsrAddWords(2, "lv deng");
  BusyWait();
  AsrAddWords(3, "lan deng");
  BusyWait();
  //添加与"纸"音相近的词语，提高识别率
  AsrAddWords(4, "shi");
  BusyWait();
  AsrAddWords(5, "chi");
  BusyWait();
  AsrAddWords(6, "zhi");
  BusyWait();
  while (cleck != 7)
  {
    WireReadData(ASR_NUM_CLECK, &cleck, 1);
    Serial.println(cleck);
    delay(100);
  }
  Serial.println("cleck is ok");
#endif

  I2CWrite(ASR_REC_GAIN, 0x40); //识别的灵敏度
  I2CWrite(ASR_VOICE_FLAG, 1); //识别结果提示音开关设置
  I2CWrite(ASR_BUZZER, 1); //开启蜂鸣器
  RGB_Set(255, 255, 255); //设置模块的RGB灯为白色
  delay(500);
  I2CWrite(ASR_BUZZER, 0); //关闭蜂鸣器
  RGB_Set(0, 0, 0); //关闭RGB灯

  //初始化硬件组件
  lcd.begin(16, 2);
  hongwai = new Hongwai(4);
  duoji = new Duoji(2);
}

void loop() {
  if (isOpen)
  {
    if (!isClose)
    {
      duoji->xuanZhuan(180);  //盖板打开
      isClose = 1;
    }
    if (hongwai->jianCe())
    {
      times++;
      delay(500);   //延时，以防止记录多次

      if (times >= MAXPAPER)
      {
        #ifdef DEBUG
        Serial.println("over");
        #endif
        overTimes = times - MAXPAPER;
        isOpen = 0;
        isClose = 0;
      }
    }

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("paper: ");
    lcd.print(times);

    lcd.setCursor(0, 1);
    lcd.print("over paper: ");
    lcd.print(overTimes);
  }
  else
  {
    if (!isClose)
    {
      duoji->xuanZhuan(5);
      isClose = 1;
    }
    else
    {
      unsigned char result;
      WireReadData(ASR_RESULT, &result, 1); //读取识别序号值，并赋值给result，默认是0xff
      delay(100);
      Serial.println(result);

      if (result == 6 || result == 5 || result == 4)
      {
        isOpen = 1;
        isClose = 0;
      }
    }
  }
  delay(10);
}
