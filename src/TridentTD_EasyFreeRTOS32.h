#ifndef __TRIDENTTD_EASY_FREERTOS32_H__
#define __TRIDENTTD_EASY_FREERTOS32_H__

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

#define EASYFREERTOS32_VERSION    1.8

#ifndef TridentOS 
#define TridentOS  EasyFreeRTOS32
#endif

#ifndef EasyTask32
#define EasyTask32  EasyFreeRTOS32
#endif

#ifndef DELAY
#define DELAY(a) vTaskDelay((a)/portTICK_PERIOD_MS);
#endif

#ifndef VOID
#define VOID
#endif

#ifndef SETUP
#define SETUP()
#endif

#ifndef LOOP
#define LOOP()     for(;;)
#endif

extern portMUX_TYPE mux;

#ifndef NO_INTERRUPTS
#define NO_INTERRUPTS()     taskENTER_CRITICAL_ISR( &mux )
#endif

#ifndef INTERRUPTS
#define INTERRUPTS()        taskEXIT_CRITICAL_ISR( &mux )
#endif

#define CORE0       ((uint8_t)0)
#define CORE1       ((uint8_t)1)

class EasyFreeRTOS32 {
public:
  EasyFreeRTOS32() {};
  void start( TaskFunction_t fn, void * const arg=NULL, const uint32_t StackDepth=2048, uint8_t core_no=1);
  inline void start( TaskFunction_t fn, const uint32_t StackDepth, uint8_t core_no) 	{ start( fn, NULL, StackDepth, core_no); }
  inline void start( uint8_t core_no, TaskFunction_t fn) 															{ start( fn, NULL, 2048, core_no);       }
  inline void start( uint8_t core_no, const uint32_t StackDepth, TaskFunction_t fn )  { start( fn, NULL, StackDepth, core_no); }
  inline void start( void* arg , TaskFunction_t fn)                                   { start( fn, arg, 2048, 1); }
  inline void start( void* arg , uint8_t core_no, TaskFunction_t fn)                  { start( fn, arg, 2048, core_no); }
  inline void start( void* arg , uint8_t core_no, const uint32_t StackDepth, TaskFunction_t fn) { start( fn, arg, StackDepth, core_no); }
  inline bool started()           { return _created; }

  void stop();
  inline void pause()             { this->stop(); }
  void resume();
  void del();
    
  EasyFreeRTOS32* ptr = const_cast<EasyFreeRTOS32*>(this);
private:
  bool _created = false;
  TaskHandle_t  _task_handler;
};


#define ISR_TYPE      true

class EasyMutex {
public:
  EasyMutex(bool isr_type=false);
  void create(bool isr_type=false);
  void del();
  bool TAKE(uint32_t prior_waken=0xFFFF);
  void GIVE();

  bool TAKE_FROM_ISR(bool task_waken=false);
  void GIVE_FROM_ISR(bool task_waken=false);
private:
  QueueHandle_t _xMutex;
  bool _isr = false;

};

#endif //__TRIDENTTD_EASY_FREERTOS32_H__
