# Lab 7-2: Managed Component from GitHub URL Demo

## คำอธิบาย
การทดลองนี้แสดงการใช้งาน managed component จาก GitHub Repository
ใช้ `Sensors` component จาก https://github.com/APPLICATIONS-OF-MICROCONTROLLERS/Lab7_Components

## ผลลัพธ์ที่คาดหวัง
- แสดงข้อความการเริ่มต้น sensor จาก GitHub component
- แสดงข้อมูล temperature และ humidity ทุก 4 วินาที
- แสดงสถานะการทำงานของ sensor
- แสดงแหล่งที่มาของ component (GitHub Repository)

## ความแตกต่างจาก Lab 7-1
- Lab 7-1: ใช้ local component (ในเครื่อง)
- Lab 7-2: ใช้ managed component จาก GitHub URL

## การใช้งาน
1. เข้าไปในโฟลเดอร์ lab7-2_Managed_url_Component
2. รันคำสั่ง `idf.py build` (จะดาวน์โหลด component จาก GitHub อัตโนมัติ)
3. ทดสอบด้วย QEMU

## สรุปคำสั่งที่ใช้ และผลลัพธ์ที่ได้

### คำสั่งที่ใช้ในการทดลอง:

1. **สร้างโครงสร้างโฟลเดอร์:**
   ```bash
   mkdir -p lab7-2_Managed_url_Component/main
   ```

2. **สร้างไฟล์ Project:**
   - `lab7-2_Managed_url_Component/CMakeLists.txt` - ไฟล์ build configuration หลัก
   - `lab7-2_Managed_url_Component/main/CMakeLists.txt` - ไฟล์ build configuration สำหรับ main
   - `lab7-2_Managed_url_Component/main/idf_component.yml` - ไฟล์ระบุ dependencies จาก GitHub
   - `lab7-2_Managed_url_Component/main/lab7-2.c` - ไฟล์ main application

3. **คำสั่ง Build และทดสอบ:**
   ```bash
   cd lab7-2_Managed_url_Component
   . $IDF_PATH/export.sh
   idf.py set-target esp32
   idf.py build
   idf.py qemu monitor
   ```

### ผลลัพธ์ที่ได้:

#### การดาวน์โหลด Managed Component:
-   ระบบดาวน์โหลด `lab7_components` จาก GitHub อัตโนมัติ
-   สร้างโฟลเดอร์ `managed_components/lab7_components/`
-   มีทั้ง Sensors และ Display components ใน managed component
-   สร้างไฟล์ `dependencies.lock` เพื่อเก็บข้อมูล dependencies

#### การ Build:
-   Build สำเร็จโดยไม่มี error
-   ระบบสามารถใช้ managed component จาก GitHub ได้
-   สร้างไฟล์ binary `lab7-2.bin` ขนาด 0x27dd0 bytes
-   ใช้พื้นที่ flash 84% (0xd8230 bytes ว่าง)

#### การทดสอบด้วย QEMU:
-   โปรแกรมเริ่มต้นทำงานได้ปกติ
-   แสดงข้อความ "🚀 Lab 7-2: Managed Component from GitHub URL Demo Started"
-   แสดงแหล่งที่มาของ component: "https://github.com/APPLICATIONS-OF-MICROCONTROLLERS/Lab7_Components"
-   เรียกใช้ฟังก์ชันจาก managed component (GitHub) ได้สำเร็จ:
  - `sensor_init()` - แสดงข้อความการเริ่มต้น sensor
  - `sensor_read_data()` - อ่านค่า temperature และ humidity ทุก 4 วินาที
  - `sensor_check_status()` - ตรวจสอบสถานะ sensor

#### ข้อมูลที่ได้จาก Sensor:
- 🌡️ **Temperature**: ค่าสุ่มจาก managed component
- 💧 **Humidity**: ค่าสุ่มจาก managed component
- 📦 **Source**: GitHub Repository

### สิ่งที่เรียนรู้:

1. **การใช้งาน Managed Component**: สามารถใช้ component จาก GitHub URL ได้โดยไม่ต้องสร้างเอง
2. **การจัดการ Dependencies**: ระบบ build จัดการ dependencies อัตโนมัติผ่าน `idf_component.yml`
3. **การดาวน์โหลดอัตโนมัติ**: ESP-IDF ดาวน์โหลด component จาก GitHub อัตโนมัติเมื่อ build
4. **การอัพเดท Component**: สามารถอัพเดท component ได้โดยการอัพเดท GitHub repository
5. **การทำงานเหมือน Local Component**: managed component ทำงานเหมือน local component ทุกประการ

### โครงสร้างไฟล์ที่สร้างขึ้น:
```
67030011/
└── lab7-2_Managed_url_Component/
    ├── CMakeLists.txt
    ├── main/
    │   ├── CMakeLists.txt
    │   ├── idf_component.yml
    │   └── lab7-2.c
    ├── managed_components/
    │   └── lab7_components/
    │       ├── CMakeLists.txt
    │       ├── Sensors/
    │       │   ├── CMakeLists.txt
    │       │   ├── sensor.h
    │       │   └── sensor.c
    │       └── Display/
    │           ├── CMakeLists.txt
    │           ├── display.h
    │           └── display.c
    ├── dependencies.lock
    ├── build/
    ├── .gitignore
    └── README.md
```

### ความแตกต่างจาก Lab 7-1:
- **Lab 7-1**: ใช้ local component (ในโฟลเดอร์ `components/`)
- **Lab 7-2**: ใช้ managed component จาก GitHub URL (ในโฟลเดอร์ `managed_components/`)
- **Lab 7-1**: ต้องสร้าง component เอง
- **Lab 7-2**: ดาวน์โหลด component จาก GitHub อัตโนมัติ

**สรุป**: การทดลองนี้สำเร็จในการใช้งาน managed component จาก GitHub URL โดยระบบสามารถดาวน์โหลดและใช้งาน component ได้อัตโนมัติ และทำงานได้เหมือนกับ local component ทุกประการ 