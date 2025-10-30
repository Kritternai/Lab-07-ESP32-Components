# Lab 7-1: Local Component Demo

## คำอธิบาย
การทดลองนี้แสดงการใช้งาน component ที่มีอยู่ในโฟลเดอร์ `components/Sensors/` ของ project

## สรุปคำสั่งที่ใช้ และผลลัพธ์ที่ได้

### คำสั่งที่ใช้ในการทดลอง:

1. **สร้างโครงสร้างโฟลเดอร์:**
   ```bash
   mkdir -p components/Sensors components/Display
   mkdir -p lab7-1_Managed_Local_Component/main
   ```

2. **สร้างไฟล์ Component:**
   - `components/Sensors/CMakeLists.txt` - ไฟล์ build configuration สำหรับ Sensors component
   - `components/Sensors/sensor.h` - Header file กำหนดฟังก์ชัน API
   - `components/Sensors/sensor.c` - Source code ของ Sensors component

3. **สร้างไฟล์ Project:**
   - `lab7-1_Managed_Local_Component/CMakeLists.txt` - ไฟล์ build configuration หลัก
   - `lab7-1_Managed_Local_Component/main/CMakeLists.txt` - ไฟล์ build configuration สำหรับ main
   - `lab7-1_Managed_Local_Component/main/lab7-1.c` - ไฟล์ main application

4. **คำสั่ง Build และทดสอบ:**
   ```bash
   cd lab7-1_Managed_Local_Component
   . $IDF_PATH/export.sh
   idf.py set-target esp32
   idf.py build
   idf.py qemu monitor
   ```

### ผลลัพธ์ที่ได้:

#### การ Build:
-   Build สำเร็จโดยไม่มี error
-   ระบบสามารถค้นหา Sensors component จากโฟลเดอร์ `../components` ได้
-   สร้างไฟล์ binary `lab7-1.bin` ขนาด 0x27c80 bytes
-   ใช้พื้นที่ flash 84% (0xd8380 bytes ว่าง)

#### การทดสอบด้วย QEMU:
-   โปรแกรมเริ่มต้นทำงานได้ปกติ
-   แสดงข้อความ "🚀 Lab 7-1: Local Component Demo Started"
-   เรียกใช้ฟังก์ชันจาก Sensors component ได้สำเร็จ:
  - `sensor_init()` - แสดงข้อความ "🔧 Sensor initialized from file: /project/components/Sensors/sensor.c, line: 13"
  - `sensor_read_data()` - อ่านค่า temperature และ humidity ทุก 3 วินาที
  - `sensor_check_status()` - ตรวจสอบสถานะ sensor

#### ข้อมูลที่ได้จาก Sensor:
- 🌡️ **Temperature**: 25.5°C - 35.4°C (ค่าสุ่ม)
- 💧 **Humidity**: 60.0% - 99.8% (ค่าสุ่ม)
-   **Status**: "All sensors operating normally"

### สิ่งที่เรียนรู้:

1. **การสร้าง Local Component**: สามารถสร้าง component ใหม่ในโฟลเดอร์ `components/` และใช้งานได้
2. **การเชื่อมต่อ Component**: ใช้ `EXTRA_COMPONENT_DIRS` ใน CMakeLists.txt เพื่อระบุตำแหน่ง component
3. **การ Build System**: ESP-IDF สามารถค้นหาและ build component อัตโนมัติ
4. **การทดสอบ**: ใช้ QEMU เพื่อทดสอบการทำงานของโปรแกรมโดยไม่ต้องใช้ hardware จริง
DME.md
```

**สรุป**: การทดลองนี้สำเร็จในการสร้างและใช้งาน Local Component โดยสามารถเรียกใช้ฟังก์ชันจาก Sensors component ได้ตามที่ออกแบบไว้ และแสดงผลลัพธ์ผ่าน QEMU emulator ได้อย่างถูกต้อง

---

## โจทย์ท้าทาย: สร้าง Display Component และใช้งานร่วมกับ Sensors Component

### คำสั่งที่ใช้ในการทำโจทย์ท้าทาย:

1. **สร้าง Display Component:**
   ```bash
   # สร้างไฟล์ Display component
   - components/Display/CMakeLists.txt
   - components/Display/display.h
   - components/Display/display.c
   ```

2. **อัปเดตไฟล์ main application:**
   - เพิ่ม `#include "display.h"`
   - เพิ่ม `#include "esp_random.h"`
   - แก้ไข `app_main()` ให้ใช้ทั้ง Sensors และ Display components

