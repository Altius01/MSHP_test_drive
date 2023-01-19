// Вспоминаем управление моторами
#define PWM_A 3
#define DIR_A 12
#define BRAKE_A 9

#define PWM_B 11
#define DIR_B 13
#define BRAKE_B 8

#define ECHOE 1
#define TRIG 2

#include <EasyUltrasonic.h>

float Kp = 5.1;

int outs_length = 4;
int outs[] = {PWM_A, PWM_B, DIR_A, DIR_B};

void move_(int speed_A, int speed_B) {
  bool dir_a = speed_A > 0 ? 1 : 0;
  bool dir_b = speed_B > 0 ? 1 : 0;

  digitalWrite(DIR_A, dir_a);
  analogWrite(PWM_A, abs(speed_A));

  digitalWrite(DIR_B, dir_b);
  analogWrite(PWM_B, speed_B);
}

EasyUltrasonic dist_sensor;

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < outs_length; ++i)
    pinMode(outs[i], OUTPUT);

//  digitalWrite(BRAKE_A, 0);
//  digitalWrite(BRAKE_B, 0);
  dist_sensor.attach(TRIG, ECHOE);
}

// Пишем Пропорциональный регулятор. Выравниваемся по короткой стороне поля
void P_reg(int finish_distance) {
  int dist = dist_sensor.getDistanceCM();

  int error = dist - finish_distance;
  // Если dist > finish_distance, то error > 0, ехать нужно вперед
  // Если dist < finish_distance, то error < 0, ехать нужно назад

  move_(error*Kp, error*Kp);
}

void loop() {
  // put your main code here, to run repeatedly:
//  P_reg(70);
  move_(255, 255);
}
