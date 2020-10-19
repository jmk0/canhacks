#include <math.h>
#include <sstream>
#include <iomanip>
#include <limits>
#include "TeslaCAN0562.hpp"

namespace canhacks
{
   TeslaCAN0562 ::
   TeslaCAN0562()
   : batteryOdo(0)
   {
   }


   void TeslaCAN0562 ::
   decode(tCAN& msg)
   {
      batteryOdo = canhacks::fixedDecode<uint32_t>(&msg.data[0], .001, 0, 0);
   }


   std::string TeslaCAN0562 ::
   dump(bool verbose)
   {
      std::ostringstream s;
      s << std::fixed << std::setprecision(3)
        << "Battery odometer: " << batteryOdo << " mi" << std::endl;
      return s.str();
   }
}
