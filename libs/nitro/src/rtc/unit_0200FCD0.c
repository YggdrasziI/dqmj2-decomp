/* NitroSDK; built from khdays-decomp (CC0) per-function sources of the functions
 * found byte-identical (tools/lib_unit_gen.py). File bounds are a hypothesis. */
#pragma force_active on

#include "nitro/types.h"

#include "nitro/os.h"

#include "nitro/rtc.h"

RTCWeek RTC_GetDayOfWeek(RTCDate *date)
{
    int cent;
    int year = (int)(2000 + date->year);
    int month = (int)date->month;
    int day = (int)date->day;

    month -= 2;

    if (month < 1) {
        month += 12;
        --year;
    }

    cent = year / 100;
    year %= 100;
    return (RTCWeek)(((26 * month - 2) / 10 + day + year + year / 4 + cent / 4 + 5 * cent) % 7);
}
