//ALL INCLUDED LIBRARIES
#include <SoftwareSerial.h>  
#include <LiquidCrystal_I2C.h> 
#include <Wire.h> 
#include <Sodaq_DS3231.h>

//using inbuilt functions for GSM and LCD
SoftwareSerial mySerial(5, 4);  
LiquidCrystal_I2C lcd(0x27, 16, 2);

//ALL VARIABLES USED
int temp = 0;
bool ask = true;
int tempask = 1;
int bulbask = 1;
bool ask2 = true;
int smokeA0 = A0;
int sensorThres = 750;

int hr = 14;
int mn = 00;
const int x = 00;
bool timechange=true;

int passcheck = 0;
bool pass = false;

int val = 0;

String state1 = "OFF";
String state2 = "OFF";
String last = "";
int REY1 = 7;  
int REY2 = 8; 

String message;

const int trigPin = 9;
const int echoPin = 11;
const int buzzer = 12;
const int ledPin = 13;
long duration;
int distance;
int safetyDistance;

void setup() {

  pinMode(trigPin, OUTPUT);  
  pinMode(echoPin, INPUT);   
  pinMode(buzzer, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);

  Serial.begin(9600);
  mySerial.begin(9600);  
  Wire.begin();
  lcd.init();
  lcd.backlight();

  delay(2000);

  pinMode(REY1, OUTPUT);
  pinMode(REY2, OUTPUT);

  digitalWrite(REY1, LOW);
  digitalWrite(REY2, LOW);

  enterpassword();
}

void loop() {
   if (Serial.available() > 0) {
      val = Serial.read();
      Serial.print(val);
    }
     if(val == '2'){
      digitalWrite(REY1, HIGH);  
      }
    if(val == '1'){
      digitalWrite(REY1, LOW);
      }
    if(val == '4'){
      digitalWrite(REY2, HIGH);  
      }
    if(val == '3'){
      digitalWrite(REY2, LOW);
   }


  
  if (mySerial.available() > 0) {

    Serial.println("Serial is available");


    Serial.println("Serial is available");



    message = mySerial.readString();


    delay(3000);

    if (message.indexOf("123") > -1) {
      Serial.println("Correct");
      pass = true;
      mySerial.println("AT+CMGS=\"+917878504529\"\r"); //the number where message would be sent
      delay(1000);
      mySerial.println("some device login to J.A.N.I.N.I. If it wasnt you make sure to report emergency");

      delay(100);

      mySerial.println((char)26);  // ASCII code of CTRL+Z

      delay(1000);
    }
  }


  while (pass) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("J.A.N.I.N.I");

    // TEMPERATURE FEATURE
    temperaturefeature();

    Serial.println("time");
       checksmoke();
       alarmcheck();
       doorcheck();
    
    sendmessagefordevices();
    
    mn = x + (millis() / 60000);
    if (mn >= 60) {
        if(timechange)
          {
            hr++;
            timechange=false;
          }
         mn = mn - 60;
    }
    if (hr >= 24) {
      hr = 00;
    }
  }
}
//.............................................................................................//
void enterpassword() {
  mySerial.println("AT+CMGF=1");  
  Serial.println("11");
  delay(1000);

  mySerial.println("AT+CNMI=2,2,0,0,0");
  Serial.println("22");
  delay(1000);


  delay(100);
  mySerial.println("AT+CMGF=1");

  delay(1000);

  mySerial.println("AT+CMGS=\"+917878504529\"\r"); 

  delay(1000);

  mySerial.println("enter password");
  Serial.print("Enter password");
  delay(100);
  //
  mySerial.println((char)26);

  delay(1000);
}


void temperaturefeature() {
  temp = rtc.getTemperature();
  Serial.println(temp);
  lcd.setCursor(12, 0);
  lcd.print(temp);
  lcd.setCursor(14, 0);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Time:");
  lcd.setCursor(5, 1);
  if (hr < 10) {
    lcd.print("0");
    lcd.setCursor(6, 1);
  }
  lcd.print(hr);
  lcd.setCursor(7, 1);
  lcd.print(":");
  lcd.setCursor(8, 1);
  if (mn < 10) {
    lcd.print("0");
    lcd.setCursor(9, 1);
  }
  lcd.print(mn);
  delay(100);
}

