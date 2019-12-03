EESchema Schematic File Version 4
LIBS:Drone-cache
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text GLabel 7150 4750 2    50   Input ~ 0
GPIO14
Text GLabel 7150 4550 2    50   Input ~ 0
GPIO12
Text GLabel 7150 4650 2    50   Input ~ 0
GPIO13
Text GLabel 7150 5550 2    50   Input ~ 0
GPIO23
Text GLabel 7150 5350 2    50   Input ~ 0
GPIO21
Text GLabel 7150 5250 2    50   Input ~ 0
GPIO19
Text GLabel 7150 5150 2    50   Input ~ 0
GPIO18
Text GLabel 7150 4450 2    50   Input ~ 0
GPIO5
Text GLabel 7150 5050 2    50   Input ~ 0
GPIO17
Text GLabel 7150 4950 2    50   Input ~ 0
GPIO16
Text GLabel 7150 4350 2    50   Input ~ 0
GPIO4
Text GLabel 7150 4850 2    50   Input ~ 0
GPIO15
$Comp
L Connector:Conn_01x10_Female J8
U 1 1 5D6C73AD
P 10250 2650
F 0 "J8" H 10278 2626 50  0000 L CNN
F 1 "MPU9250" H 10278 2535 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x10_P2.54mm_Vertical" H 10250 2650 50  0001 C CNN
F 3 "~" H 10250 2650 50  0001 C CNN
	1    10250 2650
	1    0    0    -1  
$EndComp
Text GLabel 9800 2250 0    50   Input ~ 0
MPU_VCC
Text GLabel 9800 2350 0    50   Input ~ 0
GND
Text GLabel 9800 2450 0    50   Input ~ 0
SCL
Text GLabel 9800 2550 0    50   Input ~ 0
SDA
Text GLabel 9800 2850 0    50   Input ~ 0
ADO
Text GLabel 9800 3050 0    50   Input ~ 0
NCS
Text GLabel 9800 3150 0    50   Input ~ 0
FSYNC
Wire Wire Line
	9800 3150 10050 3150
Wire Wire Line
	10050 3050 9800 3050
Wire Wire Line
	9800 2950 10050 2950
Wire Wire Line
	10050 2850 9800 2850
Wire Wire Line
	9800 2750 10050 2750
Wire Wire Line
	10050 2650 9800 2650
Wire Wire Line
	9800 2550 10050 2550
Wire Wire Line
	10050 2450 9800 2450
Wire Wire Line
	9800 2350 10050 2350
Wire Wire Line
	10050 2250 9800 2250
Text Notes 9600 2100 0    50   ~ 0
MPU9250
$Comp
L Connector:Conn_01x02_Female J2
U 1 1 5D6D62E2
P 2650 1300
F 0 "J2" H 2678 1276 50  0000 L CNN
F 1 "BATTRY" H 2678 1185 50  0000 L CNN
F 2 "RC-Battery-Connectors:XT-60_female" H 2650 1300 50  0001 C CNN
F 3 "~" H 2650 1300 50  0001 C CNN
	1    2650 1300
	-1   0    0    1   
$EndComp
Text Notes 2600 1050 0    50   ~ 0
Battery
Wire Wire Line
	2850 1200 3000 1200
Text GLabel 3450 1350 2    50   Input ~ 0
GND
$Comp
L Regulator_Switching:LM2596T-5 U1
U 1 1 5D7F1935
P 2100 2450
F 0 "U1" H 2100 2817 50  0000 C CNN
F 1 "LM2596T-5" H 2100 2726 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-5_Horizontal_TabDown" H 2150 2200 50  0001 L CIN
F 3 "http://www.ti.com/lit/ds/symlink/lm2596.pdf" H 2100 2450 50  0001 C CNN
	1    2100 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 2550 1450 2550
Wire Wire Line
	1450 2550 1450 2800
Wire Wire Line
	1450 2800 1300 2800
Connection ~ 1450 2800
Wire Wire Line
	1600 2350 1300 2350
Text GLabel 1200 2350 0    50   Input ~ 0
BAT
Text GLabel 1200 2800 0    50   Input ~ 0
GND
$Comp
L Device:C_Small C1
U 1 1 5D7FFBCB
P 1300 2550
F 0 "C1" H 1392 2596 50  0000 L CNN
F 1 "47u" H 1392 2505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 1300 2550 50  0001 C CNN
F 3 "~" H 1300 2550 50  0001 C CNN
	1    1300 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 2650 1300 2800
Connection ~ 1300 2800
Wire Wire Line
	1300 2800 1200 2800
Wire Wire Line
	1300 2450 1300 2350
Connection ~ 1300 2350
Wire Wire Line
	1300 2350 1200 2350
Wire Wire Line
	2600 2550 2750 2550
$Comp
L Device:D_Schottky_Small D2
U 1 1 5D805B17
P 2750 2700
F 0 "D2" V 2704 2768 50  0000 L CNN
F 1 "SS2040FL" V 2795 2768 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123F" V 2750 2700 50  0001 C CNN
F 3 "~" V 2750 2700 50  0001 C CNN
	1    2750 2700
	0    1    1    0   
$EndComp
Wire Wire Line
	2750 2600 2750 2550
Wire Wire Line
	2750 2550 2900 2550
