/*****************************************************
 *
 * AsycWebServer_func
 *
 * task นี้จะทำหน้าที่ สร้าง WebServer แบบ Asynchronous
 * ทาง WebServer ไม่จำเป็นต้องรอให้ client นึงๆที่ติดต่อเข้ามา
 * เรียกทำงานจนจบกระบวนการ ค่อยให้ client ถัดไปใช้งาน
 * ทำให้การทำงานแบบ Multitask มีความไหลลื่นกว่าปกติ
 *
 * หมายเหตุ
 * ภายใน task ให้ใช้ DELAY() ตัวพิมพ์ใหญ่ทั้งหมด
 * ไลบรารี่ สร้าง WebServer แบบ Asynchronous ให้ติดตั้งไลบรารี่ทั้ง 2 นี้
 *    https://github.com/me-no-dev/AsyncTCP
 *    https://github.com/me-no-dev/ESPAsyncWebServer
 *
 ****************************************************/

#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);

void AsycWebServer_func(void*) {
  //----พื้นที่สำหรับประกาศตัวแปรที่ใช้ภายใน task นี้เท่านั้น----

  //-----------------------------------------------
  VOID SETUP() {                       // VOID SETUP() ใน task ใช้พิมพ์ใหญ่
    server.on("/heap", HTTP_GET, [](AsyncWebServerRequest * request) {
      request->send(200, "text/plain", String(ESP.getFreeHeap()));
    });
    
    server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
      char buf[50];
      sprintf(buf, "<H2>Temp  : %.2f<br>\nHumid : %.2f<br></H2>\n", xDHT_temp, xDHT_humid);      
      request->send(200, "text/html", String(buf));
    });
    
    server.onNotFound([](AsyncWebServerRequest * request) {
      Serial.println("[AsyncWebServer] Page NOT FOUND ");
      request->send(404, "text/plain", "Page not found");
    });

    Serial.println("[AsyncWebServer] start!");
    Serial.printf ("[AsyncWebServer] Open http://%s on the browser.\n", WiFi.localIP().toString().c_str());
    server.begin();
  }

  VOID LOOP() {                        // VOID LOOP() ใน task ใช้พิมพ์ใหญ่
    DELAY(1);                          // DELAY(..) ใน task ใช้พิมพ์ใหญ่
  }
}

