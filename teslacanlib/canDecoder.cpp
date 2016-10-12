#include "canDecoder.hpp"
#include "TeslaCAN0102.hpp"
#include "TeslaCAN0106.hpp"
#include "TeslaCAN0116.hpp"
#include "TeslaCAN0154.hpp"
#include "TeslaCAN0210.hpp"
#include "TeslaCAN0232.hpp"
#include "TeslaCAN0256.hpp"
#include "TeslaCAN0266.hpp"
#include "TeslaCAN0302.hpp"
#include "TeslaCAN0382.hpp"
#include "TeslaCAN03d2.hpp"
#include "TeslaCAN0562.hpp"
#include "TeslaCAN06f2.hpp"

namespace canhacks
{
   CANMessage* canDecoder(tCAN& msg, MotorConfig cfg)
   {
      CANMessage *rv;
      switch (msg.id)
      {
         case 0x0102: rv = new TeslaCAN0102(cfg); rv->decode(msg); return rv;
         case 0x0106: rv = new TeslaCAN0106();    rv->decode(msg); return rv;
         case 0x0116: rv = new TeslaCAN0116();    rv->decode(msg); return rv;
         case 0x0154: rv = new TeslaCAN0154();    rv->decode(msg); return rv;
         case 0x0210: rv = new TeslaCAN0210();    rv->decode(msg); return rv;
         case 0x0232: rv = new TeslaCAN0232();    rv->decode(msg); return rv;
         case 0x0256: rv = new TeslaCAN0256();    rv->decode(msg); return rv;
         case 0x0266: rv = new TeslaCAN0266();    rv->decode(msg); return rv;
         case 0x0302: rv = new TeslaCAN0302();    rv->decode(msg); return rv;
         case 0x0382: rv = new TeslaCAN0382();    rv->decode(msg); return rv;
         case 0x03d2: rv = new TeslaCAN03d2();    rv->decode(msg); return rv;
         case 0x0562: rv = new TeslaCAN0562();    rv->decode(msg); return rv;
         case 0x06f2: rv = new TeslaCAN06f2();    rv->decode(msg); return rv;
         case 0x0145:
         case 0x01d4:
         case 0x02e5:
         default:
            return NULL;
      } // switch (msg.id)
   } // CANMessage* canDecoder(tCAN& msg, MotorConfig cfg)
} // namespace canhacks
