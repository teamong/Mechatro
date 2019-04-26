# mechatro
Library for mechatro coding board (메카트로 라이브러리)

Methods and Functions

  Mechatro();
  Mechatro(int pwmEnable, int dirPIN, int brakePIN, int senPIN)

  attach(int pwmEnable, int dirPIN, int brakePIN, int senPIN)

  speed(int pwmVal)
    pwmVAL = motor speed
    pwmPAL range
                 Forward :         1 ~ 100
       free running stop :         0
                 Reverse : -100 ~ -1
  
  fastStop()
    
  setCircuitSpec(float V_shunt_ampGain, float R_shunt, float RefVoltADC)
    set circuit specification
    V_shunt_ampGain = op-amp gain to Amplify shunt resistor voltage to an arduino
                      (default 1.1)
    R_shunt = Shunt Resitor[Ω]. (default 0.1Ω)
    RefVoltADC = Referance volt for ADC. depend on arduino setting (default 5V)
   
  getCurrent()
    Retrun RMS Current (float)
    Unit : [mA] 

  getVolt()
    * have to use after getCurrent()
    Retrun shunt resistor volt.
    Unit : [mV]

  getVoltRMS();
    * have to use after getCurrent()
    Retrun shunt resistor RMS volt.
    Unit : [mV]
