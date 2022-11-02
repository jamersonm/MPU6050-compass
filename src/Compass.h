#ifndef COMPASS_H
#define COMPASS_H

#include <Wire.h>
#include <MPU6050_light.h>

MPU6050 mpu(Wire);
float yaw = 0;
int divider;
unsigned long timer = millis();

void calibrateCompass()
{
    mpu.calcOffsets(true, true);
}

void configureCompass()
{
    Wire.begin();
    mpu.begin();
    calibrateCompass();
}

void loopCompass()
{
    mpu.update();
    if((millis() - timer) < 10) // yaw = yaw + yaw_rate*dt
    {
        yaw = mpu.getAngleZ();

        //set interval 0 <= angle < 360
        if(yaw >= 360)
        {
            divider = yaw / 360;
            for(int i = 0; i < divider; i++)
            yaw = yaw - 360;
        }
        else if(yaw < 0)
        {
            divider = yaw / 360;
            yaw = yaw + 360;
            for(int i = 0; i < divider; i++)
            yaw = yaw + 360;
        }
    }
    if((millis() - timer) > 20)
        timer = millis();
}

void printCompass()
{
    Serial.print("Compass: ");
    Serial.print(yaw);
    Serial.println("°");
}

#endif