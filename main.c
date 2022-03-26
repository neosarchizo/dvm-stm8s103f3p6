#include <stm8s.h>
#include <stm8s_clk.h>
#include <stm8s_gpio.h>
#include <stm8s_tim2.h>
#include <stdint.h>
#include <delay.h>

static void TIM2_Config(void)
{
	TIM2_TimeBaseInit(TIM2_PRESCALER_1, 256);

	TIM2_OC3Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE, 0, TIM2_OCPOLARITY_HIGH);
	TIM2_Cmd(ENABLE);
}

int main()
{
	CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
	CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1);

	TIM2_Config();

	uint8_t i = 0;

	while (1)
	{
		TIM2_SetCompare3(i++);
		delay_ms(20);
	}
}