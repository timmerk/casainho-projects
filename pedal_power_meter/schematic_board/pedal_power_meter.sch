EESchema Schematic File Version 2
LIBS:power,./zxct1009,device,conn,linear,regul,74xx,cmos4000,adc-dac,memory,xilinx,special,microcontrollers,dsp,microchip,analog_switches,motorola,texas,intel,audio,interface,digital-audio,philips,display,cypress,siliconi,contrib,valves,./pedal_power_meter.cache
EELAYER 24  0
EELAYER END
$Descr User 6000 5905
Sheet 1 1
Title "Pedal Power Meter"
Date "18 may 2009"
Rev ""
Comp "(c) Jorge Pinto 2009"
Comment1 "License: Creative Commons BY 2.5 PT"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	3650 2050 3650 1900
Wire Wire Line
	3650 1900 3750 1900
Wire Wire Line
	3700 3200 3700 3050
Wire Wire Line
	3700 3050 3850 3050
Connection ~ 2800 2850
Wire Wire Line
	3850 2850 2800 2850
Connection ~ 3450 2150
Wire Wire Line
	3450 2750 3450 2950
Wire Wire Line
	3450 2950 3450 3100
Wire Wire Line
	2800 2650 2800 2850
Wire Wire Line
	2800 2850 2800 3100
Wire Wire Line
	2550 1700 2150 1700
Wire Wire Line
	2150 1700 1850 1700
Connection ~ 2150 1700
Connection ~ 3450 1700
Wire Wire Line
	3050 1450 3450 1450
Wire Wire Line
	3450 2150 3300 2150
Wire Wire Line
	2550 1450 2150 1450
Wire Wire Line
	1850 1900 1950 1900
Wire Wire Line
	1950 1900 1950 2050
Wire Wire Line
	2300 2150 2150 2150
Wire Wire Line
	2150 2150 2150 1700
Wire Wire Line
	2150 1700 2150 1450
Wire Wire Line
	2800 3600 2800 3750
Wire Wire Line
	3450 3600 3450 3750
Wire Wire Line
	3450 1450 3450 1700
Wire Wire Line
	3450 1700 3450 2150
Wire Wire Line
	3450 2150 3450 2250
Wire Wire Line
	3850 2950 3450 2950
Connection ~ 3450 2950
Wire Wire Line
	3750 1700 3450 1700
Wire Wire Line
	3450 1700 3050 1700
$Comp
L CONN_2 P2
U 1 1 4A1153AF
P 4100 1800
F 0 "P2" V 4050 1800 40  0000 C C
F 1 "CONN_2" V 4150 1800 40  0000 C C
	1    4100 1800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 4A1153AE
P 3650 2050
F 0 "#PWR01" H 3650 2050 30  0001 C C
F 1 "GND" H 3650 1980 30  0001 C C
	1    3650 2050
	1    0    0    -1  
$EndComp
Kmarq B 3700 3200 "Atenção Pino power_in não controlado (Net 1)" F=1
$Comp
L GND #PWR02
U 1 1 4A0ED233
P 3700 3200
F 0 "#PWR02" H 3700 3200 30  0001 C C
F 1 "GND" H 3700 3130 30  0001 C C
	1    3700 3200
	1    0    0    -1  
$EndComp
$Comp
L CONN_3 K1
U 1 1 4A0ED1CB
P 4200 2950
F 0 "K1" V 4150 2950 50  0000 C C
F 1 "CONN_3" V 4250 2950 40  0000 C C
	1    4200 2950
	1    0    0    -1  
$EndComp
$Comp
L ZXCT1009 U1
U 1 1 4A0EA4BF
P 2800 2200
F 0 "U1" H 2950 2004 60  0000 C C
F 1 "ZXCT1009" H 2800 2400 60  0000 C C
	1    2800 2200
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 4A0EC766
P 3450 2500
F 0 "R4" V 3530 2500 50  0000 C C
F 1 "36K" V 3450 2500 50  0000 C C
	1    3450 2500
	-1   0    0    1   
$EndComp
$Comp
L CONN_2 P1
U 1 1 4A0E9DC1
P 1500 1800
F 0 "P1" V 1450 1800 40  0000 C C
F 1 "CONN_2" V 1550 1800 40  0000 C C
	1    1500 1800
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR03
U 1 1 4A0EC981
P 3450 3750
F 0 "#PWR03" H 3450 3750 30  0001 C C
F 1 "GND" H 3450 3680 30  0001 C C
	1    3450 3750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 4A0EC96A
P 2800 3750
F 0 "#PWR04" H 2800 3750 30  0001 C C
F 1 "GND" H 2800 3680 30  0001 C C
	1    2800 3750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR05
U 1 1 4A0EC91F
P 1950 2050
F 0 "#PWR05" H 1950 2050 30  0001 C C
F 1 "GND" H 1950 1980 30  0001 C C
	1    1950 2050
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 4A0EA648
P 3450 3350
F 0 "R5" V 3530 3350 50  0000 C C
F 1 "6K8" V 3450 3350 50  0000 C C
	1    3450 3350
	-1   0    0    1   
$EndComp
$Comp
L R R3
U 1 1 4A0EA5DA
P 2800 3350
F 0 "R3" V 2880 3350 50  0000 C C
F 1 "3K3" V 2800 3350 50  0000 C C
	1    2800 3350
	-1   0    0    1   
$EndComp
$Comp
L R R2
U 1 1 4A0E9D9F
P 2800 1700
F 0 "R2" V 2880 1700 50  0000 C C
F 1 "R01" V 2800 1700 50  0000 C C
	1    2800 1700
	0    1    1    0   
$EndComp
$Comp
L R R1
U 1 1 4A0E9D86
P 2800 1450
F 0 "R1" V 2880 1450 50  0000 C C
F 1 "R01" V 2800 1450 50  0000 C C
	1    2800 1450
	0    1    1    0   
$EndComp
$EndSCHEMATC
