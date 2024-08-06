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
    auto timeStr = getHourMinute(wFTime);
    auto rtcTimeStr = getHourMinute(timeRTC);
    display.setCursor(MODULE_RECT_X, MODULE_RECT_Y + 0 * 9 + 7 - 1); // font is 7 pixels
    display.print("NZ:" + timeStr);
    display.setCursor(MODULE_RECT_X, MODULE_RECT_Y + 1 * 9 + 7 - 1); // font is 7 pixels
    display.print("JP:" + timeStr);
    display.setCursor(MODULE_RECT_X, MODULE_RECT_Y + 2 * 9 + 7 - 1); // font is 7 pixels
    display.print("UK:" + timeStr);
    display.setCursor(MODULE_RECT_X, MODULE_RECT_Y + 3 * 9 + 7 - 1); // font is 7 pixels
    display.print("US:" + rtcTimeStr);
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