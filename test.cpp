//--------------------------------------
/*
#include <istream>
#undef __ARM_FP
#include "mbed.h"

#define WAIT_TIME_MS_0 500
#define WAIT_TIME_MS_1 250

//input of IR sensor data
DigitalIn LDRSensor_DO(PB_0);
AnalogIn LDRSensor_AO(PA_0);

//turn on/off the on-board LED: PB14 to indicate LDR Sensor DO
DigitalOut LED_PB14(PB_14);

float LDR_AO_voltage = 0.0;
double Voltage = 0.0;

int main()
{
    printf("LDR output value: %.3f V\n", LDR_AO_voltage);
    LED_PB14 = 0;
    LDRSensor_AO.set_reference_voltage(3.3f);

    while (true)
    {
        if (LDRSensor_DO.read() == 1)
        {
            // in Dark environment
            printf("In Dark!\n");
            LED_PB14 = 1;
            thread_sleep_for(WAIT_TIME_MS_0);
        }
        else
        {
            printf("In Light!\n");
            LED_PB14 = 0;
            thread_sleep_for(WAIT_TIME_MS_1);
        }

    
    LDR_AO_voltage = LDRSensor_AO.read();

    if (LDR_AO_voltage != 0)
    {
        printf("yay :)");
    }
    printf("LDR output value: %.3f V\n", LDR_AO_voltage);
    LDR_AO_voltage = LDR_AO_voltage * 3.3f;
    printf("LDR output value: %.3f V\n", LDR_AO_voltage);
    //printf(LDR_AO_voltage);
    thread_sleep_for(WAIT_TIME_MS_0);
    }
}
//---------------------------
*/

/*

#undef __ARM_FP

#include "mbed.h"
#include "lcd.h"	
#include "keypad.h"	

unsigned char key, outChar;
char Message1 [ ] = "Enter PIN number :  ";	  // Defining a 20 char string
unsigned char password[] = {'0','0','0','0'};

// ---- Main Program ---------------------------------------------------------------
int main( )
{
	printf("This is MAPP LCDKeypad running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);

	int i;
	lcd_init();						// Initialise LCD module

	while(1)
	{
		lcd_write_cmd(0x80);			// Move cursor to line 1 position 1
		for (i = 0; i < 20; i++)		//for 20 char LCD module
		{
			outChar = Message1[i];
			lcd_write_data(outChar); 	// write character data to LCD
		}
		

		lcd_write_cmd(0xC0);			// Move cursor to line 2 position 1
		for (i = 0; i < 4; i++)		//for 20 number
		{ 
			password[i] = getkey(); 				// waits and get an ascii key number when pressed
			lcd_write_data(password[i]);		//display on LCD
			
		}
		
		thread_sleep_for(1000);                 // wait 1 second
		lcd_write_cmd(0x01);			// 00000001 Clear Display instruction
	}
}
*/



#undef __ARM_FP
#include "mbed.h"
#define WAIT_TIME_MS_0 2000 //sleep enough time to allow motor turns to the preferred position
#define PERIOD_WIDTH 20 //period in ms according to the servo motor datasheet
#define PULSE_WIDTH_90_DEGREE 2400 //pulse width in us to move to 90 degree position
#define PULSE_WIDTH_0_DEGREE 1500 //pulse width in us to move to 0 position
#define PULSE_WIDTH_N_90_DEGREE 600 //pulse width in us to move to -90 degree position
PwmOut motor(PB_3);
DigitalIn button_PC12 (PC_12);
DigitalIn button_PA15 (PA_15);
int main()
{
//specify period first
motor.period_ms(PERIOD_WIDTH); //period according to the specification, e.g., 20ms
motor.pulsewidth_us(PULSE_WIDTH_0_DEGREE); //to 0 position, at the middle
printf("Move to 0 position: Middle\n");
thread_sleep_for(WAIT_TIME_MS_0); //wait for the motor moving to the position
while (button_PC12 == 1); //wait for pressing button
while (button_PC12 == 0); //wait for releasing button
motor.pulsewidth_us(PULSE_WIDTH_90_DEGREE); //to 90 degree to the right
printf("Move to 90 degree position: Right\n");
thread_sleep_for(WAIT_TIME_MS_0); //wait for the motor moving to the position
while (button_PA15 == 1); //wait for pressing button
while (button_PA15 == 0); //wait for releasing button
motor.pulsewidth_us(PULSE_WIDTH_N_90_DEGREE); //to -90 degree to the left
printf("Move to -90 degree position: Left\n");
thread_sleep_for(WAIT_TIME_MS_0); //wait for the motor moving to the position
while (button_PC12 == 1); //wait for pressing button
while (button_PC12 == 0); //wait for releasing button
motor.pulsewidth_us(PULSE_WIDTH_90_DEGREE); //to 90 degree to the right
printf("Move to 90 degree position: Right\n");
thread_sleep_for(WAIT_TIME_MS_0); //wait for the motor moving to the position

while (button_PA15 == 1); //wait for pressing button
while (button_PA15 == 0); //wait for releasing button
motor.pulsewidth_us(PULSE_WIDTH_N_90_DEGREE); //to -90 degree to the left
printf("Move to -90 degree position: Left\n");
thread_sleep_for(WAIT_TIME_MS_0); //wait for the motor moving to the position
motor.suspend();
while (true);
}//main
//-------------------------------------



