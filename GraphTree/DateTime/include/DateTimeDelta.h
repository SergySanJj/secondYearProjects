//
// Created by sergei on 29.09.18.
//

//#ifndef GRAPHTREE_DATETIMEDELTA_H
//#define GRAPHTREE_DATETIMEDELTA_H

#pragma once

#include <cstdint>
#include "DateTime.h"


namespace DT {
    class DateTime;

    class DateTimeDelta {
    public:
        DateTimeDelta(const DT::DateTime &dt1, const DT::DateTime &dt2);

        ~DateTimeDelta()= default;

        std::uint32_t getTotalSeconds();
        std::uint32_t getTotalDays();
        std::uint32_t getTotalYears()

        std::uint16_t Day() { return day; }

        std::uint16_t Month() { return month; }

        std::uint16_t Year() { return year; }

        std::uint16_t Hour() { return hour; }

        std::uint16_t Minute() { return minute; }

        std::uint16_t Seconds() { return seconds; }

    private:
        std::uint16_t day;
        std::uint16_t month;
        std::uint16_t year;

        std::uint16_t hour;
        std::uint16_t minute;
        std::uint16_t seconds;
    };



}

//#endif //GRAPHTREE_DATETIMEDELTA_H
