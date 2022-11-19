/**********************************************
 * ตัวอย่างนี้ task จะหยุด รอจนกว่า Interrupt มีการคืน
 * mutex_led มา เมื่อ task ได้รับ mutex_led จึงจะทำงานใน task
 * จนเสร็จแล้วหยุดรอ interrupt รอบใหม่ๆ
 **********************************************/

#include <TridentTD_EasyFreeRTOS32.h>

#define BUTTON1         16
#define LED             22
#define LED_ON          LOW
#define LED_OFF         HIGH

EasyMutex mutex_led(ISR_TYPE);    // กำหนด mutex ที่จะใช้งานแบบ interrupt
uint16_t isr_count;


void setup() {
  Serial.begin(115200); Serial.println();

  pinMode(LED    , OUTPUT);
  pinMode(BUTTON1, INPUT_PULLUP);
  attachInterrupt(BUTTON1, [](){
    isr_count1++;
    // เมื่อ Interrupt ทำงาน ตามเงื่อนไข
    // ค่อยส่ง mutex_led คืนไปให้ task อื่นๆ ที่จะใช้ ดึงไปทำงาน
    if(isr_count1 >=3){
      mutex_led.GIVE_FROM_ISR();    
    }
  }, FALLING );
  
  static EasyFreeRTOS32 task1;
  task1.start([task1](void*){
    VOID LOOP(){
      // จะถูก block หยุดรอจนกว่าจะมี mutex_led ได้รับเข้ามาจาก Interrupt
      if( !mutex_led.TAKE()) return;  

      // งานที่ต้องการทำ แล้วแต่จะนำไปใช้งานต่างๆ ได้
      if( isr_count1 > 0 ) {
        isr_count1 = 0;        
        Serial.println("[TASK1] run after Button1 ISR occurs");
        for(int i=0; i< 3; i++){
          digitalWrite(LED, LED_ON);
          DELAY(1000);
          digitalWrite(LED, LED_OFF);
          DELAY(1000);
        }
      }
    }
  });
  

}

void loop() {
  DELAY(1);
}

