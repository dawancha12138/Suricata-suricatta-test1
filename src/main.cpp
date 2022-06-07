#include <WiFi.h>
const char* ssid     = "Xiaomi_7C9C";//连接WIFI名(SSID)
const char* password = "qwer1234";//WIFI密码

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("--------------");
  
  WiFi.begin(ssid,password);//启动网络连接

  Serial.printf("Begin to Connect %s\r\n", ssid);
  while (WiFi.status() != WL_CONNECTED)//检测网络是否连接成功
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());//返回ESP8266的IP地址
}

void loop() {}
