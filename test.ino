#include <Arduino.h>
#include <WiFi.h>

//Firebase Library
#include <FirebaseESP32.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

//Firebase Declare
#define API_KEY "yOCt9u60Y2BPBRag3JISLFlc0x1iEnZblPwiJ8MZ"
#define DATABASE_URL "https://esp32-ac263-default-rtdb.firebaseio.com/"


#define WIFI_SSID "2304_PN2"
#define WIFI_PASSWORD "560280140"

#define Den 12
#define Quat 17
#define Den_doi_mau 14

int dataden = 0;
int dataquat = 0;
int datadendoimau = 0;


FirebaseData firebaseData ;
FirebaseAuth auth;
FirebaseConfig config;
FirebaseJson json;

void initWiFi() {
  Serial.begin(115200);  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  Serial.print("");
  while (WiFi.status() != WL_CONNECTED ){
  Serial.print(".");
  delay(1000);
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("Local IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}
void initFirebase(){


  config.token_status_callback = tokenStatusCallback;
  Firebase.begin(DATABASE_URL, API_KEY);
  Firebase.reconnectWiFi(true);
}
  String data5base = ""; 
void pushdata(){
  if (Firebase.RTDB.getString(&firebaseData, F("/Den"),&data5base)){
      dataden = data5base.toInt();
  }
    Serial.println("data in /esp is: ");
    Serial.print(dataden);
    delay(1000);
}

void initden(){
  if (Firebase.RTDB.getString(&firebaseData, F("/Den"),&data5base)){
      dataden = data5base.toInt();
  }
  if (dataden == 1){
    digitalWrite(Den, HIGH);
  }else{
    digitalWrite(Den, LOW);
  }  
}

void initquat(){
   if (Firebase.RTDB.getString(&firebaseData, F("/Quat"),&data5base)){
      dataquat = data5base.toInt();
  }
  if (dataquat == 0){
    digitalWrite(Quat, HIGH);
  }else{
    digitalWrite(Quat, LOW);
  }  
}

void initdendoimau(){
  if (Firebase.RTDB.getString(&firebaseData, F("/den doi mau"),&data5base)){
      datadendoimau = data5base.toInt();
  }
  if (datadendoimau == 1){
    digitalWrite(Den_doi_mau, HIGH);
  }else{
    digitalWrite(Den_doi_mau, LOW);
  }  
}

void setup() {
  // put your setup code here, to run once:
  initWiFi();
  initFirebase();
  pinMode(Den,OUTPUT);
  pinMode(Quat,OUTPUT);
  pinMode(Den_doi_mau,OUTPUT);
  digitalWrite(Den, LOW);
  digitalWrite(Quat, LOW);
  digitalWrite(Den_doi_mau, LOW);
}

void loop() {
  initquat();
  initdendoimau();
  initden();
  // put your main code here, to run repeatedly:
}
