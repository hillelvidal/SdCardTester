/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/hillelvidal/Library/Coding/ScanIn_Photons/SdCardTester/src/SdCardTester.ino"
#include "SdFat.h"
#include <SPI.h>

void on();
void off();
void setup();
bool check();
void loop();
void indicate(bool ok);
#line 4 "/Users/hillelvidal/Library/Coding/ScanIn_Photons/SdCardTester/src/SdCardTester.ino"
SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(SEMI_AUTOMATIC);

#define SPI_SPEED SD_SCK_MHZ(4)

SdFat sd;
SdFile file;
bool IsOk;
int iSD_CARD_RELAY_PIN = WKP;

void on()
{
  Serial.println("SD Relay ON");
  digitalWrite(iSD_CARD_RELAY_PIN, HIGH);
}

void off()
{
  Serial.println("SD Relay OFF");
  digitalWrite(iSD_CARD_RELAY_PIN, LOW);
}

// setup() runs once, when the device is first turned on.
void setup()
{
  pinMode(iSD_CARD_RELAY_PIN, OUTPUT);
  RGB.control(true);
}

bool check()
{
  IsOk = sd.begin(A2, SPI_SPEED);
  if (!IsOk)
  {
    Serial.printlnf("SD Card ERROR: Begin Failed");
    return false;
  }

  if (!file.open("check.txt", O_CREAT | O_WRITE | O_APPEND))
  {
    Serial.println("Sd Card ERROR: Error openning file");
    return false;
  }

  Serial.println("Log file opened!");

  // close file
  if (file.close())
    Serial.println("Log file closed.");
  else
  {
    Serial.println("Sd Card ERROR: file failed to be closed.");
    return false;
  }

  Serial.printlnf("SD Card Is OK.");
  return IsOk;
}

// loop() runs over and over again, as quickly as it can execute.
void loop()
{
  on();
  indicate(check());
  off();

  delay(500);
}

void indicate(bool ok)
{
  if (ok)
    RGB.color(0, 255, 0);
  else
    RGB.color(255, 0, 0);
}