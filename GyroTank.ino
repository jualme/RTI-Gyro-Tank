#include <Pixy2.h>
Pixy2 pixy;

int E1 = 5;  //M1 Speed Control
int E2 = 6;  //M2 Speed Control
int M1 = 4;  //M1 Direction Control
int M2 = 7;  //M1 Direction Control

void stop(void)  //Stop
{
  digitalWrite(E1, 0);
  digitalWrite(M1, LOW);
  digitalWrite(E2, 0);
  digitalWrite(M2, LOW);
}
void advance(char a, char b)  //Move forward
{
  analogWrite(E1, a);  //PWM Speed Control
  digitalWrite(M1, HIGH);
  analogWrite(E2, b);
  digitalWrite(M2, HIGH);
}
void back_off(char a, char b)  //Move backward
{
  analogWrite(E1, a);
  digitalWrite(M1, LOW);
  analogWrite(E2, b);
  digitalWrite(M2, LOW);
}
void turn_L(char a, char b)  //Turn Left
{
  analogWrite(E1, a);
  digitalWrite(M1, LOW);
  analogWrite(E2, b);
  digitalWrite(M2, HIGH);
}
void turn_R(char a, char b)  //Turn Right
{
  analogWrite(E1, a);
  digitalWrite(M1, HIGH);
  analogWrite(E2, b);
  digitalWrite(M2, LOW);
}

void setup(void) {
  int i;
  for (i = 4; i <= 7; i++)
    pinMode(i, OUTPUT);
  Serial.begin(9600);  //Set Baud Rate
  Serial.println("Run keyboard control");
  pixy.init();
  pixy.changeProg("line");
  digitalWrite(E1, LOW);
  digitalWrite(E2, LOW);
}

void loop(void) {
  int8_t i;
  char buf[128];
  pixy.line.getAllFeatures();
  for (i=0; i<pixy.line.numBarcodes; i++)
  {
    sprintf(buf, "barcode %d: ", i);
    Serial.print(buf);
    // gets the barcode value
    Serial.print(pixy.line.barcodes[i].m_code);
  }
  
  if (Serial.available()) {
    char val = Serial.read();
    if (val != -1) {
      switch (val) {
        case 'w':             //Move Forward
          advance(255, 255);  //move forward in max speed
          break;
        case 's':              //Move Backward
          back_off(255, 255);  //move back in max speed
          break;
        case 'a':  //Turn Left
          turn_L(100, 100);
          break;
        case 'd':  //Turn Right
          turn_R(100, 100);
          break;
        case 'z':
          Serial.println("Hello");
          break;
        case 'x':
          stop();
          break;
      }
    } else stop();
  }
}