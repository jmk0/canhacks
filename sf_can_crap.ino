#include <mcp2515.h>
#include <Canbus.h>
#include <SPI.h>
#include <SD.h>

#define LED_OPEN 7
#define LED_ERR 8
#define LED_ARD 13
#define CHIP_SELECT 9
#define CMD_LEN (sizeof("T12345678811223344556677881234\r")+1)

int g_can_speed = CANSPEED_500; // default: 500k
int g_ts_en = 0;
int ledOn = 0;
File dataFile;
// things I don't want to allocate on the stack or heap
tCAN msg;
char dataToSD[CMD_LEN];

bool fail;

void setup()
{
   fail = false;
   pinMode(LED_OPEN, OUTPUT);
   pinMode(LED_ERR, OUTPUT);
   pinMode(CHIP_SELECT, OUTPUT);
   if (Canbus.init(g_can_speed))
   {
      digitalWrite(LED_ERR, LOW);
   }
   else
   {
      digitalWrite(LED_ERR, HIGH);
      fail = true;
   }

   if (!SD.begin(CHIP_SELECT))
   {
      digitalWrite(LED_ERR, HIGH);
      fail = true;
   }
   dataFile = SD.open("candata.bin", FILE_WRITE);
   if (!dataFile)
   {
      digitalWrite(LED_ERR, HIGH);
      fail = true;
   }
}

uint8_t message_rx(tCAN *message)
{
   uint8_t rv;

   if (rv = mcp2515_check_message())
   {
      rv = mcp2515_get_message(message);
   }
   return rv;
}

void xfer_can2sd()
{
   while (message_rx(&msg))
   {
      digitalWrite(LED_OPEN, ledOn);
      ledOn = !ledOn;
      dataFile.write((char*)&msg, sizeof(msg));
      dataFile.flush();
   }
}

void loop() 
{
   if (fail)
   {
      delay(1000);
      digitalWrite(LED_ERR, ledOn);
      ledOn = !ledOn;
   }
   else
   {
      xfer_can2sd();
   }
}
