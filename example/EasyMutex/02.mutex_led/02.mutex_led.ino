/************************************************************
 * ตัวอย่างนี้จะมีการใช้เรียกใช้งาน "สิ่งดียวกัน" คือ LED
 * จาก task ต่างๆ  โดย task ไหน ได้รับงานไปก่อน
 * ผ่านทาง mutex_led ก็จะมีการเรียกใช้ LED ทำงานในแบบของตนให้เสร็จก่อน
 * ไม่ถูก task อื่นๆ มาแย่งซีนดึง LED ไปใช้แทรกคั่นระหว่างกลาง
 *
 * เมื่อ task นึงๆที่ได้รับ mutex_led ได้ทำงาน LED แบบของ task นั้นเสร็จ
 * ก็ค่อยส่งต่อ mutex_led ไปให้ task อื่นที่มีการเรียกใช้ LED เดียวกัน 
 * ให้นำ LED ไปใช้งานคนละแบบต่อไปได้
 *
 * หากไม่มี mutex_led จะเกิดการแย่งซีนของ task ต่างๆ
 * ทำงานเรียกใช้ "สิ่งเดียวกัน" คือ LED ทำงานสลับปะปน ไม่ถูกต้องได้
 ************************************************************/

#include <TridentTD_EasyFreeRTOS32.h>

#define LED       LED_BUILTIN
#define LED_ON    LOW
#define LED_OFF   HIGH

EasyMutex mutex_led;

void setup() {
  Serial.begin(115200); Serial.println();

  pinMode(LED, OUTPUT);

  // task นี้จะมีการเรียกใช้ "สิ่งเดียวกัน" กับ task อื่นๆ ในที่นี้คือ LED เดียวกัน
  // ให้กระพริบแบบทีละ 1 วินาที ติดดับ ไป 3 รอบ
  static EasyFreeRTOS32 task1;
  task1.start([task1](void*){
    //--------------------------------
    if(!mutex_led.TAKE()) return;
    //--------------------------------
    
    for(int i=0; i< 3; i++){
      digitalWrite(LED, LED_ON);
      DELAY(1000);
      digitalWrite(LED, LED_OFF);
      DELAY(1000);
    }
    
    //--------------------------------
    mutex_led.GIVE();
    //--------------------------------
    
    task1.del();
  });

  // task นี้จะมีการเรียกใช้ "สิ่งเดียวกัน" กับ task อื่นๆ ในที่นี้คือ LED เดียวกัน
  // ให้กระพริบแบบทีละ 100 ms ติดดับ ไป 20 รอบ
  static EasyFreeRTOS32 task2;
  task2.start([task2](void*){
    //--------------------------------
    if(!mutex_led.TAKE()) return;
    //--------------------------------

    for(int i=0; i< 20; i++){
      digitalWrite(LED, LED_ON);
      DELAY(100);
      digitalWrite(LED, LED_OFF);
      DELAY(100);
    }

    //--------------------------------
    mutex_led.GIVE();
    //--------------------------------
    
    task2.del();
  });
}

void loop() {
}

