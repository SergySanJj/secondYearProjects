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
        DateTimeDelta(DT::DateTime dt1, DT::DateTime dt2);

        ~DateTimeDelta() = default;

        void print() const;

        std::uint32_t Day() { return day; }

        std::uint32_t Month() { return month; }

        std::uint32_t Year() { return year; }

        std::uint32_t Hour() { return hour; }

        std::uint32_t Minute() { return minute; }

        std::uint32_t Seconds() { return seconds; }

    private:
        std::uint32_t day;
        std::uint32_t month;
        std::uint32_t year;

        std::uint32_t hour;
        std::uint32_t minute;
        std::uint32_t seconds;
    };

}

//#endif //GRAPHTREE_DATETIMEDELTA_H
