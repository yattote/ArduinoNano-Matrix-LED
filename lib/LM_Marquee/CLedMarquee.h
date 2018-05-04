#include <MD_MAX72xx.h>
#include "CCommon.h"

const int IN_BTN = 3;

enum EMarqueeStyle { Text, Pacman, BlinkEyes, PushWheel };

class CLedMarquee
{
public:
    // Constructors
    CLedMarquee(int csPin)
    {
        // initialize variables
        pinMode(IN_BTN, INPUT_PULLUP);
        m_leds = new MD_MAX72XX(csPin);
        m_leds->begin();
    };

    // Public methods
    void ShowMarquee(EMarqueeStyle style);

    // Data accessors
	int GetDevices()
	{
		return 0;
	};
private:
    // Fields
    MD_MAX72XX* m_leds;

    // Private methods
};