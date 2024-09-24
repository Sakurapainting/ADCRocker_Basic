#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Rocker.h"
#include "Serial.h"

uint16_t X, Y;
uint8_t SW;

int main(){
	OLED_Init();
	Rocker_Init();
	Serial_Init();
	

	
	OLED_ShowString(1, 1, "X:");
	OLED_ShowString(2, 1, "Y:");
	OLED_ShowString(3, 1, "SW:");

	while(1){
		X = Rocker_Get_X();
		Y = Rocker_Get_Y();
		SW = Rocker_Get_SW();
		
		OLED_ShowNum(1,3, X, 4);
		OLED_ShowNum(2,3, Y, 4);
		OLED_ShowNum(3,5, SW, 1);
		
		Serial_Printf("X=%d\r\n", X);
		Serial_Printf("Y=%d\r\n", Y);
		Serial_Printf("SW=%d\r\n", SW);
		
		Delay_ms(100);
	}
}
