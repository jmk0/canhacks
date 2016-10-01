#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdint.h>
#include <string.h>
#include "tcan.hpp"

using namespace std;

/// @note this code assumes it's running on a little-endian (e.g. Intel) host.

/*
 * Big thanks to Jason Hughes for providing much of the information
 * used in decoding the Tesla CAN messages.
 */

// 0 = single motor, -10000 = dual motor
int16_t bpCurOfs = 0;

template <typename T>
double fixedDecode(uint8_t *startPtr, double scale, unsigned shift, T offset)
{
   T tmpValInt = *(T*)startPtr;
   tmpValInt += offset;
   if (shift)
   {
         // bit shift for sign extension or, for unsigned, crud removal
      tmpValInt <<= shift;
      tmpValInt >>= shift;
   }
   return tmpValInt * scale;
}

void processDefault(tCAN& msg)
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


void processQuiet(tCAN& msg)
{
      // do nothing, used to hide message IDs until I Implement processing
}


void process0102(tCAN& msg)
{
   cout << "Battery pack: "
        << fixedDecode<uint16_t>(&msg.data[0], .01, 0, 0) << "V "
        << fixedDecode<int16_t>(&msg.data[2], .1, 1, bpCurOfs) << "A "
        << fixedDecode<int16_t>(&msg.data[4], .1, 1, bpCurOfs) << "A ";
   if (msg.header.length == 8)
      cout << fixedDecode<int16_t>(&msg.data[6], .1, 1, 0) << "C";
   cout << endl;
}


void process0256(tCAN& msg)
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
        << "Speed: " << fixedDecode<uint16_t>(&msg.data[2], .1, 4, 0) << " MPH"
        << endl;
}


void process(tCAN& msg)
{
   switch (msg.id)
   {
      case 0x0102: process0102(msg);    break;
      case 0x0256: process0256(msg);    break;
      case 0x0106:
      case 0x01d4:
      case 0x0154:
      case 0x0266:
      case 0x02e5:
      case 0x0145:
      case 0x0116:
      case 0x0232:
      case 0x0562:
      case 0x03d2:
      case 0x0302:
      case 0x0382:
      case 0x0210:
         processQuiet(msg);   break;
      default:     processDefault(msg); break;
   }
}

int main(int argc, char* argv[0])
{
   tCAN msg;

/*   msg.id = 0x0102;
   msg.header.length = 8;
   msg.data[0] = 0x66;
   msg.data[1] = 0x97;
   msg.data[2] = 0xf8;
   msg.data[3] = 0xa6;
//   msg.data[2] = 0x9f;
//   msg.data[3] = 0x83;
   msg.data[4] = 0xf2;
   msg.data[5] = 0x4d;
   msg.data[6] = 0x28;
   msg.data[7] = 0x01;
   process(msg); */
/*
   int16_t poo = 0x8394;
   cerr << poo << " " << (poo * .1) << endl;
   poo = 0x9483;
   cerr << poo << " " << (poo * .1) << endl;
*/
//   return 0;

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
