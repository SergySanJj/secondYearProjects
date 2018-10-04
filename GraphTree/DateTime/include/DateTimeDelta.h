//
// Module for difference in DateTime values.
// Created by sergei on 29.09.18.
//

#pragma once

#include "DateTime.h"

#include <cstdint>


namespace DT {
    class DateTime;

    class DateTimeDelta {
    public:
        DateTimeDelta(DT::DateTime dt1, DT::DateTime dt2);

        explicit DateTimeDelta(std::int64_t secondsDiff);

        ~DateTimeDelta() = default;

        void print() const;

        void println() const;

        std::int32_t Day() const { return day; }

        std::int32_t Month() const { return month; }

        std::int32_t Year() const { return year; }

        std::int32_t Hour() const { return hour; }

        std::int32_t Minute() const { return minute; }

        std::int32_t Seconds() const { return seconds; }

        std::int64_t TotalDays() const { return totalDays; }

        std::int64_t TotalWeeks() const { return (totalDays / 7); }

        std::int64_t TotalSeconds() const { return totalSeconds; }

        std::int64_t LastDaySeconds() const { return (hour * 3600 + minute * 60 + seconds); }

    private:
        std::int32_t day;
        std::int32_t month;
        std::int32_t year;

        std::int32_t hour;
        std::int32_t minute;
        std::int32_t seconds;

        std::int64_t totalDays;

        std::int64_t totalSeconds;

        /// Rata Die formula.
        std::int64_t daysIn(std::int32_t d, std::int32_t m, std::int32_t y);
    };

}
