# TransmitPi

TransmitPi can be used to control RF transmitters from a Raspberry Pi. 

  
## Installation
After cloning the package execute `make` to compile the code

## Usage
TransmitPi must be run as sudo. Usage is as follows
```
sudo ./TransmitPi [-r <number of repeats>] [-p <pin>] [-sync <high> <low>] transmit <binary sequence> <high> <low> <period> <duration>
```
The options are as follows - **All times are in microseconds unless otherwise specified**

* s`[-r <number of repeats>]` - Sets a transmission to include `<number of repeats>`, increasing this may help your device respond
* `[-p <pin>]` - Sets the pin to be used
* `[-sync <high> <low>]` - Transmit a sync pulse of given high/low time before the binary data sequence
* `<binary sequence>` - The binary sequence to be transmitted. Given as a string ("101010")
* `<high>/<low>/<period>` - Sets the time a pin will be set high/low for logic 1/0 respectively, along with the period of each bit.
* `<duration>` - Transmission will continue for `<duration>` **seconds**. Set to `0` for a single transmission burst.

Reliable reproduction of waveforms declines rapidly for logic times less than 10us

##Examples

To transmit the binary sequence `1100101` with a period of 200us, logic high of 100us, and logic low of 50us with 10 repeats in a burst for 2 seconds
```
sudo ./TransmitPi -r 10 transmit 10101010 100 50 200 2
```
The resultant waveform will be

![Alt text](/../screenshots/screenshots/DS1Z_QuickPrint2.png?raw=true "Total waveform")

The top waveform shows the transmit signal over 2 seconds. The bottom waveform is zoomed on a single transmit burst, where 10 repeats are visible. Zooming in gives

![Alt text](/../screenshots/screenshots/DS1Z_QuickPrint3.png?raw=true "Total waveform")

Now the top waveform shows a series of repeats, while the bottom waveform shows the binary data. Finally, zooming in to take measurements gives

![Alt text](/../screenshots/screenshots/DS1Z_QuickPrint5.png?raw=true "Total waveform")

The period is measured to be 200us, the logic 1 pulse is 99us, and the logic 0 pulse is 49us.

Below is a demonstration of a sync pulse. The waveform is of the same 100us high, 50us low, 200us period as before. The sync pulse is of 300us high, 100us low.

![Alt text](/../screenshots/screenshots/DS1Z_QuickPrint6.png?raw=true "Total waveform")



