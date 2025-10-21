#include "VietLunarCalendar.h"
#include <cmath> // Needed for floor, sin, fmod

/**
 * VietLunarCalendar - Vietnamese Lunar Calendar Library for Arduino
 * Ported from: https://www.xemamlich.uhm.vn/JavaScript/amlich-hnd.js
 * Original Author: Hồ Ngọc Đức (Ho Ngoc Duc)
 * Copyright 2004 Ho Ngoc Duc.
 */

// Encoded Lunar Year Data (TKxx - Data for 1900-2199)
const uint32_t VietLunarCalendar::TK20[] = { /* 1900-1999 */
  0x3c4bd8, 0x624ae0, 0x4ca570, 0x3854d5, 0x5cd260, 0x44d950, 0x315554, 0x5656a0, 0x409ad0, 0x2a55d2,
  0x504ae0, 0x3aa5b6, 0x60a4d0, 0x48d250, 0x33d255, 0x58b540, 0x42d6a0, 0x2cada2, 0x5295b0, 0x3f4977,
  0x644970, 0x4ca4b0, 0x36b4b5, 0x5c6a50, 0x466d50, 0x312b54, 0x562b60, 0x409570, 0x2c52f2, 0x504970,
  0x3a6566, 0x5ed4a0, 0x48ea50, 0x336a95, 0x585ad0, 0x442b60, 0x2f86e3, 0x5292e0, 0x3dc8d7, 0x62c950,
  0x4cd4a0, 0x35d8a6, 0x5ab550, 0x4656a0, 0x31a5b4, 0x5625d0, 0x4092d0, 0x2ad2b2, 0x50a950, 0x38b557,
  0x5e6ca0, 0x48b550, 0x355355, 0x584da0, 0x42a5b0, 0x2f4573, 0x5452b0, 0x3ca9a8, 0x60e950, 0x4c6aa0,
  0x36aea6, 0x5aab50, 0x464b60, 0x30aae4, 0x56a570, 0x405260, 0x28f263, 0x4ed940, 0x38db47, 0x5cd6a0,
  0x4896d0, 0x344dd5, 0x5a4ad0, 0x42a4d0, 0x2cd4b4, 0x52b250, 0x3cd558, 0x60b540, 0x4ab5a0, 0x3755a6,
  0x5c95b0, 0x4649b0, 0x30a974, 0x56a4b0, 0x40aa50, 0x29aa52, 0x4e6d20, 0x39ad47, 0x5eab60, 0x489370,
  0x344af5, 0x5a4970, 0x4464b0, 0x2c74a3, 0x50ea50, 0x3d6a58, 0x6256a0, 0x4aaad0, 0x3696d5, 0x5c92e0
};
const uint32_t VietLunarCalendar::TK21[] = { /* 2000-2099 */
  0x46c960, 0x2ed954, 0x54d4a0, 0x3eda50, 0x2a7552, 0x4e56a0, 0x38a7a7, 0x5ea5d0, 0x4a92b0, 0x32aab5,
  0x58a950, 0x42b4a0, 0x2cbaa4, 0x50ad50, 0x3c55d9, 0x624ba0, 0x4ca5b0, 0x375176, 0x5c5270, 0x466930,
  0x307934, 0x546aa0, 0x3ead50, 0x2a5b52, 0x504b60, 0x38a6e6, 0x5ea4e0, 0x48d260, 0x32ea65, 0x56d520,
  0x40daa0, 0x2d56a3, 0x5256d0, 0x3c4afb, 0x6249d0, 0x4ca4d0, 0x37d0b6, 0x5ab250, 0x44b520, 0x2edd25,
  0x54b5a0, 0x3e55d0, 0x2a55b2, 0x5049b0, 0x3aa577, 0x5ea4b0, 0x48aa50, 0x33b255, 0x586d20, 0x40ad60,
  0x2d4b63, 0x525370, 0x3e49e8, 0x60c970, 0x4c54b0, 0x3768a6, 0x5ada50, 0x445aa0, 0x2fa6a4, 0x54aad0,
  0x4052e0, 0x28d2e3, 0x4ec950, 0x38d557, 0x5ed4a0, 0x46d950, 0x325d55, 0x5856a0, 0x42a6d0, 0x2c55d4,
  0x5252b0, 0x3ca9b8, 0x62a930, 0x4ab490, 0x34b6a6, 0x5aad50, 0x4655a0, 0x2eab64, 0x54a570, 0x4052b0,
  0x2ab173, 0x4e6930, 0x386b37, 0x5e6aa0, 0x48ad50, 0x332ad5, 0x582b60, 0x42a570, 0x2e52e4, 0x50d160,
  0x3ae958, 0x60d520, 0x4ada90, 0x355aa6, 0x5a56d0, 0x462ae0, 0x30a9d4, 0x54a2d0, 0x3ed150, 0x28e952
};
const uint32_t VietLunarCalendar::TK22[] = { /* 2100-2199 */
  0x4eb520, 0x38d727, 0x5eada0, 0x4a55b0, 0x362db5, 0x5a45b0, 0x44a2b0, 0x2eb2b4, 0x54a950, 0x3cb559,
  0x626b20, 0x4cad50, 0x385766, 0x5c5370, 0x484570, 0x326574, 0x5852b0, 0x406950, 0x2a7953, 0x505aa0,
  0x3baaa7, 0x5ea6d0, 0x4a4ae0, 0x35a2e5, 0x5aa550, 0x42d2a0, 0x2de2a4, 0x52d550, 0x3e5abb, 0x6256a0,
  0x4c96d0, 0x3949b6, 0x5e4ab0, 0x46a8d0, 0x30d4b5, 0x56b290, 0x40b550, 0x2a6d52, 0x504da0, 0x3b9567,
  0x609570, 0x4a49b0, 0x34a975, 0x5a64b0, 0x446a90, 0x2cba94, 0x526b50, 0x3e2b60, 0x28ab61, 0x4c9570,
  0x384ae6, 0x5cd160, 0x46e4a0, 0x2eed25, 0x54da90, 0x405b50, 0x2c36d3, 0x502ae0, 0x3a93d7, 0x6092d0,
  0x4ac950, 0x32d556, 0x58b4a0, 0x42b690, 0x2e5d94, 0x5255b0, 0x3e25fa, 0x6425b0, 0x4e92b0, 0x36aab6,
  0x5c6950, 0x4674a0, 0x31b2a5, 0x54ad50, 0x4055a0, 0x2aab73, 0x522570, 0x3a5377, 0x6052b0, 0x4a6950,
  0x346d56, 0x585aa0, 0x42ab50, 0x2e56d4, 0x544ae0, 0x3ca570, 0x2864d2, 0x4cd260, 0x36eaa6, 0x5ad550,
  0x465aa0, 0x30ada5, 0x5695d0, 0x404ad0, 0x2aa9b3, 0x50a4d0, 0x3ad2b7, 0x5eb250, 0x48b540, 0x33d556
};

