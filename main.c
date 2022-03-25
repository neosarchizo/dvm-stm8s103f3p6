#include <stm8s.h>
#include <stm8s_clk.h>
#include <stm8s_gpio.h>
#include <stm8s_exti.h>
#include <stdint.h>
#include <delay.h>

#define TEST_LED_PORT GPIOB
#define TEST_LED_PIN GPIO_PIN_5

#define SW_PORT GPIOC
#define SW_PIN GPIO_PIN_3

void PC_IRQHandler(void) __interrupt(5)
{
	uint8_t value = GPIO_ReadInputPin(SW_PORT, SW_PIN);

	if (value)
	{
		// turn off led
		GPIO_WriteHigh(TEST_LED_PORT, TEST_LED_PIN);
	}
	else
	{
		// turn on led
		GPIO_WriteLow(TEST_LED_PORT, TEST_LED_PIN);
	}
}

int main()
{
	CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
	CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1);

	GPIO_Init(TEST_LED_PORT, TEST_LED_PIN, GPIO_MODE_OUT_OD_LOW_SLOW);
	GPIO_WriteHigh(TEST_LED_PORT, TEST_LED_PIN);

	GPIO_Init(SW_PORT, SW_PIN, GPIO_MODE_IN_PU_IT);
	EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOC, EXTI_SENSITIVITY_RISE_FALL);

	enableInterrupts();

	while (1)
	{
	}
}