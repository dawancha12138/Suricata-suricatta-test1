#include <Arduino.h>
#include <iostream>
#include <Suricata_VFD.h>
#include "soc/rtc_wdt.h"
uint8_t bright = 128;//初始亮度
uint8_t menu_v=0;//模式选择
bool EC11_A_P = 0;//以下两行为旋钮两引脚过去的值的存储
bool EC11_B_P = 0;
uint8_t EC11_A   = 21;//以下两行为旋钮引脚对应IO口的设置
uint8_t EC11_B   = 4;
uint8_t EC_BT =25;//编码器按键
bool EC_BT_ST=0;//编码器按钮的值,按下变为1
int EC=0;//
int a=0;
void IRAM_ATTR Interrupt_EC_V(void);
//使用ECV函数必须预先生命两个布尔变量用于保存A/B之前的值
//返回编码器的值
int ECV(uint8_t A,uint8_t B,bool* A_P,bool* B_P)//该函数返回EC的值，顺时针旋转一下，EC为1，逆时针旋转为负数，接受四个参数，A/B表示对应的两个IO口，A_P/B_P是预先声明用于存储AB过去值的全局布尔变量
{
    int EC=0;
    bool A_ST;
    bool B_ST;
    A_ST = digitalRead(A);
    B_ST = digitalRead(B);
    if(!A_ST&&!B_ST)
  {
    if(!*A_P&&*B_P)
    {
     EC = -1; 
    }
    else if(*A_P&&!*B_P)
    {
     EC = 1;
    }
  }
  *A_P=A_ST;
  *B_P=B_ST;
  return EC;
}

void Bright(uint8_t B,uint8_t *bright)//调整亮度,参数为编码器按键和亮度值的指针
{
    uint8_t old_bright = 0;
    VFD_WriteStr(0,"        ");
    while(!EC_BT_ST)//如果编码器按键没有被按下则一直循环
    {
        *bright+=ECV(EC11_A,EC11_B,&EC11_A_P,&EC11_B_P);
        delay(1);//只有我和上帝知道这行代码是干什么用的
        if(*bright!=old_bright)
        {
        VFD_Bright(*bright);
         char brightChar[4];
        itoa(*bright,brightChar,10);
        VFD_WriteStr(0,brightChar);
        old_bright=*bright;
        if(*bright == 0){
             VFD_WriteStr(0,"   ");
        }
        if(*bright < 10){
             VFD_WriteStr(1,"  ");
         }
         if(*bright < 100){
             VFD_WriteStr(2," ");
         }
        }
    }
}

void IRAM_ATTR Interrupt_EC_BT(void)//将编码器按钮的值设置为1
{
   EC_BT_ST=1;
}