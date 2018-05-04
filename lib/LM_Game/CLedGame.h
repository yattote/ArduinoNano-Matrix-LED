#include <MD_MAX72xx.h>
#include <CJoystick.h>

enum EGame { Tetris, Snake };

class CLedGame
{
public:
    // Constructors
    CLedGame(int csPin, int iPinAxisX, int iPinAxisY, int iPinButton)
    {
        // initialize variables
        m_leds = new MD_MAX72XX(csPin);
        m_leds->begin();

        m_Joystick = new CJoystick(iPinAxisX, iPinAxisY, iPinButton);
    };

    // Public methods
    void StartGame(EGame game);

    // Data accessors
	int GetDimensions()
	{
		return 0;
	};
private:
    // Fields
    MD_MAX72XX* m_leds;
    CJoystick* m_Joystick;

    // Private methods
};