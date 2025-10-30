#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_random.h"
#include "sensor.h"
#include "display.h"

static const char *TAG = "LAB7-1-CHALLENGE";

void app_main(void)
{
    ESP_LOGI(TAG, "🚀 Lab 7-1 Challenge: Local Components Demo (Sensors + Display) Started");
    ESP_LOGI(TAG, "📦 Using both Sensors and Display components from local folder");
    
    // เริ่มต้น components
    sensor_init();
    display_init();
    
    int reading_count = 0;
    
    while(1) {
        reading_count++;
        ESP_LOGI(TAG, "📋 Reading #%d", reading_count);
        
        display_clear();
        
        // อ่านข้อมูลจาก sensor component
        sensor_read_data();
        sensor_check_status();
        
        // จำลองการคำนวณ Heat Index จากข้อมูล sensor
        float temp = 25.5 + (float)(esp_random() % 100) / 10.0f;
        float hum = 60.0 + (float)(esp_random() % 400) / 10.0f;
        float heat_index = temp + 0.5 * hum;
        
        // แสดงข้อมูลผ่าน display component
        display_show_sensor_data(temp, hum, heat_index);
        
        // แสดงสถานะตามค่า Heat Index
        if (heat_index < 80) {
            display_show_status("✅ Comfortable");
        } else if (heat_index < 90) {
            display_show_status("⚠️  Caution");
        } else {
            display_show_status("🚨 Warning");
        }
        
        ESP_LOGI(TAG, "==========================================");
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
} 