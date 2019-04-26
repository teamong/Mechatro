/* Motor current Sensing
   when the swich at D2 PIN is turned on,
   Two Moters at MA,MB socket run full speed and stop.
   The Current form each motor is printed to Serial monitor or ploter while motors running.
   Check out more information below..
   https://cafe.naver.com/easybread/9651

   모터 전류 센싱
   D2핀에 연결된 스위치 on 시
   소켓 MA, MB에 연결된 모터가 풀 스피드로 작동되었다가 멈춤니다.
   각각의 모터에 흐르는 전류는 시리얼모니터 또는 플로터에 출력 됩니다.
   아래에서 더 많은 정보를 확인하세요.
   https://cafe.naver.com/easybread/9651   
*/

#include <Mechatro.h>

// PIN definition for L298x Driver.
// Depends on your Circuit.
#define PWM_A     3
#define PWM_B    11
#define BRAKE_A   9
#define BRAKE_B   8
#define DIR_A    12
#define DIR_B    13
#define SEN_A     0
#define SEN_B     1

Mechatro motor[2];

void setup() {
  Serial.begin(9600);
  Serial.flush();
  pinMode(2, INPUT); // SW
  motor[0].attach( PWM_A, DIR_A, BRAKE_A, SEN_A );
  motor[1].attach( PWM_B, DIR_B, BRAKE_B, SEN_B );
}

void loop() {

  while ( digitalRead(2) == LOW) {
    // wait input HIGH at D2 PIN
  }

  for ( int i = 0; i < 500; i++) {
    if ( i == 50) {
      motor[0].speed(100);
      motor[1].speed(100);;
    }
    if (i == 450) {
      motor[0].speed(0);
      motor[1].speed(0);
    }
    Serial.print( motor[0].getCurrent() );
    Serial.print( " " );
    Serial.println( motor[1].getCurrent() );
  }
}
