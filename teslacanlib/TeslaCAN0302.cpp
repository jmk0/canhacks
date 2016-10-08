#include <math.h>
#include <sstream>
#include <iomanip>
#include <limits>
#include "TeslaCAN0302.hpp"

namespace canhacks
{
   TeslaCAN0302 ::
   TeslaCAN0302()
   : socMin(0),
      socUI(0)
   {
   }


   void TeslaCAN0302 ::
   decode(tCAN& msg)
   {
      socMin = ((msg.data[0] + ((msg.data[1] & 0x03) << 8)) / 10.0);
      socUI  = (((msg.data[1] >> 2) + ((msg.data[2] & 0x0f) << 6)) / 10.0);
   }


   std::string TeslaCAN0302 ::
   dump()
   {
      std::ostringstream s;
      s << std::fixed << std::setprecision(1)
        << "State of charge minimum: " << socMin << "%" << std::endl
        << "State of charge UI: " << socUI << "%" << std::endl;
      return s.str();
   }
}
