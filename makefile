TransmitPi: TransmitPi.c TransmitPi.h
	gcc -std=c99 -g -o TransmitPi TransmitPi.c TransmitPi.h -lwiringPi -Wimplicit-function-declaration