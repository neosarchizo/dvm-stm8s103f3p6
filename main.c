#include <stm8s.h>
#include <stm8s_clk.h>
#include <stm8s_gpio.h>
#include <stm8s_uart1.h>
#include <stm8s_flash.h>
#include <stdint.h>
#include <stdio.h>
#include <delay.h>

#define EEPROM_BASE_ADDR 0x4000
#define EEPROM_SIZE 640

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

static void FLASH_Config(void)
{
	FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD);
	FLASH_Unlock(FLASH_MEMTYPE_DATA);
}

void clear(void)
{
	printf("Reset EEPROM ... ");

	for (uint16_t i = 0; i < EEPROM_SIZE; i++)
	{
		FLASH_EraseByte(EEPROM_BASE_ADDR +i);
		FLASH_WaitForLastOperation(FLASH_MEMTYPE_DATA);
	}

	printf("Done\n");
}

int main()
{
	CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
	CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1);

	UART1_Config();

	FLASH_Config();
	// clear();

	// uint8_t a = 3;
	uint8_t b = 0;

	// FLASH_ProgramByte(EEPROM_BASE_ADDR, a);
	// FLASH_WaitForLastOperation(FLASH_MEMTYPE_DATA);
	b = FLASH_ReadByte(EEPROM_BASE_ADDR);

	printf("b : %d\n", b);

	while (1)
	{
	}
}