// █████████████████████████████████████████████████████
//
// ESP32/ESP8266 BlackBook by PowerTGS (2024)
//
// author : Tomasz Majcher 
// e-mail : powerTGS440@gmail.com
// phone  : +48 668 082121
//
// █████████████████████████████████████████████████████
//
// DS1302 RTC-Module
//
// source file      : source/module/rtcDS1302/source/rtcDS1302_v2/rtcDS1302_v2.ino
// device           : esp2866
// code platform    : ArduinoIDE
// 
// █████████████████████████████████████████████████████
// P I N   G P I O
// █████████████████████████████████████████████████████

// DS1302 CLK/SCLK ---> D7 (ESP8266)
// DS1302 DAT/IO   ---> D5 (ESP8266)
// DS1302 RST/CE   ---> D6 (ESP8266)
// DS1302 VCC 3.3v ---> 3.3V
// DS1302 GND      --> GND
//
// █████████████████████████████████████████████████████
// M E M O R Y   I N F O
// █████████████████████████████████████████████████████
//
//  variables and constants in RAM (global, static), used 28284 / 80192 bytes (35%)
//  Code in flash (default, ICACHE_FLASH_ATTR), used 238324 / 1048576 bytes (22%)
//
// █████████████████████████████████████████████████████
// M A K R O
// █████████████████████████████████████████████████████

#define CLK   D7                          // pin CLK/SCLK
#define RST   D6                          // pin RST/RESET
#define DAT   D5                          // pin DAT/IO

#define FPSTR(pstr_pointer) (reinterpret_cast<const __FlashStringHelper *>(pstr_pointer))
#define F(string_literal) (FPSTR(PSTR(string_literal)))

#define SERIAL_MONITOR    true            // SERIAL włączony
#define SERIAL_SPEED      115200          // prędkość SERIAL
#define LOOP_DELAY        5000            // opóźnienie pętli LOOP 

// █████████████████████████████████████████████████████
// B I B L I O T E K I
// █████████████████████████████████████████████████████
//
// library rtc by makuna : https://github.com/msparks/arduino-ds1302
//
// █████████████████████████████████████████████████████

#include <stdio.h>
#include <DS1302.h>

// █████████████████████████████████████████████████████
// O B I E K T Y
// █████████████████████████████████████████████████████

DS1302 rtc(RST, DAT, CLK);

// █████████████████████████████████████████████████████
// D E K L A R A C J A   F U N K C J I
// █████████████████████████████████████████████████████

void   SetManualDateTime();
String dayAsString(const Time::Day day);

#if SERIAL_MONITOR
    void printRctTime();
#endif

// █████████████████████████████████████████████████████
// S E T U P
// █████████████████████████████████████████████████████

void setup () 
{
    #if SERIAL_MONITOR
        Serial.begin(SERIAL_SPEED);        
    #endif

    //SetManualDateTime();// po uruchomieniu przy następnej kompilacji wykasować tą linię,
                          // chyba że za każdym razem wgrywania programu będziemy zmieniać
                          // aktualną datę i czas (linia 114 kodu)  
}

// █████████████████████████████████████████████████████
// L O O P
// █████████████████████████████████████████████████████

void loop () 
{
    #if SERIAL_MONITOR
        printRctTime();    
        delay(LOOP_DELAY);    
    #endif
}

// █████████████████████████████████████████████████████
// FUNKCJA MANUALNIE USTAWIA CZAS ZEGARA RTC
// █████████████████████████████████████████████████████

void   SetManualDateTime()
{
    rtc.writeProtect(false);
    rtc.halt(false);  

    // Format : rok, miesiąc, dzień, godzina, minuta, sekunda, dzień tygodnia (k+angielski)
    Time t(2024, 1, 22, 14, 54, 00, Time::kMonday);
    
    
    rtc.time(t);  

    #if SERIAL_MONITOR
        Serial.printf_P( PSTR ("\nManualne ustawienie zegara RTC !!!\n" ) );
    #endif
}

// █████████████████████████████████████████████████████
// FUNKCJA ZWRACA DZIEN TYGODNIA w JĘZYKU POLSKIM
// █████████████████████████████████████████████████████

String dayAsString(const Time::Day day)
{
    switch (day) 
    {
        case Time::kSunday:     return "Niedziela";     break;
        case Time::kMonday:     return "Poniedziałek";  break;
        case Time::kTuesday:    return "Wtorek";        break;
        case Time::kWednesday:  return "Środa";         break;
        case Time::kThursday:   return "Czwartek";      break;
        case Time::kFriday:     return "Piatek";        break;
        case Time::kSaturday:   return "Niedziela";     break;
        default             :   return "Dzień Świra";   break;
    }  
}
// █████████████████████████████████████████████████████
// FUNKCJA DRUKUJE DANE Z ZETARA RTC P R I N T   R T C   T I M E
// █████████████████████████████████████████████████████

#if SERIAL_MONITOR
void printRctTime()
{
  Time t = rtc.time();                    // pobierz do zmiennej t czas z zerara DS1302  
  const String day = dayAsString(t.day);  // pobierz do zmiennej day polski dzien tygodnia  
  char buf[50];                           // bufor do sformatowania wyświetlanego łańcucha
  
  snprintf(buf, sizeof(buf), "%s %04d-%02d-%02d %02d:%02d:%02d",
           day.c_str(),
           t.yr, t.mon, t.date,
           t.hr, t.min, t.sec);
  
  Serial.printf_P( PSTR ("\n%s"), buf);                    // wydrukuj zawartość bufora
}
#endif

// █████████████████████████████████████████████████████
// END OF FILE : rtcDS1302_v2.ino
// █████████████████████████████████████████████████████
