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
long inAmax=6000;

// capteur fréquence
int trigF = 10; 
int echoF = 9; 
long lecture_echoF; 
int UoutF;
int inFmax=6000;

int led=2; // led pour illuminer les vu-mètres


long a;
float distmm;
float distmmF;

void setup() 
{ 
 pinMode(trigA, OUTPUT); // setup capteur amplitude
  digitalWrite(trigA, LOW); 
  pinMode(echoA, INPUT); 
  pinMode(5,OUTPUT);
 
 pinMode(trigF, OUTPUT); // setup capteur freq
  digitalWrite(trigF, LOW); 
  pinMode(echoF, INPUT);
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
  
  if((lecture_echoA > 3480) && (lecture_echoA > inAmax))
    {
    UoutA=0;
    distmm=0;
    }
      else if ((lecture_echoA >= 3480) && (lecture_echoA<= inAmax))
      {
      UoutA=255;
      distmm=600;
      }
  else
  {
  UoutA=map(lecture_echoA,0,3480,0,255); // converti la distance en 8 bits pour la sortie en PWM --> conversion echo en mm = /5.8 ici max 600 mm
  distmm=(lecture_echoA/5.8);  
  }
  analogWrite (5,UoutA);  // tension pour Arduino 2, Vu-mètre et bar-graph (entrée SIG)
  Serial.print("echo Amp: "); 
  Serial.println(lecture_echoA);
  Serial.print("distance: "); 
  Serial.println(distmm);
  Serial.print("tension: "); 
  Serial.println(UoutA);
  Serial.print("distance: "); 
  Serial.println(distmm);
  Serial.println("----------------------------------------------------------------------");
}

void checkFreq ()
{
  digitalWrite(trigF, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigF, LOW); 
  lecture_echoF = pulseIn(echoF, HIGH); 
  
  if((lecture_echoF > 3480) && (lecture_echoF > inFmax))
    {
    UoutF=0;
    distmmF=0;
    }
      else if ((lecture_echoF >= 3480) && (lecture_echoF<= inFmax))
      {
      UoutF=255;
      distmmF=600;
      }
  else
  {
  UoutF=map(lecture_echoF,0,3480,0,255); // converti la distance en 8 bits pour la sortie en PWM --> conversion echo en mm = /5.8 ici max 600 mm
  distmmF=(lecture_echoF/5.8);  
  }
  analogWrite (6,UoutF);  // tension pour Arduino 2, Vu-mètre et bar-graph (entrée SIG)
  Serial.print("echo freq: "); 
  Serial.println(lecture_echoF);
  Serial.print("distance: "); 
  Serial.println(distmmF);
  Serial.print("tension: "); 
  Serial.println(UoutF);
  Serial.print("distance: "); 
  Serial.println(distmmF);
  Serial.println("///////////////////////////////////////////////////////////////////////////////////////////////");
} 

void loop() 
{ 
a=millis();
//checkFreq();
checkAmpl();
delay(1000);
//Serial.print("Temps de cycle : "); 
 // Serial.println(millis()-a);
checkFreq();
delay(1000);
  
}
