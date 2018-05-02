#include <main.h>
#include <CLeds.h>

const int DATA_PIN = 1;
const int CLK_PIN = 2;
const int CS_PIN = 3;

// CLeds* m_leds;
MD_MAX72XX* m_leds;

void setup()
{
    // m_leds = new CLeds();
    m_leds = new MD_MAX72XX(DATA_PIN, CLK_PIN, CS_PIN);
    m_leds->begin();
}

void loop()
{
    // m_leds->AllLedsOnOff(true);
}