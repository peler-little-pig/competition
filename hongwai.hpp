//
//  hongwai.hpp
//  智能用纸管理系统
//
//  Created by peler on 2022/7/6.
//  Copyright © 2022 peler. All rights reserved.
//

//防止重复包含
#ifndef HONGWAI_H
#define HONGWAI_H

#include "Arduino.h"

class Hongwai
{
public:
  Hongwai(int pin);
  ~Hongwai();
  bool jianCe();
private:
  int pin;
};

#endif
