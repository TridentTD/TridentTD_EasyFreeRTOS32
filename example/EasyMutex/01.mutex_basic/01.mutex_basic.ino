/*********************************************
 * Mutex เปรียบเสมือนเป็นการ จองการทำงานของ "สิ่งเดียวกัน"
 * ให้ task นึงๆ ทำงานให้เสร็จก่อน ค่อยให้ task ถัดๆไป
 * ที่เข้ามาเรียกใช้ "สิ่งเดียวกัน" นั้น ค่อยทำงานต่อได้
 * ไม่เกิดการแย่งกันทำงาน
 * 
 * ตัวอย่างนี้ เพื่อให้เห็นความแตกต่างระหว่าง แบบไม่มี mutex
 * โดย task ต่างๆ มีเรียกใช้ "สิ่งเดียวกัน" ทำงาน 
 * ให้ทดลอง ด้วย
 * 
 *   #define TEST_WITH_MUTEX    0 
 *   
 * ผลคือ task ต่างๆ ที่ใช้ "สิ่งเดียวกัน"
 * นั้นจะมีการใช้สลับปะปนระหว่าง task กันไป 
 * 
 * แต่เมื่อ ทดลองอีกแบบ  แบบมี mutex เรียกใช้ด้วย
 * โดย task ต่างๆ มีเรียกใช้ "สิ่งเดียวกัน" ทำงาน 
 * ให้ทดลอง ด้วย
 * 
 *   #define TEST_WITH_MUTEX    1
 *   
 * ผลคือ ทำให้ task นึงๆ ทำงาน "สิ่งเดียวกัน" นั้นให้เสร็จก่อน
 * ค่อยให้ task อื่นๆ รับช่วงต่อไปทำงานได้
 * การทำงาน จะไม่สลับไปมาปะปนกันระหว่าง task ต่างๆ
 * ที่มีเรียกใช้ "สิ่งเดียวกัน" ทำงาน
 * 
 ********************************************/

#include <TridentTD_EasyFreeRTOS32.h>

#define TEST_WITH_MUTEX     1

void print_number(const char* from_task){
#if TEST_WITH_MUTEX
  static EasyMutex mutex;
  if(!mutex.TAKE()) return;
#endif

  for(int i=0;i<10;i++){
    Serial.printf("[%s] %d\n", from_task, i);
    delay(1);
  }

#if TEST_WITH_MUTEX
  mutex.GIVE();
#endif

}

void setup() {
  Serial.begin(115200); Serial.println();

  static EasyFreeRTOS32 task1,task2;
  task1.start([task1](void*){
    print_number("TASK1");    // ใน task มีการเรียกใช้ "สิ่งเดียวกัน" กับ task อื่นๆ
    task1.del();
  });
  task2.start([task2](void*){
    print_number("TASK2");    // ใน task มีการเรียกใช้ "สิ่งเดียวกัน" กับ task อื่นๆ
    task2.del();
  });
}

void loop() {
  // put your main code here, to run repeatedly:

}

