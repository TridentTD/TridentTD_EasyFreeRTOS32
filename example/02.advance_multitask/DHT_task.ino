/*
 ************************************************************** 
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
 *************************************************************
 */
 
#include <DHT.h>

void DHT_func(void*) {         // task สอง เรียกทำงานที่นี่
  //----พื้นที่สำหรับประกาศตัวแปรที่ใช้ภายใน task นี้เท่านั้น----

  //-----------------------------------------------
  DHT dht(DHT_PIN, DHT_TYPE);
  
  VOID SETUP() {              // เหมือน setup() แต่ใส่ชื่อเป็น SETUP() พิมพ์ใหญ่แทน
    Serial.println("[DHT] task begin");
    dht.begin();
  }

  VOID LOOP() {               // เหมือน loop() แต่ใส่ชื่อเป็น LOOP() พิมพ์ใหญ่แทน
    float t = NAN; float h = NAN;  
    while( isnan(t) || isnan(h) ) {
      t = dht.readTemperature();
      h = dht.readHumidity();
    }
    DHT_temp = t;  DHT_humid = h;  // ค่าที่อ่านได้ถูกต้องแล้ว ค่อย copy ไปไว้ที่ ตัวแปรค่าล่าสุด
    Serial.printf("[DHT] temp : %.2f C\thumid : %.2f %%\n", DHT_temp, DHT_humid);
    
    DELAY(DHT_INTERVAL);      // วนรอบถัดไปที่จะอ่าน sensor อีกครั้ง
  }
}
