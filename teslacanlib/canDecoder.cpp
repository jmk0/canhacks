#include "canDecoder.hpp"
#include "TeslaCAN0102.hpp"

namespace canhacks
{
   CANMessage* canDecoder(tCAN& msg, MotorConfig cfg)
   {
      CANMessage *rv;
      switch (msg.id)
      {
         case 0x0102: rv = new TeslaCAN0102(cfg); return rv;
         case 0x0256:
         case 0x0106:
         case 0x0116:
         case 0x0145:
         case 0x0154:
         case 0x01d4:
         case 0x0210:
         case 0x0232:
         case 0x0266:
         case 0x02e5:
         case 0x0302:
         case 0x0382:
         case 0x03d2:
         case 0x0562:
         default:
            return NULL;
      } // switch (msg.id)
   } // CANMessage* canDecoder(tCAN& msg, MotorConfig cfg)
} // namespace canhacks
