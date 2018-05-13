#include "CLedMarquee.h"

#pragma region Public methods

void CLedMarquee::ShowMarquee(EMarqueeStyle style)
{
    switch(style)
    {
        case EMarqueeStyle::Test:
            Test();
            TestAdvanced();
            break;

        case EMarqueeStyle::Text:
            break;

        case EMarqueeStyle::Pacman:
            //TODO: check Pacman animation works
            static boolean bInit = true;    // initialise the animation
            int idx;                        // display index (column)
            int frame;                      // current animation frame
            int deltaFrame; 

            // Is it time to animate?
            if (millis() - m_prevTimeAnim < 75) //TODO: 75 ms animation
                return;
            m_prevTimeAnim = millis();			// starting point for next time
            m_leds->control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
            // Initialise
            if (bInit)
            {
                m_leds->clear();
                idx = -DATA_WIDTH;
                frame = 0;
                deltaFrame = 1;
                bInit = false;

                // Lay out the dots
                for (uint8_t i = 0; i < m_iNumDevices; i++)
                {
                    m_leds->setPoint(3, (i * COL_SIZE) + 3, true);
                    m_leds->setPoint(4, (i * COL_SIZE) + 3, true);
                    m_leds->setPoint(3, (i * COL_SIZE) + 4, true);
                    m_leds->setPoint(4, (i * COL_SIZE) + 4, true);
                }
            }

            // clear old graphic
            for (uint8_t i = 0; i < DATA_WIDTH; i++)
                m_leds->setColumn(idx - DATA_WIDTH + i, 0);
            // move reference column and draw new graphic
            idx++;
            for (uint8_t i = 0; i < DATA_WIDTH; i++)
                m_leds->setColumn(idx - DATA_WIDTH + i, pacman[frame][i]);

            // advance the animation frame
            frame += deltaFrame;
            if (frame == 0 || frame == MAX_FRAMES - 1)
                deltaFrame = -deltaFrame;

            // check if we are completed and set initialise for next time around
            bInit = (idx == m_leds->getColumnCount() + DATA_WIDTH);
            m_leds->control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);

            break;

        case EMarqueeStyle::BlinkEyes:
            break;

        case EMarqueeStyle::PushWheel:
            break;

        case EMarqueeStyle::Shift:
            break;

        case EMarqueeStyle::Two_Zones:
            break;

        default:
            break;
    }
}

#pragma endregion

#pragma region Private methods

void CLedMarquee::Test()
{
    int i, j;

    // Demonstrates the use of setPoint and show where the zero point is in the display
    m_leds->clear();
    for (i = 0; i < ROW_SIZE; i++)
    {
        m_leds->setPoint(i, i, true);
        m_leds->setPoint(0, i, true);
        m_leds->setPoint(i, 0, true);
        delay(DELAYTIME);
    }
    delay(DELAYTIME * 3);

    // // Demonstrate the use of drawHLine(). Draws from init to end of line coordinates with only one pixel on at the same time
    // m_leds->clear();
    // for (i = 0; i < m_leds->getColumnCount(); i++)
    // {
    //     m_leds->drawHLine(i, i, m_leds->getColumnCount() - ROW_SIZE + i, true);
    //     delay(2 * DELAYTIME);
    // }

    // // Demonstrate the use of drawVLine().
    // m_leds->clear();
    // for (i = 0; i < m_leds->getColumnCount(); i++)
    // {
    //     m_leds->drawVLine(i, 0, i % ROW_SIZE, true);
    //     delay(2 * DELAYTIME);
    // }

    // Demonstrates the use of setRow()
    m_leds->clear();
    for (i = 0; i < ROW_SIZE; i++)
    {
        m_leds->setRow(i, 0xff);
        delay(2 * DELAYTIME);
        m_leds->setRow(i, 0x00);
    }

    // nested rectangles spanning the entire display
    m_leds->clear();
    for (i = 0; i < 3; i++)     //repeat 3 times
    {
        for (j = 0; j < ROW_SIZE / 2; j++)
        {
            m_leds->drawRectangle(j, j, ROW_SIZE - 1 - j, m_leds->getColumnCount() - 1 - j, true);
            delay(2 * DELAYTIME);
        }
        for (j = 0; j < ROW_SIZE / 2; j++)
        {
            m_leds->drawRectangle(j, j, ROW_SIZE - 1 - j, m_leds->getColumnCount() - 1 - j, false);
            delay(2 * DELAYTIME);
        }
    }

    // Demonstrates the use of setColumn()
    m_leds->clear();
    for (i = 0; i < m_leds->getColumnCount(); i++)
    {
        m_leds->setColumn(i, 0xff);
        delay(DELAYTIME / m_iNumDevices);
        m_leds->setColumn(i, 0x00);
    }
}

