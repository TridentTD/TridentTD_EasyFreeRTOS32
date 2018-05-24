
void myblink(void*){          //  task แรก เรียกทำงานที่นี่
  //----พื้นที่สำหรับประกาศตัวแปรที่ใช้ภายใน task นี้เท่านั้น----

  //-----------------------------------------------

  VOID SETUP(){               //  เหมือน setup() แต่ใส่ชื่อเป็น SETUP() พิมพ์ใหญ่แทน
    Serial.println("Hello Blink Task");  
    pinMode(2,OUTPUT);
  }
  
  VOID LOOP() {               // เหมือน loop() แต่ใส่ชื่อเป็น LOOP() พิมพ์ใหญ่แทน
    digitalWrite(2,HIGH);
    DELAY(1000);              // เหมือน delay(..) แต่ใส่ชื่อเป็น DELAY(..)พิมพ์ใหญ่แทน
    digitalWrite(2,LOW);
    DELAY(1000);
  }
}

