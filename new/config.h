#pragma config(Sensor, in1, gyro, sensorGyro)
#pragma config(Sensor, dgtl1, ldtEnc, sensorQuadEncoder)
#pragma config(Sensor, dgtl3, rdtEnc, sensorQuadEncoder)
#pragma config(Sensor, dgtl5, mgmEnc, sensorQuadEncoder)
#pragma config(Sensor, dgtl7, ldr4bEnc, sensorQuadEncoder)
#pragma config(Sensor, dgtl9, rdr4bEnc, sensorQuadEncoder)
#pragma config(Motor, port1, mgmr, tmotorVex393_HBridge, openLoop)
#pragma config(Motor, port3, ldr4b, tmotorVex393_MC29, openLoop)
#pragma config(Motor, port4, ldt1, tmotorVex393_MC29, openLoop)
#pragma config(Motor, port5, ldt2, tmotorVex393_MC29, openLoop)
#pragma config(Motor, port6, rdt1, tmotorVex393_MC29, openLoop)
#pragma config(Motor, port7, rdt2, tmotorVex393_MC29, openLoop)
#pragma config(Motor, port8, rdr4b, tmotorVex393_MC29, openLoop)
#pragma config(Motor, port10, mgml, tmotorVex393_HBridge, openLoop)
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)
#pragma platform(VEX2)
#include "Vex_Competition_Includes.c"
#include "driving.c"
#include "auton.c"