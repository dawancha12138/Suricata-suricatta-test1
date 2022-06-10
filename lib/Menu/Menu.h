#include <Arduino.h>
#include <iostream>
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