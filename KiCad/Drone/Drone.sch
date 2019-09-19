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
$Comp
L Connector:Conn_01x19_Female J3
U 1 1 5D691FFB
P 5950 1800
F 0 "J3" H 5978 1826 50  0000 L CNN
F 1 "ESP32_LEFT" H 5978 1735 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x19_P2.54mm_Vertical" H 5950 1800 50  0001 C CNN
F 3 "~" H 5950 1800 50  0001 C CNN
	1    5950 1800
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x19_Female J5
U 1 1 5D6953E6
P 6700 1800
F 0 "J5" H 6592 2885 50  0000 C CNN
F 1 "ESP32_RIGHT" H 6592 2794 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x19_P2.54mm_Vertical" H 6700 1800 50  0001 C CNN
F 3 "~" H 6700 1800 50  0001 C CNN
	1    6700 1800
	-1   0    0    -1  
$EndComp
Text GLabel 5550 900  0    50   Input ~ 0
3V3
Wire Wire Line
	5550 900  5750 900 
Text GLabel 5550 1000 0    50   Input ~ 0
EN
Text GLabel 5550 1100 0    50   Input ~ 0
VP
Text GLabel 5550 1200 0    50   Input ~ 0
VN
Text GLabel 5550 1300 0    50   Input ~ 0
GPIO34
Text GLabel 5550 1400 0    50   Input ~ 0
GPIO35
Text GLabel 5550 1500 0    50   Input ~ 0
GPIO32
Text GLabel 5550 1600 0    50   Input ~ 0
GPIO33
Text GLabel 5550 1700 0    50   Input ~ 0
GPIO25
Text GLabel 5550 1800 0    50   Input ~ 0
GPIO26
Text GLabel 5550 1900 0    50   Input ~ 0
GPIO27
Text GLabel 5550 2000 0    50   Input ~ 0
GPIO14
Text GLabel 5550 2100 0    50   Input ~ 0
GPIO12
Text GLabel 5550 2200 0    50   Input ~ 0
GND
Text GLabel 5550 2300 0    50   Input ~ 0
GPIO13
Text GLabel 5550 2600 0    50   Input ~ 0
CMD
Text GLabel 5550 2700 0    50   Input ~ 0
5V
Text GLabel 7100 900  2    50   Input ~ 0
GND
Text GLabel 7100 1000 2    50   Input ~ 0
GPIO23
Text GLabel 7100 1100 2    50   Input ~ 0
GPIO22
Text GLabel 7100 1200 2    50   Input ~ 0
TX
Text GLabel 7100 1300 2    50   Input ~ 0
RX
Text GLabel 7100 1400 2    50   Input ~ 0
GPIO21
Text GLabel 7100 1500 2    50   Input ~ 0
GND
Text GLabel 7100 1600 2    50   Input ~ 0
GPIO19
Text GLabel 7100 1700 2    50   Input ~ 0
GPIO18
Text GLabel 7100 1800 2    50   Input ~ 0
GPIO5
Text GLabel 7100 1900 2    50   Input ~ 0
GPIO17
Text GLabel 7100 2000 2    50   Input ~ 0
GPIO16
Text GLabel 7100 2100 2    50   Input ~ 0
GPIO4
Text GLabel 7100 2200 2    50   Input ~ 0
GPIO0
Text GLabel 7100 2300 2    50   Input ~ 0
GPIO2
Text GLabel 7100 2400 2    50   Input ~ 0
GPIO15
Text GLabel 7100 2700 2    50   Input ~ 0
CLK
Wire Wire Line
	7100 2700 6900 2700
Wire Wire Line
	6900 2600 7100 2600
Wire Wire Line
	7100 2500 6900 2500
Wire Wire Line
	6900 2400 7100 2400
Wire Wire Line
	7100 2300 6900 2300
Wire Wire Line
	6900 2200 7100 2200
Wire Wire Line
	7100 2100 6900 2100
