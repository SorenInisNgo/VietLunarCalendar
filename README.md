# VietLunarCalendar: Vietnamese Lunar Calendar for Arduino

The **VietLunarCalendar** library is an Arduino implementation of the Vietnamese Lunar Calendar (*Âm lịch Việt Nam*). It converts a standard Gregorian date (DD/MM/YYYY) into its corresponding Lunar Date, including the Can Chi (Heavenly Stem and Earthly Branch) and Solar Terms (*Tiết Khí*).

***

## ⚠️ Source and Attribution

This library is a direct port of the complex astronomical and date calculation logic, including the encoded lunar cycle data (`TKxx` arrays), from the original JavaScript files created by **Hồ Ngọc Đức (Ho Ngoc Duc)**.

* **Original Author:** Hồ Ngọc Đức (Ho Ngoc Duc)
* **Original Source URLs:**
    * `amlich-hnd.js`
    * `vncal_js.html`
    * **Main Website:** `https://www.xemamlich.uhm.vn/JavaScript/`
* **Copyright:** © 2004 Ho Ngoc Duc.

***

## Features

The library provides the following functionality:

* **Date Conversion:** Convert a **Gregorian Date** to the corresponding **Vietnamese Lunar Date** (Day/Month/Year).
* **Year's Can Chi:** Identify the Heavenly Stem and Earthly Branch for the Lunar Year.
* **Month's Can Chi:** Identify the Can Chi of the month (and detect **Intercalary/Leap** months).
* **Day's Can Chi:** Calculate the Can Chi of the specific day using the Julian Day Number (JDN).
* **Solar Terms:** Calculate the current **Solar Term** (*Tiết Khí*).

***

## Installation

This library uses the standard Arduino library folder structure.

1.  **Download:** Copy the `VietLunarCalendar.h` and `VietLunarCalendar.cpp` files.
2.  **Create Folder:** Navigate to your Arduino libraries directory (usually `~/Documents/Arduino/libraries/`).
3.  **Organize:** Create a new folder named `VietLunarCalendar` and place the two files inside a subfolder named `src`.
4.  **Restart:** Restart the Arduino IDE.

The final structure should look like this:

.../libraries/VietLunarCalendar/
├── README.md
├── src/
│   ├── VietLunarCalendar.h
│   └── VietLunarCalendar.cpp
└── examples/
    └── BasicExample/
        └── BasicExample.ino

***

## Limitations & Notes

1.  **Supported Range:** The embedded encoded data (`TKxx` arrays) only supports reliable lunar cycle calculation for the years **1900 - 2199**.
2.  **UTF-8 Encoding:** The output strings for Can, Chi, and Solar Terms contain Vietnamese characters (e.g., "Ất", "Tỵ", "Đại hàn"). You **must** configure your Arduino Serial Monitor to use **UTF-8 encoding** to display these characters correctly.
3.  **TimeZone:** All calculations assume the **Vietnamese Time Zone (UTC+7)**, consistent with the original source files.