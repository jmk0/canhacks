#include <math.h>
#include <sstream>
#include <iomanip>
#include <limits>
#include "TeslaCAN03d2.hpp"

namespace canhacks
{
   TeslaCAN03d2 ::
   TeslaCAN03d2()
   : chargeTotal(0),
      dischargeTotal(0)
   {
   }


   void TeslaCAN03d2 ::
   decode(tCAN& msg)
   {
      dischargeTotal = canhacks::fixedDecode<uint32_t>(&msg.data[0], .001, 0,
                                                       0);
      chargeTotal = canhacks::fixedDecode<uint32_t>(&msg.data[4], .001, 0, 0);
   }


   std::string TeslaCAN03d2 ::
   dump(bool verbose)
   {
      std::ostringstream s;
      s << std::fixed << std::setprecision(3)
        << "Battery lifetime charge total: " << chargeTotal << " kW*h"
        << std::endl
        << "Battery lifetime discharge total: " << dischargeTotal << " kW*h"
        << std::endl;
      return s.str();
   }
}