//...........................................................................//
void sendmessagefordevices() {
  if (mySerial.available() > 0) {
    message = mySerial.readString();
    if (message.indexOf("ON") > -1) {
      digitalWrite(REY1, HIGH);
      Serial.println("On");

      state1 = "ON";
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("State:Device1=");
      lcd.setCursor(14, 0);
      lcd.print(state1);
      lcd.setCursor(6, 1);
      lcd.print("Device2=");
      lcd.setCursor(14, 1);
      lcd.print(state2);
      delay(2000);
      mySerial.println("AT+CMGF=1");                    
      delay(1000);                                      
      mySerial.println("AT+CMGS=\"+917878504529\"\r");  
      last = "Device 1->ON";
      delay(1000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Last action=");
      lcd.setCursor(0, 1);
      lcd.print(last);
      delay(2000);
      mySerial.println("device 1 is on");  
      delay(100);
      mySerial.println((char)26); 
      delay(1000);
    }
    if (message.indexOf("OFF") > -1) {

      digitalWrite(REY1, LOW);
      Serial.println("off");

      state1 = "OFF";
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("State:Device1=");
      lcd.setCursor(14, 0);
      lcd.print(state1);
      lcd.setCursor(6, 1);
      lcd.print("Device2=");
      lcd.setCursor(14, 1);
      lcd.print(state2);
      delay(2000);
      mySerial.println("AT+CMGF=1"); 

      delay(1000);

      mySerial.println("AT+CMGS=\"+917878504529\"\r");
      delay(1000);

      last = "Device 1->OFF";

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Last action=");
      lcd.setCursor(0, 1);
      lcd.print(last);
      delay(2000);

      mySerial.println("device 1 is off"); 

      delay(100);
      //
      mySerial.println((char)26);

      delay(1000);
    }
    if (message.indexOf("START") > -1) {
      digitalWrite(REY2, HIGH);
      Serial.println("On");

      state2 = "ON";
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("State:Device1=");
      lcd.setCursor(14, 0);
      lcd.print(state1);
      lcd.setCursor(6, 1);
      lcd.print("Device2=");
      lcd.setCursor(14, 1);
      lcd.print(state2);
      delay(2000);
      mySerial.println("AT+CMGF=1");                   
      delay(1000);                                   
      mySerial.println("AT+CMGS=\"+917878504529\"\r");
      last = "Device 2->ON";
      delay(1000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Last action=");
      lcd.setCursor(0, 1);
      lcd.print(last);
      delay(2000);
      mySerial.println("device 2 is on"); 
      delay(100);
      mySerial.println((char)26);
      delay(1000);
    }

    if (message.indexOf("END") > -1) {

      digitalWrite(REY2, LOW);
      Serial.println("off");

      state2 = "OFF";
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("State:Device1=");
      lcd.setCursor(14, 0);
      lcd.print(state1);
      lcd.setCursor(6, 1);
      lcd.print("Device2=");
      lcd.setCursor(14, 1);
      lcd.print(state2);
      delay(2000);
      mySerial.println("AT+CMGF=1");

      delay(1000); 

      mySerial.println("AT+CMGS=\"+917878504529\"\r"); 
      delay(1000);

      last = "Device 2->OFF";

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Last action=");
      lcd.setCursor(0, 1);
      lcd.print(last);
      delay(2000);

      mySerial.println("device 2 is off"); 

      delay(100);
      //
      mySerial.println((char)26);

      delay(1000);
    }
  }
}
//.........................................................................//
void checksmoke() {
  int analogSensor = analogRead(smokeA0);
  // Checks if it has reached the threshold value
  if (analogSensor > sensorThres) {

    digitalWrite(buzzer, LOW);
    Serial.println(analogSensor);
    
    Serial.println(" fire");
    mySerial.println("AT+CMGF=1");
    delay(1000);                   
    mySerial.println("AT+CMGS=\"+917878504529\"\r");
    delay(1000);
    mySerial.println("fire");  
    delay(100);
    mySerial.println((char)26);  
    delay(1000);


  } else {

    digitalWrite(buzzer, HIGH);
    Serial.println("no fire");
    Serial.println(analogSensor);
  }
  delay(50);
}
//.........................................................................//
void alarmcheck() {
  if (hr == 6 && mn == 30) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Good Morning");
    digitalWrite(buzzer, HIGH);
    delay(5000);               
    digitalWrite(buzzer, LOW);  
    delay(10000);
  }
  if (hr == 23 && mn == 30) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Time to sleep");
    lcd.setCursor(0, 1);
    lcd.print("Good Night");
    digitalWrite(buzzer, HIGH); 
    delay(5000);                 
    digitalWrite(buzzer, LOW);   
    delay(10000);
  }
}
//.........................................................................//
void doorcheck() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance = duration * 0.034 / 2;

  safetyDistance = distance;
  if (safetyDistance <= 10) {
    digitalWrite(buzzer, HIGH);
    digitalWrite(ledPin, HIGH);
    mySerial.println("AT+CMGF=1"); 
    delay(1000);                    
    mySerial.println("AT+CMGS=\"+917878504529\"\r");
    delay(1000);
    mySerial.println("someone is there");
    delay(100);
    mySerial.println((char)26);
    delay(1000);
  } else {
    digitalWrite(buzzer, LOW);
    digitalWrite(ledPin, LOW);
  }
  
  Serial.print("Distance: ");
  Serial.println(distance);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
