#pragma once
#include <stdint.h>
namespace mpu
{
    typedef struct
    {
        uint8_t regAddress;
        uint8_t mask;
        uint8_t shift;
    } RegMask_t;

    typedef struct
    {
        uint8_t regAddress;
        uint8_t length;
    } RegBlock_t;
} // namespace mpu
