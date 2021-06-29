// 動手做17-2：建立微型網站伺服器，靜態IP
// 詳細的程式說明，請參閱第17章，17-25頁。

#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {0xF0, 0x7B, 0xCB, 0x4B, 0x7C, 0x9F};
IPAddress ip(192, 168, 1, 25);
IPAddress subnet(255, 255, 255, 0);
IPAddress gateway(192, 168, 1, 1);

String HTML =
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html\r\n"
    "\r\n"
    "<html><head><meta charset=\"utf-8\"></head>"
    "<body><h1>Arduino物聯網應用</h1></body></html>"
    "\r\n";

EthernetServer server(80);

void setup()
{
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
}

void loop()
{
  EthernetClient client = server.available();

  if (client)
  {
    while (client.connected())
    {
      if (client.available())
      {
        client.print(HTML);
        break;
      }
    }

    delay(1);
    client.stop();
  }
}
