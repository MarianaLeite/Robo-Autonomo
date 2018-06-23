#define ENB 5         //Enable do motor esquerdo
#define IN4 6         //Pino de ativação do motor esquerdo para frente
#define IN3 7         //Pino de ativação do motor esquerdo para trás
#define IN2 8         //Pino de ativação do motor direito para trás
#define IN1 9         //Pino de ativação do motor direito para frente
#define ENA 10        //Enable do motor direito
#define VA 180        //Velocidade motor direito
#define VB 198        //Velocidade motor esquerdo
#define echoPinD 11
#define trigPinD 12
#define echoPinE 3
#define trigPinE 4
#define data_acquisition 0
#define movement 1

long left_distance, right_distance;
int stage = 0;

void setup() {
  pinMode(ENB,OUTPUT); 
  pinMode(IN4,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(echoPinE,INPUT);
  pinMode(trigPinE,OUTPUT);
  pinMode(echoPinD,INPUT);
  pinMode(trigPinD,OUTPUT);
  analogWrite(ENA,VA);
  analogWrite(ENB,VB);
  Serial.begin(9600);
}

void move_foward() {
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}

void move_back() {
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  delay(40);
}

void turn_left() {
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  delay(40);
}

void turn_right() {
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  delay(50);
}

void stop() {
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,HIGH);
  (200);
}

int leftsensor_routine () {
  int period, distance;
  digitalWrite(trigPinE,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinE,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinE,LOW);
  period = pulseIn(echoPinE,HIGH);
  distance = (period/58);
  if (distance < 0) {
    distance *= -1;
  }
  return distance;
}

int rightsensor_routine () {
  int period, distance;
  digitalWrite(trigPinD,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinD,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinD,LOW);
  period = pulseIn(echoPinD,HIGH);
  distance = (period/58);
  if (distance < 0) {
    distance *= -1;
  }
  return distance;
}

void loop() {
  switch (stage) {
    case data_acquisition:
      move_foward();
      left_distance = leftsensor_routine();
      right_distance = rightsensor_routine();
      stage = movement;
      break;
    case movement:
      if (right_distance < 16) {
        stop();
        move_back();
        turn_left();
      }
      if (left_distance < 16) {
        stop();
        move_back();
        turn_right();
      }
      stage = data_acquisition;
      break;
  }
}
