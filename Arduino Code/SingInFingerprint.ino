/*
 *©2020 by Python Schlange
 */

#include <Keyboard.h>
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
int fingerprintID = 0;
String inData;
bool isRight;
int pos;

//Number of services to log in
#define servNum 5

//Login URLs for Google, Amazon, Stackoverflow, Arduino and Github
String LogInURL[] = {"https://accounts.google.com/signin", "https://www.amazon.de/ap/signin", "https://stackoverflow.com/users/login", "https://login.arduino.cc/", "https://github.com/login"};
String LogInUser[] = {"user.name@gmail.com", "user.name@example.com", "user.name@example.com", "username", "username"};
String LogInPwd[] = {"password", "password", "password", "password", "password"};

void StepsBefore(int serviceNum){
  switch(serviceNum){
    case 0: donothing();
    case 1: donothing();
    case 2: for(int k=0; k<18; k++) Keyboard.press(KEY_TAB); Keyboard.release(KEY_TAB);
    case 3: for(int k=0; k<2; k++) Keyboard.press(KEY_TAB); Keyboard.release(KEY_TAB);
    case 4: donothing();
    default: Serial.println("Error: Number not recognized.");
  }
}

void StepsAfter(int serviceNum){
  switch(serviceNum){
    case 0: Keyboard.write('\r'==13);
    case 1: Keyboard.write('\r'==13);
    case 2: Keyboard.press(KEY_TAB); Keyboard.release(KEY_TAB);
    case 3: Keyboard.press(KEY_TAB); Keyboard.release(KEY_TAB);
    case 4: for(int k=0; k<2; k++) Keyboard.press(KEY_TAB); Keyboard.release(KEY_TAB);
    default: Serial.println("Error: Number not recognized.");
  }
}

int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;
  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;
  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  Serial.print("Found ID #"); 
  Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); 
  Serial.println(finger.confidence);
  return finger.fingerID; 
}

void askForFingerprint() {
  fingerprintID = getFingerprintIDez();
    delay(50);
    if(fingerprintID == 1){
      isRight = true;
    }
}

void delAfterChar(String inString, String fromToKill){
  pos = inString.indexOf(fromToKill);
  inString.remove(pos, 1000);
  inData = inString;
}

void donothing() {};

void setup() {
	Serial.begin(9600);
	Keyboard.begin();
	finger.begin(57600);
    if(finger.verifyPassword()) {
        Serial.println("Found fingerprint sensor!");
    } 
    else {
        Serial.println("Did not find fingerprint sensor :(");
        while (1) { delay(1); }
    }
}
void loop() {
	inData = Serial.read();
  delAfterChar(inData, "?openid"); //Amazon
  delAfterChar(inData, "/v2/"); //Google
  delAfterChar(inData, "?ssrc"); //Stackoverflow
  delAfterChar(inData, "login?state"); //Arduino
	for (int i=0; i<servNum; i++){
     if(inData == LogInURL[i]){
        askForFingerprint();
        if(isRight == true){
           StepsBefore(i);
           Keyboard.print(LogInUser[i]);
           StepsAfter(i);
           Keyboard.println(LogInPwd[i]);
        }
        else Serial.println("Finger not recognized");
     }
	}
}