// Heavenly Stems (Can) - Uses UTF-8 for Vietnamese characters
const char* VietLunarCalendar::CAN[] = {"Giáp", "Ất", "Bính", "Đinh", "Mậu", "Kỷ", "Canh", "Tân", "Nhâm", "Quý"};
// Earthly Branches (Chi) - Uses UTF-8 for Vietnamese characters
const char* VietLunarCalendar::CHI[] = {"Tý", "Sửu", "Dần", "Mão", "Thìn", "Tỵ", "Ngọ", "Mùi", "Thân", "Dậu", "Tuất", "Hợi"};
// Solar Terms (Tiết Khí) - Uses UTF-8 for Vietnamese characters
const char* VietLunarCalendar::TIETKHI[] = {
    "Xuân phân", "Thanh minh", "Cốc vũ", "Lập hạ", "Tiểu mãn", "Mang chủng",
    "Hạ chí", "Tiểu thử", "Đại thử", "Lập thu", "Xử thử", "Bạch lộ",
    "Thu phân", "Hàn lộ", "Sương giáng", "Lập đông", "Tiểu tuyết", "Đại tuyết",
    "Đông chí", "Tiểu hàn", "Đại hàn", "Lập xuân", "Vũ Thủy", "Kinh trập"
};

VietLunarCalendar::VietLunarCalendar() {
  // Constructor
}

