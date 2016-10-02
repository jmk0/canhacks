#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdint.h>
#include <string.h>
#include "canDecoder.hpp"

using namespace std;

/// @note this code assumes it's running on a little-endian (e.g. Intel) host.

/*
 * Big thanks to Jason Hughes for providing much of the information
 * used in decoding the Tesla CAN messages.  Also thanks to the others
 * who contributed to the collection and interpretation of the
 * information.
 */


void processDefault(canhacks::tCAN& msg)
{
   cout << setw(4) << hex << msg.id << dec
        << " " << setw(2) << (int)msg.header.rtr
        << " " << setw(2) << (unsigned)msg.header.length;
   for (unsigned i = 0; i < msg.header.length; i++)
   {
      cout << " " << setw(2) << setfill('0') << hex << (unsigned)msg.data[i]
           << dec << setfill(' ');
   }
   cout << endl;
}



/// Speed and cruise control status (rear drive unit status)
void process0256(canhacks::tCAN& msg)
{
   cout << "Drive inverter system state: ";
   switch (msg.data[0] & 0x03)
   {
      case 0:  cout << "Unavailable"; break;
      case 1:  cout << "Standby";     break;
      case 2:  cout << "Fault";       break;
      case 3:  cout << "Abort";       break;
      case 4:  cout << "Enabled";     break;
      default: cout << "Unknown";     break;
   }
   cout << endl << "Vehicle hold state: ";
   switch ((msg.data[0] >> 2) & 0x03)
   {
      case 0:  cout << "Unavailable"; break;
      case 1:  cout << "Standby";     break;
      case 2:  cout << "Blend In";    break;
      case 3:  cout << "Standstill";  break;
      case 4:  cout << "Blend Out";   break;
      case 5:  cout << "Park";        break;
      case 6:  cout << "Fault";       break;
      case 7:  cout << "Init";        break;
   }
   cout << endl
        << "Drive inverter Proximity? " << ((msg.data[0] >> 6) & 0x01) << endl
        << "Inverter ready " << ((msg.data[0] >> 7) & 0x01) << endl
        << "Regen " << (msg.data[1] & 0x01) << endl
        << "Cruise control ";
   switch ((msg.data[1] >> 4) & 0xff)
   {
      case 0:  cout << "Off";         break;
      case 1:  cout << "Standby";     break;
      case 2:  cout << "Enabled";     break;
      case 3:  cout << "Standstill";  break;
      case 4:  cout << "Override";    break;
      case 5:  cout << "Fault";       break;
      case 6:  cout << "Pre-Fault";   break;
      case 7:  cout << "Pre-cancel";  break;
   }
   cout << endl
        << "Speed: " << canhacks::fixedDecode<uint16_t>(&msg.data[2], .1, 4, 0) << " MPH"
        << endl
        << "Cruise speed: " << canhacks::fixedDecode<int16_t>(&msg.data[4], .5, 7, 0)
        << " MPH" << endl
        << "Count: " << (msg.data[5] >> 4) << endl
        << "Display speed: " << (unsigned) msg.data[6]
        << (msg.data[3] & 0x80 ? " KPH" : " MPH") << endl;
}


/// Rear drive unit info
void process0106(canhacks::tCAN& msg)
{
   cout << "Rear drive motor RPM: "
        << canhacks::fixedDecode<int16_t>(&msg.data[4], 1, 0, 0) << endl
        << "Pedal position: " << (msg.data[6] * .4) << endl;
}


/// Front drive unit info
void process01d4(canhacks::tCAN& msg)
{
   
}


void process(canhacks::tCAN& msg)
{
   using namespace canhacks;
      /// @todo make the motor config a cmd-line option
   CANMessage *can = canDecoder(msg, mcSingleMotor);
   if (can == NULL)
   {
      processDefault(msg);
   }
   else
   {
      cout << can->dump() << endl;
      delete can;
   }
}


int main(int argc, char* argv[0])
{
   canhacks::tCAN msg;

   if (argc != 2)
   {
      cerr << "usage: canhexdump input-file" << endl;
      return 1;
   }
   ifstream inp(argv[1]);
   if (!inp)
   {
      cerr << "Unable to open \"" << argv[1] << "\" for input" << endl;
      return 1;
   }

   inp.read((char*)&msg, sizeof(msg));
   while (inp)
   {
      process(msg);
      inp.read((char*)&msg, sizeof(msg));
   }

   return 0;
}
