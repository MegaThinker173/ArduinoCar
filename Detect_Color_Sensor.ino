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

// Stores frequency read by the photodiodes
int blackFrequency = 0;
int whiteFrequency = 0;

// Stores the black and white colors
int blackColor = 0;
int whiteColor = 0;

void setup() {
  pinModeInit();
  // Setting frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  // Begins serial communication
  Serial.begin(9600);
}

void loop() {
  LineFollower();
  goForward(30);
  delay(1000);
  goBackward(30);
  delay(1000);
  goLeft(30);
  delay(1000);
  goRight(30);
  delay(1000);
  stopMotors();
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
  // Setting the sensorOut as an input
  pinMode(sensorOut, INPUT);
}

//turns backwards left motor and goes forward with the right motor
void goLeft(int speed){
  digitalWrite(inA, LOW);
  digitalWrite(inB, LOW);
  digitalWrite(inC, HIGH);
  digitalWrite(inD, LOW);
  analogWrite(enA, speed);
  analogWrite(enB, speed);

  Serial.print("\nGoing goLeft at L:");
  Serial.print(speed);
  Serial.print("- R:");
  Serial.println(speed);
}

//turns off right motor and goes forward with the left motor
void goRight(int speed) {
  digitalWrite(inA, HIGH);
  digitalWrite(inB, LOW);
  digitalWrite(inC, LOW);
  digitalWrite(inD, LOW);   
  analogWrite(enA, speed);
  analogWrite(enB, speed);

  Serial.print("\nGoing goRight at R:");
  Serial.print(speed);
  Serial.print("- R:");
  Serial.println(speed);
}

void goForward(int speed) {
  digitalWrite(inA, HIGH);
  digitalWrite(inB, LOW);
  digitalWrite(inC, HIGH);
  digitalWrite(inD, LOW);
  analogWrite(enA, speed);
  analogWrite(enB, speed);

  Serial.print("\nGoing goForward at F:");
  Serial.print(speed);
  Serial.print(" - B:");
  Serial.println(speed);
}

void goBackward(int speed) {
  digitalWrite(inA, LOW);
  digitalWrite(inB, HIGH);
  digitalWrite(inC, LOW);
  digitalWrite(inD, HIGH);
  analogWrite(enA, speed);
  analogWrite(enB, speed);

  Serial.print("\nGoing goBackward at B:");
  Serial.print(speed);
  Serial.print(" - B:");
  Serial.println(speed);
}

//turn off both motors
void stopMotors() {
  digitalWrite(inA, LOW);
  digitalWrite(inB, LOW);
  digitalWrite(inC, LOW);
  digitalWrite(inD, LOW);
  analogWrite(enA, LOW);
  analogWrite(enB, LOW);
}

void LineFollower() {
  // Setting (Black)
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);

  // Setting (White) 
  digitalWrite(S2,HIGH);
  digitalWrite(S3,LOW);
  
  blackFrequency = pulseIn(sensorOut, LOW);
  blackColor = map(blackFrequency, 600, 750, 255, 0);
  
  whiteFrequency = pulseIn(sensorOut, LOW);
  whiteColor = map(whiteFrequency, 28, 35, 255, 0);
  
  stopMotors();
  //Two statements inside two if statements:
  //Change based on reality so that the car is moving forward (pushing left and right to move forward)
  if (blackColor > whiteColor) {
    goLeft(150);
    delay(155);
  }
  if (whiteColor > blackColor) {
    goRight(150);
    delay(100);
  }
}
