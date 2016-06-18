#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <errno.h>
#include <unistd.h>
#include <wiringPi.h>

#define TRANSMIT_ARGC			5


// Prints help dialogue, call w/ line=0 for all lines
void print_help(int line)
{
	if( line == 1 || !line )
		printf("Usage: TransmitPi -h[elp] | -?\n");
	if( line == 2 || !line )	
		printf("Usage: TransmitPi [-r <repeats>] [-p <pin>] [-sync <high> <low>] transmit <binary> <high> <low> <period> <duration>\n");
}

// More accurate timing of long delays
void custom_delay( int time )
{
	for(int i=0; i<time/100; i++)
		delayMicroseconds(99);
	if(time%100>5)
		delayMicroseconds(time%100);
} 

// Sends sync pulse on given pin using high and low times in microseconds
int sync_pulse(int pin, int high_time, int low_time )
{
	digitalWrite(pin,1); 
	custom_delay(high_time); 
	digitalWrite(pin,0);
	custom_delay(low_time); 
}

int transmit(char* pin_char, int low, int high, int period, char* sequence, int sync_high, int sync_low, int repeat_count, int duration) 
{
	int pin = atoi(pin_char), run_once = 0;
	long time=0;
	long initial_time;
	duration = duration*1000;

	// Set up wiring pi
	if( wiringPiSetupGpio() != 0 )
	{
		printf("Error: Could not execute wiringPiSetupGpio\n");
		return 2; 
	}
	pinMode(pin,OUTPUT);
	
	// This loop runs for the desired duration
	printf("Starting loop\n");
	do
  	{ 
		// This loop repeats the transmission as specified by repeat_count
		for(int i=0;i<repeat_count;i++)
		{ 
			// Send a sync pulse if needed
			if( sync_high ) 
				sync_pulse(pin, sync_high, sync_low);
 
			// This loop reads the data sequence and writes to GPIO
			for(int count=0; count<strlen(sequence); count++)
			{
				initial_time = micros();
				digitalWrite(pin,1);
				
				
				if( sequence[count] == '0' )
					custom_delay(low-(micros()-initial_time));  
				else
					custom_delay(high-(micros()-initial_time));
				digitalWrite(pin,0);
				 
				// Measure how much time has elapsed from start of period, sleep for remaining time
				// This prevents mistimed bits from affecting the next bit
				time = micros()-initial_time;
				if(period-time > 0)
					custom_delay(period-time);
			 }
			 
			 // Reset counters for data sequence, sleep some time before sending the next repeat
			 delay(10);
		}
		// Delay some time before sending another burst of repeats
		delay(150);
	}while(millis() <= duration);
	return 0;
}

					