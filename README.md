Library for mechatro coding board with L298x
========================================
   Library for mechatro cording sheild.
   
   but it can be used any project with L298x Driver.
   
   메카트로 코딩쉴드 모터 컨틀롤 라이브러리
   
   메카트로 코딩쉴드용으로 개발 되었으나
   
   L298x 드라이버를 사용하는 어떤 프로젝트에도 사용 가능함.

Methods and Functions
-------------------

* Mechatro()
* Mechatro(int pwmEnable, int dirPIN, int brakePIN, int senPIN)
* attach(int pwmEnable, int dirPIN, int brakePIN, int senPIN)
* speed(int pwmVal)

    pwmVAL = motor speed
    
    pwmPAL range
    
                    Forward :         1 ~ 100
                  
          free running stop :         0
                 
                    Reverse : -100 ~ -1
                   
* fastStop()
    
* setCircuitSpec(float V_shunt_ampGain, float R_shunt, float RefVoltADC)
 
  set circuit specification.
    
  V_shunt_ampGain = op-amp gain to Amplify shunt resistor voltage to an arduino (default 1.1)
                      
  R_shunt = Shunt Resitor[Ω]. (default 0.1Ω)
    
  RefVoltADC = Referance volt for ADC. depend on arduino setting (default 5V)
   
* getCurrent()

  Retrun RMS Current (float)

  Unit : [mA] 

* getVolt()

  have to use after getCurrent()

  Retrun shunt resistor volt.

  Unit : [mV]

* getVoltRMS()

  have to use after getCurrent()

  Retrun shunt resistor RMS volt.

  Unit : [mV]
