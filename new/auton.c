#include "main.c"
#include "driving.c"

const int enterString[] = {247,32,32,32,32,32,69,110,116,101,114,32,32,32,32,246};//this is "�??     Enter    �?�"

const string firstAutonString = "Forward+Backward";
const string secondAutonString = "Left+Right";
const string thirdAutonString = "Stationary Goal";
const string fourthAutonString = "Nothing";

int lcdCount = 0;

const float drivingKP = 1.2;
const float drivingKI = 0.0;
const float drivingKD = 0.7;

const int C_rOfWheels = 2;
const int C_rOfRobot = 13;
const float C_PI = 3.1415926;
const int C_motorPower = 100;
const float C_dr4bconstant = 2.5;

//for left encoder, forwards is pos, backwards is neg
//for right encoder, forwards is neg, backwards is pos
void displayEnterString(int line){//this displays *enterString[]* to *line*
	clearLCDLine(line);
	for(int i = 0; i < 16; ++i){
		displayLCDChar(line, i, enterString[i]);
	}
}
int getEncValForDistance(int inches){//this returns the encoder value for drivetrain distance
	return (360*inches)/(C_rOfWheels*C_PI*2);
}
int getEncValForTurn(int degrees){//this returns how many times an encoder on the drivetrain needs to turn in relation to how far the robot needs to turn
	return degrees*((float)C_rOfRobot/(float)C_rOfWheels);
}
void gyroTurn( int degrees){
	//plz setup
}

