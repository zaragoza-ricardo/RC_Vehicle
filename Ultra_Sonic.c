/**
 * @file Ultra_Sonic.c
 *
 * @brief Source file for the Ultra_Sonic.
 *
 
 * @author Jonathan Penaloza, Ricardo Zaragoza
 */




#include "TM4C123GH6PM.h"   // TM4C123 register definitions
#include "SysTick_Delay.h"   // SysTick delay functions

// Initialize PC4 (Trigger) and PC5 (Echo)
void Ultrasonic_Init(void) {
    SYSCTL->RCGCGPIO |= 0x04;            // Enable clock to Port C using GPIO
    while(!(SYSCTL->PRGPIO & 0x04));     // Wait until ready

    GPIOC->DIR |= 0x10;      // PC4 output
    GPIOC->DIR &= ~0x20;     // PC5 input  

    GPIOC->DEN |= 0x30;      // digital enable PC4 + PC5
    GPIOC->PDR |= 0x20;      // weak pull-down on PC5 (Echo)
    GPIOC->AFSEL &= ~0x30;   // GPIO function for PC4 & PC5
}

// Send trigger and read pulse width in microseconds
uint32_t Ultrasonic_ReadPulse(void) {
    uint32_t count = 0;
    uint32_t timeout = 30000;   // ~30ms max wait

    GPIOC->DATA |= 0x10;        // Trigger HIGH
    SysTick_Delay1us(10);
    GPIOC->DATA &= ~0x10;       // Trigger LOW

    // Wait for Echo HIGH with timeout
    while(!(GPIOC->DATA & 0x20)) 
    {
        if(timeout == 0) return 0;  // No echo
        timeout--;
    }

    // Measure pulse width
    count = 0;
    while(GPIOC->DATA & 0x20) 
    {
        count++;
        SysTick_Delay1us(1);
    }

    return count;
}

    
// Convert pulse width to distance in cm
uint32_t Ultrasonic_ReadDistanceCM(void) 
	{
    uint32_t pulse = Ultrasonic_ReadPulse();
    return pulse / 58;  // approximate distance in cm
		
		
}
	
	
