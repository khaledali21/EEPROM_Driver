/*
 * EEPROM.c
 *
 * Created: 2/3/2022 2:58:16 PM
 *  Author: Khaled Ali
 */ 



#include "EEPROM.h"




void EEPROM_u8Init(){
	I2C_Init();
}

uint8_t EEPROM_u8WriteByte(uint8_t chip_select, uint16_t ByteAddress, uint8_t data){
	uint8_t u8Status = I2C_OK;
	uint8_t device_Address = EEPROM_ADDRESS_MASK | (chip_select);
	uint8_t address_high_byte = (uint8_t)(ByteAddress >> 8);
	uint8_t address_low_byte = (uint8_t) ByteAddress;
	u8Status = I2C_u8Start(device_Address, WRITE);
	if(u8Status == I2C_OK){
		u8Status = I2C_u8MasterSendData(address_high_byte);
	}
	if(u8Status == I2C_OK){
		u8Status = I2C_u8MasterSendData(address_low_byte);
	}
	if(u8Status == I2C_OK){
		u8Status = I2C_u8MasterSendData(data);
	}
	I2C_Stop();
	return u8Status;
}

uint8_t EEPROM_u8ReadByte(uint8_t chip_select, uint16_t ByteAddress, uint8_t* data){
	uint8_t u8Status = I2C_OK;
	uint8_t device_Address = EEPROM_ADDRESS_MASK | (chip_select);
	uint8_t address_high_byte = (uint8_t)(ByteAddress >> 8);
	uint8_t address_low_byte = (uint8_t) ByteAddress;
	u8Status = I2C_u8Start(device_Address, WRITE);
	if(u8Status == I2C_OK){
		u8Status = I2C_u8MasterSendData(address_high_byte);
	}
	if(u8Status == I2C_OK){
		u8Status = I2C_u8MasterSendData(address_low_byte);
	}
	if(u8Status == I2C_OK){
		u8Status = I2C_u8Start(device_Address, READ);
	}
	if(u8Status == I2C_OK){
		u8Status = I2C_u8MasterGetData(data, NACK);
	}
	I2C_Stop();
	return u8Status;
}

uint8_t EEPROM_u8WriteString(uint8_t chip_select, uint16_t stringAddress, uint8_t* str){
	uint8_t u8Status = I2C_OK;
	uint8_t device_Address = EEPROM_ADDRESS_MASK | (chip_select);
	uint8_t address_high_byte = (uint8_t)(stringAddress >> 8);
	uint8_t address_low_byte = (uint8_t) stringAddress;
	uint8_t itr = 0;
	u8Status = I2C_u8Start(device_Address, WRITE);
	if(u8Status == I2C_OK){
		u8Status = I2C_u8MasterSendData(address_high_byte);
	}
	if(u8Status == I2C_OK){
		u8Status = I2C_u8MasterSendData(address_low_byte);
	}
	while(str[itr] != '\0' && u8Status == I2C_OK){
		u8Status = I2C_u8MasterSendData(str[itr]);
		itr++;
	}
	I2C_Stop();
	return u8Status;
}

uint8_t EEPROM_u8ReadString(uint8_t chip_select, uint16_t stringAddress, uint8_t* str, uint8_t str_size){
	uint8_t u8Status = I2C_OK;
	uint8_t device_Address = EEPROM_ADDRESS_MASK | (chip_select);
	uint8_t address_high_byte = (uint8_t)(stringAddress >> 8);
	uint8_t address_low_byte = (uint8_t) stringAddress;
	uint8_t itr = 0;
	u8Status = I2C_u8Start(device_Address, WRITE);
	if(u8Status == I2C_OK){
		u8Status = I2C_u8MasterSendData(address_high_byte);
	}
	if(u8Status == I2C_OK){
		u8Status = I2C_u8MasterSendData(address_low_byte);
	}
	if(u8Status == I2C_OK){
		u8Status = I2C_u8Start(device_Address, READ);
	}
	for(itr = 0; itr < str_size - 1 && u8Status == I2C_OK; itr++){
		u8Status = I2C_u8MasterGetData(&str[itr], ACK);
	}
	if(u8Status == I2C_OK){
		u8Status = I2C_u8MasterGetData(&str[itr], NACK);
	}
	I2C_Stop();
	return u8Status;
}