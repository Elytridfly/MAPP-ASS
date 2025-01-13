/*
Pin Assignment Table
Device	        Pin Assignment	Port/Pin
DHT11	        Data	        PD2
Servo Motor 1	PWM Signal	    PA6
Servo Motor 2	PWM Signal	    PA7
Wi-Fi Module	USART Tx	    PA2
USART           Rx	            PA3
Alternate USART Tx	            PB6
Alternate USART Rx	            PB7
Additional Lines	            PC10, PC11
Green LED	    Digital Output	PB15
Red LED	        Digital Output	PB14
Buzzer	        Digital Output	PB0
LDR1	        Analog Input	PA0
LDR2	        Analog Input	PA1
*/

#undef __ARM_FP

#include "mbed.h"

#include "mbed.h"
#include "lcd.h"	
#include "keypad.h"	

#define WAIT_TIME_MS_0 500
#define WAIT_TIME_MS_1 250

#define PULSE_WIDTH_90_DEGREE 2400 //pulse width in us to move to 90 degree position
#define PULSE_WIDTH_0_DEGREE 1500 //pulse width in us to move to 0 position
#define PULSE_WIDTH_N_90_DEGREE 600 //pulse width in us to move to -90 degree position

unsigned char key, outChar;
char Message1 [ ] = "Enter PIN number :  ";	  // Defining a 20 char string
unsigned char password[] = {'0','0','0','0'};

PwmOut motor(PB_3);
DigitalIn button_PC12 (PC_12);
DigitalIn button_PA15 (PA_15);

//input of IR sensor data
DigitalIn LDRSensor_DO(PB_0);
AnalogIn LDRSensor_AO(PA_0);

//turn on/off the on-board LED: PB14 to indicate LDR Sensor DO
DigitalOut LED_PB14(PB_14);

float LDR_AO_voltage = 0.0;
double Voltage = 0.0;

int main()
{
    while (1)
    {

    }
}