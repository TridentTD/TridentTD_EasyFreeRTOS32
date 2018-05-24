/*
 ***************************************************** 
 *  Blink_func 
 *
 *  task นี้จะทำหน้าที่ สั่งไฟกระพริบ 
 *  สามารถปรับกระพริบเร็วช้าได้ตามกำหนด
 *  
 *  หมายเหตุ
 *  ภายใน task ให้ใช้ DELAY() ตัวพิมพ์ใหญ่ทั้งหมด
 *  
 ***************************************************
 */


void Blink_func(void* arg){  // Blink_task เรียกทำงานที่นี่
  // ค่า blink_delay ที่ส่งมาจากภายนอก task
  int blink_delay  = (arg == NULL)?  1000: *(int*) arg;  //ms

  VOID SETUP(){                       // VOID SETUP() พิมพ์ใหญ่
    pinMode(BLINK_LED_PIN,OUTPUT);
  }
  
  VOID LOOP() {                       // VOID LOOP() พิมพ์ใหญ่
    digitalWrite(BLINK_LED_PIN,HIGH);
    DELAY(blink_delay);               // DELAY(..)พิมพ์ใหญ่
    digitalWrite(BLINK_LED_PIN,LOW);
    DELAY(blink_delay);
  }
}