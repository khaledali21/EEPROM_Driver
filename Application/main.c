/*
 * EEPORM_Driver.c
 *
 * Created: 2/3/2022 2:44:02 PM
 * Author : Khaled Ali
 */ 
#include "../ECUAL/EEPROM/EEPROM.h"
#include "../MCAL/UART/UART.h"
#include "../ECUAL/LED/LED.h"
#include "../MCAL/TIMER/TIMER0.h"
LED_t led = {PORTB, PIN4};
uint8_t str1[20] = "Hello";
uint8_t str2[20];
int main(void)
{
	LED_u8Init(&led);
	uint8_t u8Status = 1;
	EEPROM_u8Init();
	UART_u8Init(9600);
	UART_u8SendString((uint8_t*) "Data before typing: ");
	u8Status = EEPROM_u8ReadString(0, 10, str2, 5);
	if(u8Status != 1){
		LED_u8ON(&led);
		UART_u8SendData(u8Status);
	}
	else{
		UART_u8SendString(str2);
		u8Status = EEPROM_u8WriteString(0, 10, str1);
		if(u8Status == 1){
			UART_u8SendString((uint8_t*) "\n\rData after typing: ");
			u8Status = EEPROM_u8ReadString(0, 10, str2, 5);
			if(u8Status == 1){
				UART_u8SendString(str2);
			}
			else{
				LED_u8ON(&led);
				UART_u8SendData(u8Status);
			}
		}
		else{
			LED_u8ON(&led);
			UART_u8SendData(u8Status);
		}
	}
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

