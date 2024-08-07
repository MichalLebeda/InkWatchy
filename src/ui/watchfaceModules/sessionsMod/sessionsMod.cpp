#include "sessionsMod.h"
#include <esp32/rom/crc.h>
#include <time.h>

#if SESSIONS_MODULE

void wfSessionsCheckShow(bool *showBool, bool *redrawBool)
{
    *showBool = true;
    *redrawBool = true;
}

void drawSession(const char country[], int rowIdx){
    const int16_t MODULE_RECT_END_X = MODULE_RECT_X + MODULE_W;

    const int16_t FONT_CHAR_HEIGHT = 7;
    const int16_t ROW_HEIGHT = 9;

    const int16_t COUNTRY_LABEL_X = MODULE_RECT_X;
    const int16_t COUNTRY_LABEL_WIDTH = 14;

    const int16_t CLOCK_WIDTH = 14;
    const int16_t CLOCK_LEFT_PAD = 2;
    const int16_t CLOCK_X = COUNTRY_LABEL_X + COUNTRY_LABEL_WIDTH + CLOCK_LEFT_PAD;
    const int16_t CLOCK_RIGHT_X = CLOCK_X + CLOCK_WIDTH;

    const int16_t BAR_X = CLOCK_RIGHT_X + 2;
    const int16_t BAR_HEIGHT = 7;
    const int16_t BAR_N_STEPS = 24;
    const int16_t BAR_AVAILABLE_WIDTH = MODULE_RECT_END_X - BAR_X;
    const int16_t BAR_STEP = BAR_AVAILABLE_WIDTH / BAR_N_STEPS;
    const int16_t BAR_WIDTH = BAR_N_STEPS * BAR_STEP;
    const int16_t BAR_END_X = BAR_X + BAR_WIDTH;

    const int16_t PROGRESS_OVERFLOW = 4;

    auto timeStr = getHour(timeRTCUTC0);
    auto y = MODULE_RECT_Y + rowIdx * ROW_HEIGHT + FONT_CHAR_HEIGHT + 2;

    display.setCursor(COUNTRY_LABEL_X, y); 
    display.print(country);

    display.setCursor(CLOCK_X, y); 
    display.print(timeStr);

    for (int16_t i = 0; i < BAR_N_STEPS + 1; i++){
        int16_t x = BAR_X + i * BAR_STEP;
        display.drawLine(x, y - BAR_HEIGHT, x, y, GxEPD_BLACK);
        if (i >=7 && i<=17){
            display.fillRect(
                x + 1,
                y - BAR_HEIGHT + 1, 
                BAR_STEP - 1,
                BAR_HEIGHT - 1, 
                GxEPD_BLACK
            );
        }
    }

    display.drawLine(BAR_X, y, BAR_END_X, y, GxEPD_BLACK);
    display.drawLine(BAR_X, y - BAR_HEIGHT, BAR_END_X, y - BAR_HEIGHT, GxEPD_BLACK);

    int percentOfDayTmp = calculatePercentageOfDay(wFTime.Hour, wFTime.Minute);
    // if (percentOfDay != percentOfDayTmp){
        int progress = constrain(percentOfDay, 0, 100);
        int progressX = map(progress, 0, 100, BAR_X, BAR_END_X);
        display.drawLine(progressX, MODULE_RECT_Y-PROGRESS_OVERFLOW, progressX, MODULE_RECT_Y + MODULE_H+PROGRESS_OVERFLOW, GxEPD_BLACK);
    // }
}

void redrawModuleSessions()
{
    setFont(getFont("dogicapixel4"));
    setTextSize(1);

    drawSession("NZ", 0);
    drawSession("JP", 1);
    drawSession("UK", 2);
    drawSession("US", 3);
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