## SEBi -Smart Electric Waste Bin

![](https://github.com/salmanfarisvp/SEBi/blob/master/icon.png?raw=true)


Smart and efficient way to monitor your waste bin and help you to dispose of it at the correct time.

* * *

## [](#header-2)What is Waste management? 
According to Wikipedia:

```
“Waste management or Waste disposal is all the activities
 and actions required to manage waste from its inception to its final disposal.
 This includes among other things, collection, transport, treatment and disposal of waste together
 with monitoring and regulation. It also encompasses the legal and regulatory framework that relates
 to waste management encompassing guidance on recycling etc.”
```
![](https://github.com/salmanfarisvp/SEBi/blob/master/wms.png?raw=true)


## [](#header-3)Problem in Waste Management

One of the major issues in waste management is to collect the waste at right time, also it's really a headache for waste management agencies. 
Waste management agencies are collecting waste from household/industry once in a month, 
so sometimes the waste bin will be full before the collection time or sometimes, 
such as during vacations the bin is not going to get filled and still the agency will come for collecting the waste it will waste their fuel.

## [](#header-4)Why use a smart waste bin? (Solution)

As a solution for the problem in waste management that I mentioned above we have:

When the bin is full, it will notify the waste management agency as well as us, so it will help the agency avoid the waste of fuel also make it possible for them to create a better map of collecting waste from citizens.

The network of sensors enabled smart bins connected through the IoT network generates a large amount of data, which is further analyzed and visualized at real time to gain insights about the status of waste around the city. The scope for the future work of this system can be implemented on various places like bus stops, railway stations etc.



```
  Hardware :-
        =>NodeMCU(ESP8266-12E)
        =>Ultrasonic Sensor (HCSR-04)
        =>LED

  Software :-
        =>Arduino IDE
        =>Cayenne
  
  
  ```

## [](#header-5)Wiring 

![](https://github.com/salmanfarisvp/SEBi/blob/master/wiring.PNG?raw=true)




## [](#header-6)Code

```

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


```
