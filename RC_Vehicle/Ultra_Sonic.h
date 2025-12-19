/**
 * @file PWM2_2.c
 *
 * @brief Source file for the Ultra Soncic Sensor driver.
 *
 * @note This driver assumes that the system clock's frequency is 50 MHz.
 *
 * @note 
 *
 * @author Jonathan Penaloza, Ricardo ZaragozaS
 */
#ifndef ULTRASONIC_H
#define ULTRASONIC_H
#include "Ultra_Sonic.h"

#include <stdint.h>

void Ultrasonic_Init(void);
uint32_t Ultrasonic_ReadPulse(void);
uint32_t Ultrasonic_ReadDistanceCM(void);
#endif