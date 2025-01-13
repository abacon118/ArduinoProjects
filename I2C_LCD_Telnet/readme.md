# I2C LCD Controled by Telnet
This project started as a way to test a [W5100 Shield for Arduino Uno](https://www.aliexpress.us/item/3256801741280048.html?spm=a2g0o.order_list.order_list_main.63.31101802nOL3J7&gatewayAdapt=glo2usa).  The [Arduino Ethernet Shield library](https://docs.arduino.cc/libraries/ethernet/) [Chat Server example](https://docs.arduino.cc/tutorials/ethernet-shield-rev2/chat-server/) was used for ethernet/telnet communications.  The [LiquidCrystal_I2C Library](https://github.com/johnrickman/LiquidCrystal_I2C) was used to control the LCD with I2C.

### Pinout

| Arduino | I2C LCD |
|---------|---------|
| GND     | GND     |
| 5V      | VCC     |
| A4      | SDA     |
| A5      | SLC     |
