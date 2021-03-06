#include "auton.c"
//callable vars
bool colors = false;
int timed = 0;
bool precise = false;
const int fourbarTop = 1950;
const int fourbarParallel = 500;
const int fourbarBottom = 0;
int dr4bEncAvg = (SensorValue[ldr4bEnc]-SensorValue[rdr4bEnc])/2;
const int coneDistance = 230;
const short leftButton = 1;
const short centerButton = 2;
const short rightButton = 4;
//internal vars
int c4 = 0, c3 = 0, c2 = 0, c1 = 0;
int c4Partner = 0, c3Partner = 0, c2Partner = 0, c1Partner = 0;
int clawMode = 0;
bool lcdPartnerControl = true;
int autoStack(int stackCount){
	//start at parallel dr4b and parallel 4b
	//pid vars
	//run claw
	//dr4b full height
	//4b vertical
	//go down based on proportion of stack count
	//release claw
	//dr4b full height
	//run claw
	//4b horizontal
	//down to match load height
	return stackCount++;
}
void drivetrain(bool partnerControl){
	//Drivetrain
	//set threshold to 20 and make sure it is zero under it
	const int THRESHOLD = 20;
	if(abs(vexRT[Ch4])>THRESHOLD) c4 = vexRT[Ch4];
	else c4 = 0;
	if(abs(vexRT[Ch3])>THRESHOLD) c3 = vexRT[Ch3];
	else c3 = 0;
	if(abs(vexRT[Ch2])>THRESHOLD) c2 = vexRT[Ch2];
	else c2 = 0;
	if(abs(vexRT[Ch1])>THRESHOLD) c1 = vexRT[Ch1];
	else c1 = 0;
	if(abs(vexRT[Ch4Xmtr2])>THRESHOLD) c4Partner = vexRT[Ch4Xmtr2];
	else c4Partner = 0;
	if(abs(vexRT[Ch3Xmtr2])>THRESHOLD) c3Partner = vexRT[Ch3Xmtr2];
	else c3Partner = 0;
	if(abs(vexRT[Ch2Xmtr2])>THRESHOLD) c2Partner = vexRT[Ch2Xmtr2];
	else c2Partner = 0;
	if(abs(vexRT[Ch1Xmtr2])>THRESHOLD) c1Partner = vexRT[Ch1Xmtr2];
	else c1Partner = 0;
	//send these values to the motor
	if(!partnerControl){
		motor[ldt1] = c3+c4;
		motor[ldt2] = c3+c4;
		motor[rdt1] = -c3+c4;
		motor[rdt2] = -c3+c4;		
	}
	if(partnerControl){
		if(!precise){
			motor[ldt1] = c3Partner;
			motor[ldt2] = c3Partner;
			motor[rdt1] = -c2Partner;
			motor[rdt2] = -c2Partner;
		}
		if(precise){
			motor[ldt1] = c3Partner/2;
			motor[ldt2] = c3Partner/2;
			motor[rdt1] = -c2Partner/2;
			motor[rdt2] = -c2Partner/2;
		}
	}
}
void mobileGoal(bool partnerControl){
	if(partnerControl){
		if(vexRT[Btn6DXmtr2]){
			motor[mgm] = 127;
		}
		else if(vexRT[Btn6UXmtr2])motor[mgm] = -127;
		else motor[mgm] = 0;
	}
	if(!partnerControl){
		if(vexRT[Btn8U])motor[mgm] = 127;
		else if(vexRT[Btn8D])motor[mgm] = -127;
		else motor[mgm] = 0;
	}
}
void dr4b(){
	float lPower, rPower;
	if(vexRT[Btn6U]){
 		lPower=80;
 		rPower=-80;

 	}else if(vexRT[Btn6D]){
 		lPower=-80;
 		rPower=80;

 	}else if(dr4bEncAvg < 5){
 		lPower = -15;
 		rPower = 15;
 	}
	else{
	lPower = 0;
	rPower = 0;
	}

	motor[ldr4b] = lPower;
	motor[rdr4b] = rPower;
}
task drive(){
	startTask(slowFade);
	stopTask(auton);
	while(true){
		dr4bEncAvg = (SensorValue[ldr4bEnc]-SensorValue[rdr4bEnc])/2;
		long sysTime = nSysTime;
		//call drivetrain
		drivetrain(lcdPartnerControl);
		//mobile goal
		mobileGoal(lcdPartnerControl);
		//claw
		switch(clawMode){
			case 0:
				if((SensorValue[fourbarPot])<1050 && ((SensorValue[ldr4bEnc]-SensorValue[rdr4bEnc])/2)<20){
					motor[claw]=127;
					if(vexRT[Btn5D]){
						motor[claw]=-127;
					}																				//If the claw is close enough to the ground, activate the claw
					if(vexRT[Btn5U]){
						motor[claw]=127;
					}
				}
				else{
					motor[claw]=20;
					if(vexRT[Btn5D]){
						motor[claw]=-127;
					}
					if(vexRT[Btn5U]){
						motor[claw]=127;
					}
				}
				break;
			case 1:
				if((SensorValue[fourbarPot])<1400 && ((SensorValue[ldr4bEnc]-SensorValue[rdr4bEnc])/2)<60){
					motor[claw]=127;
					if(vexRT[Btn5D]){
						motor[claw]=-127;
					}																			//Extends the range so that match loads can be easily grabbed
					if(vexRT[Btn5U]){
						motor[claw]=127;
					}
				}
				else{
					motor[claw]=20;
					if(vexRT[Btn5D]){
						motor[claw]=-127;
					}
					if(vexRT[Btn5U]){
						motor[claw]=127;
					}
				}
				break;
			case 2:
				motor[claw]=127;
				if(vexRT[Btn5D]==1){
					motor[claw]=-127;
				}
				break;
		}
			//Changing clawModes
		if(vexRT[Btn7R])clawMode=1;
		if(vexRT[Btn7L])clawMode=0;
		if(vexRT[Btn7U])clawMode=2;

		//Changing LEDs
		if(vexRT[Btn8L] && !colors && (nSysTime-timed)>3000){
			stopTask(purpleWave);
			startTask(slowFade);
			colors = true;
			timed = nSysTime;
		}
		if(vexRT[Btn8L] && colors && (nSysTime-timed)>3000){
			stopTask(purpleWave);
			stopTask(slowFade);
			colors = false;
			timed = nSysTime;
		}
		if(vexRT[Btn8R] && !colors && (nSysTime-timed)>3000){
			stopTask(slowFade);
			startTask(purpleWave);
			colors = true;
			timed = nSysTime;
		}
		if(vexRT[Btn8R] && colors && (nSysTime-timed)>3000){
			stopTask(slowFade);
			stopTask(purpleWave);
			colors = false;
			timed = nSysTime;
		}
		//Changing driveModes
		if(vexRT[Btn5UXmtr2]) precise = true;
		if(vexRT[Btn5DXmtr2]) precise = false;
		//dr4b - Non-PID version
		dr4b();
		motor[fourbar]=c2;
		//displays current battery and backup battery voltage
		clearLCDLine(0);
		clearLCDLine(1);
		displayLCDString(0,0,"Battery: ");
		displayLCDNumber(0,9, nAvgBatteryLevel);
		displayLCDString(0,13, " mV");
		displayLCDString(1,0,"Backup: ");
		displayLCDNumber(1,9, BackupBatteryLevel);
		displayLCDString(1,13, " mV");

		//keep the loop timing consistently 25 ms
		int timeDiff = nSysTime - sysTime;
		wait1Msec(25-timeDiff);
		EndTimeSlice();
	}
}
void callsUnusedVariablesDontCallThis(){
	int discardVar;
	if(false){
		discardVar = fourbarTop;
		discardVar = fourbarParallel;
		discardVar = fourbarBottom;
		discardVar = coneDistance;
		autoStack(0);
		callsUnusedVariablesDontCallThis();
	}
}
