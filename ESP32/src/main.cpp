// =========================================================================
// This code is placed under the MIT License
// Copyright 2019 Laboratory of sYNsetic Cosmic Science. All rights reserved.
// For the license information refer to LICENSE file in root directory.
// =========================================================================

/**
 * @file main.cpp
 * Main function.
 */
 /*
  * VSPI
  * SCLK #18
  * MOSI #23
  * MISO #19
  * CS(SS) #5
  */

 #include <SPI.h>
 #include <Arduino.h>

 #define CS 5
 #define MISO 19
 #define MOSI 23
 #define SCLK 18
 ////////Reset Sensors/////////////////////////////////////////////////////////////////
 #define PWR_MGMT_1 0x6b
 #define INT_PIN_CFG 0x37
 ////////Acceleration Sensor Config//////////////////////////////////////////////
 #define ACCEL_CONFIG 0x1c
 #define ACCEL_FS_SEL_2G 0x00
 #define ACCEL_FS_SEL_4G 0x08
 #define ACCEL_FS_SEL_8G 0x10
 #define ACCEL_FS_SEL_16G 0x18
 ////////Gyro Sensor Config//////////////////////////////////////////////////////
 #define GYRO_CONFIG 0x1b
 #define GYRO_FS_SEL_250DPS 0x00
 #define GYRO_FS_SEL_500DPS 0x08
 #define GYRO_FS_SEL_1000DPS 0x10
 #define GYRO_FS_SEL_2000DPS 0x18
 ////////Magnetic Sensor Config//////////////////////////////////////////////////
 #define AK8963_ADDRESS 0x0c
 #define CNTL1 0x0a
 #define CNTL1_MODE_SEL_8HZ 0x12
 #define CNTL1_MODE_SEL_100HZ 0x16
 #define ST1 0x02
 ////////Data Registers for Read and Write///////////////////////////////////////////////////////////////
 #define AC_GY_DATA_REG 0x3b
 #define COMPASS_DATA_REG ST1 0x02
 #define SPI_RW 0x80
 ////////Constants////////////////////////////////////////////////////////////////
 float accRange;
 float gyroRange;

 uint8_t accGyroTempData[14];
 uint8_t magneticData[7];
 uint8_t ST1Bit;

 int16_t ax = 0;
 int16_t ay = 0;
 int16_t az = 0;
 int16_t gx = 0;
 int16_t gy = 0;
 int16_t gz = 0;
 int16_t tempMPU9250Raw = 0;
 int16_t mx = 0;
 int16_t my = 0;
 int16_t mz = 0;

 float accX = 0;
 float accY = 0;
 float accZ = 0;

 float gyroX = 0;
 float gyroY = 0;
 float gyroZ = 0;

 float tempMPU9250 = 0;

 float magX = 0;
 float magY = 0;
 float magZ = 0;

 float ofs_ax=0;
 float ofs_ay=0;
 float ofs_az=0;
 float ofs_gx=0;
 float ofs_gy=0;
 float ofs_gz=0;
 ////////spiread///////////////////////////////////////////
 uint8_t spiRead(uint8_t reg){
   uint8_t data;
   digitalWrite(CS, LOW);
     SPI.transfer(reg | SPI_RW);
     data = SPI.transfer(0x00);
   digitalWrite(CS, HIGH);
 return data;
 };


 ////////spiWrite////////////////////////////////////////
 void spiWrite(uint8_t reg,uint8_t data){
   digitalWrite(CS, LOW);
     SPI.transfer(reg | SPI_RW);
     SPI.transfer(data);
   digitalWrite(CS,HIGH);
 };


 ////////spiStore///////////////////////////////////////
 void spiStore(uint8_t reg,uint8_t Nbytes,uint8_t* data){
   digitalWrite(CS, LOW);
     SPI.transfer(reg | SPI_RW);//move to header address adding the read/write command
     for(int i=0;i<Nbytes;i++)
     {data[i] = SPI.transfer(0xff);}
   digitalWrite(CS, HIGH);

 };


 ////////MPU9250_setup////////////////////////////////////////
 void MPU9250_setup(){
   //Accel&Gyro read and store
     spiStore(AC_GY_DATA_REG,14,accGyroTempData);
       //Magnetic read and store
       //spiStoreM(ST1, 1);//読み出し準備ができたか確認
       //(COMPASS_DATA_REG, 7);//7番目の0x09(ST2)まで読まないとデータが更新されない
   //Acc
     ax = (int16_t)((accGyroTempData[0] << 8) | accGyroTempData[1]);//shift accGyroTempData[i] << 8，add(|) accGyroTempData[1] (Low byte of the data)
     ay = (int16_t)((accGyroTempData[2] << 8) | accGyroTempData[3]);
     az = (int16_t)((accGyroTempData[4] << 8) | accGyroTempData[5]);
   //Gyro
     gx = (int16_t)((accGyroTempData[8] << 8) | accGyroTempData[9]);
     gy = (int16_t)((accGyroTempData[10] << 8) | accGyroTempData[11]);
     gz = (int16_t)((accGyroTempData[12] << 8) | accGyroTempData[13]);
   //Magnetic
   /*
     mx = (magneticData[3] << 8) | magneticData[2];
     my = (magneticData[1] << 8) | magneticData[0];
     mz = -((magneticData[5] << 8) | magneticData[4]);//加速度，ジャイロセンサと軸の向きが逆
     */
   //Temp
     tempMPU9250Raw = (float)((accGyroTempData[6] << 8) | accGyroTempData[7]);
   //calculate accel
     accX = ax * accRange / 32768.0;//[G]に変換
     accY = ay * accRange / 32768.0;//[G]に変換
     accZ = az * accRange / 32768.0;//[G]に変換
   //calculate gyro
     gyroX = gx * gyroRange / 32768.0;//[deg/s]に変換
     gyroY = gy * gyroRange / 32768.0;//[deg/s]に変換
     gyroZ = gz * gyroRange / 32768.0;//[deg/s]に変換
   //calculate temp
     tempMPU9250 = ((tempMPU9250Raw - 0.0) / 333.87) + 21.0f;
   //calculate magnetic
   /*
     magX = mx / 32768.0f * 4800.0f;//[uT]に変換
     magY = my / 32768.0f * 4800.0f;//[uT]に変換
     magZ = mz / 32768.0f * 4800.0f;//[uT]に変換
   */
 }
 //////////////MPU9250////////////////////////////////////////////
 void MPU9250(){
   //Accel&Gyro read and store
     spiStore(AC_GY_DATA_REG,14,accGyroTempData);
       //Magnetic read and store
       //spiStoreM(ST1, 1);//読み出し準備ができたか確認
       //(COMPASS_DATA_REG, 7);//7番目の0x09(ST2)まで読まないとデータが更新されない
   //Acc
     ax = (int16_t)((accGyroTempData[0] << 8) | accGyroTempData[1]);//shift accGyroTempData[i] << 8，add(|) accGyroTempData[1] (Low byte of the data)
     ay = (int16_t)((accGyroTempData[2] << 8) | accGyroTempData[3]);
     az = (int16_t)((accGyroTempData[4] << 8) | accGyroTempData[5]);
   //Gyro
     gx = (int16_t)((accGyroTempData[8] << 8) | accGyroTempData[9]);
     gy = (int16_t)((accGyroTempData[10] << 8) | accGyroTempData[11]);
     gz = (int16_t)((accGyroTempData[12] << 8) | accGyroTempData[13]);
   //Magnetic
   /*
     mx = (magneticData[3] << 8) | magneticData[2];
     my = (magneticData[1] << 8) | magneticData[0];
     mz = -((magneticData[5] << 8) | magneticData[4]);//加速度，ジャイロセンサと軸の向きが逆
     */
   //Temp
     tempMPU9250Raw = (float)((accGyroTempData[6] << 8) | accGyroTempData[7]);
   //calculate accel
     accX = ax * accRange / 32768.0 - ofs_ax;//[G]に変換
     accY = ay * accRange / 32768.0 - ofs_ay;//[G]に変換
     accZ = az * accRange / 32768.0 - ofs_az;//[G]に変換
   //calculate gyro
     gyroX = gx * gyroRange / 32768.0 - ofs_gx;//[deg/s]に変換
     gyroY = gy * gyroRange / 32768.0 - ofs_gy;//[deg/s]に変換
     gyroZ = gz * gyroRange / 32768.0 - ofs_gz;//[deg/s]に変換
   //calculate temp
     tempMPU9250 = ((tempMPU9250Raw - 0.0) / 333.87) + 21.0f;
   //calculate magnetic
   /*
     magX = mx / 32768.0f * 4800.0f;//[uT]に変換
     magY = my / 32768.0f * 4800.0f;//[uT]に変換
     magZ = mz / 32768.0f * 4800.0f;//[uT]に変換
   */
 }




 ////////Measuring Offsets/////////////////////////////////////////int16_t ofs_ax,ofs_ay,ofs_az,ofs_gx,ofs_gy,ofs_gz
 void MeasureOffsetAcc(){
   int16_t sum_ax =0;
   int16_t sum_ay =0;
   int16_t sum_az =0;
   int16_t sum_gx =0;
   int16_t sum_gy =0;
   int16_t sum_gz =0;

   for(int i=0;i<1000;i++){
     MPU9250_setup();
     sum_ax += accX;
     sum_ay += accY;
     sum_az += accZ;
     sum_gx += gyroX;
     sum_gy += gyroY;
     sum_gz += gyroZ;
   }

   ofs_ax = sum_ax/1000;
   ofs_ay = sum_ay/1000;
   ofs_az = sum_az/1000;
   ofs_gx = sum_gx/1000;
   ofs_gy = sum_gy/1000;
   ofs_gz = sum_gz/1000;

 };


 ////////setup/////////////////////////////////////////////////////
 void setup(){
   delay(100);
   Serial.begin(9600);
   SPI.begin();

   SPI.setClockDivider(SPI_CLOCK_DIV16);
   SPI.setBitOrder(MSBFIRST);//SPIバスの入出力に使用するビットオーダー(LSBFIRST or MSBFIRST)
   SPI.setDataMode(SPI_MODE3);//SPIの転送モード


   spiWrite(PWR_MGMT_1,0x00);
   spiWrite(ACCEL_CONFIG,ACCEL_FS_SEL_16G);
   accRange = 16.0;
   spiWrite(GYRO_CONFIG, GYRO_FS_SEL_2000DPS);
   gyroRange = 2000;
   spiWrite(INT_PIN_CFG,0x02);
   spiWrite(CNTL1,CNTL1_MODE_SEL_100HZ);

   pinMode(CS, OUTPUT);
   MeasureOffsetAcc();
 };
 ////////loop////////////////////////////////////////////////////////
 void loop(){
   MPU9250();

   Serial.println(spiRead(0x75),HEX);//who am i
   Serial.print("ax: ");
   Serial.print(accX);
   Serial.print("\t");
   Serial.print("ay: ");
   Serial.print(accY);
   Serial.print("\t");
   Serial.print("az: ");
   Serial.print(accZ);
   Serial.print("\t");
   Serial.print("gx: ");
   Serial.print(gyroX);
   Serial.print("\t");
   Serial.print("gy: ");
   Serial.print(gyroY);
   Serial.print("\t");
   Serial.print("gz: ");
   Serial.print(gyroZ);
   Serial.print("\t");
   Serial.print("temp: ");
   Serial.print(tempMPU9250);
   /*
   Serial.println("\t");
   Serial.print("mx: ");
   Serial.print(magX);
   Serial.print("\t");
   Serial.print("my: ");
   Serial.print(magY);
   Serial.print("\t");
   Serial.print("mz: ");
   Serial.print(magZ);
   Serial.print("\t");
   */
 delay(500);

 };
