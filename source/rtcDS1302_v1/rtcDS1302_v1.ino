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
// source file      : source/module/rtcDS1302/source/rtcDS1302_v1/rtcDS1302_v1.ino
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
//
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
// library rtc by makuna : https://www.arduino.cc/reference/en/libraries/rtc-by-makuna/
//
// █████████████████████████████████████████████████████

#include <RtcDS1302.h>

// █████████████████████████████████████████████████████
// O B I E K T Y
// █████████████████████████████████████████████████████

ThreeWire myWire(DAT,CLK,RST); // IO, SCLK, CE
RtcDS1302 <ThreeWire> Rtc(myWire);

// █████████████████████████████████████████████████████
// S E T U P
// █████████████████████████████████████████████████████

void setup () 
{
    #if SERIAL_MONITOR
        Serial.begin(57600);
        Serial.printf_P( PSTR ("\nData i czas kompilacji: ") );
        Serial.print(__DATE__);
        Serial.print(__TIME__);
    #endif
   
    Rtc.Begin();        // inicjacja obiektu Rtc

    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);   // ustawiamy datę i czas kompilacji
    Rtc.SetDateTime(compiled);                                // ustawiamy datę i czas 
    
}

// █████████████████████████████████████████████████████
// L O O P
// █████████████████████████████████████████████████████

void loop () 
{
    RtcDateTime now = Rtc.GetDateTime();
    printRctTime(now);
    delay(LOOP_DELAY);    
}

// █████████████████████████████████████████████████████
// P R I N T   R T C   T I M E
// █████████████████████████████████████████████████████

void printRctTime(const RtcDateTime& dt)
{
    char datestring[26];

    snprintf_P                            // formatowanie łańcucha char do wyświetlenia
    (
        datestring, 
        countof(datestring),
        PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
        dt.Month(),
        dt.Day(),
        dt.Year(),
        dt.Hour(),
        dt.Minute(),
        dt.Second() 
    );
            
    Serial.printf_P( PSTR ("\n %s"), datestring);
}

// █████████████████████████████████████████████████████
// END OF FILE : rtcDS1302.ino
// █████████████████████████████████████████████████████
