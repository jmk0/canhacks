#ifndef TESLACAN0302_HPP
#define TESLACAN0302_HPP

#include <stdint.h>
#include "CANMessage.hpp"
#include "teslacan.hpp"

namespace canhacks
{
      /** Tesla Model S CAN message ID 0x0302.
       * Battery state of charge.
       */
   class TeslaCAN0302 : public CANMessage
   {
   public:
         /// Initialize everything to 0
      TeslaCAN0302();
         /** Turn the binary CAN message into the message's engineering data.
          * @param[in] msg The binary CAN message to decode. */
      virtual void decode(tCAN& msg);
         /** Return a string containing a human-readable
          * representation of the message. */
      virtual std::string dump();

      double socMin; ///< %
      double socUI;  ///< %
   };
}

#endif // TESLACAN0302_HPP
