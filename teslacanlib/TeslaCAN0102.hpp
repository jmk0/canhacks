#ifndef TESLACAN0102_HPP
#define TESLACAN0102_HPP

#include <stdint.h>
#include "CANMessage.hpp"
#include "teslacan.hpp"

namespace canhacks
{
      /** Tesla Model S CAN message ID 0x0102.
       * Battery Management System current and voltage.
       */
   class TeslaCAN0102 : public CANMessage
   {
   public:
         /// Initialize everything to 0
      TeslaCAN0102(MotorConfig cfg);
         /** Turn the binary CAN message into the message's engineering data.
          * @param[in] msg The binary CAN message to decode. */
      void decode(tCAN& msg);
         /** Return a string containing a human-readable
          * representation of the message. */
      std::string dump();

      double batteryPackVoltage; ///< In volts, naturally.
      double batteryPackCurrent; ///< In amps.
      double unfilteredCurrent;  ///< Not really sure what this is.
         /// Negative battery terminal temperature in degrees C.
      double negTerminalTemp;
   protected:
      uint16_t bpCurOffs; ///< Battery pack current offset.
   };
}

#endif // TESLACAN0102_HPP
