#include <math.h>
#include <sstream>
#include <iomanip>
#include <limits>
#include "TeslaCAN0210.hpp"

namespace canhacks
{
   TeslaCAN0210 ::
   TeslaCAN0210()
   : inputPower(0),
      outputCurrent(0),
      outputVoltage(0),
      inletTemp(0)
   {
   }


   void TeslaCAN0210 ::
   decode(tCAN& msg)
   {
      inputPower = msg.data[3] << 4;
      outputCurrent = msg.data[4];
      outputVoltage = msg.data[5] / 10.0;
      inletTemp = (((int8_t)msg.data[2]) * 0.5) + 40;
   }


   std::string TeslaCAN0210 ::
   dump(bool verbose)
   {
      std::ostringstream s;
      s << std::fixed << std::setprecision(1)
        << "Input power: " << inputPower << " W" << std::endl
        << "Output current: " << outputCurrent << " A" << std::endl
        << "Inlet temp: " << inletTemp << " deg C" << std::endl;
         // might be interesting to add output power and converter efficiency
      return s.str();
   }
}
