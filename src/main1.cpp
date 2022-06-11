#include <Arduino.h>
#include <Suricata_VFD.h>
#include <iostream>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <stdlib.h>
#include "esp32-hal-cpu.h"
#include <Menu.h>
using namespace std;

uint8_t EC_BT =22;//编码器按键
uint8_t menu_v=0;//模式选择
int EC = 0;
bool EC_BT_ST=0;
uint16_t bright_time = 0;
const char *ssid1 = "Xiaomi_7C9C";    //首选wifi SSID
const char *password1 = "qwer1234";    //首选wifi 密码

WiFiUDP ntpUDP;    //更新时间
NTPClient timeClient(ntpUDP, "ntp1.aliyun.com",8*60*60, 30*60*1000);    //设置时区


void setup() {
  setCpuFrequencyMhz(80);
  pinMode(EC11_A, INPUT_PULLUP);//设置IO口模式
  pinMode(EC11_B, INPUT_PULLUP);
  pinMode(EC_BT,INPUT_PULLUP);
    Serial.begin(115200);    //串口设置波特率
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
  VFD_Bright(bright);
    

}

void loop() {
  timeClient.update();
  String str=timeClient.getFormattedTime();
  char *formattedTime=(char*)str.c_str();
  EC_BT_ST=digitalRead(EC_BT);
  if(!EC_BT_ST)//如果编码器按键被按下
  {
    delay(100);
    Serial.print("123");
    EC_BT_ST=digitalRead(EC_BT);
    while(EC_BT_ST)//编码器按键不被按下就继续循环
    {
    menu_v+=ECV(EC11_A,EC11_B,&EC11_A_P,&EC11_B_P);
    menu_v%=3;
    switch (menu_v)//进入菜单调整模式
    {
    case 0:
    VFD_WriteStr(0,"        ");
    VFD_WriteStr(0,"Time");
    Serial.print("time");
      break;
    case 1:
    VFD_WriteStr(0,"        ");
    VFD_WriteStr(0,"Channel");
    Serial.print("Channel");
      break;
    case 2:
    VFD_WriteStr(0,"        ");
    VFD_WriteStr(0,"Bright");
    Serial.print("Bright");
    break;
    default:
      break;
    }
    EC_BT_ST=digitalRead(EC_BT);
    }
    delay(50);
  } 
  switch (menu_v)//依照对应的模式选择应该执行什么代码
  { 
  case 0:
  VFD_WriteStr(0, formattedTime);//如果是时间模式就更新时间
  Serial.print(formattedTime);
    break;
  case 1:
  VFD_WriteStr(0,"        ");
  VFD_WriteStr(0,"test");
  Serial.print("test");
    break;
  case 2:
        Bright(EC_BT,&bright);

  break;
  default:
    break;
  }
}
  // EC=ECV(EC11_A,EC11_B,&EC11_A_P,&EC11_B_P);
  // bright = bright +EC;
  // if(old_bright != bright){
  //   VFD_Bright(bright);
  //   char brightChar[4];
  //   itoa(bright,brightChar,10);
  //   // char EC11_A_ST_C[2];
  //   // itoa(EC11_A_ST,EC11_A_ST_C,10);
  //   // char EC11_B_ST_C[2];
  //   // itoa(EC11_B_ST,EC11_B_ST_C,10);
  //   char EC_C[2];
  //   itoa(EC,EC_C,10);
  //   VFD_WriteStr(3," ");
  //   VFD_WriteStr(4,EC_C);
  //   VFD_WriteStr(5," ");
  //   VFD_WriteStr(6," ");
  //   VFD_WriteStr(7," ");
  //   VFD_WriteStr(0,brightChar);
  //   if(bright == 0){
  //     VFD_WriteStr(0,"   ");
  //   }
  //   if(bright < 10){
  //     VFD_WriteStr(1,"  ");
  //   }
  //   if(bright < 100){
  //     VFD_WriteStr(2," ");
  //   }
  //   if(EC != 0)
  //     bright_time = 0;
  //   bright_time = bright_time + 1;
  //   if(bright_time > 1000){
  //     old_bright = bright;
  //     bright_time = 0;
  //   }
  //}
  // if(EC_BT)

  // if(old_bright == bright){
  //   timeClient.update();
  //   String str=timeClient.getFormattedTime();
  //   char *formattedTime=(char*)str.c_str();
  //   VFD_WriteStr(0, formattedTime);
  // }
