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
int dagoi=0;
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
  if(dagoi==0){
  thuc_hien_cuoc_goi();
  dagoi=1;
  }
  WiFiClient client = server.available();
  if(millis() -times >= 1000){
    Serial.println(30 - (millis() - times)/1000);
  }
 
// Serial.println(millis()-times);
  // Read the first line of the request
  

 digitalWrite(led, HIGH);
   
  
 // giatri = 0;
  
  //phanhoi(1);
  
  //Firebase.setInt(firebaseData, "/DATA/val",0);
  digitalWrite(led, LOW); 


  String request = client.readStringUntil('\r');
  Serial.println("VOICE: "+ String(request));
  client.flush();
 if(request == "GET /h%C3%A3y%20g%E1%BB%8Di%20gi%C3%BAp%20t%C3%B4i HTTP/1.1"){
  Serial.println("TOI DA GOI GIUP BAN");
 
 }
 if(request == "GET /t%C3%B4i%20an%20to%C3%A0n HTTP/1.1"){
    Serial.println("TOI DA GUI TIN NHAN CHO BAN");
    guisms();
    Firebase.setInt(firebaseData, "/DATA/val",0);
  giatri = 0;
  dagoi=0;i
  //Firebase.setInt(firebaseData, "/DATA/val",0);
  //delay(1000);
  //times = millis();
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
    

    MPU6050
       
#include <ESP8266WiFi.h> 
#include <FirebaseESP8266.h> 
#define WIFI_SSID "My xinh dep nhat tren doi"   
#define WIFI_PASSWORD "99999999"  
#define DATABASE_URL "esptest-cf441-default-rtdb.firebaseio.com"    
FirebaseData fbdo;  //Gọi thư viện firebase  dang json

/* 4, Define the FirebaseAuth data for authentication data */
FirebaseAuth auth;   

/* Define the FirebaseConfig data for config data */
FirebaseConfig config;   //kết nối với data firebase

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h> //Thư viện giao tiếp 
#include <Wire.h>          //Thư viện i2C
Adafruit_MPU6050 mpu;   //đặt tên cho MPU
void setup() {
  Wire.begin(2,0);   //Khởi động giao tiếp i2c với chân GPIO2 là SDA và GPIO0 là SCL
  Serial.begin(9600);  
  WiFi.mode(WIFI_STA);  //Chế độ kết nối wìi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); //Bắt đầu kết nối wifi
  while (WiFi.status() != WL_CONNECTED) {  //Nếu chưa có kết kết nối
    Serial.print(".");                 
    delay(1000);}
     Serial.print("NHAP IP VAO APP: ");
 
  Serial.print(WiFi.localIP());  //hiển thị ip của esp lên Serial
  // put your setup code here, to run once:
 config.database_url = DATABASE_URL;   //Kết nối với fire base bằng URL của DATA firebase

  config.signer.test_mode = true; //Chế độ của data firebase(TRUE = Chế độ khóa)
  //firebase
  Firebase.reconnectWiFi(true);

  /* Initialize the library with the Firebase authen and config */
 Firebase.begin(&config, &auth); //Khởi động firebase

  delay(1000);
  if (!mpu.begin()) {  //Nếu không kết nối được với MPU thì báo lỗi 
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(1000);
    pinMode(2, OUTPUT);
    digitalWrite(2, LOW);   //Đèn led trên MCU sáng
    
    }}
  

}

void loop() {
  sensors_event_t a, g, temp;//Xet biến 
mpu.getEvent(&a, &g, &temp);
  // put your main code here, to run repeatedly:
  float giatocx = a.acceleration.x;   //đọc giá trị gia tốc từ MPU gửi về
  float giatocy = a.acceleration.y;   //
  float giatocz = a.acceleration.z;
  float gocX = g.acceleration.x;   //Đọc giá trị góc từ MPU gửi về
  float gocY = g.acceleration.y;
  float gocZ = g.acceleration.z;
  Serial.println(String("GIA TOC X: ") + String(giatocx));   //In lên màn hình qua serial
  Serial.println(String("GIA TOC Y: ") + String(giatocy)); // 
  Serial.println(String("GIA TOC Z: ") + String(giatocz));
  
  Serial.println(String("GOC X: ") + String(gocX));
  Serial.println(String("GOC Y: ") + String(gocY));
  Serial.println(String("GOC Z: ") + String(gocZ));
  if( ( giatocx >4 ) || ( giatocy >4 ) && ( giatocz >4)){  //Nếu gia góc đọc về và gia tốc lớn hơn giá trị set thì 
    if( gocX >(-0.06) || ( gocY >(-0.04) )&& gocZ < 0){
      //Đẩy lên fire base Thư mục chính DATA, mục con val là giá trị 1
 Serial.printf("Set int... %s\n", Firebase.setFloat(fbdo, "/DATA/val", 1) ? "ok" : fbdo.errorReason().c_str());
 
 Serial.println("PHAT HIEN TE NGA");
  delay(100); 
  }
  }
  delay(1000);
}
