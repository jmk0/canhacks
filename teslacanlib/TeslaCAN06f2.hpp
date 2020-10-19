#ifndef TESLACAN06f2_HPP
#define TESLACAN06f2_HPP

#include <stdint.h>
#include "CANMessage.hpp"
#include "teslacan.hpp"

namespace canhacks
{
      /** Tesla Model S CAN message ID 0x06f2.
       * Battery Management System current and voltage.
       */
   class TeslaCAN06f2 : public CANMessage
   {
   public:
         /// Initialize everything to 0
      TeslaCAN06f2();
         /** Turn the binary CAN message into the message's engineering data.
          * @param[in] msg The binary CAN message to decode. */
      virtual void decode(tCAN& msg);
         /** Return a string containing a human-readable
          * representation of the message. */
      virtual std::string dump(bool verbose = true);

         /// Identifier for the battery pack
      uint8_t index;
         /// Four data values from the message, either temperature or voltage.
      double d1, d2, d3, d4;
         /// If true, d1-d4 contain voltages otherwise they contain temps.
      bool volts;
   };
}

#endif // TESLACAN06f2_HPP
