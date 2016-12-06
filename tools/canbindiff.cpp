#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <map>
#include <stdint.h>
#include <string.h>
#include "tcan.hpp"

using namespace std;

int main(int argc, char* argv[0])
{
   canhacks::tCAN msg;
   uint32_t timeMS;
   typedef list<canhacks::tCAN> MsgList;
   map<unsigned, MsgList> msgColl;
   map<unsigned, MsgList>::iterator mci;
   map<unsigned, canhacks::tCAN> msgUniq;
   map<unsigned, canhacks::tCAN>::iterator mui;

   if (argc != 2)
   {
      cerr << "usage: canbindiff input-file" << endl;
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
      msgColl[msg.id].push_back(msg);
      inp.read((char*)&timeMS, sizeof(timeMS));
      inp.read((char*)&msg, sizeof(msg));
   }

   for (mci = msgColl.begin(); mci != msgColl.end(); mci++)
   {
      MsgList::iterator mli;
         // clear our "changed bits" message
      memset(&msgUniq[mci->first], 0, sizeof(canhacks::tCAN));
      canhacks::tCAN prev;
      for (mli = mci->second.begin(); mli != mci->second.end(); mli++)
      {
         if (mli == mci->second.begin())
         {
               // First message, just save it and move on to the next
               // to establish a reference for comparison.
            prev = *mli;
            continue;
         }
         for (unsigned i = 0; i < mli->header.length; i++)
         {
               // any bits changed between the current and previous
               // message will be set in msgUniq
            msgUniq[mci->first].data[i] |= prev.data[i] ^ mli->data[i];
         }
      }
   }

   cout << "msg  ................1.......2.......3.......4.......4.......5....... count" << endl
        << "     0.......8.......6.......4.......2.......0.......8.......6......." << endl
        << "---- ---------------------------------------------------------------- ------" << endl;
   for (mui = msgUniq.begin(); mui != msgUniq.end(); mui++)
   {
      cout << setw(4) << hex << mui->first << dec << " ";
      for (unsigned i = 0; i < 8; i++)
      {
         for (unsigned j = 0; j < 8; j++)
         {
            cout << (mui->second.data[i] & 0x01);
            mui->second.data[i] >>= 1;
         }
      }
      cout << " " << setw(6) << msgColl[mui->first].size() << endl;
   }

   return 0;
}
