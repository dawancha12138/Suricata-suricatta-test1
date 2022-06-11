#include <Arduino.h>
#include <iostream>
uint8_t bright = 128;
bool EC11_A_P = 0;
bool EC11_B_P = 0;
uint8_t EC11_A   = 21;
uint8_t EC11_B   = 4;
//使用ECV函数必须预先生命两个布尔变量用于保存A/B之前的值
//返回编码器的值
int ECV(uint8_t A,uint8_t B,bool* A_P,bool* B_P)//该函数返回EC的值，顺时针旋转一下，EC为1，逆时针旋转为负数，接受四个参数，A/B表示对应的两个IO口，A_P/B_P是预先生命的全局布尔变量
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
    while(digitalRead(B))//如果编码器按键没有被按下则一直循环
    {
        *bright+=ECV(EC11_A,EC11_B,&EC11_A_P,&EC11_B_P);
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