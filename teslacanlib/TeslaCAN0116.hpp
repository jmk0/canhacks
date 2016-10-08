#ifndef TESLACAN0116_HPP
#define TESLACAN0116_HPP

#include <stdint.h>
#include "CANMessage.hpp"
#include "teslacan.hpp"

namespace canhacks
{
      /** Tesla Model S CAN message ID 0x0116.
       * Rear drive unit torque and status information.
       */
   class TeslaCAN0116 : public CANMessage
   {
   public:
      enum Gear
      {
         gInvalid = -1,
         gPark = 1,
         gReverse = 2,
         gNeutral = 3,
         gDrive = 4
      };

         /// Initialize everything to 0
      TeslaCAN0116();
         /** Turn the binary CAN message into the message's engineering data.
          * @param[in] msg The binary CAN message to decode. */
      virtual void decode(tCAN& msg);
         /** Return a string containing a human-readable
          * representation of the message. */
      virtual std::string dump();

      double torqueEst; ///< Torque estimate in N*m.
      double speed;     ///< In MPH.
      Gear gearRequest;
      Gear gear;
   };
}

std::ostream& operator<<(std::ostream& s, canhacks::TeslaCAN0116::Gear g);

#endif // TESLACAN0116_HPP
