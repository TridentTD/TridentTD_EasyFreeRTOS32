#include <TridentTD_EasyFreeRTOS32.h>
#include <WiFi.h>
#include <DFRobot_SHT20.h>
#include <Wire.h>

#define SSID            "----------"
#define PASSWORD        "----------"
#define SHT20_I2C_SDA   22
#define SHT20_I2C_SCL   25


// ประกาศ ตัวแปร task และ function สำหรับ task
EasyFreeRTOS32   WiFi_task, SHT20_task;


void setup(){  // setup() หลักตัวพิมพ์เล็ก
  Serial.begin(115200); Serial.println();
    
  WiFi_task.start(CORE0, 4096, [](void *param){
    VOID SETUP(){
      Serial.println("[WiFi] begin ...");
      WiFi.begin(SSID, PASSWORD);
    }
    VOID LOOP(){
      if( !WiFi.isConnected() ) {  
        while(!WiFi.isConnected() ) DELAY(400);
        Serial.print("[WiFi] WiFi Connected, IP : ");
        Serial.println(WiFi.localIP());
      }
      DELAY(10000);
    }
  });

  SHT20_task.start(CORE1, [](void*param){
    DFRobot_SHT20 sht20(&Wire1, SHT20_I2C_ADDR);
    bool sht20_is_inited= false;
    VOID SETUP(){
      Serial.println("[SHT20] initing..");
      Wire1.begin(SHT20_I2C_SDA, SHT20_I2C_SCL);
      Wire1.beginTransmission(SHT20_I2C_ADDR);
      sht20_is_inited = (0== Wire1.endTransmission());
      if(sht20_is_inited ) {
        Serial.println("[SHT20] init OK"); //SHT20_I2C_ADDR
      }else{
        Serial.println("[SHT20] init failed");
        SHT20_task.del();   // ทำลาย SHT20_task ทิ้งไปไม่ต้องทำงานอีก
      }
    }
    VOID LOOP(){
      DELAY(1000);
      if(sht20_is_inited ) {
        float sht_temp = sht20.readTemperature();
        float sht_hum  = sht20.readHumidity();  
    
        Serial.printf("[SHT20] Tempperature : %.2f °C\n", sht_temp);
        Serial.printf("[SHT20] Humidity     : %.2f %%\n", sht_hum);
      }
    }
  });  
}

void loop(){ DELAY(1); }  // loop() หลักตัวพิมพ์เล็ก ไม่จำเป็นต้องใช้แต่ให้มีไว้เสมอ

