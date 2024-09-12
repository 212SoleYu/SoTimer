/*
 * File name: aes.h
 * Description: to init the AES module
 */
#ifndef _AES_H
#define _AES_H

#include<Modules/driver_include.h>

#define AES_BASE        0x09C0

#define AES_LENGTH      (512)              // bytes
extern const  uint8_t plaintext[AES_LENGTH];
extern const  uint8_t ciphertext[AES_LENGTH];
extern  uint8_t dataBuffer[AES_LENGTH];

extern const  uint8_t aes_key[16];



void aes_init();


#endif
