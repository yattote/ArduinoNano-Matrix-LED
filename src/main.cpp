#include <main.h>

#ifdef GAME
#include <CLedGame.h>
#elif MARQUEE
#include <CLedMarquee.h>
#endif

const int DATA_PIN = 11;    //MOSI [Master Out Slave In]: 11
const int CLK_PIN = 13;     //SCK  [Master Clock]:        13
const int CS_PIN = 10;      //SS   [Slave Select]:        10
const int IN_AXIS_X = 17;   //A3
const int IN_AXIS_Y = 18;   //A4
const int IN_BUTTON = 2;

#ifdef GAME
CLedGame* m_leds;
#elif MARQUEE
CLedMarquee* m_leds;
#endif

void setup()
{
    #ifdef GAME
    m_leds = new CLedGame(CS_PIN, IN_AXIS_X, IN_AXIS_Y, IN_BUTTON);
    #elif MARQUEE
    m_leds = new CLedMarquee(CS_PIN);
    #endif
}

void loop()
{
    #ifdef GAME
    m_leds->StartGame(Snake);
    #elif MARQUEE
    m_leds->ShowMarquee(Pacman);
    delay(500);
    m_leds->ShowMarquee(Text);
    delay(500);
    #endif
}