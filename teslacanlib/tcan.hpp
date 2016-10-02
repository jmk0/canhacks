#ifndef TCAN_HPP
#define TCAN_HPP

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

#endif // TCAN_HPP
