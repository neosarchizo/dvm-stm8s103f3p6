#include <stm8s.h>
#include <stm8s_clk.h>
#include <stm8s_gpio.h>
#include <stm8s_uart1.h>
#include <stdint.h>
#include <stdio.h>
#include <delay.h>

static void UART1_Config(void)
{
	UART1_Init(
		115200,
		UART1_WORDLENGTH_8D,
		UART1_STOPBITS_1,
		UART1_PARITY_NO,
		UART1_SYNCMODE_CLOCK_DISABLE,
		UART1_MODE_TXRX_ENABLE
	);
	UART1_Cmd(ENABLE);
}

int putchar(int c)
{
	UART1_SendData8(c);
	while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET)
	{
	}
	return c;
}

int main()
{
	CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
	CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1);

	UART1_Config();

	printf("Hello world!\n");

	while (1)
	{
		if (UART1_GetFlagStatus(UART1_FLAG_RXNE) == SET)
		{
			int c = UART1_ReceiveData8();
			putchar(c);
		}
	}
}