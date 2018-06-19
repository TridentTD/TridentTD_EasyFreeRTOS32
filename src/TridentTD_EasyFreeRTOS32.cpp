#include "TridentTD_EasyFreeRTOS32.h"

#ifndef TASK_RESUME
#define TASK_RESUME(c)  vTaskResume(c)
#endif
#ifndef TASK_STOP
#define TASK_STOP(c)    vTaskSuspend(c)
#endif

void EasyFreeRTOS32::stop()   { TASK_STOP(_task_handler);   }
void EasyFreeRTOS32::resume() { TASK_RESUME(_task_handler); }

void EasyFreeRTOS32::start( TaskFunction_t fn, void * const arg, const uint32_t StackDepth, uint8_t core_no) {
  String task_name = String("FreeRTOS_Task_")+ String(random(10000));
  //Serial.println(task_name);
  if(core_no>1) core_no = 1;
  xTaskCreatePinnedToCore( fn, task_name.c_str(),StackDepth, arg, 5, &ptr->_task_handler, core_no); 
  //xTaskCreate( fn, task_name.c_str(),StackDepth, arg, 5, &ptr->_task_handler); 
}

portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;
