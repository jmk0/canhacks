#include <math.h>
#include <sstream>
#include <limits>
#include "TeslaCAN0106.hpp"

namespace canhacks
{
   TeslaCAN0106 ::
   TeslaCAN0106()
   : motorRPM(0),
      pedalPos(0)
   {
   }


   void TeslaCAN0106 ::
   decode(tCAN& msg)
   {
      motorRPM = canhacks::fixedDecode<int16_t>(&msg.data[4], 1, 0, 0);
      pedalPos = msg.data[6] * .4;
   }


   std::string TeslaCAN0106 ::
   dump()
   {
      std::ostringstream s;
      s << "Rear drive motor RPM: " << motorRPM << std::endl
        << "Pedal position: " << pedalPos << std::endl;
      return s.str();
   }
}
