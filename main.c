#include <stm8s.h>
#include <stm8s_clk.h>
#include <stm8s_gpio.h>
#include <stm8s_tim2.h>
#include <stm8s_adc1.h>
#include <stdint.h>
#include <delay.h>

static void TIM2_Config(void)
{
	TIM2_TimeBaseInit(TIM2_PRESCALER_1, 1024);

	TIM2_OC3Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE, 0, TIM2_OCPOLARITY_HIGH);
	TIM2_Cmd(ENABLE);
}

uint16_t ADC_Read(uint8_t channel)
{
	ADC1_Init(
		ADC1_CONVERSIONMODE_SINGLE,
		channel,
		ADC1_PRESSEL_FCPU_D2,
		ADC1_EXTTRIG_TIM,
		DISABLE,
		ADC1_ALIGN_RIGHT,
		channel,
		DISABLE);
	ADC1_Cmd(ENABLE);

	ADC1_StartConversion();
	
	while (RESET == ADC1_GetFlagStatus(ADC1_FLAG_EOC))
	{
	}
	ADC1_ClearFlag(ADC1_FLAG_EOC);

	uint16_t result = ADC1_GetConversionValue();
	ADC1_DeInit();
	return result;
}

int main()
{
	CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
	CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1);

	TIM2_Config();

	while (1)
	{
		uint16_t valAdc = ADC_Read(ADC1_CHANNEL_3);
		TIM2_SetCompare3(valAdc);
	}
}