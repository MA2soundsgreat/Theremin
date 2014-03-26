/* Code de l'Arduino 1 - capteurs US + led
code sous license GPL*/

// définition des broches utilisées 


/* si bargraph clignotant, 2 sorties en plus (ou 1 si vumètre sur 1,25V) et ajouter ces lignes
UoutABG=map(lecture_echoA,290,3480,0,64);
pinMode(3,OUTPUT);
analogWrite(3,UoutABG);
*/

// capteur amplitude
int trigA = 12; 
int echoA = 11; 
long lecture_echoA; 
int UoutA;
long satA=6000;
float distmm;

// capteur fréquence
int trigF = 10; 
int echoF = 9; 
long lecture_echoF; 
int UoutF;
int satF=6000;
float distmmF;

int dist_mini=200;



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
   
 Serial.begin(9600);  
}


void checkAmpl () // fonction check amplitude
{
  digitalWrite(trigA, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigA, LOW); 
  lecture_echoA = pulseIn(echoA, HIGH); 
  
  if(lecture_echoA < dist_mini) 
  {
  UoutA=0;
  distmm=0;
  }
  else if((lecture_echoA > 3480) && (lecture_echoA > satA))
    {
    UoutA=0;
    distmm=0;
    }
      else if ((lecture_echoA >= 3480) && (lecture_echoA<= satA))
      {
      UoutA=255;
      distmm=600;
      }
  else
  {
  UoutA=map(lecture_echoA,200,3480,0,255); // converti la distance en 8 bits pour la sortie en PWM --> conversion echo en mm = /5.8 ici max 600 mm
  distmm=(lecture_echoA/5.8);  
  }
  analogWrite (5,UoutA);  // tension pour Arduino 2, Vu-mètre et bar-graph (entrée SIG)
  Serial.print("echo Amp: "); 
  Serial.println(lecture_echoA);
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
  
  if(lecture_echoF < dist_mini) 
  {
  UoutF=0;
  distmmF=0;
  }
  else if((lecture_echoF > 3480) && (lecture_echoF > satF))
    {
    UoutF=0;
    distmmF=0;
    }
      else if ((lecture_echoF >= 3480) && (lecture_echoF<= satF))
      {
      UoutF=255;
      distmmF=600;
      }
  else
  {
  UoutF=map(lecture_echoF,200,3480,0,255); // converti la distance en 8 bits pour la sortie en PWM --> conversion echo en mm = /5.8 ici max 600 mm
  distmmF=(lecture_echoF/5.8);  
  }
  analogWrite (6,UoutF);  // tension pour Arduino 2, Vu-mètre et bar-graph (entrée SIG)
  Serial.print("echo freq: "); 
  Serial.println(lecture_echoF);
  Serial.print("tension: "); 
  Serial.println(UoutF);
  Serial.print("distance: "); 
  Serial.println(distmmF);
  Serial.println("///////////////////////////////////////////////////////////////////////////////////////////////");
} 

void loop() 
{ 
//a=millis();
//checkFreq();
checkAmpl();
delay(2000);
//Serial.print("Temps de cycle : "); 
 // Serial.println(millis()-a);
checkFreq();
delay(2000);
  
}
