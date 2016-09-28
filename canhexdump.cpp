#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdint.h>
#include <string.h>

using namespace std;

// make sure the compiler doesn't change the size of the structure
// we're reading off disk.
#pragma pack(push,1)
typedef struct
{
   uint16_t id;
   struct {
      int8_t rtr : 1;
      uint8_t length : 4;
   } header;
   uint8_t data[8];
} tCAN;

int main(int argc, char* argv[0])
{
   tCAN msg;
      /* This was to verify the consistency of the data structure between
       * Arduino and the x86 g++ compiler.
       printf("&msg=%x size=%d offset.id=%d offset_header=%d\n",
       &msg, sizeof(msg), (char*)&msg.id - (char*)&msg, 
       (char*)&msg.header - (char*)&msg);
       printf("msg.header.size=%d offset_data=%d\n",
       sizeof(msg.header), (char*)msg.data - (char*)&msg);
      */

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
      cout << setw(4) << hex << msg.id << dec
           << " " << setw(2) << (int)msg.header.rtr
           << " " << setw(2) << (unsigned)msg.header.length;
      for (unsigned i = 0; i < msg.header.length; i++)
      {
         cout << " " << setw(2) << setfill('0') << hex << (unsigned)msg.data[i]
              << dec << setfill(' ');
      }
      cout << endl;
      inp.read((char*)&msg, sizeof(msg));
   }
   return 0;
}
