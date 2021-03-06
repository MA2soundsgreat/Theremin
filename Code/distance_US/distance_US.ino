/* Utilisation du capteur Ultrason HC-SR04 */

// définition des broches utilisées 
int trig = 12; 
int echo = 11; 
long lecture_echo; 
float mm;

void setup() 
{ 
  pinMode(trig, OUTPUT); 
  digitalWrite(trig, LOW); 
  pinMode(echo, INPUT); 
  Serial.begin(9600); 
}

void loop() 
{ 
  digitalWrite(trig, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trig, LOW); 
  lecture_echo = pulseIn(echo, HIGH); 
  mm =(float) (lecture_echo / 5.8); 
  Serial.print("Distance en mm : "); 
  Serial.println(mm); 
  delay(500); 
}