Connection ~ 2750 2550
$Comp
L pspice:INDUCTOR L1
U 1 1 5D80C70F
P 3150 2550
F 0 "L1" H 3150 2765 50  0000 C CNN
F 1 "989BS-270M" H 3150 2674 50  0000 C CNN
F 2 "Inductor_SMD:L_12x12mm_H6mm" H 3150 2550 50  0001 C CNN
F 3 "~" H 3150 2550 50  0001 C CNN
	1    3150 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 2550 3550 2550
$Comp
L Device:C_Small C2
U 1 1 5D80F134
P 3550 2700
F 0 "C2" H 3642 2746 50  0000 L CNN
F 1 "22u" H 3642 2655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3550 2700 50  0001 C CNN
F 3 "~" H 3550 2700 50  0001 C CNN
	1    3550 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 2600 3550 2550
Connection ~ 3550 2550
Wire Wire Line
	2750 2800 3550 2800
Connection ~ 2750 2800
Wire Wire Line
	3550 2550 3550 2350
Wire Wire Line
	3550 2350 2600 2350
Text GLabel 4700 2550 2    50   Input ~ 0
5V
Text GLabel 8950 2250 2    50   Input ~ 0
MPU_VCC
Text GLabel 8650 2250 0    50   Input ~ 0
3V3
Wire Wire Line
	8650 2250 8950 2250
Text Notes 1500 2050 2    50   ~ 0
11Vto5VReg
Text Notes 3050 3350 2    50   ~ 0
Raspberry Pi 3
Wire Wire Line
	3700 3700 3700 3800
Wire Wire Line
	3700 3700 3950 3700
Text GLabel 3950 3700 2    50   Input ~ 0
5V
Text GLabel 3950 3900 2    50   Input ~ 0
GND
Wire Wire Line
	3950 3900 3800 3900
Text GLabel 2950 4100 0    50   Input ~ 0
GND
Wire Wire Line
	2950 4100 3100 4100
Wire Wire Line
	3800 4600 3700 4600
Connection ~ 3800 3900
Wire Wire Line
	3800 3900 3700 3900
Wire Wire Line
	3800 4300 3700 4300
Wire Wire Line
	3800 3900 3800 4300
Connection ~ 3800 4300
Wire Wire Line
	3800 4300 3800 4600
Wire Wire Line
	3800 4600 3800 5100
Wire Wire Line
	3800 5100 3700 5100
Connection ~ 3800 4600
Wire Wire Line
	3800 5100 3800 5300
Wire Wire Line
	3800 5300 3700 5300
Connection ~ 3800 5100
Wire Wire Line
	3200 5600 3100 5600
Connection ~ 3100 4100
Wire Wire Line
	3100 4100 3200 4100
Wire Wire Line
	3100 4900 3200 4900
Connection ~ 3100 4900
Text GLabel 2950 3700 0    50   Input ~ 0
3V3
Wire Wire Line
	3000 3700 3000 4500
Connection ~ 3000 3700
Wire Wire Line
	3000 3700 2950 3700
Wire Wire Line
	3700 4000 3950 4000
Wire Wire Line
	3700 4100 3950 4100
Text GLabel 3950 4000 2    50   Input ~ 0
PI_UART_TX
Text GLabel 3950 4100 2    50   Input ~ 0
PI_UART_RX
Text GLabel 8950 2400 2    50   Input ~ 0
SDA
Text GLabel 8950 2550 2    50   Input ~ 0
ADO
Wire Wire Line
	8650 2550 8950 2550
Text Notes 8300 2600 2    50   ~ 0
MISO
Text Notes 8300 2450 2    50   ~ 0
MOSI
Text GLabel 8650 2550 0    50   Input ~ 0
GPIO19
Wire Wire Line
	8650 2400 8950 2400
Text GLabel 1050 5950 0    50   Input ~ 0
GPIO21
Text GLabel 8950 2700 2    50   Input ~ 0
SCL
Wire Wire Line
	8950 2700 8650 2700
Text GLabel 8650 2700 0    50   Input ~ 0
GPIO18
Text GLabel 8950 2850 2    50   Input ~ 0
NCS
Text GLabel 8650 2850 0    50   Input ~ 0
GPIO5
Wire Wire Line
	8650 2850 8950 2850
Text Notes 8300 2750 2    50   ~ 0
CLK
Text Notes 8300 2900 2    50   ~ 0
SS
Text Notes 9150 2150 2    50   ~ 0
SPI master:ESP32 slave:MPU9250\nusing vspi
Text GLabel 2950 4600 0    50   Input ~ 0
PI_GPIO10
Text GLabel 2950 4700 0    50   Input ~ 0
PI_GPIO9
Text GLabel 2950 4800 0    50   Input ~ 0
PI_GPIO11
Wire Wire Line
	3700 4800 3950 4800
Text GLabel 3950 4800 2    50   Input ~ 0
PI_GPIO8
Text GLabel 4750 2100 2    50   Input ~ 0
GPIO15
Text GLabel 8650 4500 0    50   Input ~ 0
GPIO14
Text GLabel 8650 1200 0    50   Input ~ 0
GPIO13
Text GLabel 8650 1100 0    50   Input ~ 0
GPIO12
Text Notes 4300 5850 2    50   ~ 0
uart RPI3 to ESP32
Text Notes 10050 3750 2    50   ~ 0
DPS310
Wire Wire Line
	9850 4000 9700 4000
