/*****************************************************************
 *  ตัวอย่าง 
 *     - WiFi task  : สำหรับจัดการ WiFi 
 *     - DHT task   : สำหรับ อ่านค่า DHT Sensor อย่างเดียวไปเรื่อยๆ
 *     - Blink task : สำหรับไฟกระพริบ แล้วแต่จะสั่งใช้งาน
 *     - AsyncWebServer task : สำหรับ สร้าง WebServer แบบ Asynchonous ทำงาน 
 *                             ทุกครั้งที่มีการต่อไวไฟสำเร็จ
 *  
 *  หมายเหตุ
 *  ติดตั้ง Library ทั้ง 4 ให้เรียบร้อย
 *  library สำหรับ WebServer แบบ Asynchronous
 *     https://github.com/me-no-dev/AsyncTCP
 *     https://github.com/me-no-dev/ESPAsyncWebServer
 * 
 *  library สำหรับ DHT sensor
 *     https://github.com/adafruit/Adafruit_Sensor
 *     https://github.com/adafruit/DHT-sensor-library
 *
 ******************************************************************/

#include <TridentTD_EasyFreeRTOS32.h>

// ประกาศ ตัวแปร task และ function สำหรับ task
EasyFreeRTOS32   DHT_task, Blink_task, WiFi_task, AsyncWebServer_task;
void DHT_func(void*), Blink_func(void*), WiFi_func(void*), AsyncWebServer_func(void*);

//----พื้นที่ส่วนนี้สำหรับประกาศตัวแปรที่ใช้แชร์ข้อมูลกันระหว่าง task ------
int     xBlink_Delay;    // กำหนดความเร็วของไฟกระพริบ       (มาตรฐานให้ใช้ x นำ)
float   xDHT_temp;       // อุณหภูมิ จาก DHT ค่าล่าสุดที่อ่านได้  (มาตรฐานให้ใช้ x นำ)
float   xDHT_humid;      // ความชื้น จาก DHT ค่าล่าสุดที่อ่านได้  (มาตรฐานให้ใช้ x นำ)
//---------------------------------------------------------

void setup(){  // setup() หลักตัวพิมพ์เล็ก
  Serial.begin(115200); Serial.println();
    
  DHT_task.start( DHT_func );
  WiFi_task.start( WiFi_func );  
}

void loop(){}  // loop() หลักตัวพิมพ์เล็ก ไม่จำเป็นต้องใช้แต่ให้มีไว้เสมอ

