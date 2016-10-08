#ifndef TESLACAN0232_HPP
#define TESLACAN0232_HPP

#include <stdint.h>
#include "CANMessage.hpp"
#include "teslacan.hpp"

namespace canhacks
{
      /** Tesla Model S CAN message ID 0x0232.
       * Battery power limits.
       */
   class TeslaCAN0232 : public CANMessage
   {
   public:
         /// Initialize everything to 0
      TeslaCAN0232();
         /** Turn the binary CAN message into the message's engineering data.
          * @param[in] msg The binary CAN message to decode. */
      virtual void decode(tCAN& msg);
         /** Return a string containing a human-readable
          * representation of the message. */
      virtual std::string dump();

      double maxDischargePower; ///< kW
      double maxRegenPower;     ///< kW
   };
}

#endif // TESLACAN0232_HPP
