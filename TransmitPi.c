
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <errno.h>
#include <unistd.h>
#include <wiringPi.h>
#include "TransmitPi.h"
 
int verbose = 0;

int main(int argc, char *argv[]) 
{ 
  int WIRINGPI_CODES=1;	// Allows for return code checking of wiringPiSetupSys()
  
  // Set default values for optional vars, may be updated in switch
  int repeat_count = 1;
  int singlet = 0;
  int pin = 17; char *char_pin = "17";
  int sync_high = 0, sync_low = 0;

   
  // Process args
  for(int i=1; i<argc; i++)
	{
		if( !strcmp(argv[i],"-?") || !strcmp(argv[i],"-h") || !strcmp(argv[i],"-help") )
		{				
			print_help(0);
			return 0;
		}
		else if( !strcmp(argv[i],"transmit") )
		{
			if(verbose)
				printf("Starting in transmit mode");

			if( argc-i-1 != 5 )
			{
				fprintf(stdout,"Must have 5 required options, found %i\n",argc-i-1);
				print_help(2);
				return 1;
			}
			else
			{
				char* sequence = argv[i+1];
				int high = atoi(argv[i+2]);
				int low = atoi(argv[i+3]);
				int period = atoi(argv[i+4]);
				int duration = atoi(argv[argc-1]);
				if(verbose)
				{
					fprintf(stdout,"Transmit length - %i bits\n",strlen(sequence) );
					// Read out binary array
					printf("Logic sequence - ");
					printf(sequence);
					printf("\n");
					fprintf(stdout,"Duration - %is\n",duration);
				}
				transmit(char_pin, low, high, period, sequence, sync_high, sync_low, repeat_count, duration);
			}
			i = argc;


		}
		else if( !strcmp(argv[i],"-v") )
		{ 
			verbose = 1;
			printf("Starting in verbose mode...\n");
		}
		else if( !strcmp(argv[i],"-r") )
		{
			if( !atoi(argv[i+1]) )
			{
				printf("Error: Invalid repeat count, did you use an integer >=1 ?\n");
				return 1;
			}
			else
			{
				repeat_count = atoi(argv[i+1]);
				fprintf(stdout,"Repeat count - %i\n",repeat_count);
				i++;
			}
		}
		else if( !strcmp(argv[i],"-p") )
		{
			if( !atoi(argv[i+1]) )
			{
				printf("Error: Invalid BCM pin selection\n");
				return 1;
			}
			else
			{
				pin = atoi(argv[i+1]);
				char_pin = argv[i+1];
				fprintf(stdout,"Pin - %i\n",pin);
				i++;
			}
		}
		else if( !strcmp(argv[i],"-sync") )
		{ 
			
			sync_high = atoi(argv[i+1]);
			sync_low = atoi(argv[i+2]);
			if( !sync_high || !sync_low )
			{ 
				printf("Error: Invalid sync times\n");
				print_help(4);
				return 1;
			}
			i=i+2;
		}
		else
		{
			printf("Unrecognized option ");
			printf(argv[i]);
			printf("\n");
			return 1;
		}
	}

	return 0;
}
