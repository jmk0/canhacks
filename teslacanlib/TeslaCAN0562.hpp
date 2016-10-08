#ifndef TESLACAN0562_HPP
#define TESLACAN0562_HPP

#include <stdint.h>
#include "CANMessage.hpp"
#include "teslacan.hpp"

namespace canhacks
{
      /** Tesla Model S CAN message ID 0x0562.
       * Battery odometer information.
       */
   class TeslaCAN0562 : public CANMessage
   {
   public:
         /// Initialize everything to 0
      TeslaCAN0562();
         /** Turn the binary CAN message into the message's engineering data.
          * @param[in] msg The binary CAN message to decode. */
      virtual void decode(tCAN& msg);
         /** Return a string containing a human-readable
          * representation of the message. */
      virtual std::string dump();

      double batteryOdo;   ///< Battery odometer in mi.
   };
}

#endif // TESLACAN0562_HPP
