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
* `<high>/<low>/<period>` - Sets the high/low times and period of the binary sequence
* `<duration>` - Transmission will continue for `<duration>` **seconds**. Set to `0` for a single transmission burst.