/**
 * Computes the Julian Day Number (JDN) for a Gregorian date (dd/mm/yy).
 */
long VietLunarCalendar::jdn(int dd, int mm, int yy) {
  int a = floor((14 - mm) / 12);
  long y = yy + 4800 - a;
  int m = mm + 12 * a - 3;
  long jd = dd + floor((153 * m + 2) / 5) + 365 * y + floor(y / 4) - floor(y / 100) + floor(y / 400) - 32045;
  return jd;
}

/**
 * Computes the Sun's longitude (in radians) at a given JDN (based on Jean Meeus's algorithms).
 */
double VietLunarCalendar::sunLongitude(long jdn) {
  double T = (jdn - 2451545.0) / 36525.0; // Time in Julian centuries from J2000.0
  double T2 = T * T;
  double dr = PI / 180.0; // degree to radian
  
  double M = 357.52910 + 35999.05030 * T - 0.0001559 * T2 - 0.00000048 * T2 * T; // Mean Anomaly (degree)
  double L0 = 280.46645 + 36000.76983 * T + 0.0003032 * T2; // Mean Longitude (degree)
  
  double DL = (1.914600 - 0.004817 * T - 0.000014 * T2) * sin(dr * M);
  DL += (0.019993 - 0.000101 * T) * sin(dr * 2 * M);
  DL += 0.000290 * sin(dr * 3 * M);
  
  double L = L0 + DL; // True Longitude (degree)
  
  L = L * dr; // Convert to radian
  L = fmod(L, 2 * PI); // Normalize to [0, 2*PI)
  if (L < 0) L += 2 * PI;
  return L;
}

/**
 * Computes the Solar Term index (0-23) for the start of the day.
 */
int VietLunarCalendar::getSunLongitudeIndex(long dayNumber, double timeZone) {
  double jdnTime = dayNumber - 0.5 - timeZone / 24.0;
  double longitude = sunLongitude(jdnTime);
  
  return floor(longitude / PI * 12);
}

// --- Can Chi and Tiet Khi Accessors ---

String VietLunarCalendar::getTietKhi(long jd) {
  int index = getSunLongitudeIndex(jd + 1, 7.0); 
  return String(TIETKHI[index]);
}

String VietLunarCalendar::getYearCanChi(int year) {
  String s = String(CAN[(year + 6) % 10]) + " " + String(CHI[(year + 8) % 12]);
  return s;
}

String VietLunarCalendar::getDayCanChi(const LunarDate& lunar) {
  if (lunar.jd == 0) return "Invalid Day";
  String s = String(CAN[(lunar.jd + 9) % 10]) + " " + String(CHI[(lunar.jd + 1) % 12]);
  return s;
}

String VietLunarCalendar::getMonthCanChi(const LunarDate& lunar) {
  String s = String(CAN[(lunar.year * 12 + lunar.month + 3) % 10]) + " " + String(CHI[(lunar.month + 1) % 12]);
  if (lunar.leap) {
    s += " (intercalary)";
  }
  return s;
}

/**
 * getLunarDate: Main function to retrieve the Lunar Date.
 * NOTE: The internal functions (getYearCode, decodeLunarYear, getYearInfo, findLunarDate) 
 * which utilize the TKxx data and bitwise operations must be fully implemented here 
 * to make the calendar fully functional across the 1900-2199 range.
 */
LunarDate VietLunarCalendar::getLunarDate(int dd, int mm, int yyyy) {
  long jd = jdn(dd, mm, yyyy);
  
  if (yyyy < 1900 || yyyy > 2199) {
    return {0, 0, 0, false, jd}; 
  }
  
  LunarDate ly1[14];
  // Placeholder call - must be fully implemented
  getYearInfo(yyyy, ly1); 
  
  // Check if the date belongs to the previous Lunar Year (before Tet)
  if (jd < ly1[0].jd) {
    LunarDate ly2[14];
    // Placeholder call - must be fully implemented
    getYearInfo(yyyy - 1, ly2); 
    return findLunarDate(jd, ly2, 14);
  }
  
  // Placeholder call - must be fully implemented
  return findLunarDate(jd, ly1, 14); 
}