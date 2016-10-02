#ifndef CANDECODER_HPP
#define CANDECODER_HPP

#include "tcan.hpp"
#include "teslacan.hpp"
#include "CANMessage.hpp"

namespace canhacks
{
   CANMessage* canDecoder(tCAN& msg, MotorConfig cfg);
}

#endif // CANDECODER_HPP
