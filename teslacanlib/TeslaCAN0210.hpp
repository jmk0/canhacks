#ifndef TESLACAN0210_HPP
#define TESLACAN0210_HPP

#include <stdint.h>
#include "CANMessage.hpp"
#include "teslacan.hpp"

namespace canhacks
{
      /** Tesla Model S CAN message ID 0x0210.
       * DC-DC converter status.
       */
   class TeslaCAN0210 : public CANMessage
   {
   public:
         /// Initialize everything to 0
      TeslaCAN0210();
         /** Turn the binary CAN message into the message's engineering data.
          * @param[in] msg The binary CAN message to decode. */
      virtual void decode(tCAN& msg);
         /** Return a string containing a human-readable
          * representation of the message. */
      virtual std::string dump();

      uint16_t inputPower;    ///< Watts.
      uint16_t outputCurrent; ///< Amps.
      double   outputVoltage; ///< Volts.
      double   inletTemp;     ///< degrees C.
   };
}

#endif // TESLACAN0210_HPP
