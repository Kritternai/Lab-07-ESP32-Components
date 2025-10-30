# Lab 7-3: Custom Components Demo (sensor + display)

## คำอธิบาย
การทดลองนี้แสดงการสร้าง ESP32 Components ใหม่ด้วยคำสั่ง `idf.py create-component`
สร้าง components 2 ตัว: `sensor` และ `display` แล้วใช้งานร่วมกัน

## ผลลัพธ์ที่คาดหวัง
- แสดงข้อความการเริ่มต้น sensor และ display components
- แสดงข้อมูล temperature และ humidity ทุก 6 วินาที
- แสดง Heat Index และสถานะความปลอดภัย
- แสดงข้อมูลในรูปแบบตารางที่สวยงาม

## ความแตกต่างจาก Lab 7-1 และ 7-2
- Lab 7-1: ใช้ local component (สร้างเอง)
- Lab 7-2: ใช้ managed component จาก GitHub URL
- Lab 7-3: สร้าง component ใหม่ด้วย `idf.py create-component`

## การใช้งาน
1. เข้าไปในโฟลเดอร์ lab7-3_esp32_Component
2. รันคำสั่ง `idf.py build`
3. ทดสอบด้วย QEMU

## สรุปคำสั่งที่ใช้ และผลลัพธ์ที่ได้

### คำสั่งที่ใช้ในการทดลอง:

1. **สร้างโครงสร้างโฟลเดอร์:**
   ```bash
   mkdir -p lab7-3_esp32_Component/main
   ```

2. **สร้าง Components ด้วย idf.py create-component:**
   ```bash
   cd lab7-3_esp32_Component
   mkdir -p components
   cd components
   idf.py create-component sensor
   idf.py create-component display
   ```

3. **แก้ไขไฟล์ Components:**
   - `components/sensor/CMakeLists.txt` - เพิ่ม dependencies "log" และ "driver"
   - `components/sensor/include/sensor.h` - กำหนด API functions
   - `components/sensor/sensor.c` - implement sensor functions พร้อม GPIO LED
   - `components/display/CMakeLists.txt` - เพิ่ม dependency "log"
   - `components/display/include/display.h` - กำหนด API functions
   - `components/display/display.c` - implement display functions

4. **สร้างไฟล์ Main Application:**
   - `main/CMakeLists.txt` - ไฟล์ build configuration สำหรับ main
   - `main/lab7-3.c` - ไฟล์ main application

5. **คำสั่ง Build และทดสอบ:**
   ```bash
   cd lab7-3_esp32_Component
   . $IDF_PATH/export.sh
   idf.py set-target esp32
   idf.py build
   idf.py qemu
   ```

### ผลลัพธ์ที่ได้:

#### การสร้าง Components:
- ✅ สร้าง sensor component ด้วย `idf.py create-component sensor`
- ✅ สร้าง display component ด้วย `idf.py create-component display`
- ✅ โครงสร้างไฟล์ถูกสร้างอัตโนมัติ:
  - `CMakeLists.txt` - ไฟล์ build configuration
  - `include/component.h` - ไฟล์ header
  - `component.c` - ไฟล์ source

#### การ Build:
- ✅ Build สำเร็จโดยไม่มี error
- ✅ ระบบสามารถค้นหาและใช้ custom components ได้
- ✅ สร้างไฟล์ binary `lab7-3.bin` ขนาด 0x299e0 bytes
- ✅ ใช้พื้นที่ flash 84% (0xd6620 bytes ว่าง)

#### การทดสอบด้วย QEMU:
- ✅ โปรแกรมเริ่มต้นทำงานได้ปกติ
- ✅ แสดงข้อความ "🚀 Lab 7-3: Custom Components Demo (sensor + display) Started"
- ✅ แสดงแหล่งที่มาของ components: "Using components created with idf.py create-component"
- ✅ เรียกใช้ฟังก์ชันจาก custom components ได้สำเร็จ:
  - **Sensor Component**: `sensor_init()`, `sensor_read_temperature()`, `sensor_read_humidity()`
  - **Display Component**: `display_init()`, `display_clear()`, `display_show_sensor_data()`, `display_show_status()`

