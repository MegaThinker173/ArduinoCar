#define S0 4
#define S1 11
#define S2 2
#define S3 3
#define sensorOut 12

// motor one
#define enA 10
#define inA 9
#define inB 8
// motor two
#define enB 5
#define inC 7
#define inD 6

int Rfrequency;
int Gfrequency;
int Bfrequency;

void setup() {
  pinModeInit();
  // Setting frequency scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  Serial.begin(9600);
}

bool R_Red = false;
bool G_Red = false;
bool B_Red = false;

void loop() {
  RGB();
  if ((Rfrequency > 130) && (Rfrequency < 180)){
    R_Red = true;
  } else {
    R_Red = false;
  }
  
  if ((Gfrequency > 300) && (Gfrequency < 380)){
    G_Red = true;
  }else {
    G_Red = false;
  }
  
  if ((Bfrequency > 55) && (Bfrequency < 100)){
    B_Red = true;
  }
  else {
    B_Red = false;
  }

  if (R_Red && G_Red && B_Red) {
    goForward(200,150);
  }
  else if (R_Red && (G_Red == false) && B_Red) {
    goForward(100,200);
  }
  else if ((R_Red == false) && (G_Red == false) && (B_Red == false)) {
    goForward(200,150); 
  }
  else {
    stopMotors();
  }
}

void pinModeInit() {
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(inA, OUTPUT);
  pinMode(inB, OUTPUT);
  pinMode(inC, OUTPUT);
  pinMode(inD, OUTPUT);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
}

void RGB() {
  // Setting (Red)
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  Rfrequency = pulseIn(sensorOut, LOW);
  delay(100);

  // Setting (Green)
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  Gfrequency = pulseIn(sensorOut, LOW);
  delay(100);

  //Setting (Blue)
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  Bfrequency = pulseIn(sensorOut, LOW);
  delay(100);
}

void goForward(int speedLeftMotor, int speedRightMotor) {
  digitalWrite(inA, HIGH);
  digitalWrite(inB, LOW);
  digitalWrite(inC, HIGH);
  digitalWrite(inD, LOW);
  analogWrite(enA, speedRightMotor);
  analogWrite(enB, speedLeftMotor);

  Serial.print("\nGoing Forward at L:");
  Serial.print(speedLeftMotor);
  Serial.print("- R:");
  Serial.println(speedRightMotor);
}

void goBackWards(int speedLeftMotor, int speedRightMotor) {
  digitalWrite(inA, LOW);
  digitalWrite(inB, HIGH);
  digitalWrite(inC, LOW);
  digitalWrite(inD, HIGH);
  analogWrite(enA, speedRightMotor);
  analogWrite(enB, speedLeftMotor);

  Serial.print("\nGoing BackWards at L:");
  Serial.print(speedLeftMotor);
  Serial.print("- R:");
  Serial.println(speedRightMotor);
}

void goLeft(int speed) {
  digitalWrite(inA, HIGH);
  digitalWrite(inB, LOW);
  digitalWrite(inC, LOW);
  digitalWrite(inD, HIGH);
  analogWrite(enA, speed);
  analogWrite(enB, speed);

  Serial.print("\nGoing goLeft at L:");
  Serial.print(speed);
  Serial.print("- R:");
  Serial.println(speed);
}

void goRight(int speed) {
  digitalWrite(inA, LOW);
  digitalWrite(inB, HIGH);
  digitalWrite(inC, HIGH);
  digitalWrite(inD, LOW);
  analogWrite(enA, speed);
  analogWrite(enB, speed);

  Serial.print("\nGoing goRight at L:");
  Serial.print(speed);
  Serial.print("- R:");
  Serial.println(speed);
}

void stopMotors() {
  digitalWrite(inA, LOW);
  digitalWrite(inB, LOW);
  digitalWrite(inC, LOW);
  digitalWrite(inD, LOW);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}