3. **คำสั่ง Build และทดสอบ:**
   ```bash
   cd lab7-1_Managed_Local_Component
   . $IDF_PATH/export.sh
   idf.py reconfigure  # เพื่อให้ระบบค้นพบ Display component
   idf.py build
   idf.py qemu monitor
   ```

### ผลลัพธ์ที่ได้จากโจทย์ท้าทาย:

#### การ Build:
-   Build สำเร็จโดยไม่มี error
-   ระบบสามารถค้นหาและใช้ทั้ง Sensors และ Display components ได้
-   สร้างไฟล์ binary `lab7-1.bin` ขนาด 0x283e0 bytes
-   ใช้พื้นที่ flash 84% (0xd7c20 bytes ว่าง)

#### การทดสอบด้วย QEMU:
-   โปรแกรมเริ่มต้นทำงานได้ปกติ
-   แสดงข้อความ "🚀 Lab 7-1 Challenge: Local Components Demo (Sensors + Display) Started"
-   เรียกใช้ฟังก์ชันจากทั้ง 2 components ได้สำเร็จ:
  - **Sensors Component**: `sensor_init()`, `sensor_read_data()`, `sensor_check_status()`
  - **Display Component**: `display_init()`, `display_clear()`, `display_show_sensor_data()`, `display_show_status()`

#### ข้อมูลที่ได้จาก Sensor และ Display:
- 🌡️ **Temperature**: 25.8°C - 34.9°C (ค่าสุ่ม)
- 💧 **Humidity**: 60.3% - 96.8% (ค่าสุ่ม)
- 🔥 **Heat Index**: 62.95 - 77.90 (คำนวณจาก temp + 0.5 * humidity)
-   **Status**: "  Comfortable" (เมื่อ Heat Index < 80)

#### การแสดงผลผ่าน Display Component:
```
┌─────────────────────────────────┐
│        SENSOR DATA DISPLAY      │
├─────────────────────────────────┤
│ 🌡️  Temperature:  33.60°C      │
│ 💧 Humidity:     80.10%       │
│ 🔥 Heat Index:   73.65        │
└─────────────────────────────────┘
┌─────────────────────────────────┐
│         SYSTEM STATUS           │
├─────────────────────────────────┤
│ Status:   Comfortable         │
└─────────────────────────────────┘
```

### สิ่งที่เรียนรู้จากโจทย์ท้าทาย:

1. **การสร้าง Multiple Components**: สามารถสร้างและใช้งานหลาย components พร้อมกันได้
2. **การเชื่อมต่อระหว่าง Components**: main application สามารถเรียกใช้ฟังก์ชันจากหลาย components ได้
3. **การแสดงผลข้อมูล**: Display component ช่วยในการแสดงผลข้อมูลในรูปแบบที่สวยงามและอ่านง่าย
4. **การคำนวณข้อมูล**: สามารถประมวลผลข้อมูลจาก Sensors และแสดงผลผ่าน Display ได้
5. **การจัดการ Dependencies**: ระบบ build สามารถจัดการ dependencies ระหว่าง components ได้อัตโนมัติ

**สรุปโจทย์ท้าทาย** การสร้าง Display component และใช้งานร่วมกับ Sensors component สำเร็จ โดยสามารถแสดงข้อมูล sensor ในรูปแบบตารางที่สวยงาม และคำนวณ Heat Index เพื่อแสดงสถานะความปลอดภัยได้ตามที่ออกแบบไว้ 