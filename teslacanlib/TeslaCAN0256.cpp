#include <math.h>
#include <sstream>
#include <iomanip>
#include <limits>
#include "TeslaCAN0256.hpp"

namespace canhacks
{
   TeslaCAN0256 ::
   TeslaCAN0256()
   : driveInverterState(isInvalid),
      vehHoldState(hsInvalid),
      cruiseCtlState(csInvalid),
      speed(0),
      cruiseSpeed(0),
      count(0),
      dispSpeed(dsInvalid)
   {
   }


   void TeslaCAN0256 ::
   decode(tCAN& msg)
   {
      driveInverterState = (InverterState)(msg.data[0] & 0x03);
      vehHoldState = (HoldState)((msg.data[0] >> 2) & 0x03);
      driveInvProx = ((msg.data[0] >> 6) & 0x01);
      inverterReady = ((msg.data[0] >> 7) & 0x01);
      regen = (msg.data[1] & 0x01);
      cruiseCtlState = (CruiseState)((msg.data[1] >> 4) & 0xff);
      speed = fixedDecode<uint16_t>(&msg.data[2], .1, 4, 0);
      dispUnit = (SpeedUnit)(msg.data[3] >> 7);
      cruiseSpeed = fixedDecode<int16_t>(&msg.data[4], .5, 7, 0);
      count = (msg.data[5] >> 4);
      dispSpeed = msg.data[6];
   }


   std::string TeslaCAN0256 ::
   dump()
   {
      using namespace std;
      ostringstream s;
      s << boolalpha << fixed
        << "Drive inverter system state: " << driveInverterState << endl
        << "Vehicle hold state: " << vehHoldState << endl
        << "Drive inverter Proximity? " << driveInvProx << endl
        << "Inverter ready " << inverterReady << endl
        << "Regen " << regen << endl
        << "Cruise control " << cruiseCtlState << endl
        << setprecision(1)
        << "Speed: " << speed << " MPH" << endl
        << "Cruise speed: " << cruiseSpeed << " MPH" << endl
        << "Count: " << count << endl
        << "Display speed: " << dispSpeed << " " << dispUnit << endl;
      return s.str();
   }
}


std::ostream& operator<<(std::ostream& s,
                         canhacks::TeslaCAN0256::InverterState iState)
{
   switch (iState)
   {
      case canhacks::TeslaCAN0256::isUnavailable: s << "Unavailable"; break;
      case canhacks::TeslaCAN0256::isStandby:     s << "Standby";     break;
      case canhacks::TeslaCAN0256::isFault:       s << "Fault";       break;
      case canhacks::TeslaCAN0256::isAbort:       s << "Abort";       break;
      case canhacks::TeslaCAN0256::isEnabled:     s << "Enabled";     break;
      default:                                    s << "Invalid";     break;
   }
   return s;
}


std::ostream& operator<<(std::ostream& s,
                         canhacks::TeslaCAN0256::HoldState hState)
{
   switch (hState)
   {
      case canhacks::TeslaCAN0256::hsUnavailable: s << "Unavailable"; break;
      case canhacks::TeslaCAN0256::hsStandby:     s << "Standby";     break;
      case canhacks::TeslaCAN0256::hsBlendIn:     s << "Blend In";    break;
      case canhacks::TeslaCAN0256::hsStandstill:  s << "Standstill";  break;
      case canhacks::TeslaCAN0256::hsBlendOut:    s << "Blend Out";   break;
      case canhacks::TeslaCAN0256::hsPark:        s << "Park";        break;
      case canhacks::TeslaCAN0256::hsFault:       s << "Fault";       break;
      case canhacks::TeslaCAN0256::hsInit:        s << "Init";        break;
      default:                                    s << "Invalid";     break;
   }
   return s;
}


std::ostream& operator<<(std::ostream& s,
                         canhacks::TeslaCAN0256::CruiseState cState)
{
   switch (cState)
   {
      case canhacks::TeslaCAN0256::csOff:        s << "Off";         break;
      case canhacks::TeslaCAN0256::csStandby:    s << "Standby";     break;
      case canhacks::TeslaCAN0256::csEnabled:    s << "Enabled";     break;
      case canhacks::TeslaCAN0256::csStandstill: s << "Standstill";  break;
      case canhacks::TeslaCAN0256::csOverride:   s << "Override";    break;
      case canhacks::TeslaCAN0256::csFault:      s << "Fault";       break;
      case canhacks::TeslaCAN0256::csPreFault:   s << "Pre-Fault";   break;
      case canhacks::TeslaCAN0256::csPreCancel:  s << "Pre-cancel";  break;
      default:                                   s << "Invalid";     break;
   }
   return s;
}


std::ostream& operator<<(std::ostream& s,
                         canhacks::TeslaCAN0256::SpeedUnit unit)
{
   switch (unit)
   {
      case canhacks::TeslaCAN0256::dsMPH: s << "MPH"; break;
      case canhacks::TeslaCAN0256::dsKPH: s << "KPH"; break;
      default:                            s << "Invalid"; break;
   }
   return s;
}
