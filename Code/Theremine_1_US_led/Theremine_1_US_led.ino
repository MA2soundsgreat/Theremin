/* Code de l'Arduino 1 - capteurs US + led
code sous license GPL*/

// définition des broches utilisées 

// capteur amplitude


/* si bargraph clignotant, 2 sorties en plus (ou 1 si vumètre sur 1,25V) et ajouter ces lignes
UoutABG=map(lecture_echoA,290,3480,0,64);
pinMode(3,OUTPUT);
analogWrite(3,UoutABG);
*/

int trigA = 12; 
int echoA = 11; 
long lecture_echoA; 
int UoutA;
int inAmax=4000;

// capteur fréquence
int trigf = 10; 
int echof = 9; 
long lecture_echof; 
int UoutF;
int inFmax=4000;

int led=2; // led pour illuminer les vu-mètres

void setup() 
{ 
 pinMode(trigA, OUTPUT); // setup capteur amplitude
  digitalWrite(trigA, LOW); 
  pinMode(echoA, INPUT); 
  pinMode(5,OUTPUT);
 
 pinMode(trigf, OUTPUT); // setup capteur freq
  digitalWrite(trigf, LOW); 
  pinMode(echof, INPUT);
  pinMode(6,OUTPUT);
  

 pinMode(2, OUTPUT); //allume les leds des vu-mètres
  digitalWrite(2,HIGH);
 
 Serial.begin(9600);  
}


void checkAmpl () // fonction check amplitude
{
  digitalWrite(trigA, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigA, LOW); 
  lecture_echoA = pulseIn(echoA, HIGH); 
  if(lecture_echoA>inAmax)
  {
  UoutA==0;
  }
  else
  {
  UoutA=map(lecture_echoA,290,3480,0,255); // converti la distance en 8 bits pour la sortie en PWM --> conversion echo en mm = /5.8 ici max 600 mm
  }
  analogWrite (5,UoutA);  // tension pour Arduino 2, Vu-mètre et bar-graph (entrée SIG)
  Serial.print("Valeur amplitude : "); 
  Serial.println(UoutA);
}

void checkFreq ()
{
  digitalWrite(trigf, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigf, LOW); 
  lecture_echof = pulseIn(echof, HIGH); 
   if(lecture_echof>inFmax)
  {
  UoutF==0;
  }
  else
  {
  UoutF= map(lecture_echof,290,3480,0,255); 
  }
  analogWrite (6,UoutF); //tension pour Arduino 2, Vu-mètre, bar-graph et ampli
  Serial.print("Valeur fréquence : "); 
  Serial.println(UoutF);
}


void loop() 
{ 

checkFreq();
checkAmpl();
delay(200);
  
}