Wire Wire Line
	6900 2000 7100 2000
Wire Wire Line
	7100 1900 6900 1900
Wire Wire Line
	6900 1800 7100 1800
Wire Wire Line
	7100 1700 6900 1700
Wire Wire Line
	6900 1600 7100 1600
Wire Wire Line
	7100 1500 6900 1500
Wire Wire Line
	6900 1400 7100 1400
Wire Wire Line
	7100 1300 6900 1300
Wire Wire Line
	6900 1200 7100 1200
Wire Wire Line
	7100 1100 6900 1100
Wire Wire Line
	6900 1000 7100 1000
Wire Wire Line
	7100 900  6900 900 
Wire Wire Line
	5750 1000 5550 1000
Wire Wire Line
	5550 1100 5750 1100
Wire Wire Line
	5750 1200 5550 1200
Wire Wire Line
	5550 1300 5750 1300
Wire Wire Line
	5750 1400 5550 1400
Wire Wire Line
	5550 1500 5750 1500
Wire Wire Line
	5750 1600 5550 1600
Wire Wire Line
	5550 1700 5750 1700
Wire Wire Line
	5750 1800 5550 1800
Wire Wire Line
	5550 1900 5750 1900
Wire Wire Line
	5750 2000 5550 2000
Wire Wire Line
	5550 2100 5750 2100
Wire Wire Line
	5750 2200 5550 2200
Wire Wire Line
	5550 2300 5750 2300
Wire Wire Line
	5750 2400 5550 2400
Wire Wire Line
	5550 2500 5750 2500
Wire Wire Line
	5750 2600 5550 2600
Wire Wire Line
	5550 2700 5750 2700
Text Notes 6100 650  2    50   ~ 0
ESP32-devkitC-V2
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
Text GLabel 9800 2650 0    50   Input ~ 0
EDA
Text GLabel 9800 2750 0    50   Input ~ 0
ECL
Text GLabel 9800 2850 0    50   Input ~ 0
ADO
Text GLabel 9800 2950 0    50   Input ~ 0
INT
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
P 2900 2250
F 0 "U1" H 2900 2617 50  0000 C CNN
F 1 "LM2596T-5" H 2900 2526 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:TO-263-5_TabPin3" H 2950 2000 50  0001 L CIN
F 3 "http://www.ti.com/lit/ds/symlink/lm2596.pdf" H 2900 2250 50  0001 C CNN
	1    2900 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 2350 2250 2350
Wire Wire Line
	2250 2350 2250 2600
Wire Wire Line
	2250 2600 2100 2600
Connection ~ 2250 2600
Wire Wire Line
	2400 2150 2100 2150
Text GLabel 2000 2150 0    50   Input ~ 0
BAT
Text GLabel 2000 2600 0    50   Input ~ 0
GND
$Comp
L Device:C_Small C1
U 1 1 5D7FFBCB
P 2100 2350
F 0 "C1" H 2192 2396 50  0000 L CNN
F 1 "47u" H 2192 2305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2100 2350 50  0001 C CNN
F 3 "~" H 2100 2350 50  0001 C CNN
	1    2100 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 2450 2100 2600
Connection ~ 2100 2600
Wire Wire Line
	2100 2600 2000 2600
Wire Wire Line
	2100 2250 2100 2150
Connection ~ 2100 2150
Wire Wire Line
	2100 2150 2000 2150
Wire Wire Line
	3400 2350 3550 2350
$Comp
L Device:D_Schottky_Small D2
U 1 1 5D805B17
P 3550 2500
F 0 "D2" V 3504 2568 50  0000 L CNN
F 1 "SS2040FL" V 3595 2568 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123F" V 3550 2500 50  0001 C CNN
F 3 "~" V 3550 2500 50  0001 C CNN
	1    3550 2500
	0    1    1    0   
$EndComp
Wire Wire Line
	3550 2400 3550 2350
Wire Wire Line
	3550 2350 3700 2350
