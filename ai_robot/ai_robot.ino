#include <SoftwareSerial.h>

#include <DFRobot_LedControl.h>

#define LED_N 0
#define LED_L 1
#define LED_R 2

#define CS_L 2
#define CLK_L 3
//#define LHAND_F 4
//#define LHAND_B 5
//#define RHAND_F 6
//#define RHAND_B 7
#define DIN_L 8
#define CS_R 9
#define CLK_R 4
#define DIN_R 5
#define Soft 6

#define HEAD_L A0
#define HEAD_R A1

SoftwareSerial soft(6,7);

const uint8_t maxBitmap[][8] = {
  {B00000000, B00000000, B00000000, B00000000, B11111111, B00000000, B00000000, B00000000},
  {B00000000, B00001000, B00010100, B00100010, B01000001, B00000000, B00000000, B00000000},
  {B00000000, B00010000, B00101000, B01000100, B10000010, B00000000, B00000000, B00000000}
};
// 创建对象
DFRobot_LedControl led_l;
DFRobot_LedControl led_r;


// 主程序开始
void setup() {
  soft.begin(9600);
  led_l.begin(DIN_L, CLK_L, CS_L);//DIN, CLK, CS
  led_r.begin(DIN_R, CLK_R, CS_R);//DIN, CLK, CS
  pinMode(HEAD_L, OUTPUT);
  pinMode(HEAD_R, OUTPUT);
//  pinMode(LHAND_F, OUTPUT);
//  pinMode(LHAND_B, OUTPUT);
//  pinMode(RHAND_F, OUTPUT);
//  pinMode(RHAND_B, OUTPUT);
  eyesOff();
  noTurn();
}

void loop() {
  if (soft.available()) {
    soft.read();
    eyesOn();
    shake();
    eyesOff();
  }
}

void eyesOff() {
  led_l.show(maxBitmap[LED_N]);
  led_r.show(maxBitmap[LED_N]);
}

void eyesOn() {
  led_l.show(maxBitmap[LED_L]);
  led_r.show(maxBitmap[LED_R]);
}

void shake() {
  leftTurn();
  noTurn();
  rightTurn();
  noTurn();
  leftTurn();
  noTurn();
}

void noTurn() {
  digitalWrite(HEAD_L, 1);
  digitalWrite(HEAD_R, 1);
//  digitalWrite(LHAND_F, 1);
//  digitalWrite(LHAND_B, 1);
//  digitalWrite(RHAND_F, 1);
//  digitalWrite(RHAND_B, 1);
  delay(500);
//  Serial.println("0");
}

void leftTurn() {
  digitalWrite(HEAD_L, 1);
  digitalWrite(HEAD_R, 0);
//  digitalWrite(LHAND_F, 1);
//  digitalWrite(LHAND_B, 0);
//  digitalWrite(RHAND_F, 1);
//  digitalWrite(RHAND_B, 0);
//  Serial.println("L");
  delay(500);
}

void rightTurn() {
  digitalWrite(HEAD_L, 0);
  digitalWrite(HEAD_R, 1);
//  digitalWrite(LHAND_F, 0);
//  digitalWrite(LHAND_B, 1);
//  digitalWrite(RHAND_F, 0);
//  digitalWrite(RHAND_B, 1);
//  Serial.println("R");
  delay(1000);
}
