#include "light_sensor.h"


void Light_Sensor_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStruct;
	ADC_CommonInitTypeDef 	ADC_CommonInitStruct;
	ADC_InitTypeDef 		ADC_InitStruct;
	
	//打开GPIO F组时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	//打开ADC3时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);  
	
	GPIO_InitStruct.GPIO_Pin	= GPIO_Pin_7;  		//引脚7
	GPIO_InitStruct.GPIO_Mode	= GPIO_Mode_AN;			//输出
	GPIO_InitStruct.GPIO_PuPd	= GPIO_PuPd_NOPULL;		//浮空	 
	GPIO_Init(GPIOF, &GPIO_InitStruct);
	
	ADC_CommonInitStruct.ADC_Mode				= ADC_Mode_Independent; 		//独立模式
	ADC_CommonInitStruct.ADC_Prescaler			= ADC_Prescaler_Div4; 			// 84/4 = 21MHZ  频率不能大于 36MHZ
	ADC_CommonInitStruct.ADC_DMAAccessMode		= ADC_DMAAccessMode_Disabled; 	//不用DMA
	ADC_CommonInitStruct.ADC_TwoSamplingDelay	= ADC_TwoSamplingDelay_5Cycles;	//两个采样阶段之间的延迟5个时钟

	//2、初始化ADC_CCR寄存器。
     ADC_CommonInit(&ADC_CommonInitStruct);
	 
	 //3、初始化ADC1参数，设置ADC1的工作模式以及规则序列的相关信息。
	ADC_InitStruct.ADC_Resolution 			= ADC_Resolution_12b;//12位模式 精度 4095
	ADC_InitStruct.ADC_ScanConvMode 		= DISABLE;//非扫描模式	
	ADC_InitStruct.ADC_ContinuousConvMode 	= DISABLE;//关闭连续转换
	ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//禁止触发检测，使用软件触发
	ADC_InitStruct.ADC_DataAlign 			= ADC_DataAlign_Right;//右对齐	
	ADC_InitStruct.ADC_NbrOfConversion 		= 1;//1个转换在规则序列中 
	ADC_Init(ADC3, &ADC_InitStruct);		//ADC初始化
	
	//4、使能ADC。
    ADC_Cmd(ADC3, ENABLE);
	//5、配置规则通道参数：
     ADC_RegularChannelConfig(ADC3,ADC_Channel_5,1,ADC_SampleTime_15Cycles);	
	
}

u16 Get_Light_Sensor_Value(void)
{
	u16 value;
	
	//启动软件转换
	ADC_SoftwareStartConv(ADC3);

	//7、等待转换完成，读取ADC值。
	while(ADC_GetFlagStatus(ADC3, ADC_FLAG_EOC) == RESET );
	
	//获取ADC的值 
	value = ADC_GetConversionValue(ADC3);
	
	return value;

}
