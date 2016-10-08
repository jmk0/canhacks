#ifndef TESLACAN0382_HPP
#define TESLACAN0382_HPP

#include <stdint.h>
#include "CANMessage.hpp"
#include "teslacan.hpp"

namespace canhacks
{
      /** Tesla Model S CAN message ID 0x0382.
       * Battery power status.
       */
   class TeslaCAN0382 : public CANMessage
   {
   public:
         /// Initialize everything to 0
      TeslaCAN0382();
         /** Turn the binary CAN message into the message's engineering data.
          * @param[in] msg The binary CAN message to decode. */
      virtual void decode(tCAN& msg);
         /** Return a string containing a human-readable
          * representation of the message. */
      virtual std::string dump();

         // kW*h is a unit of power, not energy.  All fields are in
         // units of kW*h.

      double nomFullPackPower;
      double nomPowerRem;
      double expPowerRem;
      double idealPowerRem;
      double powerToFullCharge;
      double powerBuffer;
   };
}

#endif // TESLACAN0382_HPP
