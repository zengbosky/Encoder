// Encoder.h
/*
 *   Name:        Encoder 编码器
 *   Created:	  2019/5/29 17:04:32
 *   Author:      Skybo
 *	 explanation: 库使用两个输入信号，低电平有效，
 *                采用外部中断触发信号测量转速和转向，需要用两路外部中断
 *				  如果变量要在中断中访问，要使用volatile进行申明
 */

#ifndef _ENCODER_h
#define _ENCODER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class Encoder
{
public:
	/*
	 *触发方式,
	 *LOW 低电平触发,
	 *CHANGE 电平变化，高电平变低电平、低电平变高电平,
	 *RISING 上升沿触发,
	 *FALLING 下降沿触发,
	 *HIGH 高电平触发(该中断模式仅适用于Arduino due)
	 */
	Encoder(uint8_t Vpin, uint8_t Dpin, uint8_t Mode);   //初始化
	void Test();       //执行程序，输出速度和方向
	short Veloctity = 0;        //速度(r/s)
	short Direction = 0;        //方向(1为正，-1为反)

private:
	int cycle = 1000;          //循环周期为1s，单位r/s
	unsigned long time = 0;    //周期记录时间，中断函数中，会失效
	volatile unsigned long timeV = 0;       //速度的单位时间
	volatile unsigned long timeV_old = 0;   //速度的单位上次时间
	volatile unsigned long timeD = 0;	    //方向的单位时间
	volatile unsigned long count = 0;	    //计数值
	int flag = 0;        //1s的时间判断变量
	int point = 0;       //方向判断变量
	uint8_t V_pin;       //速度引脚
	uint8_t D_pin;       //方向引脚
	uint8_t Way;         //触发方式
	void blink0();       //中断函数0，速度
	void blink1();       //中断函数1，方向
	static void ISR0();  //ISR胶水程序
	static void ISR1();
	static Encoder* instance0;
	static Encoder* instance1;
};


#endif

