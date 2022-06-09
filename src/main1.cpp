#include <Arduino.h>
#include <Suricata_VFD.h>
#include <iostream>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <stdlib.h>

using namespace std;

uint8_t TEMT6000 = 34;    //环境光传感器连接在GPIO34
uint16_t bright_time = 0;
uint8_t bright = 128;
uint8_t old_bright = 0;
uint8_t EC11_A   = 21;
uint8_t EC11_B   = 4;

int EC = 0;
bool EC11_A_P = 0;
bool EC11_B_P = 0;
bool EC11_A_ST;
bool EC11_B_ST;

const char *ssid1 = "Kidiota_Wifi";    //首选wifi SSID
const char *password1 = "return01";    //首选wifi 密码

WiFiUDP ntpUDP;    //更新时间
NTPClient timeClient(ntpUDP, "ntp1.aliyun.com",8*60*60, 30*60*1000);    //设置时区


void setup() {
  pinMode(EC11_A, INPUT_PULLUP);
  pinMode(EC11_B, INPUT_PULLUP);
  Serial.begin(115200);    //串口设置波特率
  pinMode(TEMT6000,INPUT);
  VFD_SETUP();    //屏幕初始化
  WiFi.begin(ssid1, password1);    //连接WiFi
  uint8_t i = 0;  
  while(WiFi.status() != WL_CONNECTED){    //如果没连上WiFi，执行下列代码
      VFD_WriteStr(i, ".");    //在屏幕上显示一个点
      i = i + 1;    //向后移一位
      Serial.print(".");
      delay(100);
    }
  VFD_WriteStr(0,"OK");
  Serial.print("WiFi ok");
  delay(1000);
  VFD_WriteStr(0,"        ");

}

void loop() {
  // put your main code here, to run repeatedly:
    //旋钮调光////////////////////////////////////////////////////////////
  EC11_A_ST = digitalRead(EC11_A);
  EC11_B_ST = digitalRead(EC11_B);
  EC = 0;
  if(!EC11_A_ST&&!EC11_B_ST)//
  {
    if(!EC11_A_P&&EC11_B_P)
    {
     EC = -1; 
    }
    else if(EC11_A_P&&!EC11_B_P)
    {
     EC = 1;
    }
  }
  EC11_A_P=EC11_A_ST;
  EC11_B_P=EC11_B_ST;
  bright = bright + EC;

  if(old_bright != bright){
    VFD_Bright(bright);
    char brightChar[4];
    itoa(bright,brightChar,10);
    char EC11_A_ST_C[2];
    itoa(EC11_A_ST,EC11_A_ST_C,10);
    char EC11_B_ST_C[2];
    itoa(EC11_B_ST,EC11_B_ST_C,10);
    char EC_C[2];
    itoa(EC,EC_C,10);
    VFD_WriteStr(4,EC_C);
    VFD_WriteStr(7,EC11_B_ST_C);
    VFD_WriteStr(6,EC11_A_ST_C);
    VFD_WriteStr(0,brightChar);
    if(bright == 0){
      VFD_WriteStr(0,"   ");
    }
    if(bright < 10){
      VFD_WriteStr(1,"  ");
    }
    if(bright < 100){
      VFD_WriteStr(2," ");
    }
    if(EC != 0)
      bright_time = 0;
    bright_time = bright_time + 1;
    if(bright_time > 2000){
      old_bright = bright;
      bright_time = 0;
    }
  }

  if(old_bright == bright){
    timeClient.update();
    String str=timeClient.getFormattedTime();
    char *formattedTime=(char*)str.c_str();
    VFD_WriteStr(0, formattedTime);
  }
  
  //Serial.println(timeClient.getFormattedTime());
  uint16_t light = analogRead(TEMT6000);
  Serial.println(light);
  delay(100);
}
