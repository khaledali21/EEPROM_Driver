/*
 * EEPROM.h
 *
 * Created: 2/3/2022 2:58:06 PM
 *  Author: Khaled Ali
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include "../../MCAL/I2C/I2C.h"



#define EEPROM_ADDRESS_MASK 0x50


void EEPROM_u8Init();

uint8_t EEPROM_u8WriteByte(uint8_t chip_select, uint16_t ByteAddress, uint8_t data);

uint8_t EEPROM_u8ReadByte(uint8_t chip_select, uint16_t ByteAddress, uint8_t* data);

uint8_t EEPROM_u8WriteString(uint8_t chip_select, uint16_t stringAddress, uint8_t* str);

uint8_t EEPROM_u8ReadString(uint8_t chip_select, uint16_t stringAddress, uint8_t* str, uint8_t str_size);



#endif /* EEPROM_H_ */