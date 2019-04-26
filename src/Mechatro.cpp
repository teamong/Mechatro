#include <Mechatro.h>

Mechatro::Mechatro() {
  this->resetRMS();
}

Mechatro::Mechatro(int pwmEnable, int dirPIN, int brakePIN, int senPIN) {
  this->attach(pwmEnable, dirPIN, brakePIN, senPIN);
}

void Mechatro::attach(int pwmEnable, int dirPIN, int brakePIN, int senPIN) {
  _pwmEnable = pwmEnable;
  _dirPIN    = dirPIN;
  _brakePIN  = brakePIN;
  _senPIN    = senPIN;
  pinMode(_pwmEnable, OUTPUT);
  pinMode(_dirPIN, OUTPUT);
  pinMode(_brakePIN, OUTPUT);
  digitalWrite(_dirPIN, 1);    // 0:Reverse, 1:Forward
  digitalWrite(_brakePIN, 0);  // 0 : Fast Motor Stop Off, 1 : Fast Motor Stop On
  this->resetRMS();
}

/*
  ■ pwmVAL = motor speed
  ■ pwmPAL range
                 Forward :         1 ~ 100
       free running stop :         0
                 Reverse : -100 ~ -1
*/
void Mechatro::speed(int pwmVal) {
  digitalWrite(_brakePIN, 0);

  if (pwmVal > 100) {
    pwmVal = 100;
  }
  if (pwmVal < -100) {
    pwmVal = -100;
  }

  if (pwmVal == 0 ) {
    analogWrite(_pwmEnable, 0);
  }
  else
  {
    if ( pwmVal < 0 ) {
      pwmVal = -pwmVal;
      digitalWrite(_dirPIN, 0);
    }
    else {
      digitalWrite(_dirPIN, 1);
    }
    pwmVal = map(pwmVal, 0, 100, 0, 255);
    analogWrite(_pwmEnable, pwmVal);
  }
}

void Mechatro::fastStop() {
  digitalWrite(_brakePIN, 1);
}

float Mechatro::getCurrent() {
  ADC_Shunt = analogRead(_senPIN);
  V_sen = ( ADC_Shunt * _RefVoltADC ) / 1.023;
  V_RMSsen = ( this->calRMS(ADC_Shunt) * _RefVoltADC ) / 1.023;
  C_RMSshunt = V_RMSsen / volt_per_current;
  return C_RMSshunt;
}

float Mechatro::getVolt() {
  return this->V_sen;
}
float Mechatro::getVoltRMS() {
  return this->V_RMSsen;
}

void Mechatro::setCircuitSpec(float V_shunt_ampGain, float R_shunt, float RefVoltADC) {
  volt_per_current = V_shunt_ampGain * R_shunt;
  _RefVoltADC      = RefVoltADC;
}

// Calculating Root Mean Square
float Mechatro::calRMS(float value) {

  /*
    int i = RMS_i - 1;
    if ( i < 0 ) {
      i = RMS_band - 1;
    }

    if ( abs( SamplingData[i] - value) > 300 ) {
      this->resetRMS();
      SamplingDataSquare_sum = value * value;
      SamplingData[0] = value;
      return value;
    } else {
  */
  SamplingDataSquare_sum -= SamplingData[RMS_i] * SamplingData[RMS_i];
  SamplingData[RMS_i]     = value;
  SamplingDataSquare_sum += SamplingData[RMS_i] * SamplingData[RMS_i];

  RMS_i++;
  if ( RMS_i == RMS_band ) {
    RMS_i = 0;
  }
  if ( RMS_n <  RMS_band ) {
    RMS_n++;
  }
  return sqrt( SamplingDataSquare_sum / RMS_n );
  //}
}

void Mechatro::resetRMS() {
  RMS_i = 1;
  RMS_n = 1;
  for ( int i = 0 ; i < RMS_band ; i++) {
    SamplingData[i]  = 0;
  }
}
