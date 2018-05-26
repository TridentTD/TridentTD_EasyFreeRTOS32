/*
 ***************************************************** 
 *  WiFi_func 
 *
 *  task นี้จะทำหน้าที่ เชื่อมต่อ WiFi เท่านั้น
 *  หากไวไฟหลุด จะข้ามไปสั่ง Blink_task ให้กระพริบถี่ๆ 
 *  
 *  หมายเหตุ
 *  ภายใน task ให้ใช้ DELAY() ตัวพิมพ์ใหญ่ทั้งหมด
 *  
 *****************************************************
 */

#include <WiFi.h>

void WiFi_func(void*){  
  //----พื้นที่สำหรับประกาศตัวแปรที่ใช้ภายใน task นี้เท่านั้น----

  //-----------------------------------------------

  VOID SETUP(){         // ภายใน task ใช้ SETUP() พิมพ์ใหญ่
    WiFi.begin( WIFI_SSID, WIFI_PASSWORD );
  }

  VOID LOOP(){         // ภายใน task ใช้ LOOP() พิมพ์ใหญ่
    if( !WiFi.isConnected() ) {
      // สั่ง Blink_task ให้ ไฟกระพริบ ถี่ ทุก 80 ms
      void *blink_delay = new int(80);  //ms
      Blink_task.start( Blink_func, blink_delay);
  
      while(!WiFi.isConnected() ) DELAY(400);
      Serial.print("[WiFi] WiFi Connected, IP : ");
      Serial.println(WiFi.localIP());
      
      // สัง Blink_task หยุดการทำงาน หลังไวไฟเชื่อมต่อได้แล้ว
      Blink_task.stop();  

      // สั่งให้ AsyncWebServer_task เริ่มทำงาน
      AsyncWebServer_task.start(AsycWebServer_func);
    }
    
    DELAY( WIFI_INTERVAL *60000); // เช็คสถานะไวไฟทุกๆ กี่นาทีถัดไป
  }
}