/*

//DHT11_samplecode.cpp
#undef __ARM_FP
#include "mbed.h"
#include "DHT11.h"
#define WAIT_TIME_MS_0 500
#define WAIT_TIME_MS_1 1500
DigitalOut led1(LED1);
DigitalIn button(PC_13);
#define DHT11_PIN PD_2
DHT11 dht11(DHT11_PIN);
int main()
{
int temperature = 0, humidity = 0;
while (1)
{
//get temperature
temperature = dht11.readTemperature();
if (temperature != DHT11::ERROR_CHECKSUM && temperature != DHT11::ERROR_TIMEOUT)
{
printf("Temperature: %d °C\n", temperature);
}
else
{
printf("%s\n", dht11.getErrorString(temperature));
}
thread_sleep_for(1000);
//get humidity
humidity = dht11.readHumidity();
if (humidity != DHT11::ERROR_CHECKSUM && temperature != DHT11::ERROR_TIMEOUT)
{
printf("humidity: %d %%\n", humidity);
}
else
{
printf("%s\n", dht11.getErrorString(humidity));
}
thread_sleep_for(1000);
//get temperature and humidity
int result = dht11.readTemperatureHumidity(temperature, humidity);
if (result != DHT11::ERROR_CHECKSUM && temperature != DHT11::ERROR_TIMEOUT)
{
printf("Temperature: %d °C and humidity: %d %%\n", temperature, humidity);
}
else
{
printf("%s\n", dht11.getErrorString(result));
}
thread_sleep_for(1000);
}
}
//-------------------------------------
*/

/*
#undef __ARM_FP

#include "mbed.h"
#define WAIT_TIME_MS 1000
#define WAIT_TIME_US 3000

#define DISPLAY_BAR_MASK 0x000000FF //PORT C0: PC_7 - PC_0
#define DISPLAY_BAR_RESET 0x00000000 

//set Port C0 as output
PortOut displayBarPort(PortC, DISPLAY_BAR_MASK);

//Set Port A, GPIO Pin 1 (PA_1) as digitial out put pin
//declare a buzzer as a DigitalOut object by passing PA_1 as the initialition parameter 
DigitalOut buzzer(PA_1); 

//Function to generate one tone
void onetone(void) 
{
    unsigned int k;
    
    //Determines duration of tone
    for (k = 0; k < 100; k++) 
    {
        wait_us(3000);  
        buzzer = !buzzer; //Invert logic level at PA_1       
    }
}

int main()
{
    printf("This is MAPP BuzzOne running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    
    displayBarPort = DISPLAY_BAR_RESET;

    buzzer = 0;

    //sound ON then OFF
    onetone( ); 
    
    //pattern on LED display bar: ob10101010
    displayBarPort = 0xAA;
    thread_sleep_for(WAIT_TIME_MS);

     //sound ON then OFF
    onetone( ); 
    
    //pattern on LED display bar: 0b01010101
    displayBarPort = 0x55;
    thread_sleep_for(WAIT_TIME_MS);

    while (true);    //loop forever to stop music!

}
    */