// Encoder.cpp
/*
 *   Name:        Encoder 编码器
 *   Created:	  2019/5/29 17:04:32
 *   Author:      Skybo
 *	 explanation: 库使用两个输入信号，低电平有效，
 *                采用外部中断触发信号测量转速和转向，需要用两路外部中断
 */

#include "Encoder.h"
#include "Arduino.h"

//供ISR胶水程序使用
Encoder* Encoder::instance0;
Encoder* Encoder::instance1;

//初始化
Encoder::Encoder(uint8_t Vpin, uint8_t Dpin, uint8_t Mode)
{
	V_pin = Vpin;
	D_pin = Dpin;
	Mode = Way;
	pinMode(V_pin, INPUT);              //计数输入引脚
	pinMode(D_pin, INPUT);              //方向输入引脚
	attachInterrupt(digitalPinToInterrupt(V_pin), ISR0, Way);           //中断0调用函数blink0
	instance0 = this;
	attachInterrupt(digitalPinToInterrupt(D_pin), ISR1, Way);           //中断1调用函数blink1
	instance1 = this;
	time = millis();                   //周期时间1s
	timeV = millis();				   //V 时间初值
	timeV_old = millis();			   //V 时间旧值
	timeD = millis();				   //D 时间初值
}

void Encoder::Test()
{
	if (flag == 0)
	{
		time = millis();
		flag = 1;
	}
	else
	{
		if ((millis() - time) >= cycle)	//
		{
			Veloctity = count;
			Direction = point;
			count = 0;
			flag = 0;
			if (count == 0)
			{
				point = 0;
			}	
		}
	}
}

void Encoder::blink0()
{
	if ((millis() - timeV) > 3) //防抖动处理
	{
		count++;
		timeV_old = timeV;
		timeV = millis();
	}
}

void Encoder::blink1()
{
	if ((millis() - timeD) > 3) //防抖动处理
	{
		//count1++;
		timeD = millis();
		if ((timeV - timeV_old) / 2 > (timeD - timeV))
		{
			point = 1;
		}
		if ((timeV - timeV_old) / 2 < (timeD - timeV))
		{
			point = -1;
		}
	}
}

void Encoder::ISR0()
{
	instance0->blink0();
}

void Encoder::ISR1()
{
	instance1->blink1();
}


