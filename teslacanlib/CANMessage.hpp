#ifndef CANMESSAGE_HPP
#define CANMESSAGE_HPP

#include <string>
#include "tcan.hpp"

namespace canhacks
{
      /// Define a base class for CAN messages in engineering units.
   class CANMessage
   {
   public:
      CANMessage() {}
         /** Turn the binary CAN message into the message's engineering data.
          * @param[in] msg The binary CAN message to decode. */
      virtual void decode(tCAN& msg) = 0;
         /** Return a string containing a human-readable
          * representation of the message. */
      virtual std::string dump() = 0;
   };


      /** Generic decoding function for multi-byte quantities.  Can
       * also be used for single-byte quantities, albeit somewhat less
       * optimally.
       * @tparam T The integer data type used for decoding prior to
       *   scaling.  This should be a fixed bit size, e.g. uint16_t.
       * @param[in] startPtr A pointer to the first byte in the
       *   message to be decoded.
       * @param[in] scale A scale value to multiply the integer
       *   quantity by to get the correct precision of the engineering
       *   units value before returning.
       * @param[in] leftShift The integer quantity will be shifted
       *   left by this number of bits before being right shifted (see
       *   rightShift).
       * @param[in] rightShift The integer quantity will be shifted
       *   right by this number of bits before being scaled and
       *   returned.
       * @param[in] offset A value added to the integer quantity prior
       *   to scaling.
       */
   template <typename T>
   double fixedDecode(uint8_t *startPtr, double scale, unsigned leftShift,
                      unsigned rightShift, T offset)
   {
      T tmpValInt = *(T*)startPtr;
      tmpValInt += offset;
         // bit shift for sign extension or, for unsigned, crud removal
      if (leftShift)
         tmpValInt <<= leftShift;
      if (rightShift)
         tmpValInt >>= rightShift;
      return tmpValInt * scale;
   }


      /** Generic decoding function for multi-byte quantities.  Can
       * also be used for single-byte quantities, albeit somewhat less
       * optimally.
       * @tparam T The integer data type used for decoding prior to
       *   scaling.  This should be a fixed bit size, e.g. uint16_t.
       * @param[in] startPtr A pointer to the first byte in the
       *   message to be decoded.
       * @param[in] scale A scale value to multiply the integer
       *   quantity by to get the correct precision of the engineering
       *   units value before returning.
       * @param[in] shift Number of most significant bits in the bytes
       *   that are not part of the value.  For example, there might
       *   be a 12-bit value stored in the 12 LSBs of a 16-bit word.
       *   In that case, a "shift" of 4 would remove those four excess
       *   bits from the integer quantity, and, in the case of a
       *   signed quantity, xtend the sign bit appropriately.
       * @param[in] offset A value added to the integer quantity prior
       *   to scaling.
       */
   template <typename T>
   double fixedDecode(uint8_t *startPtr, double scale, unsigned shift,
                      T offset)
   {
      return fixedDecode<T>(startPtr, scale, shift, shift, offset);
   }
}

#endif // CANMESSAGE_HPP
