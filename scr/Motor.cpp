#include "Motor.h"

Motor::Motor() {
  for ( int i ; i < RMS_band ; i++) {
    v_2[i]  = 0;
  }
}

Motor::Motor(int _pwmPin, int _dirPin, int _brakePin, int _senPin) {
  this->attach(_pwmPin, _dirPin, _brakePin, _senPin);
}

void Motor::attach(int _pwmPin, int _dirPin, int _brakePin, int _senPin) {
  pwmPin   = _pwmPin;
  dirPin   = _dirPin;
  brakePin = _brakePin;
  senPin   = _senPin;
  pinMode(pwmPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(brakePin, OUTPUT);
  digitalWrite(dirPin, 1);    // 모터 방향 설정 0:역, 1:정
  digitalWrite(brakePin, 0);  // 0:브레이크 해제, 1:브레이크 작동
  for ( int i ; i < RMS_band ; i++) {
    v_2[i]  = 0;
  }
}

int Motor::speed(int pwmVal) {
  if (pwmVal == 0 ) {
    digitalWrite(brakePin, 0);    // 0:브레이크 해제, 1:브레이크 작동
    analogWrite(pwmPin, 0);       // 모터 속도 : 0(정지) ~ 255(최고속)
  }
  else
  {
    if ( pwmVal < 0 ) {
      pwmVal = -pwmVal;
      digitalWrite(dirPin, 0);                   // 모터 방향 설정 0:역, 1:정
    }
    else {
      digitalWrite(dirPin, 1);                    // 모터 방향 설정 0:역, 1:정
    }
    pwmVal = map(pwmVal, 0, 100, 100, 255);
    digitalWrite(brakePin, 0);    // 0:브레이크 해제, 1:브레이크 작동
    analogWrite(pwmPin, pwmVal);  // 모터 속도 : 0(정지) ~ 255(최고속)
  }
  return 0;
}

float Motor::calCurrent() {
  volt    = analogRead(senPin);
  volt    = this->calRMS_vlot(volt);
  volt    = (volt * 5.0 ) / 1023.0;
  current = volt / vpc;
  return  current;
}

float Motor::calTorque() {
  volt    = analogRead(senPin);
  volt    = this->calRMS_vlot(volt);
  volt    = (volt * 5.0 ) / 1023.0;
  current = volt / vpc;
  t_gfcm  = Km * current;
  return  t_gfcm;
}

void Motor::setProperties(float _Km, float _currentLimit) {
  Km = _Km;
  currentLimit = _currentLimit;
}

float Motor::calRMS_vlot(float _value) {

  float v_2_temp;
  v_2_temp = _value * _value;
  v_2_sum = v_2_sum - v_2[RMS_i] + v_2_temp ;
  v_2[RMS_i]  = v_2_temp;

  RMS_i++;
  if ( RMS_i == RMS_band ) { RMS_i = 0; }
  if ( RMS_n <  RMS_band ) { RMS_n++;   }
  return sqrt( v_2_sum / RMS_n );
}
