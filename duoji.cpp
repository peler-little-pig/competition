//
//  duoji.cpp
//  智能用纸管理系统
//
//  Created by peler on 2022/7/6.
//  Copyright © 2022 peler. All rights reserved.
//

#include "duoji.hpp"

Duoji::Duoji(int pin)
{
  this->pin = pin;  //预留以便扩展
  this->servo.attach(this->pin);
}

Duoji::~Duoji()
{

}

void Duoji::xuanZhuan(int degree)
{
  this->servo.write(degree);
}
