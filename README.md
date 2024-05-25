# Arduino-Soil-Sensor
https://www.faranux.com/product/the-5-in-1-soil-sensor-npkphconductivitytemperature-and-humidity/


## SD Card
Arduino --> Master
SD Card Module ---> Slave

SCK - Serial Clock
MISO - Master In Slave Out (Card will send data to Arduino)
MOSI - Master Out Slave In (Arduino Will Send Data to Card)
SS - Slave Select (if high communication off | if low communication on)


## For Arduino Mega
cs-53
MOSI-51
SCK-52
MISO-50

## LCD Display
Past LCD libery on this path
c:\Users\shant\Documents\Arduino
ic model :- LCDWIKI_KBV mylcd(ILI9486,40,38,39,44,41); //model,cs,cd,wr,rd,reset



