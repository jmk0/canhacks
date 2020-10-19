#ifndef TESLACAN0154_HPP
#define TESLACAN0154_HPP

#include <stdint.h>
#include "CANMessage.hpp"
#include "teslacan.hpp"

namespace canhacks
{
      /** Tesla Model S CAN message ID 0x0154.
       * Rear drive unit measurement information.
       */
   class TeslaCAN0154 : public CANMessage
   {
   public:
         /// Initialize everything to 0
      TeslaCAN0154();
         /** Turn the binary CAN message into the message's engineering data.
          * @param[in] msg The binary CAN message to decode. */
      virtual void decode(tCAN& msg);
         /** Return a string containing a human-readable
          * representation of the message. */
      virtual std::string dump(bool verbose = true);

      double torque; ///< Newton*meters
      double pedalA; ///< pedal (accelerator?) position, 0% to 102%
      double pedalB; ///< pedal (accelerator?) position, 0% to 102%
   };
}

#endif // TESLACAN0154_HPP
