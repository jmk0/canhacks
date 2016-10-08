#include <math.h>
#include <sstream>
#include <iomanip>
#include <limits>
#include "TeslaCAN0154.hpp"

namespace canhacks
{
   TeslaCAN0154 ::
   TeslaCAN0154()
   : torque(0),
      pedalA(0),
      pedalB(0)
   {
   }


   void TeslaCAN0154 ::
   decode(tCAN& msg)
   {
      torque = canhacks::fixedDecode<int16_t>(&msg.data[5], 0.25, 3, 0);
      pedalA = msg.data[2] * .4;
      pedalB = msg.data[3] * .4;
   }


   std::string TeslaCAN0154 ::
   dump()
   {
      std::ostringstream s;
      s << std::setprecision(2) << std::fixed
        << "Rear drive motor torque: " << torque << " N*m ("
        << (torque * 0.737562149277) << " ft*lb)" << std::endl
        << "Pedal position A: " << pedalA << std::endl
        << "Pedal position B: " << pedalA << std::endl;
      return s.str();
   }
}
