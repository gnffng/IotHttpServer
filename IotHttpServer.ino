#include <FS.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <WakeOnLan.h>


const char* ssid = "*****"; //WiFi 이름
const char* password = "*****"; //WiFi Password

WiFiUDP UDP;
WakeOnLan WOL(UDP);

const char *MACAddress = "1C:1B:0D:1E:33:51";

// HTTP 로 연결될 포트 설정
AsyncWebServer server(80);

void setup()
{
    Serial.begin(115200);
    delay(10);
    
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    // 와이파이망에 연결
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());  

    setApi();
    startServer();
}

// HTTP route 및 method 구현
// method : HTTP_POST, HTTP_GET, HTTP_PUT, HTTP_ANY
void setApi() {    
    server.on("/wol", HTTP_GET, [](AsyncWebServerRequest *request){
        if(WOL.sendMagicPacket(MACAddress)){
          request->send(200, "text/plain", "Success WOL");
        }
        else{
          request->send(500, "text/plain", "Fail WOL");
        }
        
    });
}

// HTTP 서버 시작
void startServer() {
    server.begin();
}

void loop()
{
    
}