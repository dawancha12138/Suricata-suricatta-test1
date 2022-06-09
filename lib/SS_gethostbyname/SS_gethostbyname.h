#include <WiFi.h>
#include "lwip/dns.h"
#include <string.h>
#include <sys/param.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "driver/gpio.h"
#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"

struct SS_hostandport//返回值所用的结构体
{
    char SS_host[100];//地址
    __uint16_t SS_port;//端口
};
 const struct addrinfo hints = {
        .ai_family = AF_INET,           /* 指定返回地址的协议簇，AF_INET(IPv4)、AF_INET6(IPv6)、AF_UNSPEC(IPv4 and IPv6)*/
        .ai_socktype = SOCK_STREAM,     /* 设定返回地址的socket类型，流式套接字 */     
    }; 
struct SS_hostandport* SS_gethostbyname(const char* name,const char* port,struct SS_hostandport* address)//接受域名、端口和最终存储IP地址和端口的结构体作为参数
{
    
    struct addrinfo *result;//用于存储得到的IP地址和端口
    int err;
    err = getaddrinfo(name,port, &hints, &result);
    if(err != 0)  
    {      /* 返回值不为0，函数执行失败*/
        Serial.printf("getaddrinfo err: %d \n",err);//输出错误代码
        address=NULL;//失败返回NULL
        return address;
    }
    char buf[100];                         /* 用来存储IP地址字符串 */
    struct sockaddr_in  *ipv4 = NULL;   /* IPv4地址结构体指针 */
        if(result->ai_family == AF_INET) 
    {
        ipv4 = (struct sockaddr_in *)result->ai_addr;//将得到的IP地址赋给新的IPv4结构体指针
        inet_ntop(result->ai_family, &ipv4->sin_addr, buf, sizeof(buf));//将接受到的IP地址信息转换成为点分十进制IP地址存入buf字符串
        Serial.printf("[IPv4]%s [port]%d \n",buf,ntohs(ipv4->sin_port));//打印转换后的IP地址和端口号
        if(address!=NULL)
        {
        strcpy(address->SS_host,buf);//将得到的IP地址存入最终将要返回的结构体
        address->SS_port=ntohs(ipv4->sin_port);//将端口存入最终将要返回的结构体
        }
        
    }
    else
    {   
        Serial.printf("got IPv4 err !!!\n");
        address=NULL;
    }
        return address;
};

 