Text GLabel 9700 4000 0    50   Input ~ 0
GND
Text GLabel 10800 4000 2    50   Input ~ 0
VDD
Text GLabel 10800 4100 2    50   Input ~ 0
VDDIO
Text GLabel 10800 4200 2    50   Input ~ 0
CSBN
Text GLabel 10800 4300 2    50   Input ~ 0
GND
Text GLabel 9700 4100 0    50   Input ~ 0
SDO
Text GLabel 9700 4200 0    50   Input ~ 0
SCK
Text GLabel 9700 4300 0    50   Input ~ 0
SDI
Wire Wire Line
	9700 4300 9850 4300
Wire Wire Line
	9850 4200 9700 4200
Wire Wire Line
	9700 4100 9850 4100
Wire Wire Line
	10650 4000 10800 4000
Wire Wire Line
	10800 4100 10650 4100
Wire Wire Line
	10650 4200 10800 4200
Wire Wire Line
	10800 4300 10650 4300
Text GLabel 8650 3750 0    50   Input ~ 0
3V3
Wire Wire Line
	8950 3750 8850 3750
Text GLabel 8950 3750 2    50   Input ~ 0
VDD
Text GLabel 8950 3900 2    50   Input ~ 0
VDDIO
Wire Wire Line
	8950 3900 8850 3900
Wire Wire Line
	8850 3900 8850 3750
Connection ~ 8850 3750
Wire Wire Line
	8850 3750 8650 3750
Text Notes 8300 4400 2    50   ~ 0
CLK
Text GLabel 8650 4350 0    50   Input ~ 0
GPIO18
Text Notes 8300 4100 2    50   ~ 0
MOSI
Text Notes 8300 4250 2    50   ~ 0
MISO
Text GLabel 8950 4200 2    50   Input ~ 0
SDO
Text GLabel 8950 4050 2    50   Input ~ 0
SDI
Wire Wire Line
	8950 4050 8650 4050
Wire Wire Line
	8650 4200 8950 4200
Text GLabel 8950 4350 2    50   Input ~ 0
SCK
Wire Wire Line
	8950 4350 8650 4350
Text GLabel 8950 4500 2    50   Input ~ 0
CSBN
Wire Wire Line
	8950 4500 8650 4500
Text Notes 8300 4550 2    50   ~ 0
SS
$Comp
L Connector:Conn_01x04_Female J7
U 1 1 5D6CA05D
P 10250 1100
F 0 "J7" H 10278 1076 50  0000 L CNN
F 1 "US-015" H 10278 985 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical" H 10250 1100 50  0001 C CNN
F 3 "~" H 10250 1100 50  0001 C CNN
	1    10250 1100
	1    0    0    -1  
$EndComp
Text GLabel 9800 1000 0    50   Input ~ 0
US_VCC
Text GLabel 9800 1100 0    50   Input ~ 0
Trig
Text GLabel 9800 1200 0    50   Input ~ 0
Echo
Text GLabel 9800 1300 0    50   Input ~ 0
GND
Wire Wire Line
	9800 1300 10050 1300
Wire Wire Line
	10050 1200 9800 1200
Wire Wire Line
	9800 1100 10050 1100
Wire Wire Line
	10050 1000 9800 1000
Text Notes 9600 850  0    50   ~ 0
US-015
Text GLabel 9100 1000 2    50   Input ~ 0
US_VCC
Wire Wire Line
	9100 1000 8650 1000
Text GLabel 8650 1000 0    50   Input ~ 0
5V
Text GLabel 9100 1100 2    50   Input ~ 0
Trig
Wire Wire Line
	8650 1100 9100 1100
Text GLabel 9100 1200 2    50   Input ~ 0
Echo
Wire Wire Line
	8650 1200 9100 1200
Text GLabel 3900 1650 0    50   Input ~ 0
PWM1
Text GLabel 3900 1800 0    50   Input ~ 0
PWM2
Text GLabel 3900 1950 0    50   Input ~ 0
PWM3
Text GLabel 3900 2100 0    50   Input ~ 0
PWM4
Wire Wire Line
	3900 1800 4100 1800
Wire Wire Line
	3900 2100 4300 2100
Text GLabel 9600 6100 0    50   Input ~ 0
GND
$Comp
L Device:C_Small C3
U 1 1 5D7EFA83
P 9900 5900
F 0 "C3" V 10129 5900 50  0000 C CNN
F 1 "1u" V 10038 5900 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 9900 5900 50  0001 C CNN
F 3 "~" H 9900 5900 50  0001 C CNN
	1    9900 5900
	-1   0    0    1   
$EndComp
Wire Wire Line
	9900 5800 9900 5750
Text GLabel 4750 1950 2    50   Input ~ 0
GPIO4
Text GLabel 1850 4050 2    50   Input ~ 0
PWM1
Text GLabel 1850 4150 2    50   Input ~ 0
PWM2
Text GLabel 1850 4250 2    50   Input ~ 0
PWM3
Text GLabel 1850 4350 2    50   Input ~ 0
PWM4
$Comp
L Connector:Conn_01x06_Female J1
U 1 1 5D8394B4
P 1250 4050
F 0 "J1" H 1142 4435 50  0000 C CNN
F 1 "ESC" H 1142 4344 50  0000 C CNN
F 2 "Connector_JST:JST_SH_BM06B-SRSS-TB_1x06-1MP_P1.00mm_Vertical" H 1250 4050 50  0001 C CNN
F 3 "~" H 1250 4050 50  0001 C CNN
	1    1250 4050
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1850 4050 1450 4050
Wire Wire Line
	1450 4150 1850 4150
