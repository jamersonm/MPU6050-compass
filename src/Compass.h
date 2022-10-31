#ifndef COMPASS_H
#define COMPASS_H

#include <Wire.h>
#include <MPU6050_light.h>

MPU6050 mpu(Wire);

class Compass {
private:
    float first;
    float last;
public:
    Compass(){configureCompass();}
    ~Compass(){}

    void calibrateCompass();
    void configureCompass();
    float readCompass();
    void printCompass();
};

void Compass::configureCompass()
{
    Wire.begin();
    mpu.begin();
    calibrateCompass();
}

void Compass::calibrateCompass()
{
    mpu.calcOffsets(true,true); // gyro and accelero
}

float Compass::readCompass()
{
    mpu.update();
    return (mpu.getAngleZ());
}

void Compass::printCompass()
{
    Serial.println(readCompass());
}

#endif