#ifndef TESLACAN0106_HPP
#define TESLACAN0106_HPP

#include <stdint.h>
#include "CANMessage.hpp"
#include "teslacan.hpp"

namespace canhacks
{
      /** Tesla Model S CAN message ID 0x0106.
       * Rear drive unit information.
       */
   class TeslaCAN0106 : public CANMessage
   {
   public:
         /// Initialize everything to 0
      TeslaCAN0106();
         /** Turn the binary CAN message into the message's engineering data.
          * @param[in] msg The binary CAN message to decode. */
      virtual void decode(tCAN& msg);
         /** Return a string containing a human-readable
          * representation of the message. */
      virtual std::string dump(bool verbose = true);

      int16_t motorRPM;  ///< Goes negative in reverse.
      double pedalPos;   ///< 0% to 102%.
   };
}

#endif // TESLACAN0106_HPP