Connection ~ 3550 2350
$Comp
L pspice:INDUCTOR L1
U 1 1 5D80C70F
P 3950 2350
F 0 "L1" H 3950 2565 50  0000 C CNN
F 1 "989BS-270M" H 3950 2474 50  0000 C CNN
F 2 "Inductor_SMD:L_12x12mm_H6mm" H 3950 2350 50  0001 C CNN
F 3 "~" H 3950 2350 50  0001 C CNN
	1    3950 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 2350 4350 2350
$Comp
L Device:C_Small C2
U 1 1 5D80F134
P 4350 2500
F 0 "C2" H 4442 2546 50  0000 L CNN
F 1 "22u" H 4442 2455 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4350 2500 50  0001 C CNN
F 3 "~" H 4350 2500 50  0001 C CNN
	1    4350 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 2400 4350 2350
Connection ~ 4350 2350
Wire Wire Line
	4350 2350 4550 2350
Wire Wire Line
	3550 2600 4350 2600
Connection ~ 3550 2600
Wire Wire Line
	4350 2350 4350 2150
Wire Wire Line
	4350 2150 3400 2150
Text GLabel 4550 2350 2    50   Input ~ 0
5V
Text GLabel 8950 2250 2    50   Input ~ 0
MPU_VCC
Text GLabel 8650 2250 0    50   Input ~ 0
3V3
Wire Wire Line
	8650 2250 8950 2250
Text Notes 2300 1850 2    50   ~ 0
11Vto5VReg
Text Notes 5850 4450 2    50   ~ 0
Raspberry Pi 3
Wire Wire Line
	6500 4800 6500 4900
Wire Wire Line
	6500 4800 6750 4800
Text GLabel 6750 4800 2    50   Input ~ 0
5V
Text GLabel 6750 5000 2    50   Input ~ 0
GND
Wire Wire Line
	6750 5000 6600 5000
Text GLabel 5750 5200 0    50   Input ~ 0
GND
Wire Wire Line
	5750 5200 5900 5200
Wire Wire Line
	6600 5700 6500 5700
Connection ~ 6600 5000
Wire Wire Line
	6600 5000 6500 5000
Wire Wire Line
	6600 5400 6500 5400
Wire Wire Line
	6600 5000 6600 5400
Connection ~ 6600 5400
Wire Wire Line
	6600 5400 6600 5700
Wire Wire Line
	6600 5700 6600 6200
Wire Wire Line
	6600 6200 6500 6200
Connection ~ 6600 5700
Wire Wire Line
	6600 6200 6600 6400
Wire Wire Line
	6600 6400 6500 6400
Connection ~ 6600 6200
Wire Wire Line
	6000 6700 5900 6700
Connection ~ 5900 5200
Wire Wire Line
	5900 5200 6000 5200
Wire Wire Line
	5900 6000 6000 6000
Connection ~ 5900 6000
Text GLabel 5750 4800 0    50   Input ~ 0
3V3
Wire Wire Line
	5800 4800 5800 5600
Connection ~ 5800 4800
Wire Wire Line
	5800 4800 5750 4800
Wire Wire Line
	6500 5100 6750 5100
Wire Wire Line
	6500 5200 6750 5200
Text GLabel 6750 5100 2    50   Input ~ 0
PI_UART_TX
Text GLabel 6750 5200 2    50   Input ~ 0
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
Text GLabel 3750 3650 0    50   Input ~ 0
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
Text GLabel 5750 5700 0    50   Input ~ 0
PI_GPIO10
Text GLabel 5750 5800 0    50   Input ~ 0
PI_GPIO9
Text GLabel 5750 5900 0    50   Input ~ 0
PI_GPIO11
Wire Wire Line
	6500 5900 6750 5900
