#include <math.h>
#include <sstream>
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
/*
      switch ((msg.data[0] >> 2) & 0x03)
      {
         case 0:  s << "Unavailable"; break;
         case 1:  s << "Standby";     break;
         case 2:  s << "Blend In";    break;
         case 3:  s << "Standstill";  break;
         case 4:  s << "Blend Out";   break;
         case 5:  s << "Park";        break;
         case 6:  s << "Fault";       break;
         case 7:  s << "Init";        break;
      }
      s << endl
*/
        << "Drive inverter Proximity? " << driveInvProx << endl
        << "Inverter ready " << inverterReady << endl
        << "Regen " << regen << endl
        << "Cruise control " << cruiseCtlState << endl
/*
      switch ((msg.data[1] >> 4) & 0xff)
      {
         case 0:  s << "Off";         break;
         case 1:  s << "Standby";     break;
         case 2:  s << "Enabled";     break;
         case 3:  s << "Standstill";  break;
         case 4:  s << "Override";    break;
         case 5:  s << "Fault";       break;
         case 6:  s << "Pre-Fault";   break;
         case 7:  s << "Pre-cancel";  break;
      }
      s << endl
*/
        << "Speed: " << speed << " MPH" << endl
        << "Cruise speed: " << cruiseSpeed << " MPH" << endl
        << "Count: " << count << endl
        << "Display speed: " << dispSpeed << dispUnit << endl;
      return s.str();
   }
}
