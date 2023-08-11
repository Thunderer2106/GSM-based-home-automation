#include <SoftwareSerial.h>

SoftwareSerial mySerial(11,12);
String textMessage="";

void setup()
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(100);
  pinMode(LED_BUILTIN,OUTPUT);
  
}


void loop()

{
 
  RecieveMessage();
  delay(1000);
   //SendMessage();
   //delay(1000);
  
  
}





 void RecieveMessage()
{
    Serial.println("get mode");
  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  delay(1000);
  textMessage=mySerial.readString();
   Serial.println(textMessage);
 
   if (textMessage.indexOf("LEDON")>=0){
     Serial.println("LED is turned on");
    digitalWrite(LED_BUILTIN,HIGH);
     SendMessage();
    textMessage="";
  }
  delay(1000);
  if(textMessage.indexOf("LEDOFF")>=0){
    Serial.println("LED is turned OFF");
    digitalWrite(LED_BUILTIN,LOW);
    SendMessage();
    textMessage="";
 }
 delay(1000);
}


  void SendMessage()
{
  Serial.println("send mode");
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+917904253540\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("operation done");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