Wire Wire Line
	1850 4250 1450 4250
Wire Wire Line
	1450 4350 1850 4350
Text Notes 1250 3600 0    50   ~ 0
ESC
Text GLabel 1050 6250 0    50   Input ~ 0
ESC_VIN
Text GLabel 1250 6250 2    50   Input ~ 0
BAT
$Comp
L Connector:Conn_01x04_Female J6
U 1 1 5D8A1E50
P 10050 4100
F 0 "J6" H 10078 4076 50  0000 L CNN
F 1 "DPS310_LEFT" H 10078 3985 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical" H 10050 4100 50  0001 C CNN
F 3 "~" H 10050 4100 50  0001 C CNN
	1    10050 4100
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Female J9
U 1 1 5D8A24A8
P 10450 4100
F 0 "J9" H 10342 4385 50  0000 C CNN
F 1 "DPS310_RIGHT" H 10342 4294 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical" H 10450 4100 50  0001 C CNN
F 3 "~" H 10450 4100 50  0001 C CNN
	1    10450 4100
	-1   0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Female U2
U 1 1 5D708C9C
P 2700 6050
F 0 "U2" H 2400 6250 50  0000 L CNN
F 1 "SKI03021" H 2550 6250 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:TO-263-3_TabPin4" H 2700 6050 50  0001 C CNN
F 3 "~" H 2700 6050 50  0001 C CNN
	1    2700 6050
	1    0    0    -1  
$EndComp
Text Notes 1200 5450 0    50   ~ 0
SKI03021 PowerMOSFET
Wire Wire Line
	1450 2800 2100 2800
Wire Wire Line
	2100 2750 2100 2800
Connection ~ 2100 2800
Wire Wire Line
	2100 2800 2750 2800
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5D79ADAC
P 3350 1350
F 0 "#FLG0101" H 3350 1425 50  0001 C CNN
F 1 "PWR_FLAG" H 3350 1523 50  0000 C CNN
F 2 "" H 3350 1350 50  0001 C CNN
F 3 "~" H 3350 1350 50  0001 C CNN
	1    3350 1350
	-1   0    0    1   
$EndComp
Connection ~ 3350 1350
Wire Wire Line
	3350 1350 3450 1350
$Comp
L Device:D_Schottky_Small D1
U 1 1 5D7B59B4
P 3150 1250
F 0 "D1" V 3104 1318 50  0000 L CNN
F 1 "SS2040FL" V 3195 1318 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123F" V 3150 1250 50  0001 C CNN
F 3 "~" V 3150 1250 50  0001 C CNN
	1    3150 1250
	0    1    1    0   
$EndComp
Wire Wire Line
	3150 1350 3350 1350
Wire Wire Line
	3000 1150 3150 1150
Wire Wire Line
	3350 1150 3450 1150
Connection ~ 3350 1150
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 5D79BE2D
P 3350 1150
F 0 "#FLG0102" H 3350 1225 50  0001 C CNN
F 1 "PWR_FLAG" H 3350 1323 50  0000 C CNN
F 2 "" H 3350 1150 50  0001 C CNN
F 3 "~" H 3350 1150 50  0001 C CNN
	1    3350 1150
	1    0    0    -1  
$EndComp
Text GLabel 3450 1150 2    50   Input ~ 0
BAT
Connection ~ 3150 1150
Wire Wire Line
	3150 1150 3350 1150
Wire Wire Line
	3150 1350 3000 1350
Wire Wire Line
	3000 1350 3000 1300
Wire Wire Line
	3000 1300 2850 1300
Connection ~ 3150 1350
Wire Wire Line
	3000 1200 3000 1150
$Comp
L Connector:Conn_01x02_Female J10
U 1 1 5D71E71C
P 1600 4950
F 0 "J10" H 1492 4625 50  0000 C CNN
F 1 "to ESC Power" H 1492 4716 50  0000 C CNN
F 2 "RC-Battery-Connectors:XT-60_female" H 1600 4950 50  0001 C CNN
F 3 "~" H 1600 4950 50  0001 C CNN
	1    1600 4950
	-1   0    0    1   
$EndComp
Text GLabel 2000 4850 2    50   Input ~ 0
ESC_VIN
Text GLabel 2000 4950 2    50   Input ~ 0
ESC_GND
Wire Wire Line
	2000 4950 1800 4950
Wire Wire Line
	1800 4850 2000 4850
Text Notes 1250 4550 0    50   ~ 0
to ESC XT60 connector
Text Notes 9150 3650 2    50   ~ 0
SPI master:ESP32 slave:DPS310\nusing vspi
Text GLabel 3950 4400 2    50   Input ~ 0
PI_PIGPIO_TX
Wire Wire Line
	3950 4400 3700 4400
Text GLabel 3950 4500 2    50   Input ~ 0
PI_PIGPIO_RX
Wire Wire Line
	3950 4500 3700 4500
