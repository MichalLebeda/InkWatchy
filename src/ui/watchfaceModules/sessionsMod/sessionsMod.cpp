#include "sessionsMod.h"
#include <esp32/rom/crc.h>

#if SESSIONS_MODULE

void wfSessionsCheckShow(bool *showBool, bool *redrawBool)
{
    *showBool = true;
    *redrawBool = true;
}

void redrawModuleSessions()
{
    setFont(getFont("dogicapixel4"));
    setTextSize(1);
    display.setCursor(MODULE_RECT_X + MODULE_W - 60, MODULE_RECT_Y + 7 - 1); // font is 7 pixels
    auto timeStr = getHourMinute(wFTime);
    display.print("Test:" + timeStr);
}

void wfSessionsRequestShow(buttonState button, bool *showBool)
{
    redrawModuleSessions();
}

// Lambda doesn't work here
RTC_DATA_ATTR wfModule wfSessions = {
    true,
    wfSessionsCheckShow,
    wfSessionsRequestShow,
};

#endif