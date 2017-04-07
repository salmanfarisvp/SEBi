/**------------------------------------------------------------------------------------------
  SEBi-Smart Eelctric Waste Bin by Salman Faris

  Hardware
  =>Arduino Uno
  =>IR transrecver
  =>Servo 90
  =>GSM Module

 

  -----------------------------------------------------------------------------------------**/

#include <NewPing.h>
#include <Servo.h> 
#include <SoftwareSerial.h>

int ir; //ir for user detection
int motor; //grinder pin

Servo myservo;

SoftwareSerial mySerial(9, 10); //setting serial connection to hardware mode in pin D9 and D10 
//D9 to RX and D10 to TX

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {

 ir = A1; //IR Connected to A1
 motor=5; //grinder connect to pin D5
  
 pinMode(ir,INPUT);  


 myservo.attach(6); //Servo Connected to pin 9

 mySerial.begin(9600);   // Setting the baud rate of GSM Module  

  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)

  delay(100);



  
}

void loop() {

autoopen(); //check the autoopen fuction for more info

info(); // check the level function for more info

}

void autoopen()
{
  int value = analogRead(ir);  //read ir value into value

  Serial.println(value);
 
  if (value >= 50)   //checking the ir value
  {
    myservo.write(90); //servo will rotate 90 degree
    
  }
  else
  {
    myservo.write(0); //servo will rotate 0 degree (where it's start')
    
  }

}

void info()
{
   delay(50);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS)
  int distance = uS / US_ROUNDTRIP_CM; // distance stored

  if(distance < 10){  // check the waste bin is full

  //sending sms if the waste is full and turn on the grinder

  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+91xxxxxxxxxx\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("Waste Bin Is full,and starting the grinder ");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);

   digitalWrite(motor,HIGH); //trun on the grinder 

}
}

