/*****************************************************
 * 
 *  Blink_func 
 *
 *  task นี้จะทำหน้าที่ สั่งไฟกระพริบ 
 *  สามารถปรับกระพริบเร็วช้าได้ตามกำหนด
 *  
 *  หมายเหตุ
 *  ภายใน task ให้ใช้ DELAY() ตัวพิมพ์ใหญ่ทั้งหมด
 *  
 ****************************************************/

#define BLINK_LED_PIN       2
#define DEFAULT_BLINK_DELAY 1000

// Task Share Variables Info
// xBlink_Dalay   : สำหรับ task ภายนอกกำหนดความเร็วการกระพริบใน task นี้ได้

void Blink_func(void* arg){  // Blink_task เรียกทำงานที่นี่
  VOID SETUP(){                       // VOID SETUP() ใน task ใช้พิมพ์ใหญ่
    pinMode(BLINK_LED_PIN,OUTPUT);
    if( xBlink_Delay <= 0) xBlink_Delay = DEFAULT_BLINK_DELAY;
  }

  VOID LOOP() {                       // VOID LOOP() ใน task ใช้พิมพ์ใหญ่
    digitalWrite(BLINK_LED_PIN,HIGH);
    DELAY(xBlink_Delay);              // DELAY(..) ใน task ใช้พิมพ์ใหญ่
    digitalWrite(BLINK_LED_PIN,LOW);
    DELAY(xBlink_Delay);
  }
}

