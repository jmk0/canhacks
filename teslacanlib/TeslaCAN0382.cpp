#include <math.h>
#include <sstream>
#include <iomanip>
#include <limits>
#include "TeslaCAN0382.hpp"

namespace canhacks
{
   TeslaCAN0382 ::
   TeslaCAN0382()
   : nomFullPackPower(0),
      nomPowerRem(0),
      expPowerRem(0),
      idealPowerRem(0),
      powerToFullCharge(0),
      powerBuffer(0)
   {
   }


   void TeslaCAN0382 ::
   decode(tCAN& msg)
   {
      nomFullPackPower = (msg.data[0] + ((msg.data[1] & 0x03) << 8)) * 0.1;
      nomPowerRem = ((msg.data[1] >> 2) + ((msg.data[2] & 0x0f) * 64)) * 0.1;
      expPowerRem = ((msg.data[2] >> 4) + ((msg.data[3] & 0x3f) * 16)) * 0.1;
      idealPowerRem = ((msg.data[3] >> 6) + ((msg.data[4] & 0xff) * 4)) * 0.1;
      powerToFullCharge = (msg.data[5] + ((msg.data[6] & 0x03) << 8)) * 0.1;
      powerBuffer = ((msg.data[6] >> 2) + ((msg.data[7] & 0x03) * 64)) * 0.1;
   }


   std::string TeslaCAN0382 ::
   dump()
   {
      std::ostringstream s;
      s << std::fixed << std::setprecision(1)
        << "Nominal pack full power: " << nomFullPackPower << "kW*h"
        << std::endl
        << "Nominal power remaining: " << nomPowerRem << "kW*h" << std::endl
        << "Expected power remaining: " << expPowerRem << "kW*h" << std::endl
        << "Ideal power remaining: " << idealPowerRem << "kW*h" << std::endl
        << "Power to charge complete: " << powerToFullCharge << "kW*h"
        << std::endl
        << "Power buffer: " << powerBuffer << "kW*h" << std::endl;
      return s.str();
   }
}
