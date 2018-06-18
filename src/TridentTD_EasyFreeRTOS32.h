#ifndef __TRIDENTTD_EASY_FREERTOS32_H__
#define __TRIDENTTD_EASY_FREERTOS32_H__

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

#ifndef TridentOS 
#define TridentOS  EasyFreeRTOS32
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

#ifndef NO_INTERRUPTS	
#define NO_INTERRUPTS()     do { portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;  taskENTER_CRITICAL_ISR( &mux ) ; } while(0)	
#endif	
	
#ifndef INTERRUPTS	
#define INTERRUPTS()        do { portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;  taskEXIT_CRITICAL_ISR( &mux ) ; } while(0)	
#endif

class EasyFreeRTOS32 {
public:
  EasyFreeRTOS32() {};
  void start( TaskFunction_t fn, void * const arg=NULL, const uint32_t StackDepth=2048, uint8_t core_no=1);
  void stop();
  void resume();
    
  EasyFreeRTOS32* ptr = const_cast<EasyFreeRTOS32*>(this);
private:
  TaskHandle_t  _task_handler;
};

#endif //__TRIDENTTD_EASY_FREERTOS32_H__
