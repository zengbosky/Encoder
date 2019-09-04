// main
/*
 *  Name:       Encoder.ino
 *  Created:	2019/5/29 17:04:32
 *  Author:     Skybo
 *  explanation:
 */

#include "Encoder.h"

Encoder Hall(2, 3, FALLING);
int num = 0;

void setup()
{
    Serial.begin(9600);
}


void loop()
{
	Hall.Test();
	while (num != Hall.Veloctity)
	{
		num = Hall.Veloctity;
		Serial.print(Hall.Veloctity);
		Serial.println("r/s");
		Serial.println(Hall.Direction);
		if (Hall.Direction == 1)
		{
			Serial.println("Forward");
		}
		else if (Hall.Direction == -1)
		{
			Serial.println("Reverse");
		}
	}	
}
