#include "stm32f10x.h"                  // Device header
#include "AD.h"

void Rocker_Init(void){
	AD_Init();
	
	//GPIOA PA2 for SW
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;				
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 ;		//for SW
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	
}

uint8_t Rocker_Get_SW(void){
	uint8_t DataSW = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2);
	return DataSW;
}

uint16_t Rocker_Get_X(void){
	uint16_t DataX = AD_GetValue(ADC_Channel_0);
	return DataX;
}

uint16_t Rocker_Get_Y(void){
	uint16_t DataY = AD_GetValue(ADC_Channel_1);
	return DataY;
}
