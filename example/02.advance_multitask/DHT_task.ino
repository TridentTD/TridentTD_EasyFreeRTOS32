/************************************************************** 
 *
 *  DHT_func
 * 
 *  task นี้จะทำหน้าที่ อ่านค่าเซนเซอร์ DHT อย่างเดียว 
 *  จะไม่มีการทำงานอย่างอื่นเป็นการแบ่ง งานกันทำอย่างเด็ดขาดไม่ปะปนกัน
 *  โดยค่าล่าสุดของ DHT sensor จะถูกเก็บไว้ที่ตัวแปร DHT_temp , DHT_humid 
 *  ซึ่ง task อื่นๆ สามารถนำไปใช้งานได้ เมื่อต้องการ
 *  
 *  หมายเหตุ
 *  ภายใน task ให้ใช้ DELAY() ตัวพิมพ์ใหญ่ทั้งหมด
 *  ไลบรารี่ DHT ใช้ของ Adafruit โดย ให้ติดตั้งไลบรารี่ทั้ง 2 นี้
 *     https://github.com/adafruit/Adafruit_Sensor
 *     https://github.com/adafruit/DHT-sensor-library
 *  
 **************************************************************/
 
#include <DHT.h>

#define DHT_PIN             5           // กำหนดขา pin
#define DHT_TYPE            DHT11       // กำหนดประเภท DHT11 หรือ DHT22
#define DHT_INTERVAL        1000        // (ms) กำหนดช่วงเวลาที่จะเข้าไปอ่านค่า sensor ซ้ำ

// Task Share Variables Info
// xDHT_temp   : ข้อมูล อุณหภูมิ ล่าสุด สำหรับ task อื่นนำไปใช้ได้ 
// xDHT_humid  : ข้อมูล ความชื้น ล่าสุด สำหรับ task อื่นนำไปใช้ได้ 

void DHT_func(void*) {
  //----พื้นที่สำหรับประกาศตัวแปรที่ใช้ภายใน task นี้เท่านั้น----
  DHT dht(DHT_PIN, DHT_TYPE);
  //-----------------------------------------------
  VOID SETUP() {                       // VOID SETUP() ใน task ใช้พิมพ์ใหญ่
    Serial.println("[DHT] task begin");
    dht.begin();
  }

  VOID LOOP() {                       // VOID LOOP() ใน task ใช้พิมพ์ใหญ่
    float t = NAN; float h = NAN;  
    while( isnan(t) || isnan(h) ) {
      t = dht.readTemperature();
      h = dht.readHumidity();
    }
    xDHT_temp = t;  xDHT_humid = h;  // ค่าที่อ่านได้ถูกต้องแล้ว ค่อย copy ไปไว้ที่ ตัวแปรค่าล่าสุด
    Serial.printf("[DHT] temp : %.2f C\thumid : %.2f %%\n", xDHT_temp, xDHT_humid);
    
    DELAY(DHT_INTERVAL);              // วนรอบถัดไปที่จะอ่าน sensor อีกครั้ง
  }
}

