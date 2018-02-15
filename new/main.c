#pragma config(Sensor, in1,    fourbarPot,     sensorPotentiometer)
#pragma config(Sensor, in2,    gyro1,          sensorGyro)
#pragma config(Sensor, in3,    gyro2,          sensorGyro)
#pragma config(Sensor, dgtl1,  ldtEnc,         sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  data,           sensorDigitalOut)
#pragma config(Sensor, dgtl4,  clock,          sensorDigitalOut)
#pragma config(Sensor, dgtl5,  ldr4bEnc,       sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  rdr4bEnc,       sensorQuadEncoder)
#pragma config(Sensor, dgtl9,  rdtEnc,         sensorQuadEncoder)
#pragma config(Sensor, dgtl11, sound,          sensorSONAR_mm)
#pragma config(Motor,  port1,           mgm,           tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           ldt1,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           ldr4b,         tmotorVex393_MC29, PIDControl, reversed, encoderPort, dgtl5)
#pragma config(Motor,  port4,           fourbar,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           rdt1,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           ldt2,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           claw,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           rdr4b,         tmotorVex393_MC29, openLoop, encoderPort, dgtl7)
#pragma config(Motor,  port9,           rdt2,          tmotorVex393_MC29, openLoop)
#pragma config(MotorPidSetting,  port3,  25, 100, 1000, 2, 10,   100, 0, 40)
#pragma config(MotorPidSetting,  port8,  25, 100, 1000, 2, 10,   100, 0, 40)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma DebuggerWindows("Globals")
#pragma DebuggerWindows("Locals")
#pragma DebuggerWindows("Sensors")
#pragma DebuggerWindows("VexLCD")
#pragma DebuggerWindows("taskStatus")
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)
#pragma platform(VEX2)
#include "Vex_Competition_Includes.c"
#include "driving.c"
#include "auton.c"
#include "lights.c"
#include "gyroLib.c"
void waitForRelease()
{
	while(nLCDButtons != 0)
		wait1Msec(5);
}
void waitForPress()
{
	while(nLCDButtons == 0)
		wait1Msec(5);
}
void pre_auton(){//Selects auton program
	bStopTasksBetweenModes = false;
	delay(1100);
	GyroInit(in2);
	clearLCDLine(0);
	clearLCDLine(1);
	bLCDBacklight = true;
	playTone(440,10);
	wait1Msec(100);
	playTone(660,10);
	while(nLCDButtons != centerButton){
		switch(lcdCount){
		case 0:
			clearLCDLine(0);
			clearLCDLine(1);
			displayLCDString(0,0, firstAutonString);
			displayEnterString(1);
			waitForPress();
			if(nLCDButtons == leftButton){
				waitForRelease();
				lcdCount = 3;
			}
			else if(nLCDButtons == rightButton){
				waitForRelease();
				lcdCount++;
			}
			SensorValue[rdr4bEnc]=0;
			SensorValue[ldr4bEnc]=0;
		break;
		case 1:
			clearLCDLine(0);
			clearLCDLine(1);
			displayLCDString(0,0, secondAutonString);
			displayEnterString(1);
			waitForPress();
			if(nLCDButtons == leftButton){
				waitForRelease();
				lcdCount--;
			}
			else if(nLCDButtons == rightButton){
				waitForRelease();
				lcdCount++;
			}
			SensorValue[rdr4bEnc]=0;
			SensorValue[ldr4bEnc]=0;
			SensorValue[ldtEnc]=0;
			SensorValue[rdtEnc]=0;
			break;
		case 2:
			clearLCDLine(0);
			clearLCDLine(1);
			displayLCDString(0,0, thirdAutonString);
			displayEnterString(1);
			waitForPress();
			if(nLCDButtons == leftButton){
				waitForRelease();
				lcdCount--;
			}
			else if(nLCDButtons == rightButton){
				waitForRelease();
				lcdCount++;
			}
			SensorValue[rdr4bEnc]=0;
			SensorValue[ldr4bEnc]=0;
			SensorValue[ldtEnc]=0;
			SensorValue[rdtEnc]=0;
			break;
		case 3:
			clearLCDLine(0);
			clearLCDLine(1);
			displayLCDString(0,0, fourthAutonString);
			displayEnterString(1);
			waitForPress();
			if(nLCDButtons == leftButton)
			{
				waitForRelease();
				lcdCount--;
			}
			else if(nLCDButtons == rightButton)
			{
				waitForRelease();
				lcdCount = 0;
			}
			SensorValue[rdr4bEnc]=0;
			SensorValue[ldr4bEnc]=0;
			SensorValue[ldtEnc]=0;
			SensorValue[rdtEnc]=0;
			break;
		default:
			lcdCount = 3;
			SensorValue[rdr4bEnc]=0;
			SensorValue[ldr4bEnc]=0;
			SensorValue[ldtEnc]=0;
			SensorValue[rdtEnc]=0;
			break;
		}
		SensorValue[ldtEnc]=0;
		SensorValue[rdtEnc]=0;
	}
}
task autonomous(){
	startTask(auton);
}
task usercontrol(){
	startTask(fadeColors);
	startTask(drive);
}
