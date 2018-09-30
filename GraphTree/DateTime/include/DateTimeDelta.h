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

        explicit DateTimeDelta(std::int64_t dd, std::int64_t mm, std::int64_t yy,
                               std::int64_t h, std::int64_t m, std::int64_t s);

        ~DateTimeDelta() = default;

        void print() const;

        std::int64_t Day() const { return day; }

        std::int64_t Month() const { return month; }

        std::int64_t Year() const { return year; }

        std::int64_t Hour() const { return hour; }

        std::int64_t Minute() const { return minute; }

        std::int64_t Seconds() const { return seconds; }

        std::int64_t TotalDays() const { return totalDays; }

        std::int64_t TotalWeeks() const { return (totalDays / 7); }

        std::int64_t TotalSeconds() const { return totalSeconds; }

        std::int64_t LastDaySeconds() const { return (hour * 3600 + minute * 60 + seconds); }

    private:
        std::int64_t day;
        std::int64_t month;
        std::int64_t year;

        std::int64_t hour;
        std::int64_t minute;
        std::int64_t seconds;

        std::int64_t totalDays;

        std::int64_t totalSeconds;

        // Rata Die formula
        std::int64_t daysIn(std::int64_t d, std::int64_t m, std::int64_t y);
    };

}