Text GLabel 6750 5900 2    50   Input ~ 0
PI_GPIO8
Text GLabel 9150 5100 2    50   Input ~ 0
GPIO15
Text GLabel 8650 4500 0    50   Input ~ 0
GPIO14
Text GLabel 8650 1200 0    50   Input ~ 0
GPIO13
Text GLabel 8650 1100 0    50   Input ~ 0
GPIO12
Text Notes 6000 3450 2    50   ~ 0
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
Text GLabel 8650 5100 0    50   Input ~ 0
PWM1
Text GLabel 8650 5250 0    50   Input ~ 0
PWM2
Text GLabel 8650 5400 0    50   Input ~ 0
PWM3
Text GLabel 8650 5550 0    50   Input ~ 0
PWM4
Wire Wire Line
	9150 5100 8650 5100
Wire Wire Line
	8650 5250 9150 5250
Wire Wire Line
	9150 5400 8650 5400
Wire Wire Line
	8650 5550 9150 5550
Text GLabel 4850 950  2    50   Input ~ 0
EN
Text GLabel 4450 950  0    50   Input ~ 0
GND
$Comp
L Device:C_Small C3
U 1 1 5D7EFA83
P 4650 950
F 0 "C3" V 4879 950 50  0000 C CNN
F 1 "1u" V 4788 950 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4650 950 50  0001 C CNN
F 3 "~" H 4650 950 50  0001 C CNN
	1    4650 950 
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4450 950  4550 950 
Wire Wire Line
	4750 950  4850 950 
Text GLabel 9150 5250 2    50   Input ~ 0
GPIO4
Text GLabel 5550 2400 0    50   Input ~ 0
SD2
Text GLabel 5550 2500 0    50   Input ~ 0
SD3
Text GLabel 7100 2500 2    50   Input ~ 0
SD1
Text GLabel 7100 2600 2    50   Input ~ 0
SD0
Text GLabel 2300 3550 2    50   Input ~ 0
PWM1
Text GLabel 2300 3650 2    50   Input ~ 0
PWM2
Text GLabel 2300 3750 2    50   Input ~ 0
PWM3
Text GLabel 2300 3850 2    50   Input ~ 0
PWM4
$Comp
L Connector:Conn_01x06_Female J1
U 1 1 5D8394B4
P 1700 3550
F 0 "J1" H 1592 3935 50  0000 C CNN
F 1 "ESC" H 1592 3844 50  0000 C CNN
F 2 "Connector_JST:JST_SH_BM06B-SRSS-TB_1x06-1MP_P1.00mm_Vertical" H 1700 3550 50  0001 C CNN
F 3 "~" H 1700 3550 50  0001 C CNN
	1    1700 3550
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2300 3550 1900 3550
Wire Wire Line
	1900 3650 2300 3650
Wire Wire Line
	2300 3750 1900 3750
Wire Wire Line
	1900 3850 2300 3850
Wire Wire Line
	1900 3350 2300 3350
Text GLabel 2300 3350 2    50   Input ~ 0
GND
Text Notes 1700 3100 0    50   ~ 0
ESC
Text GLabel 3750 3850 0    50   Input ~ 0
ESC_VIN
Text GLabel 3750 3750 0    50   Input ~ 0
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
P 4200 3750
F 0 "U2" H 4228 3726 50  0000 L CNN
F 1 "SKI03021" H 4228 3635 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:TO-263-3_TabPin4" H 4200 3750 50  0001 C CNN
F 3 "~" H 4200 3750 50  0001 C CNN
	1    4200 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 3650 4000 3650
Wire Wire Line
	4000 3750 3850 3750
Wire Wire Line
	4000 3950 3850 3950
Wire Wire Line
	3850 3950 3850 3750
Connection ~ 3850 3750
Wire Wire Line
	3850 3750 3750 3750
Wire Wire Line
	3750 3850 4000 3850
Text Notes 3150 3400 0    50   ~ 0
SKI03021 PowerMOSFET
Wire Wire Line
	2250 2600 2900 2600
Wire Wire Line
	2900 2550 2900 2600
