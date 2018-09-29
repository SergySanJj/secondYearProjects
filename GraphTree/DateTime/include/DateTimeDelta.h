//
// Created by sergei on 29.09.18.
//

#pragma once

#include <cstdint>
#include "DateTime.h"


namespace DT {
    class DateTime;

    class DateTimeDelta {
    public:
        DateTimeDelta(DT::DateTime dt1, DT::DateTime dt2);

        explicit DateTimeDelta(std::uint32_t dd, std::uint32_t mm, std::uint32_t yy,
                               std::uint32_t h, std::uint32_t m, std::uint32_t s);

        ~DateTimeDelta() = default;

        void print() const;

        std::uint32_t Day() { return day; }

        std::uint32_t Month() { return month; }

        std::uint32_t Year() { return year; }

        std::uint32_t Hour() { return hour; }

        std::uint32_t Minute() { return minute; }

        std::uint32_t Seconds() { return seconds; }

        std::int32_t TotalDays() { return totalDays; }

        std::int32_t TotalWeeks() { return (totalDays / 7); }

        std::int64_t TotalSeconds() { return totalSeconds; }

        std::int32_t LastDaySeconds() { return (hour * 3600 + minute * 60 + seconds); }

    private:
        std::uint32_t day;
        std::uint32_t month;
        std::uint32_t year;

        std::uint32_t hour;
        std::uint32_t minute;
        std::uint32_t seconds;

        std::int32_t totalDays;

        std::int64_t totalSeconds;

        // Rata Die formula
        std::int32_t daysIn(int d, int m, int y);
    };

}
