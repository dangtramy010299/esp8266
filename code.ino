#include <SoftwareSerial.h>
#define rxPin D5
#define txPin D6
#define led D7
SoftwareSerial sim800(rxPin, txPin);
#include <ESP8266WiFi.h>
#include "FirebaseESP8266.h"
#include <ArduinoJson.h>
FirebaseData firebaseData;
FirebaseJson json;
#define WIFI_SSID "Tra My"
#define WIFI_PASSWORD "01021999"
#define DATABASE_URL "esptest-cf441-default-rtdb.firebaseio.com"
#define API_KEY "HZ8dyhTHJ120fbeEJVRM4G0RhMXboaGi8mujk9Y5"
int giatri =0, xacnhan1=0;
long times=0;

WiFiServer server(80);
void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);}// Start the server
  
 server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("NHAP IP VAO APP: ");
 
  Serial.print(WiFi.localIP());
  // put your setup code here, to run once:
Firebase.begin("esptest-cf441-default-rtdb.firebaseio.com","HZ8dyhTHJ120fbeEJVRM4G0RhMXboaGi8mujk9Y5");
Firebase.reconnectWiFi(true);
  delay(1000);
Firebase.setInt(firebaseData, "/DATA/val",0);

  delay(1000);
  sim800.begin(9600);
  delay(1000);
  times = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  if( Firebase.getInt(firebaseData,("/DATA/val"))){
  giatri = firebaseData.intData();
 Serial.println("GIA TRI " + String(giatri));
 }
 times = millis();
 while(giatri == 1 ){
  Serial.println("NEU BAN AN TOAN HAY XAC NHAN VOI GOOGLE VOICE, NEU KHONG CUOC GOI TU DONG SE DUOC BAT DAU SAU 30 GIAY");
  thuc_hien_cuoc_goi();
  WiFiClient client = server.available();
  if(millis() -times >= 1000){
    Serial.println(30 - (millis() - times)/1000);
  }
 
// Serial.println(millis()-times);
  // Read the first line of the request
  
if(millis() -times > 30000){
 digitalWrite(led, HIGH);
   delay(1000);
  Firebase.setInt(firebaseData, "/DATA/val",0);
  giatri = 0;
  delay(1000);
  //phanhoi(1);
  guisms();
  //Firebase.setInt(firebaseData, "/DATA/val",0);
  digitalWrite(led, LOW); 
}

  String request = client.readStringUntil('\r');
  Serial.println("VOICE: "+ String(request));
  client.flush();
 if(request == "GET /h%C3%A3y%20g%E1%BB%8Di%20gi%C3%BAp%20t%C3%B4i HTTP/1.1"){
  Serial.println("TOI DA GOI GIUP BAN");
  phanhoi(1);
 }
 if(request == "GET /t%C3%B4i%20an%20to%C3%A0n HTTP/1.1"){
    Serial.println("TOI DA HUY CUOC GOI CHO BAN");
  giatri = 0;
  Firebase.setInt(firebaseData, "/DATA/val",0);
  delay(1000);
  times = millis();
 }
 
// Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); // do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
 }
 
  
 
}
void phanhoi(int tipe) {
  if (tipe == 1) {
    delay(1000);
    sim800.println("ATD+84325972718;");             ////////Thay số điện thoại cần gọi
    delay(1000);
    Serial.println("DANG GOI DIEN");
    delay(20000);
    sim800.println("ATH");                              // Ngat cuoc goi
    delay(5000);
    Serial.println("DA NGAT CUOC GOI");
  }}
  void guisms() {
  
 
    sim800.println("AT+CMGF=1");
  delay(1000);
  sim800.println("AT+CMGS=\"+84325972718\"\r");   //Số điện thoại nhận tin nhắn phản hồi
  delay(1000);
    sim800.println("NGUOI NHA BAN AN TOAN");
    Serial.println("DA GUI TIN NHẮN");
    delay(2000);
    delay(100);
  sim800.println((char)26);
  delay(1000);
  }
  void thuc_hien_cuoc_goi() {
{
  
    sim800.println("ATD+84325972718;");             ////////Thay số điện thoại cần gọi
    delay(1000);
    Serial.println("DANG GOI DIEN");
    delay(20000);
    sim800.println("ATH");                              // Ngat cuoc goi
    delay(1000);
    Serial.println("DA NGAT CUOC GOI");
 }
}
 
