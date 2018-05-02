#include <MD_MAX72xx.h>

class CLeds
{
public:
    // Constructors
    CLeds()
    {
        // initialize variables

        // process variables
    };

    // Public methods
    void AllLedsOnOff(bool bLedsOn);
    void SetLedOnOff(int x, int y, int z, bool bLedOn);

    // Data accessors
	int GetDimensions()
	{
		return m_iDimensions;
	};
private:
    // Fields
    int m_iDimensions;

    // Private methods
};