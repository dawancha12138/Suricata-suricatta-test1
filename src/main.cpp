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
#include <SS_gethostbyname.h>

const char* ssid     = "Xiaomi_7C9C";//连接WIFI名(SSID)
const char* password = "qwer1234";//WIFI密码
struct SS_hostandport address;

    // const struct addrinfo hints = {
    //     .ai_family = AF_INET,           /* 指定返回地址的协议簇，AF_INET(IPv4)、AF_INET6(IPv6)、AF_UNSPEC(IPv4 and IPv6)*/
    //     .ai_socktype = SOCK_STREAM,     /* 设定返回地址的socket类型，流式套接字 */     
    // }; 
    // char buf[100];  
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
  SS_gethostbyname("kidiota.f3322.net","19132",&address);//使用SS_gethostbyname需要提供域名、端口和事先声明的一个SS_hostandport结构体用于存储返回的IP地址和端口，该函数只能用于解码IPv4,
  if(&address!=NULL)
  {
  Serial.printf("ip:%s\nport:%d",address.SS_host,address.SS_port);
  }
  // Serial.print("Connected, IP address: ");
  // Serial.println(WiFi.localIP());//返回ESP8266的IP地址
  //  struct addrinfo *result;
  //   int err;
  //   err = getaddrinfo("kidiota.f3322.net", "19132", &hints, &result);
  //   if(err != 0)        /* 返回值不为0，函数执行失败*/
  //       Serial.printf("getaddrinfo err: %d \n",err);
  //                            /* 用来存储IP地址字符串 */
  //   struct sockaddr_in  *ipv4 = NULL;   /* IPv4地址结构体指针 */
  //       if(result->ai_family == AF_INET) 
  //   {
  //       ipv4 = (struct sockaddr_in *)result->ai_addr;//将得到的IP地址赋给新的IPv4结构体指针
  //       inet_ntop(result->ai_family, &ipv4->sin_addr, buf, sizeof(buf));//将接受到的IP地址信息转换成为点分十进制IP地址存入buf字符串
  //       Serial.printf("[IPv4]%s [port]%d \n",buf,ntohs(ipv4->sin_port));//打印转换后的IP地址和端口号
  //   }
  //   else
  //       Serial.printf("got IPv4 err !!!\n");
}

void loop() {
  //   Serial.print("Connecting to");
  // Serial.println(buf);
  // WiFiClient client;//tcp连接
  // const int httpPort=19132;//端口号
  // if(!client.connect(buf,httpPort)){//连接失败//只有上帝知道这是干什么用的
  //   Serial.println("connection failed");
  //   Serial.println(WiFi.localIP());
  //   return;
  // }
  // //向服务器发送请求
  // client.print("HelloServer!");
  // //读取返回值
  // while(client.available()){
  //   String line=client.readStringUntil('\r');
  //   Serial.print(line);
  // }
  // Serial.println();
  // Serial.println("closing connection");
  // delay(5000000);
}
