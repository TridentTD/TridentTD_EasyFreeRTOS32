#include "TridentTD_EasyFreeRTOS32.h"

#ifndef TASK_RESUME
#define TASK_RESUME(c)  vTaskResume(c)
#endif
#ifndef TASK_STOP
#define TASK_STOP(c)    vTaskSuspend(c)
#endif
#ifndef TASK_DELETE
#define TASK_DELETE(c)  vTaskDelete(c)
#endif

void EasyFreeRTOS32::stop()   { if(_created ) TASK_STOP(_task_handler);   }
void EasyFreeRTOS32::resume() { if(_created ) TASK_RESUME(_task_handler); }
void EasyFreeRTOS32::del()    { if(_created ) { _created= false; TASK_DELETE(_task_handler); } }

void EasyFreeRTOS32::start( TaskFunction_t fn, void * const arg, const uint32_t StackDepth, uint8_t core_no) {
	if( _created ) this->del();

  String task_name = String("FreeRTOS_Task_")+ String(random(10000));
  //Serial.println(task_name);
  if(core_no>1) core_no = 1;
  xTaskCreatePinnedToCore( fn, task_name.c_str(),StackDepth, arg, 5, &ptr->_task_handler, core_no); 
  _created = true;
  //xTaskCreate( fn, task_name.c_str(),StackDepth, arg, 5, &ptr->_task_handler); 
}

portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;


//-----------------------------------------------
EasyMutex::EasyMutex(bool isr_type){
  this->create(isr_type);
}

void EasyMutex::create(bool isr_type){
  if(isr_type) {
    _isr = true;
    _xMutex = xSemaphoreCreateBinary();
    Serial.println("Create Semophore Bin");
  }else{
    _isr = false;
    _xMutex = xSemaphoreCreateMutex();
  }
}

void EasyMutex::del(){
	vSemaphoreDelete(_xMutex);
}
bool EasyMutex::TAKE(uint32_t prior_waken) {
  return xSemaphoreTake(_xMutex, pdMS_TO_TICKS(prior_waken));
}

void EasyMutex::GIVE() {
  xSemaphoreGive(_xMutex);
}

bool EasyMutex::TAKE_FROM_ISR(bool task_waken){
  if(_isr == false) {
    this->del();
    this->create(true);
  }
  bool _task_waken = task_waken;
  return xSemaphoreTakeFromISR(_xMutex, (BaseType_t*) &_task_waken);
}

void EasyMutex::GIVE_FROM_ISR(bool task_waken){
  if(_isr == false) {
    this->del();
    this->create(true);
  }

  bool _task_waken = task_waken;
  xSemaphoreGiveFromISR(_xMutex, (BaseType_t*) &_task_waken);
}
