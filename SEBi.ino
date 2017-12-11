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

char ssid[] = "FoxLab"; 
char password[] = "foxlabmakerspacemaker"; 

char username[] = "e9de82f0-de60-11e7-ba6c-75d14f3b7ebe";
char mqtt_password[] = "1c63d4c93709c61a6e6f597522bce10d1c4f82f9"; 
char client_id[] = "0b35d200-de61-11e7-ad90-91233d82c471"; 

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