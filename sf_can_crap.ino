#include <mcp2515.h>
#include <Canbus.h>
#include <SPI.h>
#include <SD.h>

// Define Joystick connection pins
#define UP     A1
#define DOWN   A3
#define LEFT   A2
#define RIGHT  A5
#define CLICK  A4
// LED flashed when there is data being read from the CAN BUS (D7 on shield)
#define LED_OPEN 7
// LED blinks slowly on error conditions (typically a missing SD), or
// quickly to indicate bus speed
// 1 blink = 125K
// 3 blinks = 500K
#define LED_ERR 8
// LED on Arduino UNO board. Unused, hard to see.
#define LED_ARD 13
// chip select used for writing to the SD card
#define CHIP_SELECT 9
#define CAN_SPEED_UP CANSPEED_500
#define CAN_SPEED_DN CANSPEED_125

/// speed of the CAN BUS on initialization
int defCanSpeed = CANSPEED_500; // default: 500k
/// state of the OPEN LED
int ledOn = 0;
/// output file on SD card
File dataFile;
/// CAN message storage, I don't want to allocate on the stack or heap.
tCAN msg;
/** If true, usually because the SD card is missing.  Bus
 * initialization failure can also cause a failure state.  If set to
 * true, the ERR LED slowly blinks.  A reset of the board is required
 * after correcting the issue. */
bool fail;

/// Flash the ERR LED the specified number of times.
void flashOpen(unsigned count)
{
   for (unsigned i = 0; i < count; i++)
   {
      digitalWrite(LED_OPEN, HIGH);
      delay(300);
      digitalWrite(LED_OPEN, LOW);
      delay(300);
   }
}

/** Set the CAN bus speed to the given value.  The OPEN LED is quickly
 * flashed the given number of times. */
void setCANSpeed(int spd, unsigned flashCount)
{
   if (Canbus.init(spd))
   {
      flashOpen(flashCount);
   }
   else
   {
      digitalWrite(LED_ERR, HIGH);
      fail = true;
   }
}

void setup()
{
   fail = false;
      // set up LED pins
   pinMode(LED_OPEN, OUTPUT);
   pinMode(LED_ERR, OUTPUT);
      // set up pin for SPI SD card interface
   pinMode(CHIP_SELECT, OUTPUT);
      // initialize the joystick pins
   pinMode(UP,INPUT);
   pinMode(DOWN,INPUT);
   pinMode(LEFT,INPUT);
   pinMode(RIGHT,INPUT);
   pinMode(CLICK,INPUT);
      //Pull analog pins high to enable reading of joystick movements
   digitalWrite(UP, HIGH);
   digitalWrite(DOWN, HIGH);
   digitalWrite(LEFT, HIGH);
   digitalWrite(RIGHT, HIGH);
   digitalWrite(CLICK, HIGH);

      // initialize the can bus
   setCANSpeed(defCanSpeed, 3);

      // initialize the SD card access
   if (!SD.begin(CHIP_SELECT))
   {
      digitalWrite(LED_ERR, HIGH);
      fail = true;
   }
      // open an output file on the SD card
   dataFile = SD.open("candata.bin", FILE_WRITE);
   if (!dataFile)
   {
      digitalWrite(LED_ERR, HIGH);
      fail = true;
   }
}

/** Receive a message from the CAN bus.
 * @param[out] message structure where the CAN message will be stored.
 * @return 0 if no message was received. */
uint8_t message_rx(tCAN *message)
{
   uint8_t rv;

   if (rv = mcp2515_check_message())
   {
      rv = mcp2515_get_message(message);
   }
   return rv;
}

/// Get a message from the CAN bus and store it on the SD card.
void xfer_can2sd()
{
   while (message_rx(&msg))
   {
      digitalWrite(LED_OPEN, ledOn);
      ledOn = !ledOn;
      dataFile.write((const uint8_t *)&msg, sizeof(msg));
      dataFile.flush();
   }
}

void loop() 
{
   if (fail)
   {
         // something's broken, just flash the ERR LED
      delay(1000);
      digitalWrite(LED_ERR, ledOn);
      ledOn = !ledOn;
   }
   else
   {
         // normal ops, record data
      xfer_can2sd();
         // use the joystick to change BUS speed
      if (digitalRead(UP) == 0)
      {
         setCANSpeed(CAN_SPEED_UP, 3);
      }
      if (digitalRead(DOWN) == 0)
      {
         setCANSpeed(CAN_SPEED_DN, 1);
      }
   }
}
