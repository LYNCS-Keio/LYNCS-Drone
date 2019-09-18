#pragma once

#define DPS_310_SPI_MODE        3
#define DPS_310_SPI_CLOCK       10000000  // 10 MHz

#define SCALE_FACTOR_1          524288
#define SCALE_FACTOR_2          1572864
#define SCALE_FACTOR_4          3670016
#define SCALE_FACTOR_8          7864320
//enable pressure or temperature shift
#define SCALE_FACTOR_16         253952
//enable pressure or temperature shift
#define SCALE_FACTOR_32         516096
//enable pressure or temperature shift
#define SCALE_FACTOR_64         1040384
//enable pressure or temperature shift
#define SCALE_FACTOR_128        2088960

#define REG_PSR_B2              0x00
#define REG_PSR_B1              0x01
#define REG_PSR_B0              0x02
#define REG_TMP_B2              0x03
#define REG_TMP_B1              0x04
#define REG_TMP_B0              0x05
#define REG_PSR_CFG             0x06
#define REG_TMP_CFG             0x07
#define REG_MEAS_CFG            0x08
#define REG_CFG_REG             0x09
#define REG_INT_STS             0x0A
#define REG_FIFO_STS            0x0B
#define REG_RESET               0x0C
#define REG_PRODUCT_ID          0x0D
#define REG_COEF                0x10
#define REG_TMP_COEF_SRCE       0x28