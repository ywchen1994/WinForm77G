#pragma once
#include<iostream>
using namespace std;
typedef unsigned char uint8;
typedef uint16_t uint16;

class Radar_77G
{
private:
	uint8 buffer_array[16] = {0};
public:
	
	uint8 getSum();
	uint8 getRadarID();
	uint8 getTargetID();
	uint8 getTargetPriority();
	uint8 getReportSequenceNumber();
	float getRx();
	float getRy();
	float getVelocity();
	float getAngle();
	float getRCS();
	float getAceleration();
	uint8 getTargetType();
	
};


inline uint8 Radar_77G::getSum()
{
	uint8 Sum;
	for (uint8 i = 0; i < 16; i++)
		Sum += buffer_array[i];
	return Sum;
}
inline uint8 Radar_77G::getRadarID()
{
	return buffer_array[0];
	//0~15; 
	//0: Driver Back Side Radar.
	//	1 : Passenger Back Side Radar
    //	2 : Driver Front Side Radar.
	//	3 : Passenger Side Front Side Radar
    //	4 : Forward Collision Warning Radar
	//	5 : Rear Collision Warning Radar

}
inline uint8 Radar_77G::getTargetID()
{
	return buffer_array[1];
}

//1~32，0 : 此目標無效
inline uint8 Radar_77G::getTargetPriority()
{
	if (1 <= buffer_array[2] && buffer_array[2] <= 32)
		return buffer_array[2];
	else
		return 0;
}

//Each Radar should increase the Report Sequence Number 
//in a circular sequence from 0~255 when the radar sends
//a multi - target report.
inline uint8 Radar_77G::getReportSequenceNumber()
{
	return buffer_array[3];
}

//Longitudinal Distance(RX，meter)
inline float Radar_77G::getRx()
{
	uint16 temp =(uint16)buffer_array[4] + (uint16)buffer_array[5] << 8;
	return (float)(temp - 10000) / 100.0f;
}

//Longitudinal Distance(RY，meter)
inline float Radar_77G::getRy() {
	uint16 temp = (uint16)buffer_array[6] + (uint16)buffer_array[7] << 8;
	return (float)(temp - 10000) / 100.0f;
}

//Relative Velocity(km/h)
inline float Radar_77G::getVelocity()
{
	uint16 temp = (uint16)buffer_array[8] + (uint16)buffer_array[9] << 8;
	return (float)(temp - 10000) / 100.0f;
}

//Azimuth Angle(degree)
inline float Radar_77G::getAngle()
{
	uint16 temp = (uint16)buffer_array[10] + (uint16)buffer_array[11] << 8;
	return (float)(temp - 10000) / 100.0f;
}

//RCS(dB)
inline float Radar_77G::getRCS()
{
	uint16 temp = (uint16)buffer_array[12] + (uint16)buffer_array[13] << 8;
	return (float)temp / 10.0f - 100.0f;
}
//Acceleration(m/s^2)
inline float Radar_77G::getAceleration()
{
	return ((float)buffer_array[14] - 100.0f) / 10.0f;
}
//Target Type
//1：guardrail
//5：moving target in detection zone
//6：stationary target in detection zone(for RCTA)
//10：moving target in warning zone
//11：stationary target in warning zone(for RCTA)
inline uint8 Radar_77G::getTargetType(){
	return buffer_array[15];
}