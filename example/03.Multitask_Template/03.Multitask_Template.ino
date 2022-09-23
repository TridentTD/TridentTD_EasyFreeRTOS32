#include <TridentTD_EasyFreeRTOS32.h>

EasyFreeRTOS32   task1, task2, task3, task4, task5;    // ประกาศตัวแปร task
void  task1_func(void*), task2_func(void*),       // ฟังกชั่นที่ task จะเรียกทำงาน
      task3_func(void*), task4_func(void*), task5_func(void*);

//----พื้นที่ส่วนนี้สำหรับประกาศตัวแปรที่ใช้แชร์ข้อมูลกันระหว่าง task ------


//---------------------------------------------------------

void setup(){  // setup() หลัก ใช้ตัวพิมพ์เล็ก
  Serial.begin(115200); Serial.println();

  task1.start( task1_func );  // เรียก task1_func ขึ้นมาทำงาน
  task2.start( task2_func );	// เรียก task2_func ขึ้นมาทำงาน
}

void loop(){}  // loop() หลักใช้ตัวพิมพ์เล็ก

/*
 * ข้อกำหนดมาตรฐาน TridentOS
 *   - ใน setup() หลัก ไม่มีการทำงานอย่างอื่นใด
 *     นอกจาก เรียก task ที่ต้องการขึ้นมาทำงาน
 *   - ใน loop() หลัก  ไม่มีการทำงานอย่างอื่นใดๆเลย
 *   - ในแต่ละ task จะมี VOID SETUP()  และ VOID LOOP() เป็นของตัวเอง โดยใช้พิพม์ใหญ่
 *     และหากจะใช้ DELAY(..) ให้ใช้พิมพ์ใหญ่เสมอ
 *   - ใน task นึงๆ สามารถเรียก task อื่นๆ ขึ้นมาทำงาน ก็ได้
 *     เช่น สามารถเรียก task3.begin( task3_func); ขึ้นมาทำงานจากภายใน task1 ได้
 *   - หากจะหยุด task หลังทำงานไปแล้ว
 *     เช่น หยุดการทำงาน task3  ก็ใช้คำสั่ง  task3.stop();
 *   - หากจะให้กลับมาทำงานใหม่ ก็เรียก task3.resume();
 *   - ตัวแปรที่ใช้แชร์ระหว่าง task มาตรฐานให้ใช้ x พิมพ์เล็กนำหน้าเสมอ
 */