Connection ~ 2900 2600
Wire Wire Line
	2900 2600 3550 2600
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
P 3500 4550
F 0 "J10" H 3392 4225 50  0000 C CNN
F 1 "to ESC Power" H 3392 4316 50  0000 C CNN
F 2 "RC-Battery-Connectors:XT-60_female" H 3500 4550 50  0001 C CNN
F 3 "~" H 3500 4550 50  0001 C CNN
	1    3500 4550
	-1   0    0    1   
$EndComp
Text GLabel 3900 4450 2    50   Input ~ 0
ESC_VIN
Text GLabel 3900 4550 2    50   Input ~ 0
GND
Wire Wire Line
	3900 4550 3700 4550
Wire Wire Line
	3700 4450 3900 4450
Text Notes 3150 4150 0    50   ~ 0
to ESC XT60 connector
Text Notes 9150 3650 2    50   ~ 0
SPI master:ESP32 slave:DPS310\nusing vspi
Text GLabel 6750 5500 2    50   Input ~ 0
PI_PIGPIO_TX
Wire Wire Line
	6750 5500 6500 5500
Text GLabel 6750 5600 2    50   Input ~ 0
PI_PIGPIO_RX
Wire Wire Line
	6750 5600 6500 5600
Wire Wire Line
	6000 3800 6400 3800
Wire Wire Line
	6400 3700 6000 3700
Text Notes 5250 3700 0    50   ~ 0
TX
Text Notes 5250 3800 0    50   ~ 0
RX
Text Notes 6800 3700 0    50   ~ 0
RX
Text Notes 6800 3800 0    50   ~ 0
TX
Text GLabel 6000 3800 0    50   Input ~ 0
PI_PIGPIO_RX
Text GLabel 6000 3700 0    50   Input ~ 0
PI_PIGPIO_TX
Text GLabel 9150 5550 2    50   Input ~ 0
GPIO17
Text GLabel 9150 5400 2    50   Input ~ 0
GPIO16
Text GLabel 6400 3700 2    50   Input ~ 0
RX
Text GLabel 6400 3800 2    50   Input ~ 0
TX
Wire Wire Line
	5900 6700 5900 6000
Wire Wire Line
	6000 5900 5750 5900
Wire Wire Line
	5750 5800 6000 5800
Wire Wire Line
	6000 5700 5750 5700
Wire Wire Line
	6000 4800 5800 4800
Wire Wire Line
	5800 5600 6000 5600
Wire Wire Line
	5900 6000 5900 5200
$Comp
L Connector_Generic:Conn_02x20_Odd_Even J4
U 1 1 5D829EEE
P 6300 5700
F 0 "J4" H 6350 6817 50  0000 C CNN
F 1 "Raspberry Pi" H 6350 6726 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x20_P2.54mm_Vertical" H 6300 5700 50  0001 C CNN
F 3 "~" H 6300 5700 50  0001 C CNN
	1    6300 5700
	-1   0    0    -1  
$EndComp
Connection ~ 6500 4800
Text GLabel 8650 4050 0    50   Input ~ 0
GPIO23
Text GLabel 8650 2400 0    50   Input ~ 0
GPIO23
Text GLabel 8650 4200 0    50   Input ~ 0
GPIO19
Text Notes 3800 2800 0    50   ~ 0
Anothor 5V power source
Text GLabel 4600 3100 2    50   Input ~ 0
5V
Wire Wire Line
	4600 3100 4350 3100
$Comp
L Connector:Conn_01x02_Female J11
U 1 1 5D86C630
P 4150 3200
F 0 "J11" H 4042 2875 50  0000 C CNN
F 1 "Conn_01x02_Female" H 4042 2966 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 4150 3200 50  0001 C CNN
F 3 "~" H 4150 3200 50  0001 C CNN
	1    4150 3200
	-1   0    0    1   
$EndComp
Text GLabel 4600 3200 2    50   Input ~ 0
GND
Wire Wire Line
	4600 3200 4350 3200
$EndSCHEMATC
