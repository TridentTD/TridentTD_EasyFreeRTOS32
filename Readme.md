TridentTD_EasyFreeRTOS32 Library
===

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
ไลบรารี่สำหรับ เขียนแบบ Multitasking แบบ TridentTD บนเพรตฟอร์ม ESP32  

<p align="center">
  <img src="Picture.png" alt="image"/>
</p>  

### วิธีการใช้งาน  

1. เรียกใช้ไลบรารี่  
```c  
     #include <TridentTD_EasyFreeRTOS32.h>
``` 
2. ประกาศตัวแปร task ย่อยๆ และ ฟังกชั่น ที่ task จะเรียกขึ้นทำงาน  
```c  
     EasyFreeRTOS32   task1, task2, task3;
     void task1_func(void*), task2_func(void*), task3_func(void*);
```
3. รูปแบบมาตรฐาน ฟังก์ชั่น task ย่อยๆ ที่จะถูกเรียกใช้งาน เป็นดังนี้  
```c
    void task1_func(void*)  {   // ฟังกชั่นที่ task1 เรียกทำงาน  - void ใช้ตัวพิมพ์เล็ก
          //----พื้นที่สำหรับประกาศตัวแปรที่ใช้ภายใน task นี้เท่านั้น----

          //-----------------------------------------------

          VOID SETUP() {  // VOID SETUP() ใน task ให้ใช้ตัวพิมพ์ใหญ่

          }
          VOID LOOP() {   // VOID LOOP() ใน task ให้ใช้ตัวพิมพ์ใหญ่

          }
    }

```
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
**หมายเหตุ**  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
ภายในฟังกชั่น task ให้ใช้ delay ด้วยคำสั่ง DELAY(..) ตัวพิมพ์ใหญ่เท่านั้น  

4. หากจะเรียก task ไหนทำงาน เช่น สำหรับ task1 ใช้คำสั่ง  
```c
     task1.start(task1_func);
```
5. หากจะหยุด task ไหนทำงาน เช่น สำหรับ task1 ใช้คำสั่ง  
```c
     task1.stop();
```
6. หากจะใช้งานต่อ task ไหนทำงาน เช่น สำหรับ task1 ใช้คำสั่ง  
```c
     task1.resume();
```

7. สำหรับการแลกเปลี่ยนข้อมูลระหว่าง task ให้ ประกาศตัวแปรไว้ใน  
พื้นที่ ประกาศตัวแปรสำหรับแชร์ระหว่าง task (ดูที่ Template)  
โดย ให้มีมาตรฐานการตั้งชื่อ ตัวแปรสำหรับแชร์ระหว่าง task ให้ขึ้นต้นนำด้วยตัว x (เอ็กซ์พิมพ์เล็ก)

```c
    //------- พื้นที่สำหรับประกาศตัวแปรแชร์ระหว่าง task ---------------
     float  xDHT_temp, xDHT_humid;    // มีตัว x เล็กนำหน้า เพื่อง่ายต่อการสังเกตุ
    //---------------------------------------------------------
```

### การจูนพื้นที่เม็มโมรี่สำหรับ task นึงๆ
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
ในบางครั้งเพื่อการทำงานของ task นึงๆ เพื่อให้สามารถทำงานได้อย่างมีประสิทธิภาพ   
บางคราวเราอาจมีความจำเป็นต้องมีการปรับจูนพื้นที่เม็มสำหรับ task นึงๆให้เหมาะสมกับการใช้งาน  
  
วิธีการปรับจูนพื้นที่เม็มโมมี่ สำหรับ task นึงๆสามารถปรับได้ด้วยคำสั่งดังนี้  
```c
     task1.start(task1_func, NULL, 4096);  // ขอใช้พื้นที่ขนาด 4096bytes
```


-----
**TridentTD**  
24 พฤษภาคม 2561 (ปีแห่งฤดูฝนตกชุก)  
วัน ๕᧪๗ ปีจอ  
Version 1.0  

