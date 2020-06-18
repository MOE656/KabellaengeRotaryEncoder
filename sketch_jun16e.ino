//Moritz Rank 73270
//ramo1015@hs-karlsruhe.de
//Automatische Kabelabmessung



#include <Wire.h>              //IIC Bus
#include <ACROBOTIC_SSD1306.h> //Bibliotheken für OLED


#include <Encoder.h>            //Bibliothek für rotary encoder






Encoder myEnc(17, 5);         //initalierung rotary encoder


int inPin = 14;              //initalierung knopf
int val = 0;    

 //output string
String output;        
     
//gemessene Länge
double lenght=0;

//Variable für den encoder loop
long oldPosition  = 0;


void setup() 
{

  //OLED
  Wire.begin();  
  oled.init();                      // Initialze SSD1306 OLED display
  oled.clearDisplay();              // Clear screen
  
  //input pin für knopf
  pinMode(inPin, INPUT);
 
}



void loop() 
{
  
  long newPosition = myEnc.read();    //aktuelle Position des encoders wird gelesen
  if (newPosition != oldPosition)     //wenn die neue position nicht der alten postion entspricht wird ales geupdatet
  {
    int diff=newPosition-oldPosition; //differenz zum berechnen der zurückgelegten länge
    
    lenght+=diff*0.785;               //faktor für ein d=20mm laufrad, eine umdrehung ensprechen 80 updates des encoders, also bei d=20mm eine maximale auflösung von 0.785mm
    oldPosition=newPosition;          //update für die oldPosition variable
  }

  val = digitalRead(inPin);           //lesen des knopf inputs
  if (val == HIGH)                    //wenn der knopf gedrückt ist wird die länge auf 0 gesetzt
    {
      lenght=0;
      
    }

  
  output=String(lenght);              //oled aufgabe wird aufgebaut als string
  output += " mm";                    //die ausgerechnte Länge mit einheit
  oled.setTextXY(3,3);                //position des Texts auf dem OLED
  oled.putString(output);             //ausgabe string wird auf das OLED geschrieben
  

    
}
