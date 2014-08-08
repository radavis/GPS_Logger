/**********************************************
  "GPS_Logger" - ITEAD GPS Shield Demo

  Modified example from:
  http://imall.iteadstudio.com/im120417017.html

  This sample code _should_ read GPS data
  from the module and write it to a FAT16
  formatted SD card. Format the card, then
  Create a file on the SD card named
  "datalog.txt". It has been modified to work
  with the Arduino Leonardo.

 **********************************************

  I'm assuming that the following connections
  on the GPS shield are made, since the serial
  port connections are not changed from the
  default.

    * Rx-D1
    * Tx-D0

 **********************************************

  **Separation of USB and serial communication.**

  On the Leonardo and Micro, the main Serial
  class refers to the virtual serial driver
  on the board for connection to your computer
  over USB. It's not connected to the physical
  pins 0 and 1 as it is on the Uno and earlier
  boards. To use the hardware serial port (pins
  0 and 1, RX and TX), use Serial1. (See the
  Serial reference pages for more information.)

  from: http://arduino.cc/en/Guide/ArduinoLeonardo
  Micro?from=Guide.ArduinoLeonardo

 **********************************************

  **Serial**

  The Arduino Leonardo board uses Serial1 to
  communicate via TTL (5V) serial on pins 0 (RX)
  and 1 (TX). Serial is reserved for USB CDC
  communication. For more information, refer to
  the Leonardo getting started page and hardware
  page.

  from: http://arduino.cc/en/Reference/Serial

 **********************************************

  ** Testing procedure **

  1) Load this sketch onto the Arduino without
  the GPS shield attached.

  2) Unplug the Arduino from Power/USB.

  3) Attach the GPS shield with FAT16 formatted
  SD card installed.

  4) Connect Rx to D1 on the GPS shield.

  5) Connect Tx to D0 on the GPS shield.

  6) Connect Arduino + GPS shield to your PC

  7) Open up the Serial Monitor

  8) Debugging output should indicate if and
  when this sketch is having issues.

 **********************************************/

#include <SD.h>
#include <SPI.h>

const int chipSelect = 10;  // for SD enable
const int lineLength = 200;

void setup() {
  Serial.begin(9600);  // USB Serial on Leonardo
  while(!Serial) ; // wait for USB Serial connection
  Serial.println("GPS Logger Demo\n");
  Serial.println("USB Serial Port up!\n");

  Serial1.begin(9600);  // GPS Serial connection
  Serial.println("GPS Serial Port up!\n");

  pinMode(chipSelect, OUTPUT);
  if (!SD.begin(chipSelect))
    return;
  Serial.println("SD card enabled!\n");
}

void loop() {
  int index = 0;
  char temp = ' ';
  String dataString = "";

  Serial.println("Open 'datalog.txt' for writing...");
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  if(dataFile) {
    Serial.println("Success!\n");

    Serial.println("Attempt to read from GPS device:");
    while(Serial1.available()) {

      temp = Serial1.read();
      Serial.print(temp);

      dataString += String(temp);
      index++;
      if(index > lineLength)
        break;
    }

    dataFile.print(dataString);
    dataFile.close();
  }
}
