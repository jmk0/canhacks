#ifndef TESLACAN0256_HPP
#define TESLACAN0256_HPP

#include <iostream>
#include <stdint.h>
#include "CANMessage.hpp"
#include "teslacan.hpp"

namespace canhacks
{
      /** Tesla Model S CAN message ID 0x0256.
       * Battery Management System current and voltage.
       */
   class TeslaCAN0256 : public CANMessage
   {
   public:
         /// Driver inverter system state.
      enum InverterState
      {
         isInvalid = -1,
         isUnavailable = 0,
         isStandby = 1,
         isFault = 2,
         isAbort = 3,
         isEnabled = 4
      };
         /// Vehicle hold state.
      enum HoldState
      {
         hsInvalid = -1,
         hsUnavailable = 0,
         hsStandby = 1,
         hsBlendIn = 2,
         hsStandstill = 3,
         hsBlendOut = 4,
         hsPark = 5,
         hsFault = 6,
         hsInit = 7
      };
         /// Cruise control state.
      enum CruiseState
      {
         csInvalid = -1,
         csOff = 0,
         csStandby = 1,
         csEnabled = 2,
         csStandstill = 3,
         csOverride = 4,
         csFault = 5,
         csPreFault = 6,
         csPreCancel = 7
      };
         /// How the car's UI displays speed.
      enum SpeedUnit
      {
         dsInvalid = -1,
         dsMPH = 0,
         dsKPH = 1
      };

         /// Initialize everything
      TeslaCAN0256();
         /** Turn the binary CAN message into the message's engineering data.
          * @param[in] msg The binary CAN message to decode. */
      virtual void decode(tCAN& msg);
         /** Return a string containing a human-readable
          * representation of the message. */
      virtual std::string dump();

      bool driveInvProx;  ///< Drive inverter proximity?
      bool inverterReady;
      bool regen;
      InverterState driveInverterState;
      HoldState vehHoldState;
      CruiseState cruiseCtlState;
      double speed;       ///< Always in MPH.
      double cruiseSpeed; ///< Cruise control speed setting.
      unsigned count;     ///< Unknown.
      unsigned dispSpeed; ///< Speed as displayed on instrument cluster.
      SpeedUnit dispUnit; ///< Units on instrument cluster speed display.
   };
}


std::ostream& operator<<(std::ostream& s,
                         canhacks::TeslaCAN0256::InverterState iState);

std::ostream& operator<<(std::ostream& s,
                         canhacks::TeslaCAN0256::HoldState hState);

std::ostream& operator<<(std::ostream& s,
                         canhacks::TeslaCAN0256::CruiseState cState);

std::ostream& operator<<(std::ostream& s,
                         canhacks::TeslaCAN0256::SpeedUnit unit);

#endif // TESLACAN0256_HPP
