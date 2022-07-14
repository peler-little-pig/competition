//
//  duoji.hpp
//  智能用纸管理系统
//
//  Created by peler on 2022/7/6.
//  Copyright © 2022 peler. All rights reserved.
//

//防止重复包含
#ifndef DUOJI_H
#define DUOJI_H

#include "Arduino.h"
#include <Servo.h>  //Arduino舵机库

class Duoji
{
public:
  Duoji(int pin);
  ~Duoji();
  void xuanZhuan(int degree);
private:
  int pin;
  Servo servo;
};

#endif
