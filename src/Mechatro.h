/*
   Mechatro.h

   Library for mechatro cording sheild.
   but it can be used any project with L298x Driver

   Created by botto, april 13, 2019.
   Released into the public domain.

   메카트로 코딩쉴드 모터 컨틀롤 라이브러리
   메카트로 코딩쉴드용으로 개발 되었으나
   L298x 드라이버를 사용하는 어떤 프로젝트에도 사용 가능함.

   URL : https://cafe.naver.com/easybread
*/

#include <Arduino.h>

#ifndef MECHATRO_H
#define MECHATRO_H

class Mechatro
{
  public:

    Mechatro();
    //Mechatro(int pwmEnable, int dirPIN );
    Mechatro(int pwmEnable, int dirPIN, int brakePIN, int senPIN);

    void attach(int pwmEnable, int dirPIN, int brakePIN, int senPIN);
    void speed(int pwmVal);
    void fastStop();
    
    //
    void setCircuitSpec(float V_shunt_ampGain, float R_shunt, float RefVoltADC);
    
    // Use getVolt(),getVoltRMS() after getCurrent();
    float getCurrent();    // Unit : [mA] , Retrun RMS Current.
    float getVolt();       // Unit : [mV] , for comparing calculated volt with shunt resistor volt of circuit.
    float getVoltRMS();    // Unit : [mV] , for checking RMS result.

  private:

    float calRMS(float Value);
    void resetRMS();

    float V_sen;
    float V_RMSsen;
    float C_RMSshunt;

    byte  _pwmEnable;
    byte  _dirPIN;
    byte  _brakePIN;
    byte  _senPIN;

    // ADC Data at Shut Resistor
    int ADC_Shunt;

    // Circuit Specification
    float _RefVoltADC = 5.0;
    float volt_per_current = 1.1;   // at R_shunt=0.1[Ω], V_shunt_ampGain = 11
    /*  What is the Volt per current?
        It is used to caluate the current at motor.
        When V_sen is the volt from analogRead(_senPIN) at R_shunt=0.1, V_shunt_ampGain = 11

        V_shunt = V_sen / V_shunt_ampGain = I_shunt * R_shunt
                = V_sen / 11              = I_shunt * 0.1

        ∴ I_shunt = V_sen / 1.1

        The constant value 1.1[V/A] is called volt_per_current.
    */

    // Variables for calculating Root Mean Square
    int   RMS_band = 20;
    float SamplingData[20];
    float SamplingDataSquare_sum  =  0;
    int   RMS_i    =  1;
    int   RMS_n    =  1;

};
#endif