Text Notes 3200 6150 0    50   ~ 0
TX
Text Notes 3200 6250 0    50   ~ 0
RX
Text Notes 4750 6150 0    50   ~ 0
RX
Text Notes 4750 6250 0    50   ~ 0
TX
Text GLabel 3950 6200 0    50   Input ~ 0
PI_UART_RX
Text GLabel 3950 6100 0    50   Input ~ 0
PI_UART_TX
Text GLabel 4750 1650 2    50   Input ~ 0
GPIO17
Text GLabel 4750 1800 2    50   Input ~ 0
GPIO16
Wire Wire Line
	3100 5600 3100 4900
Wire Wire Line
	3200 4800 2950 4800
Wire Wire Line
	2950 4700 3200 4700
Wire Wire Line
	3200 4600 2950 4600
Wire Wire Line
	3200 3700 3000 3700
Wire Wire Line
	3000 4500 3200 4500
Wire Wire Line
	3100 4900 3100 4100
$Comp
L Connector_Generic:Conn_02x20_Odd_Even J4
U 1 1 5D829EEE
P 3500 4600
F 0 "J4" H 3550 5717 50  0000 C CNN
F 1 "Raspberry Pi" H 3550 5626 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x20_P2.54mm_Vertical" H 3500 4600 50  0001 C CNN
F 3 "~" H 3500 4600 50  0001 C CNN
	1    3500 4600
	-1   0    0    -1  
$EndComp
Connection ~ 3700 3700
Text GLabel 8650 4050 0    50   Input ~ 0
GPIO23
Text GLabel 8650 2400 0    50   Input ~ 0
GPIO23
Text GLabel 8650 4200 0    50   Input ~ 0
GPIO19
Text Notes 800  900  0    50   ~ 0
Anothor 5V power source
Text GLabel 1600 1200 2    50   Input ~ 0
5V
Wire Wire Line
	1600 1200 1350 1200
$Comp
L Connector:Conn_01x02_Female J11
U 1 1 5D86C630
P 1150 1300
F 0 "J11" H 1042 975 50  0000 C CNN
F 1 "Conn_01x02_Female" H 1042 1066 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 1150 1300 50  0001 C CNN
F 3 "~" H 1150 1300 50  0001 C CNN
	1    1150 1300
	-1   0    0    1   
$EndComp
Text GLabel 1600 1300 2    50   Input ~ 0
GND
Wire Wire Line
	1600 1300 1350 1300
Text Notes 2800 6000 0    50   ~ 0
GATE
Text Notes 2800 6100 0    50   ~ 0
DRAIN
Text Notes 2800 6200 0    50   ~ 0
SOURCE
Wire Wire Line
	2500 6250 2350 6250
Wire Wire Line
	2250 6150 2500 6150
Wire Wire Line
	2500 6050 2350 6050
Wire Wire Line
	2350 6250 2350 6050
Wire Wire Line
	1250 6250 1050 6250
Text GLabel 2250 6350 3    50   Input ~ 0
ESC_GND
$Comp
L Device:R_Small R2
U 1 1 5DCE3F7E
P 1950 6150
F 0 "R2" H 2009 6196 50  0000 L CNN
F 1 "10k" H 2009 6105 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 1950 6150 50  0001 C CNN
F 3 "~" H 1950 6150 50  0001 C CNN
	1    1950 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 6150 2250 6350
$Comp
L Device:D_Schottky_Small D4
U 1 1 5DD5F165
P 1700 6150
F 0 "D4" V 1654 6218 50  0000 L CNN
F 1 "SS2040FL" H 1600 6050 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123F" V 1700 6150 50  0001 C CNN
F 3 "~" V 1700 6150 50  0001 C CNN
	1    1700 6150
	0    1    1    0   
$EndComp
$Comp
L Device:D_Schottky_Small D3
U 1 1 5DD79C14
P 1700 5750
F 0 "D3" V 1654 5818 50  0000 L CNN
F 1 "SS2040FL" H 1500 5650 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123F" V 1700 5750 50  0001 C CNN
F 3 "~" V 1700 5750 50  0001 C CNN
	1    1700 5750
	0    1    1    0   
$EndComp
Wire Wire Line
	1700 5850 1700 5950
Connection ~ 1700 5950
Wire Wire Line
	1700 6050 1700 5950
Text GLabel 1800 5600 2    50   Input ~ 0
5V
Wire Wire Line
	1800 5600 1700 5600
Wire Wire Line
	1700 5600 1700 5650
Wire Wire Line
	1700 6250 1700 6350
Wire Wire Line
	1950 6350 1950 6450
Wire Wire Line
	1700 6350 1950 6350
Text GLabel 1950 6450 3    50   Input ~ 0
GND
Text GLabel 2300 6050 0    50   Input ~ 0
GND
Wire Wire Line
	2300 6050 2350 6050
Connection ~ 2350 6050
Wire Wire Line
	1950 6250 1950 6350
Wire Wire Line
	1700 5950 1950 5950
Connection ~ 1950 6350
Wire Wire Line
	1950 6050 1950 5950
Connection ~ 1950 5950
Wire Wire Line
	1950 5950 2500 5950