void CLedMarquee::TestAdvanced()
{
    int i, j, n;
  
    // Combination of setRow() and setColumn() like crosses with user controlled
    m_leds->clear();
    m_leds->control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);

    // diagonally down the display R to L
    for (i = 0; i < ROW_SIZE; i++)
    {
        for (j = 0; j < m_iNumDevices; j++)
        {
            m_leds->setColumn(j, i, 0xff);
            m_leds->setRow(j, i, 0xff);
        }
        m_leds->update();           //update manually as control(MD_MAX72XX::UPDATE) is switched off
        delay(2 * DELAYTIME);
        for (j = 0; j < m_iNumDevices; j++)
        {
            m_leds->setColumn(j, i, 0x00);
            m_leds->setRow(j, i, 0x00);
        }
    }

    // moving up the display on the R
    for (i = ROW_SIZE - 1; i >= 0; i--)
    {
        for (j = 0; j < m_iNumDevices; j++)
        {
            m_leds->setColumn(j, i, 0xff);
            m_leds->setRow(j, ROW_SIZE - 1, 0xff);
        }
        m_leds->update();
        delay(2 * DELAYTIME);
        for (j = 0; j < m_iNumDevices; j++)
        {
            m_leds->setColumn(j, i, 0x00);
            m_leds->setRow(j, ROW_SIZE - 1, 0x00);
        }
    }

    // diagonally up the display L to R
    for (i = 0; i < ROW_SIZE; i++)
    {
        for (j = 0; j < m_iNumDevices; j++)
        {
            m_leds->setColumn(j, i, 0xff);
            m_leds->setRow(j, ROW_SIZE - 1 - i, 0xff);
        }
        m_leds->update();
        delay(3 * DELAYTIME);
        for (j = 0; j < m_iNumDevices; j++)
        {
            m_leds->setColumn(j, i, 0x00);
            m_leds->setRow(j, ROW_SIZE - 1 - i, 0x00);
        }
    }
    m_leds->control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);

    // Bullseye. Demonstrate the use of buffer based repeated patterns across all devices.
    m_leds->clear();
    m_leds->control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
    for (n = 0; n < 2; n++)
    {
        byte b = 0xff;
        i = 0;

        while (b != 0x00)
        {
            for (j = 0; j < m_iNumDevices + 1; j++)
            {
                m_leds->setRow(j, i, b);
                m_leds->setColumn(j, i, b);
                m_leds->setRow(j, ROW_SIZE - 1 - i, b);
                m_leds->setColumn(j, COL_SIZE - 1 - i, b);
            }
            m_leds->update();
            delay(2 * DELAYTIME);
            for (j = 0; j < m_iNumDevices + 1; j++)
            {
                m_leds->setRow(j, i, 0);
                m_leds->setColumn(j, i, 0);
                m_leds->setRow(j, ROW_SIZE - 1 - i, 0);
                m_leds->setColumn(j, COL_SIZE - 1 - i, 0);
            }

            bitClear(b, i);
            bitClear(b, 7 - i);
            i++;
        }

        while (b != 0xff)
        {
            for (j = 0; j < m_iNumDevices + 1; j++)
            {
                m_leds->setRow(j, i, b);
                m_leds->setColumn(j, i, b);
                m_leds->setRow(j, ROW_SIZE - 1 - i, b);
                m_leds->setColumn(j, COL_SIZE - 1 - i, b);
            }
            m_leds->update();
            delay(2 * DELAYTIME);
            for (j = 0; j < m_iNumDevices + 1; j++)
            {
                m_leds->setRow(j, i, 0);
                m_leds->setColumn(j, i, 0);
                m_leds->setRow(j, ROW_SIZE - 1 - i, 0);
                m_leds->setColumn(j, COL_SIZE - 1 - i, 0);
            }

            i--;
            bitSet(b, i);
            bitSet(b, 7-i);
        }
    }

    m_leds->control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);

    // Demonstrates animation of a diagonal stripe moving across the display with points plotted outside the display region ignored.
    // const uint16_t maxCol = m_iNumDevices * ROW_SIZE;
    // const uint8_t  stripeWidth = 10;
    // m_leds->clear();
    // for (i = 0; i < maxCol + ROW_SIZE + stripeWidth; i++)
    // {
    //     for (j = 0; j < ROW_SIZE; j++)
    //     {
    //         m_leds->setPoint(j, i - j, true);
    //         m_leds->setPoint(j, i - j - stripeWidth, false);
    //     }
    //     delay(DELAYTIME);
    // }

    // setPoint() used to draw a Spiral across the whole display
    int rmin = 0, rmax = ROW_SIZE - 1;
    int cmin = 0, cmax = (COL_SIZE * m_iNumDevices) - 1;

    m_leds->clear();
    while ((rmax > rmin) && (cmax > cmin))
    {
        // do row
        for (int i = cmin; i <= cmax; i++)
        {
            m_leds->setPoint(rmin, i, true);
            delay(DELAYTIME / m_iNumDevices);
        }
        rmin++;

        // do column
        for (i = rmin; i <= rmax; i++)
        {
            m_leds->setPoint(i, cmax, true);
            delay(DELAYTIME / m_iNumDevices);
        }
        cmax--;

        // do row
        for (i = cmax; i >= cmin; i--)
        {
            m_leds->setPoint(rmax, i, true);
            delay(DELAYTIME / m_iNumDevices);
        }
        rmax--;

        // do column
        for (i = rmax; i >= rmin; i--)
        {
            m_leds->setPoint(i, cmin, true);
            delay(DELAYTIME / m_iNumDevices);
        }
        cmin++;
    }

    // Animation of a bouncing ball
    i = 0;
    int r = 0, c = 2;
    int dR = 1, dC = 1;	// delta row and column

    m_leds->clear();
    while (i++ < 100)
    {
        m_leds->setPoint(r, c, false);
        r += dR;
        c += dC;
        m_leds->setPoint(r, c, true);
        delay(DELAYTIME/2);

        if ((r == 0) || (r == ROW_SIZE - 1))
            dR = -dR;
        if ((c == 0) || (c == m_leds->getColumnCount() - 1))
            dC = -dC;
    }

    // Demonstrates control of display intensity (brightness) across the full range.
    // m_leds->clear();
    // j = 0;
    // for (i = 0; i <= MAX_INTENSITY / 2; i++)        // NOTE: seems 1088AS don't support MAX_INTENSITY and can provoke strange behavior
    // {
    //     m_leds->control(MD_MAX72XX::INTENSITY, i);  // Grow and get brighter
    //     if (i % 2 == 0)
    //         m_leds->setRow(j++, 0xff);
    //     delay(DELAYTIME * 2);
    // }
    // m_leds->control(MD_MAX72XX::INTENSITY, MAX_INTENSITY / 2);
    // delay(DELAYTIME);

    //Blinks the display on and off.
    i = 3;
    m_leds->clear();
    while (i > 0)
    {
        m_leds->control(MD_MAX72XX::TEST, MD_MAX72XX::ON);
        delay(DELAYTIME * i);
        m_leds->control(MD_MAX72XX::TEST, MD_MAX72XX::OFF);
        delay(DELAYTIME * i);
        i--;
    }
}

#pragma endregion