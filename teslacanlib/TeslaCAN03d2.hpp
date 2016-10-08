#ifndef TESLACAN03D2_HPP
#define TESLACAN03D2_HPP

#include <stdint.h>
#include "CANMessage.hpp"
#include "teslacan.hpp"

namespace canhacks
{
      /** Tesla Model S CAN message ID 0x03d2.
       * Battery lifetime energy stats.
       */
   class TeslaCAN03d2 : public CANMessage
   {
   public:
         /// Initialize everything to 0
      TeslaCAN03d2();
         /** Turn the binary CAN message into the message's engineering data.
          * @param[in] msg The binary CAN message to decode. */
      virtual void decode(tCAN& msg);
         /** Return a string containing a human-readable
          * representation of the message. */
      virtual std::string dump();

      double chargeTotal;    ///< Lifetime charge total, kW*h.
      double dischargeTotal; ///< Lifetime discharge total, kW*h.
   };
}

#endif // TESLACAN03d2_HPP