$Comp
L Device:D_Schottky_Small D5
U 1 1 5DE86A56
P 3900 2550
F 0 "D5" V 3854 2618 50  0000 L CNN
F 1 "SS2040FL" V 3945 2618 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123F" V 3900 2550 50  0001 C CNN
F 3 "~" V 3900 2550 50  0001 C CNN
	1    3900 2550
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small R1
U 1 1 5DD274C6
P 1300 5950
F 0 "R1" V 1104 5950 50  0000 C CNN
F 1 "1k" V 1195 5950 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 1300 5950 50  0001 C CNN
F 3 "~" H 1300 5950 50  0001 C CNN
	1    1300 5950
	0    1    1    0   
$EndComp
Wire Wire Line
	1200 5950 1050 5950
Wire Wire Line
	1400 5950 1700 5950
Wire Wire Line
	3800 2550 3550 2550
$Comp
L Device:D_Zener_Small D7
U 1 1 5DD49A4B
P 4100 2700
F 0 "D7" V 4054 2768 50  0000 L CNN
F 1 "UDZV5.1B" V 4145 2768 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-323" V 4100 2700 50  0001 C CNN
F 3 "~" V 4100 2700 50  0001 C CNN
	1    4100 2700
	0    1    1    0   
$EndComp
Wire Wire Line
	4100 2600 4100 2550
Wire Wire Line
	4100 2550 4000 2550
Wire Wire Line
	4100 2550 4700 2550
Connection ~ 4100 2550
NoConn ~ 1450 3850
NoConn ~ 1450 3950
$Comp
L Device:R_Small R3
U 1 1 5DDE1F8C
P 4000 1750
F 0 "R3" H 4059 1796 50  0000 L CNN
F 1 "10k" H 4059 1705 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 4000 1750 50  0001 C CNN
F 3 "~" H 4000 1750 50  0001 C CNN
	1    4000 1750
	1    0    0    -1  
$EndComp
Connection ~ 4000 1650
Wire Wire Line
	4000 1650 3900 1650
Text GLabel 3850 2300 0    50   Input ~ 0
GND
$Comp
L Device:R_Small R4
U 1 1 5DE0D211
P 4100 1900
F 0 "R4" H 4159 1946 50  0000 L CNN
F 1 "10k" H 4159 1855 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 4100 1900 50  0001 C CNN
F 3 "~" H 4100 1900 50  0001 C CNN
	1    4100 1900
	1    0    0    -1  
$EndComp
Connection ~ 4100 1800
$Comp
L Device:R_Small R5
U 1 1 5DE1BFE6
P 4200 2050
F 0 "R5" H 4259 2096 50  0000 L CNN
F 1 "10k" H 4259 2005 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 4200 2050 50  0001 C CNN
F 3 "~" H 4200 2050 50  0001 C CNN
	1    4200 2050
	1    0    0    -1  
$EndComp
Connection ~ 4200 1950
Wire Wire Line
	4200 1950 3900 1950
$Comp
L Device:R_Small R6
U 1 1 5DE2B3F3
P 4300 2200
F 0 "R6" H 4359 2246 50  0000 L CNN
F 1 "10k" H 4359 2155 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 4300 2200 50  0001 C CNN
F 3 "~" H 4300 2200 50  0001 C CNN
	1    4300 2200
	1    0    0    -1  
$EndComp
Connection ~ 4300 2100
Wire Wire Line
	4200 2300 4100 2300
Wire Wire Line
	4200 2150 4200 2300
Wire Wire Line
	4000 1850 4000 2300
Connection ~ 4000 2300
Wire Wire Line
	4000 2300 3850 2300
Wire Wire Line
	4300 2300 4200 2300
Connection ~ 4200 2300
Wire Wire Line
	4300 2100 4750 2100
Wire Wire Line
	4200 1950 4750 1950
Wire Wire Line
	4100 1800 4750 1800
Wire Wire Line
	4000 1650 4750 1650
Wire Wire Line
	4100 2000 4100 2300
Connection ~ 4100 2300
Wire Wire Line
	4100 2300 4000 2300
Connection ~ 3550 2800
Wire Wire Line
	3550 2800 4100 2800
Text GLabel 4700 2800 2    50   Input ~ 0
GND
Connection ~ 4100 2800
Wire Wire Line
	4700 2800 4100 2800
$Comp
L RF_Module:ESP32-WROOM-32 U3
U 1 1 5DE9A89C
P 6450 5150
F 0 "U3" H 6450 6731 50  0000 C CNN
F 1 "ESP32-WROOM-32" H 6450 6640 50  0000 C CNN
F 2 "RF_Module:ESP32-WROOM-32" H 6450 3650 50  0001 C CNN
F 3 "https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf" H 6150 5200 50  0001 C CNN
	1    6450 5150
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x03_Female J3
U 1 1 5DEB9441
P 6950 2450
F 0 "J3" H 6978 2426 50  0000 L CNN
F 1 "AZ1086H-3.3" H 6978 2335 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 6950 2450 50  0001 C CNN
F 3 "~" H 6950 2450 50  0001 C CNN
	1    6950 2450
	1    0    0    -1  
$EndComp
Text GLabel 5750 2350 0    50   Input ~ 0
GND
Text GLabel 5750 2450 0    50   Input ~ 0
3V3
Text GLabel 5750 2550 0    50   Input ~ 0
5V
Text GLabel 7300 4250 2    50   Input ~ 0
ESP_RX
Wire Wire Line
	7300 4250 7050 4250
Text GLabel 7300 4050 2    50   Input ~ 0
ESP_TX
Wire Wire Line
	7300 4050 7050 4050
Wire Wire Line
	6450 6550 6450 6700
