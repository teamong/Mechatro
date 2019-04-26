/* Run and stop
   Check out more information below..
   https://cafe.naver.com/easybread/9651

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

Mechatro MA;
Mechatro MB;

void setup() {
  MA.attach( PWM_A, DIR_A, BRAKE_A, SEN_A );
  MB.attach( PWM_B, DIR_B, BRAKE_B, SEN_B );
}

void loop() {

  // foreward Full speed
  MA.speed(100);
  MB.speed(100);
  delay(2000);

  // free running stop
  MA.speed(0);
  MB.speed(0);
  delay(2000);

  //Reverse Full speed
  MA.speed(-100);
  MB.speed(-100);
  delay(2000);

  // fastStop
  MA.fastStop();
  MB.fastStop();

  while(1){}

}