#### ข้อมูลที่ได้จาก Sensor:
- 🌡️ **Temperature**: 21.10°C - 39.70°C (ค่าสุ่ม)
- 💧 **Humidity**: 40.30% - 78.90% (ค่าสุ่ม)
- 🔥 **Heat Index**: 45.25 - 77.85 (คำนวณจาก temp + 0.5 * humidity)
- ✅ **Status**: "✅ Comfortable" (เมื่อ Heat Index < 80)

#### การแสดงผลผ่าน Display Component:
```
┌─────────────────────────────────┐
│        SENSOR DATA DISPLAY      │
├─────────────────────────────────┤
│ 🌡️  Temperature:  35.70°C      │
│ 💧 Humidity:     78.90%       │
│ 🔥 Heat Index:   75.15        │
└─────────────────────────────────┘
┌─────────────────────────────────┐
│         SYSTEM STATUS           │
├─────────────────────────────────┤
│ Status: ✅ Comfortable         │
└─────────────────────────────────┘
```

### สิ่งที่เรียนรู้:

1. **การสร้าง Component ด้วย idf.py create-component**: สร้างโครงสร้างไฟล์อัตโนมัติ
2. **การจัดการ Dependencies**: ระบุ dependencies ใน CMakeLists.txt
3. **การใช้งาน GPIO**: ใช้ GPIO LED indicator ใน sensor component
4. **การทำงานร่วมกันของ Components**: sensor และ display ทำงานร่วมกันได้
5. **การ Build System**: ESP-IDF ค้นหา components ในโฟลเดอร์ components/ อัตโนมัติ
6. **การทดสอบ**: ใช้ QEMU เพื่อทดสอบการทำงานของโปรแกรม

### โครงสร้างไฟล์ที่สร้างขึ้น:
```
67030011/
└── lab7-3_esp32_Component/
    ├── CMakeLists.txt
    ├── components/
    │   ├── sensor/
    │   │   ├── CMakeLists.txt
    │   │   ├── include/
    │   │   │   └── sensor.h
    │   │   └── sensor.c
    │   └── display/
    │       ├── CMakeLists.txt
    │       ├── include/
    │       │   └── display.h
    │       └── display.c
    ├── main/
    │   ├── CMakeLists.txt
    │   └── lab7-3.c
    ├── build/
    ├── .gitignore
    └── README.md
```

### ความแตกต่างหลักระหว่าง Lab 7-1, 7-2 และ 7-3:
- **Lab 7-1**: ใช้ local component (สร้างเองในโฟลเดอร์ `components/`)
- **Lab 7-2**: ใช้ managed component (ดาวน์โหลดจาก GitHub ในโฟลเดอร์ `managed_components/`)
- **Lab 7-3**: สร้าง custom component ใหม่ด้วย `idf.py create-component` (ในโฟลเดอร์ `components/`)

### ข้อดีของการใช้ idf.py create-component:
1. **สร้างโครงสร้างไฟล์อัตโนมัติ**: ไม่ต้องสร้างไฟล์เอง
2. **มาตรฐาน**: โครงสร้างไฟล์เป็นมาตรฐานตาม ESP-IDF
3. **ความรวดเร็ว**: สร้าง component ใหม่ได้เร็ว
4. **ความถูกต้อง**: ลดข้อผิดพลาดในการสร้างไฟล์

**สรุป**: การทดลองนี้สำเร็จในการสร้าง custom components ด้วย `idf.py create-component` และใช้งานร่วมกันได้ โดยระบบสามารถ build และทดสอบได้สำเร็จ และแสดงผลลัพธ์ตามที่ออกแบบไว้ 