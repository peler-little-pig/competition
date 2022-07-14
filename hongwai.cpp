//
//  hongwai.cpp
//  智能用纸管理系统
//
//  Created by peler on 2022/7/6.
//  Copyright © 2022 peler. All rights reserved.
//

#include "hongwai.hpp"

Hongwai::Hongwai(int pin)
{
  this->pin = pin;
  pinMode(this->pin,INPUT);
}

Hongwai::~Hongwai()
{
  
}

bool Hongwai::jianCe()
{
  return !digitalRead(this->pin);
}
