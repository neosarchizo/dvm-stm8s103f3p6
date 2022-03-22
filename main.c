#include <stm8s.h>
#include <stm8s_clk.h>
#include <stm8s_gpio.h>
#include <stdint.h>
#include <delay.h>

#define TEST_LED_PORT GPIOB
#define TEST_LED_PIN GPIO_PIN_5

void toggleByWrite(void)
{
	GPIO_Write(TEST_LED_PORT, 1 << 5);
	delay_ms(1000);
	GPIO_Write(TEST_LED_PORT, 0);
	delay_ms(1000);
}

void toggleByHighLow(void)
{
	GPIO_WriteHigh(TEST_LED_PORT, TEST_LED_PIN);
	delay_ms(1000);
	GPIO_WriteLow(TEST_LED_PORT, TEST_LED_PIN);
	delay_ms(1000);
}

void toggleByReverse(void)
{
	GPIO_WriteReverse(TEST_LED_PORT, TEST_LED_PIN);
	delay_ms(1000);
}

int main()
{
	CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
	CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1);

	GPIO_Init(TEST_LED_PORT, TEST_LED_PIN, GPIO_MODE_OUT_OD_LOW_SLOW);

	while (1)
	{
		toggleByReverse();
	}
}