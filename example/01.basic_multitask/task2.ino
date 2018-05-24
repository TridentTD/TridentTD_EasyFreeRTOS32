
void myprint(void*){          // task สอง เรียกทำงานที่นี่
  //----พื้นที่สำหรับประกาศตัวแปรที่ใช้ภายใน task นี้เท่านั้น----

  //-----------------------------------------------
  
  VOID SETUP(){               // เหมือน setup() แต่ใส่ชื่อเป็น SETUP() พิมพ์ใหญ่แทน
    for(int i = 0; i <=20; ++i){
      Serial.println(random(1000));
      DELAY(300);             // เหมือน delay(..) แต่ใส่ชื่อเป็น DELAY(..)พิมพ์ใหญ่แทน
    }
    Serial.println("------------------------");
    Serial.println("END myprint Task");
  }

  VOID LOOP(){                // เหมือน loop() แต่ใส่ชื่อเป็น LOOP() พิมพ์ใหญ่แทน
    DELAY(1);
  }
}

