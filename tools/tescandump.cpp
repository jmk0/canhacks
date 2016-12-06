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
   uint32_t timeMS;

   if (argc != 2)
   {
      cerr << "usage: tescandump input-file" << endl;
      return 1;
   }
   ifstream inp(argv[1]);
   if (!inp)
   {
      cerr << "Unable to open \"" << argv[1] << "\" for input" << endl;
      return 1;
   }

   inp.read((char*)&timeMS, sizeof(timeMS));
   inp.read((char*)&msg, sizeof(msg));
   while (inp)
   {
      cout << "time " << timeMS << " ms" << endl;
      process(msg);
      inp.read((char*)&timeMS, sizeof(timeMS));
      inp.read((char*)&msg, sizeof(msg));
   }

   return 0;
}
