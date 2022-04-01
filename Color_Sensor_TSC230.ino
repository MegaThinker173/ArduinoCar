// define pin
#define S0 4
#define S1 11
#define S2 2
#define S3 3
#define sensorOut 12
/*
#define RGBled_Green 10
#define RGBled_Red   9
#define RGBled_Blue  11
*/

int blackFrequency = 0;
int whiteFrequency = 0;

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // sensorOut is input
  pinMode(sensorOut, INPUT);
  
  // Frequency Scale is 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
   // Begins serial communication 
  Serial.begin(9600);
}
void loop() {
  /*// Red
  digitalWrite (RGBled_Green, HIGH);
  digitalWrite (RGBled_Red, HIGH);
  digitalWrite (RGBled_Blue, HIGH);
  delay(100);*/
  
  // Read blackline
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  
  // read Frequency
  blackFrequency = pulseIn(sensorOut, LOW);
  
   // Ghi ra Serial
  Serial.print("B = ");
  Serial.print(blackFrequency);
  delay(100);
  Serial.print("\n");
  
  // read redline
  digitalWrite(S2,HIGH);
  digitalWrite(S3,LOW);
  
  // Read Frequency
  whiteFrequency = pulseIn(sensorOut, LOW);
  
  // print surface value (G)
  Serial.print(" W = ");
  Serial.print(whiteFrequency);
  delay(100);
  Serial.print("\n");
}
