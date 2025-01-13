/*
Telnet I2C LCD
Andrew Bowman 2025

Refrences:
https://docs.arduino.cc/tutorials/ethernet-shield-rev2/chat-server/
https://github.com/johnrickman/LiquidCrystal_I2C/blob/master/examples/HelloWorld/HelloWorld.pde

Liquid Crystal I2C
| Arduino | I2C LCD |
|---------|---------|
| GND     | GND     |
| 5V      | VCC     |
| A4      | SDA     |
| A5      | SLC     |
 */

#include <SPI.h>
#include <Ethernet.h>

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network.
// gateway and subnet are optional:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 177);
IPAddress myDns(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);


// telnet defaults to port 23
EthernetServer server(23);
bool alreadyConnected = false; // whether or not the client was connected previously
int numChars = 0;
int row = 0; // for LCD_Print
int column = 0; //for LCD_Print
void setup() {
  // You can use Ethernet.init(pin) to configure the CS pin
  //Ethernet.init(10);  // Most Arduino shields
  //Ethernet.init(5);   // MKR ETH Shield
  //Ethernet.init(0);   // Teensy 2.0
  //Ethernet.init(20);  // Teensy++ 2.0
  //Ethernet.init(15);  // ESP8266 with Adafruit FeatherWing Ethernet
  //Ethernet.init(33);  // ESP32 with Adafruit FeatherWing Ethernet

  // initialize the Ethernet device
  Ethernet.begin(mac, ip, myDns, gateway, subnet);

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }

  // start listening for clients
  server.begin();

  Serial.print("Telnet address:");
  Serial.println(Ethernet.localIP());

  lcd.init();                      // initialize the lcd 
  lcd.init();
  lcd.backlight();

}

void loop() {
  // wait for a new client:
  EthernetClient client = server.available();

  // when the client sends the first byte, say hello:
  if (client) {
    if (!alreadyConnected) {
      // clear out the input buffer:
      client.flush();
      Serial.println("We have a new client");
      client.println("Hello, client!");
      lcd.clear();
      alreadyConnected = true;
    }

    if (client.available() > 0) {
      // read the bytes incoming from the client:
      char thisChar = client.read();
      // echo the bytes back to the client:
      server.write(thisChar);
      if(numChars >65){  // 65 characters are printed dring startup.  If your IP is different, it may take more or less.
        LCD_Print(thisChar);}
      // echo the bytes to the server as well:
      Serial.println(numChars);
      Serial.write(thisChar);
      numChars = numChars+1;

    }
  }
}

void LCD_Print(char thisChar){  // Prints to LCD Screen and manages cursor location 
  if(column == 16){
    if(row == 1)
      row = 0;
    else
      row = 1;
    column = 0;
  }
  lcd.setCursor(column,row);
  lcd.print(thisChar);
  column = column + 1;
}
