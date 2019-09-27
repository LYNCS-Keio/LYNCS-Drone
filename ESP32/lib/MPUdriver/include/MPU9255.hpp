#pragma once
#include "MPU.hpp"
namespace mpu9255
{
    using namespace mpu;
    class MPU9255 : public MPU
    {
    private:
        /* data */
    public:
        MPU9255(mpu_bus_t* bus);
        ~MPU9255();
    };
    
} // namespace mpu9255
