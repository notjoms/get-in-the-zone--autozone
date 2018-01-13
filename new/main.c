#pragma config(Sensor, in1,    gyroBot,        sensorGyro)
#pragma config(Sensor, in2,    gyroTop,        sensorGyro)
#pragma config(Sensor, dgtl1,  ldtEnc,         sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  rdtEnc,         sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  ldr4bEnc,       sensorQuadEncoder)
#pragma config(Sensor, dgtl9,  rdr4bEnc,       sensorQuadEncoder)
#pragma config(Sensor, dgtl11, fourbarEnc,     sensorQuadEncoder)
#pragma config(Motor,  port1,           mgmr,          tmotorVex393HighSpeed_HBridge, openLoop)
#pragma config(Motor,  port2,           fourbar,       tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port3,           ldr4b,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           ldt1,          tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port5,           ldt2,          tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port6,           rdt1,          tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port7,           rdt2,          tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port8,           rdr4b,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           claw,          tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port10,          mgml,          tmotorVex393HighSpeed_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma DebuggerWindows("Globals")
#pragma DebuggerWindows("Locals")
#pragma DebuggerWindows("Sensors")
#pragma DebuggerWindows("debugStream")
#pragma DebuggerWindows("joystickSimple")
#pragma DebuggerWindows("VexLCD")
#pragma DebuggerWindows("vexCompetitionControl")
#pragma DebuggerWindows("taskStatus")
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)
#pragma platform(VEX2)
#include "Vex_Competition_Includes.c"
#include "driving.c"
#include "auton.c"

const short leftButton = 1;
const short centerButton = 2;
const short rightButton = 4;
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
	gyroInit(gyro1,1,1);
	gyroInit(gyro2,2,1);
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
			displayLCDString(1,0, enterString);
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
			SensorValue[fourbarEnc]=0;
		break;
		case 1:
			clearLCDLine(0);
			clearLCDLine(1);
			displayLCDString(0,0, secondAutonString);
			displayLCDString(1,0, enterString);
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
			SensorValue[fourbarEnc]=0;
			SensorValue[ldtEnc]=0;
			SensorValue[rdtEnc]=0;
			break;
		case 2:
			clearLCDLine(0);
			clearLCDLine(1);
			displayLCDString(0,0, thirdAutonString);
			displayLCDString(1,0, enterString);
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
			SensorValue[fourbarEnc]=0;
			SensorValue[ldtEnc]=0;
			SensorValue[rdtEnc]=0;
			break;
		case 3:
			clearLCDLine(0);
			clearLCDLine(1);
			displayLCDString(0,0, fourthAutonString);
			displayLCDString(1,0, enterString);
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
			SensorValue[fourbarEnc]=0;
			SensorValue[ldtEnc]=0;
			SensorValue[rdtEnc]=0;
			break;
		default:
			lcdCount = 0;
			SensorValue[rdr4bEnc]=0;
			SensorValue[ldr4bEnc]=0;
			SensorValue[fourbarEnc]=0;
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
	startTask(drive);
}