void moveForwards(int distance){//this moves the robot forwards *distance* inches
	int encVal = getEncValForDistance(distance);
	SensorValue[ldtEnc] = 0;
	SensorValue[rdtEnc] = 0;
	int lastError = encVal;
	int totalError = 0;
	while(true){//-encVal<SensorValue[rdtEnc]){
		int error = encVal+SensorValue[rdtEnc];
		if(totalError<50)totalError += error;
		else totalError=0;
		int power = ((drivingKP*error)+(drivingKI*totalError)+(drivingKD*(error-lastError)));
		if(power>90){
			motor[ldt1]=motor[ldt2]=90;
			motor[rdt1]=motor[rdt2]=-90;
		}
		else if(power<10&&power<-10){
			motor[ldt1]=motor[ldt2]=0;
			motor[rdt1]=motor[rdt2]=0;
		}else{
			motor[ldt1]=motor[ldt2]=power;
			motor[rdt1]=motor[rdt2]=-power;
		}
		string err = "";
		err = err + error;
		writeDebugStreamLine(err);
		wait1Msec(25);
	}
	motor[ldt1]=motor[ldt2]=0;
	motor[rdt1]=motor[rdt2]=0;
}
void moveBackwards(int distance){//this moves the robot backwards *distance* inches
	int encVal = getEncValForDistance(distance);
	SensorValue[ldtEnc] = 0;
	SensorValue[rdtEnc] = 0;
	int lastError = encVal;
	int totalError = 0;
	while(encVal>SensorValue[rdtEnc]){
		int error = encVal+SensorValue[rdtEnc];
		if(totalError<50)totalError += error;
		else totalError=0;
		int power = ((drivingKP*error)+(drivingKI*totalError)+(drivingKD*(error-lastError)));
		if(power>90){
			motor[ldt1]=motor[ldt2]=-90;
			motor[rdt1]=motor[rdt2]=90;
		}
		if(power<10){
			motor[ldt1]=motor[ldt2]=0;
			motor[rdt1]=motor[rdt2]=0;
		}
		else{
		motor[ldt1]=motor[ldt2]=-power;
		motor[rdt1]=motor[rdt2]=power;
		}
		wait1Msec(25);
	}
	motor[ldt1]=motor[ldt2]=0;
	motor[rdt1]=motor[rdt2]=0;
}
void turnRight(int degrees){//this turns the robot to the right *degrees* degrees
	gyroTurn((float)degrees);
	motor[ldt1] = motor[ldt2] = C_motorPower;
	motor[rdt1] = motor[rdt2] = C_motorPower;
	wait1Msec((15*1000)/(7*degrees));
	motor[ldt1] = motor[ldt2] = 0;
	motor[rdt1] = motor[rdt2] = 0;
}
void turnLeft(int degrees){//this turns the robot to the left *degrees* degrees
	gyroTurn((float)(-degrees));
	motor[ldt1] = motor[ldt2] = -C_motorPower;
	motor[rdt1] = motor[rdt2] = -C_motorPower;
	wait1Msec((15*1000)/(7*degrees));
	motor[ldt1] = motor[ldt2] = 0;
	motor[rdt1] = motor[rdt2] = 0;
}
void lowerMGM(){//lowers mgm
	motor[mgm]= C_motorPower;
	wait1Msec(500);
	motor[mgm] = 0;
}
void raiseMGM(){//raises mgm
	motor[mgm] = -C_motorPower;
	wait1Msec(500);
	motor[mgm] = 0;
}
void rotateDr4bUpTo(float distance){//rotates double reverse fourbar up to *distance* height
	int encVal = abs(distance*C_dr4bconstant);
	SensorValue[rdr4bEnc]=0;
	SensorValue[ldr4bEnc]=0;
	while(SensorValue[ldr4bEnc]>-encVal && SensorValue[rdr4bEnc]<encVal){
		motor[ldr4b] = -C_motorPower;
		motor[rdr4b] = C_motorPower;
		encVal = abs(distance*C_dr4bconstant);
	}
	motor[ldr4b] = motor[rdr4b] = 0;
}
void rotateDr4bDownTo(float distance){//rotates double reverse fourbar down to *distance* height
	SensorValue[rdr4bEnc]=0;
	SensorValue[ldr4bEnc]=0;
	int encVal = abs(distance*C_dr4bconstant);
	while(SensorValue[ldr4bEnc]<encVal && SensorValue[rdr4bEnc]>-encVal){
		motor[ldr4b] = C_motorPower;
		motor[rdr4b] = -C_motorPower;
		encVal = abs(distance*C_dr4bconstant);
	}
	motor[ldr4b] = motor[rdr4b] = 0;
}
void harvesterUp(){//intakes the cone
	motor[claw] = C_motorPower;
	wait1Msec(500);
	motor[claw] = 0;
}
void harvesterDown(){ //shoots out the code
	motor[claw] = -C_motorPower;
	wait1Msec(1000);
	motor[claw] = 0;
}
void rotateFourbarTo(int position){
	if(SensorValue[fourbarPot]<position){//if the current position is less than desired
		motor[fourbar] = C_motorPower;
		while(SensorValue[fourbarPot]<position) wait1Msec(5);
		motor[fourbar] = 0;
	}else if(SensorValue[fourbarPot]>position){//if the current position is greater than desired
		motor[fourbar] = -C_motorPower;
		while(SensorValue[fourbarPot]>position) wait1Msec(5);
		motor[fourbar] = 0;
	}
}
task auton(){//main task
	getEncValForTurn(1);
	switch(lcdCount){
		case 0:
			displayLCDString(0,0, firstAutonString);
			displayLCDString(1,0, "is running!");
			moveForwards(10);
			moveBackwards(10);
			break;
		case 1:
			displayLCDString(0,0, secondAutonString);
			displayLCDString(1,0, "is running!");
			turnLeft(20);
			turnRight(20);
			break;
		case 2:
			displayLCDString(0,0, thirdAutonString);
			displayLCDString(1,0, "is running!");
			rotateDr4bUpTo(35);
			rotateFourbarTo(75);
			moveForwards(3);
			rotateFourbarTo(50);
			wait1Msec(500);
			moveForwards(2.5);
			wait1Msec(1000);
			motor[ldr4b] = motor[rdr4b] = 0;
			motor[claw] = -100;
			wait1Msec(2000);
			motor[claw] = 0;
			moveBackwards(7);
			break;
		case 3:
			displayLCDString(0,0, fourthAutonString);
			displayLCDString(1,0, "is running!");
			break;
		default:
			break;
	}
}
