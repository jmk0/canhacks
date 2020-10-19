#include <math.h>
#include <sstream>
#include <limits>
#include "TeslaCAN0102.hpp"

namespace canhacks
{
   TeslaCAN0102 ::
   TeslaCAN0102(MotorConfig cfg)
   : batteryPackVoltage(0.),
      batteryPackCurrent(0.),
      negTerminalTemp(std::numeric_limits<double>::quiet_NaN())
   {
      switch (cfg)
      {
         case mcSingleMotor: bpCurOffs =      0; break;
         case mcDualMotor:   bpCurOffs = -10000; break;
         default:            bpCurOffs = -32767; break; // fool.
      }
   }


   void TeslaCAN0102 ::
   decode(tCAN& msg)
   {
      batteryPackVoltage = fixedDecode<uint16_t>(&msg.data[0], .01, 0, 0);
      batteryPackCurrent = fixedDecode<int16_t>(&msg.data[2], .1, 1, bpCurOffs);
      unfilteredCurrent  = fixedDecode<int16_t>(&msg.data[4], .1, 1, bpCurOffs);
      if (msg.header.length == 8)
         negTerminalTemp = fixedDecode<int16_t>(&msg.data[6], .1, 1, 0);
      else
         negTerminalTemp = std::numeric_limits<double>::quiet_NaN();
   }


   std::string TeslaCAN0102 ::
   dump(bool verbose)
   {
      std::ostringstream s;
      s << "Battery pack: " << batteryPackVoltage << "V "
        << batteryPackCurrent << "A "
        << unfilteredCurrent < "A";
      if (!isnan(negTerminalTemp))
      {
         s << " " << negTerminalTemp << "C";
      }
      s << std::endl;
      return s.str();
   }
}
