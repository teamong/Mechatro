#ifndef MOTOR_H
#define MOTOR_H
#include <Arduino.h>
#define PWM_A     3
#define PWM_B    11
#define BRAKE_A   9
#define BRAKE_B   8
#define DIR_A    12
#define DIR_B    13
#define SEN_A     0
#define SEN_B     1

class Motor
{
  public:
    Motor();
    Motor(int _pwmPin, int _dirPin, int _brakePin, int _senPin);
    void attach(int _pwmPin, int _dirPin, int _brakePin, int _senPin);
    
    void  setProperties(float _Km, float _currentLimit);
    int   speed(int pwmVal);
    float calCurrent();
    float calTorque();
    
  private:
    float calRMS_vlot(float _value);
    byte  pwmPin;
    byte  dirPin;
    byte  brakePin;
    byte  senPin;

    float volt;
    float current;
    int   t_gfcm;
    
    // Motor constant
    float vpc = 1.1;     // volt_per_current,  R=0.1, amp = 11   V=I*R → V/11 = I* 0.1 →  I = V / 1.1 ,  1.1[V/A]
    float Km;
    float currentLimit;    
  
    // RMS of volt
    int   RMS_band = 20;
    float v_2[20]  ;
    float v_2_sum  =  0;
    int   RMS_i    =  0;
    int   RMS_n    =  0;
};
#endif
