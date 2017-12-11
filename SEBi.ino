/**------------------------------------------------------------------------------------------
  Author :- Salman Faris - salmanfaris.me

Hardware :-
        =>NodeMCU
        =>Ultrasonice Sensor
        =>LED

Software :-
        =>Arduino IDE
        =>Cayenne
  
 
-----------------------------------------------------------------------------------------**/
#include <CayenneMQTTESP8266.h> 

char ssid[] = "Wifi Name"; 
char password[] = "Wifi password"; 

char username[] = "mqqt User Name";
char mqtt_password[] = "mqtt Password"; 
char client_id[] = "mqtt Clinet ID"; 

#define trigPin D2 
#define echoPin D5 

int Red = D6; 

void setup()
{ 

 Cayenne.begin(username,mqtt_password,client_id,ssid,password); 

pinMode(Red,OUTPUT); 
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT); 
Serial.begin(115200);  

digitalWrite(Red,HIGH); 

} 
void loop(){
 
 Cayenne.loop(); 

long duration, distance; 

digitalWrite(trigPin, LOW);  
delayMicroseconds(2);  
digitalWrite(trigPin, HIGH); 
delayMicroseconds(10);  
digitalWrite(trigPin, LOW); 
duration = pulseIn(echoPin, HIGH); 
distance = (duration/2) / 29.1; 

Serial.println(distance); 

if(distance <= 5 )
{
  digitalWrite(Red,HIGH);
}
else{
  digitalWrite(Red,LOW);
  
}

Cayenne.virtualWrite(3,distance); 

delay(1000); 

} 

CAYENNE_IN(1)
{ 
  digitalWrite(Red,!getValue.asInt()); 
}  