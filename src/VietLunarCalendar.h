#ifndef VIETLUNARCALENDAR_H
#define VIETLUNARCALENDAR_H

#include <Arduino.h>

/**
 * VietLunarCalendar - Vietnamese Lunar Calendar Library for Arduino
 * * CORE LOGIC AND DATA SOURCE:
 * This library is based on the algorithms and encoded data 
 * from the JavaScript files created by Ho Ngoc Duc.
 * * Original Source URLs: 
 * - https://www.xemamlich.uhm.vn/JavaScript/amlich-hnd.js
 * - https://www.xemamlich.uhm.vn/JavaScript/vncal_js.html
 * * Original Author: Hồ Ngọc Đức (Ho Ngoc Duc)
 * Copyright 2004 Ho Ngoc Duc.
 */

/**
 * Structure to hold Lunar Date information
 */
struct LunarDate {
  int day;
  int month;
  int year;
  bool leap; // true if it's an intercalary (leap) month
  long jd;   // Julian Day Number (JDN)
};

class VietLunarCalendar {
private:
  // Encoded data for years 1900 - 2199 (TK20, TK21, TK22)
  static const uint32_t TK20[]; // 1900-1999
  static const uint32_t TK21[]; // 2000-2099
  static const uint32_t TK22[]; // 2100-2199
  
  // Arrays for Vietnamese Can (Heavenly Stems), Chi (Earthly Branches), and Tiet Khi (Solar Terms)
  // Note: These strings use UTF-8 encoding for Vietnamese characters.
  static const char* CAN[];
  static const char* CHI[];
  static const char* TIETKHI[];

  // Internal helper functions (Requires full implementation from original JS logic)
  uint32_t getYearCode(int yyyy);
  LunarDate findLunarDate(long jd, const LunarDate ly[], int size);
  void decodeLunarYear(int yy, uint32_t k, LunarDate ly[]);
  void getYearInfo(int yyyy, LunarDate ly[]);
  
  // Computes Julian Day Number (JDN) from Gregorian date
  long jdn(int dd, int mm, int yy);
  
  // Computes Sun Longitude (needed for Solar Terms)
  double sunLongitude(long jdn);
  int getSunLongitudeIndex(long dayNumber, double timeZone = 7.0);

public:
  VietLunarCalendar();
  
  // Retrieves the Lunar Date for a given Gregorian date
  LunarDate getLunarDate(int dd, int mm, int yyyy);

  // Gets the Heavenly Stem and Earthly Branch (Can Chi) of the Day
  String getDayCanChi(const LunarDate& lunar);

  // Gets the Can Chi of the Month
  String getMonthCanChi(const LunarDate& lunar);

  // Gets the Can Chi of the Year
  String getYearCanChi(int year);
  
  // Gets the Solar Term (Tiết Khí) corresponding to the Julian Day Number
  String getTietKhi(long jd);
};

#endif