#include "stm32f10x.h"                  // Device header

void AD_Init(void){
	//开时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//ADCCLK
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);		//6分频 72mhz/6
	
	//GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;				//ANOLOG ADC ONLY
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 ;		//for x & y
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	
	//adc init
	ADC_InitTypeDef ADC_InitStructure;
	
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;		
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_InitStructure.ADC_ScanConvMode =  DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	
	ADC_Init(ADC1, &ADC_InitStructure);
	
	ADC_Cmd(ADC1, ENABLE);
	
	//校准
	ADC_ResetCalibration(ADC1);								//开始 复位校准
	while(ADC_GetResetCalibrationStatus(ADC1) == SET);		//等待 复位校准 完成
	ADC_StartCalibration(ADC1);								//开始 校准
	while(ADC_GetCalibrationStatus(ADC1) == SET);			//等待 校准 完成
	
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);					//开始 软件转换  	--连续转换
}

uint16_t AD_GetValue(uint8_t Channel){
	
	//规则组菜单列表：序列1，通道ANY，采样时间
	ADC_RegularChannelConfig(ADC1, Channel, 1, ADC_SampleTime_55Cycles5);
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);					//开始 软件转换  	--非连续转换
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);	//等待 转换 完成	--非连续转换
	
	return ADC_GetConversionValue(ADC1);
}
