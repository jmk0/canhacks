#ifndef TESLACAN0266_HPP
#define TESLACAN0266_HPP

#include <stdint.h>
#include "CANMessage.hpp"
#include "teslacan.hpp"

namespace canhacks
{
      /** Tesla Model S CAN message ID 0x0266.
       * Rear drive unit power information.
       */
   class TeslaCAN0266 : public CANMessage
   {
   public:
         /// Initialize everything to 0
      TeslaCAN0266();
         /** Turn the binary CAN message into the message's engineering data.
          * @param[in] msg The binary CAN message to decode. */
      virtual void decode(tCAN& msg);
         /** Return a string containing a human-readable
          * representation of the message. */
      virtual std::string dump(bool verbose = true);

      double inverter12V;     ///< 12V inverter measured Voltage.
      uint16_t dissipation;   ///< power dissipation in Watts.
         // what is this? mechanical power?
      double mechPower;       ///< kW
      uint16_t statorCurrent; ///< Amps
      uint16_t regenPowerMax; ///< kW
      uint16_t drivePowerMax; ///< kW, min 1kW
   };
}

#endif // TESLACAN0266_HPP