Wire Wire Line
	6450 6700 6150 6700
Text GLabel 6150 6700 0    50   Input ~ 0
GND
Wire Wire Line
	5850 3950 5200 3950
Text GLabel 5200 3950 0    50   Input ~ 0
ESP_EN
Wire Wire Line
	5650 4250 5850 4250
Wire Wire Line
	5850 4150 5650 4150
Text GLabel 10250 5750 2    50   Input ~ 0
ESP_EN
Wire Wire Line
	7050 3950 7200 3950
Wire Wire Line
	7200 3950 7200 3800
$Comp
L Device:R_Small R7
U 1 1 5E01F5AB
P 7200 3700
F 0 "R7" H 7259 3746 50  0000 L CNN
F 1 "10k" H 7259 3655 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 7200 3700 50  0001 C CNN
F 3 "~" H 7200 3700 50  0001 C CNN
	1    7200 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 3600 7200 3500
Text GLabel 7200 3400 1    50   Input ~ 0
3V3
Connection ~ 7200 3950
$Comp
L Switch:SW_Push SW1
U 1 1 5E07E4B8
P 7600 3950
F 0 "SW1" H 7600 4235 50  0000 C CNN
F 1 "SW_Push" H 7600 4144 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm" H 7600 4150 50  0001 C CNN
F 3 "~" H 7600 4150 50  0001 C CNN
	1    7600 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	7800 3950 7900 3950
Wire Wire Line
	7900 3950 7900 4000
Text GLabel 7900 4000 3    50   Input ~ 0
GND
$Comp
L Device:R_Small R8
U 1 1 5E0A5AC5
P 9900 5600
F 0 "R8" H 9841 5554 50  0000 R CNN
F 1 "10k" H 9841 5645 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 9900 5600 50  0001 C CNN
F 3 "~" H 9900 5600 50  0001 C CNN
	1    9900 5600
	-1   0    0    1   
$EndComp
Wire Wire Line
	10250 5750 9900 5750
Connection ~ 9900 5750
Wire Wire Line
	9900 5750 9900 5700
Wire Wire Line
	9900 6000 9900 6100
Wire Wire Line
	9600 6100 9900 6100
Wire Wire Line
	9900 5500 9900 5350
Text GLabel 10150 5350 2    50   Input ~ 0
3V3
Wire Wire Line
	10150 5350 9900 5350
$Comp
L Connector:Conn_01x06_Female J5
U 1 1 5E15EEDB
P 8100 5450
F 0 "J5" H 7992 5835 50  0000 C CNN
F 1 "Conn_01x06_Female" H 7992 5744 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Horizontal" H 8100 5450 50  0001 C CNN
F 3 "~" H 8100 5450 50  0001 C CNN
	1    8100 5450
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8300 5250 8800 5250
Text GLabel 8800 5250 2    50   Input ~ 0
GND
NoConn ~ 8300 5350
Text GLabel 8800 5650 2    50   Input ~ 0
ESP_RX
Text GLabel 8800 5550 2    50   Input ~ 0
ESP_TX
Wire Wire Line
	8800 5650 8300 5650
Wire Wire Line
	8300 5550 8800 5550
$Comp
L Device:C_Small C7
U 1 1 5E1FFC5C
P 9450 5750
F 0 "C7" V 9221 5750 50  0000 C CNN
F 1 "0.1uF" V 9312 5750 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 9450 5750 50  0001 C CNN
F 3 "~" H 9450 5750 50  0001 C CNN
	1    9450 5750
	0    1    1    0   
$EndComp
Wire Wire Line
	8300 5750 9350 5750
Wire Wire Line
	9550 5750 9900 5750
$Comp
L Device:D_Schottky_Small D6
U 1 1 5E225E2F
P 8650 5450
F 0 "D6" H 8650 5245 50  0000 C CNN
F 1 "SS2040FL" H 8650 5336 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123F" V 8650 5450 50  0001 C CNN
F 3 "~" V 8650 5450 50  0001 C CNN
	1    8650 5450
	-1   0    0    1   
$EndComp
Wire Wire Line
	8550 5450 8300 5450
Text GLabel 8800 5450 2    50   Input ~ 0
5V
Wire Wire Line
	8800 5450 8750 5450
Wire Wire Line
	7150 4850 7050 4850
Wire Wire Line
	7150 4950 7050 4950
Wire Wire Line
	7050 5050 7150 5050
Wire Wire Line
	7150 5150 7050 5150
Wire Wire Line
	7050 5250 7150 5250
Wire Wire Line
	7150 5550 7050 5550
Wire Wire Line
	7050 5450 7150 5450
Wire Wire Line
	7150 6150 7050 6150
Wire Wire Line
	7150 6250 7050 6250
Wire Wire Line
	7150 5950 7050 5950
Wire Wire Line
	7150 6050 7050 6050
Wire Wire Line
	7150 5650 7050 5650
Wire Wire Line
	7150 5750 7050 5750
Wire Wire Line
	7150 5850 7050 5850
Wire Wire Line
	7150 4750 7050 4750
Wire Wire Line
	7150 4550 7050 4550
Wire Wire Line
	7150 4650 7050 4650
Wire Wire Line
	7150 4450 7050 4450
Wire Wire Line
	7150 4350 7050 4350
Wire Wire Line
	7150 5350 7050 5350
