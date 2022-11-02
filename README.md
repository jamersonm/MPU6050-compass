# MPU6050-compass
Multitasking compass on TTGO-Tbeam using MPU6050tbeam    

## Menu

1. [Hardware](#hardware)  
  1.1 [TTGo-Tbeam](#ttgo-tbeam)  
  1.2 [MPU6050](#mpu6050)
2. [Software](#software)  
  2.1 [MPU6050_light library](#mpu6050_light-library)  
  2.2 [Compass](#compass)  
  2.3 [main](#main)
3. [Freedom moviment](#freedom-moviment)  
4. [References](#references)

### Hardware
#### TTGo-Tbeam

#### MPU6050


### Software
#### MPU6050_light library
- By .pio file, this library will be automatically imported.  
- Link to GitHub page [MPU6050_ligth](https://github.com/rfetick/MPU6050_light).  

#### Compass
- At first, was included the dependencies  
```
#include <Wire.h>
#include <MPU6050_light.h>
```
and setted global variables required on next methods.
```
MPU6050 mpu(Wire);              //MPU6050 object
float yaw = 0;                  
int divider;                    //to set degrees range
unsigned long timer = millis(); //auxiliar variable of time
```
- Then, two methods to initialize and calibrate the sensor was defined.
```
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
```
- The loop function calculates the integral of Z axis angular speed by time using a small interval of 10 miliseconds.
```
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
```
- At last, the print function just do what its name says.
```
void printCompass()
{
    Serial.print("Compass: ");
    Serial.print(yaw);
    Serial.println("°");
}
```

#### main
- As Compass, at first was included the dependencies and setted the auxiliar global variable of time.
```
#include <Arduino.h>
#include "Compass.h"

unsigned long timer_print = millis();
```
- On setup, just was initiated serial communication and the compass. 
```
void setup() {
  Serial.begin(9600);
  configureCompass(); //initialize  the MPU 6050 sensor
}
```
- Otherwise, on loop was started loopCompass and setted to print yaw every 5 seconds.
```
void loop() {
  loopCompass(); // MPU sensor start getting yaw
  if((millis() - timer_print) > 5000) // after 5 segs
  {
    printCompass(); // print yaw
    timer_print = millis();
  }
}
```

### Freedom moviment
- With a MPU6050 gyroscope and accelerometer sensor is possible calculate the acceleration by carrying out an integral acceleration of the object over time and the angular speed of each axis.
![Freedom moviment](https://www.ceva-dsp.com/wp-content/uploads/sites/3/2018/11/HIL-What-is-an-IMU-wk-1.jpg)  
- On this experience was requested get yaw coordinate. So, the calculation was about how fast the z-axis orientation changes, in another other, $yaw = \int z_ω dt$

### References
- Rafiq, A., Rohman, W., & Riyanto, S. (2020). Development of a Simple and Low-cost Smartphone Gimbal with MPU-6050 Sensor. Journal of Robotics and Control (JRC), 1(4), 136-140. doi:https://doi.org/10.18196/jrc.1428
