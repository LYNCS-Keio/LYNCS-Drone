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
////////Data Registers for Read and Write/////////////////////////////////////////
#define AC_GY_DATA_REG 0x3b
#define COMPASS_DATA_REG ST1 0x02
#define SPI_W 0x80
////////Constants////////////////////////////////////////////////////////////////
float accRange;
float gyroRange;

uint8_t accGyroTempData[14]={0};
uint8_t magneticData[7]={0};
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
    SPI.transfer(reg|SPI_W);
    data = SPI.transfer(0x00);
  digitalWrite(CS, HIGH);
return data;
};

////////spiWrite////////////////////////////////////////
void wry(uint8_t reg,uint8_t data){
  digitalWrite(CS, LOW);
  SPI.transfer(reg & B01111111);
  SPI.transfer(data); // write, bit 7 low
  digitalWrite(CS, HIGH);
};
////////spiStore///////////////////////////////////////
void spiStore(uint8_t reg,uint8_t Nbytes,uint8_t* data){
  digitalWrite(CS, LOW);
    SPI.transfer(reg|SPI_W);//move to header address adding the read/write command
    for(int i=0;i<Nbytes;i++)
    {data[i] = SPI.transfer(0xff);}
  digitalWrite(CS, HIGH);
};

//////////////MPU9250////////////////////////////////////////////
void MPU9250(){
  //Accel&Gyro read and store
    spiStore(AC_GY_DATA_REG,14,accGyroTempData);
  //Acc
    ax = (accGyroTempData[0] << 8) | accGyroTempData[1];//shift accGyroTempData[i] << 8，add(|) accGyroTempData[1] (Low byte of the data)
    ay = (accGyroTempData[2] << 8) | accGyroTempData[3];
    az = (accGyroTempData[4] << 8) | accGyroTempData[5];
  //Gyro
    gx = (accGyroTempData[8] << 8) | accGyroTempData[9];
    gy = (accGyroTempData[10] << 8) | accGyroTempData[11];
    gz = (accGyroTempData[12] << 8) | accGyroTempData[13];
  //Temp
    tempMPU9250Raw = (int16_t)((accGyroTempData[6] << 8) | accGyroTempData[7]);
  //calculate accel

    accX = ax * accRange / 32768.0;//[G]に変換
    accY = ay * accRange / 32768.0;//[G]に変換
    accZ = az * accRange / 32768.0;//[G]に変換
  //calculate gyro
    gyroX =gx * gyroRange / 32768.0;//[deg/s]に変換
    gyroY =gy * gyroRange / 32768.0;//[deg/s]に変換
    gyroZ =gz * gyroRange / 32768.0;//[deg/s]に変換

  //calculate temp
    tempMPU9250 = (tempMPU9250Raw - 0.0) / 333.87 + 21.0f;

  delay(10);
};

////////setup/////////////////////////////////////////////////////
void setup(){
  pinMode(CS, OUTPUT);
  pinMode(MOSI,OUTPUT);
  pinMode(MISO,INPUT);
  pinMode(SCLK,OUTPUT);

  digitalWrite(CS,HIGH);
  Serial.begin(115200);
  SPI.begin();

  delay(35);
  SPI.setClockDivider(SPI_CLOCK_DIV16);
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE3);

  wry(PWR_MGMT_1,0x00);
  wry(0x1a,0x00);
  wry(GYRO_CONFIG, 0x18);
  wry(ACCEL_CONFIG,0x18);
  gyroRange = 2000;
  accRange = 16.0;
  uint8_t j,k;
  j=spiRead(ACCEL_CONFIG);
  k=spiRead(GYRO_CONFIG);
  Serial.print(k);
  Serial.print(j);
  gyroRange = 2000;
  wry(INT_PIN_CFG,0x02);
  wry(CNTL1,CNTL1_MODE_SEL_100HZ);

};
////////loop////////////////////////////////////////////////////////
void loop(){
  MPU9250();

  Serial.print("ax: ");
  Serial.print(accX,4);
  Serial.print("\t");
  Serial.print("ay: ");
  Serial.print(accY,4);
  Serial.print("\t");
  Serial.print("az: ");
  Serial.print(accZ,4);
  Serial.print("\t");
  Serial.print("gx: ");
  Serial.print(gyroX,4);
  Serial.print("\t");
  Serial.print("gy: ");
  Serial.print(gyroY,4);
  Serial.print("\t");
  Serial.print("gz: ");
  Serial.print(gyroZ,4);
  Serial.print("\t");
  Serial.print("temp: ");
  Serial.println(tempMPU9250,4);

delay(5);

};