Wire Wire Line
	7150 4150 7050 4150
Wire Wire Line
	5700 5150 5850 5150
Wire Wire Line
	5850 5250 5700 5250
Wire Wire Line
	5700 5550 5850 5550
Wire Wire Line
	5700 5350 5850 5350
Wire Wire Line
	5700 5450 5850 5450
Wire Wire Line
	5850 5650 5700 5650
Text GLabel 4350 6200 2    50   Input ~ 0
ESP_RX
Text GLabel 4350 6100 2    50   Input ~ 0
ESP_TX
Wire Wire Line
	4350 6200 3950 6200
Wire Wire Line
	3950 6100 4350 6100
$Comp
L Device:C_Small C4
U 1 1 5E703ED7
P 5800 2900
F 0 "C4" H 5892 2946 50  0000 L CNN
F 1 "0.1uF" H 5892 2855 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5800 2900 50  0001 C CNN
F 3 "~" H 5800 2900 50  0001 C CNN
	1    5800 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 2550 5800 2550
$Comp
L Device:C_Small C5
U 1 1 5E76DBB0
P 6200 2900
F 0 "C5" H 6292 2946 50  0000 L CNN
F 1 "0.1uF" H 6292 2855 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6200 2900 50  0001 C CNN
F 3 "~" H 6200 2900 50  0001 C CNN
	1    6200 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 2450 6000 2450
Wire Wire Line
	5800 2550 5800 2800
Connection ~ 5800 2550
Wire Wire Line
	5800 2550 6750 2550
Wire Wire Line
	6200 2800 6200 2450
Connection ~ 6200 2450
Wire Wire Line
	6200 2450 6550 2450
Wire Wire Line
	6200 3000 6200 3150
Wire Wire Line
	6200 3150 5800 3150
Wire Wire Line
	5800 3150 5800 3000
Wire Wire Line
	5800 3150 5700 3150
Connection ~ 5800 3150
Text GLabel 5700 3150 0    50   Input ~ 0
GND
$Comp
L Device:C_Small C6
U 1 1 5E7C1FC9
P 6550 2900
F 0 "C6" H 6642 2946 50  0000 L CNN
F 1 "22uF" H 6642 2855 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6550 2900 50  0001 C CNN
F 3 "~" H 6550 2900 50  0001 C CNN
	1    6550 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 2800 6550 2450
Connection ~ 6550 2450
Wire Wire Line
	6550 2450 6750 2450
Wire Wire Line
	6550 3000 6550 3150
Wire Wire Line
	6550 3150 6200 3150
Connection ~ 6200 3150
Wire Wire Line
	7200 3950 7400 3950
NoConn ~ 7150 4150
NoConn ~ 5650 4150
NoConn ~ 5650 4250
NoConn ~ 5700 5650
NoConn ~ 5700 5550
NoConn ~ 5700 5450
NoConn ~ 5700 5350
NoConn ~ 5700 5250
NoConn ~ 5700 5150
NoConn ~ 7150 5450
NoConn ~ 7150 5650
NoConn ~ 7150 5750
NoConn ~ 7150 5850
NoConn ~ 7150 5950
NoConn ~ 7150 6050
NoConn ~ 7150 6150
NoConn ~ 7150 6250
Text GLabel 9800 2950 0    50   Input ~ 0
INT
Text GLabel 9800 2750 0    50   Input ~ 0
ECL
Text GLabel 9800 2650 0    50   Input ~ 0
EDA
NoConn ~ 9800 2750
NoConn ~ 9800 2650
NoConn ~ 9800 2950
NoConn ~ 9800 3150
NoConn ~ 3700 4200
NoConn ~ 3200 3800
NoConn ~ 3200 3900
NoConn ~ 3200 4000
NoConn ~ 3200 4200
NoConn ~ 3200 4300
NoConn ~ 3200 4400
NoConn ~ 3200 4600
NoConn ~ 3200 4700
NoConn ~ 3200 4800
NoConn ~ 3200 5000
NoConn ~ 3200 5100
NoConn ~ 3200 5200
NoConn ~ 3200 5300
NoConn ~ 3200 5400
NoConn ~ 3200 5500
NoConn ~ 3700 5600
NoConn ~ 3700 5500
NoConn ~ 3700 5400
NoConn ~ 3700 5200
NoConn ~ 3700 5000
NoConn ~ 3700 4900
NoConn ~ 3700 4800
NoConn ~ 3700 4700
NoConn ~ 3700 4500
NoConn ~ 3700 4400
NoConn ~ 7400 6650
Wire Wire Line
	6450 3750 6450 3500
Wire Wire Line
	6450 3500 7200 3500
Connection ~ 7200 3500
Wire Wire Line
	7200 3500 7200 3400
$Comp
L power:PWR_FLAG #FLG0103
U 1 1 5E244658
P 6000 2450
F 0 "#FLG0103" H 6000 2525 50  0001 C CNN
F 1 "PWR_FLAG" H 6000 2623 50  0000 C CNN
F 2 "" H 6000 2450 50  0001 C CNN
F 3 "~" H 6000 2450 50  0001 C CNN
	1    6000 2450
	1    0    0    -1  
$EndComp
Connection ~ 6000 2450
Wire Wire Line
	6000 2450 6200 2450
Wire Wire Line
	5750 2350 6750 2350
$EndSCHEMATC
