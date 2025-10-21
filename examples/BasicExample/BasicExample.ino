#include "VietLunarCalendar.h"

// Instantiate the calendar object
VietLunarCalendar lunarCal;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("--- Vietnamese Lunar Calendar Program ---");
  Serial.println();
}

void loop() {
  // Example 1: Regular day (October 21, 2025)
  printDateInfo(21, 10, 2025);
  
  // Example 2: Gregorian New Year (January 1, 2026)
  printDateInfo(1, 1, 2026);
  
  // Example 3: Tết Nguyên Đán (Lunar New Year Day) (February 5, 2027)
  printDateInfo(5, 2, 2027);

  // Example 4: Intercalary month (April 19, 2001 - Intercalary 2nd Lunar Month)
  printDateInfo(19, 4, 2001);

  Serial.println("\n--- End of Examples. Reset to run again ---");
  while(true); // Halt after running examples
}

/**
 * Helper function to print date details to the Serial Monitor.
 */
void printDateInfo(int dd, int mm, int yyyy) {
  Serial.print("Gregorian Date: ");
  Serial.print(dd); Serial.print("/"); Serial.print(mm); Serial.print("/"); Serial.println(yyyy);

  LunarDate lunar = lunarCal.getLunarDate(dd, mm, yyyy);

  if (lunar.day == 0) {
    Serial.println("-> Calculation Error (Out of 1900-2199 range or logic error).");
    return;
  }
  
  Serial.print("-> Lunar Date: ");
  Serial.print(lunar.day); Serial.print("/");
  Serial.print(lunar.month); Serial.print("/");
  Serial.print(lunar.year);
  if (lunar.leap) {
    Serial.println(" (Intercalary Month)");
  } else {
    Serial.println();
  }
  
  Serial.print("   Year Can Chi: ");
  Serial.println(lunarCal.getYearCanChi(lunar.year));
  
  Serial.print("   Month Can Chi: ");
  Serial.println(lunarCal.getMonthCanChi(lunar));
  
  Serial.print("   Day Can Chi: ");
  Serial.println(lunarCal.getDayCanChi(lunar));
  
  Serial.print("   Solar Term (Tiết Khí): ");
  Serial.println(lunarCal.getTietKhi(lunar.jd));
  
  Serial.println("-------------------------------------");
}