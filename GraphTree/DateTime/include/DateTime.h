//
// DT module
// Created by sju on 24.09.18.
//

//#ifndef GRAPHTREE_DATETIME_H
//#define GRAPHTREE_DATETIME_H


#pragma once

#include <iostream>
#include <cstdint>
#include <tuple>
#include <string>

#include "DateTimeDelta.h"

namespace DT {
    class DateTimeDelta;

    // Return true if date is valid, return false otherwise.
    bool validateDate(std::uint16_t d, std::uint16_t m, std::uint16_t y);

    // Returns an integer that represents week day (Mon=1, Tue=2...) if date is invalid return -1.
    std::int32_t getDayOfWeek(std::uint16_t d, std::uint16_t m, std::uint16_t y);

    // Returns day name from integer 1..7
    std::string toDayOfWeek(std::int32_t day);

    // Return true if year is a leap year, false otherwise.
    bool isLeapYear(std::uint32_t year);

    class Date {
    public:
        explicit Date(std::uint16_t d, std::uint16_t m, std::uint16_t y);

        ~Date() = default;

        Date &operator=(const Date &rsv);

        bool const operator==(const Date &rsv);

        bool const operator!=(const Date &rsv);

        bool const operator<(const Date &rsv);

        bool const operator>(const Date &rsv);

        std::uint16_t Month() const { return month; }

        std::uint16_t Day() const { return day; }

        std::uint16_t Year() const { return year; }

    private:
        std::uint16_t month;
        std::uint16_t day;
        std::uint16_t year;
    };

    class Time {
    public:
        explicit Time(std::uint16_t h, std::uint16_t m, std::uint16_t s);

        ~Time() = default;

        bool const operator==(const Time &rsv);

        bool const operator!=(const Time &rsv);

        bool const operator<(const Time &rsv);

        bool const operator>(const Time &rsv);

        std::uint16_t Hour() const { return hour; }

        std::uint16_t Minute() const { return minute; }

        std::uint16_t Seconds() const { return seconds; }


    private:
        std::uint16_t hour, minute, seconds;

        bool checkInRange(std::uint16_t val, std::uint16_t a, std::uint16_t b) { return (val >= a && val <= b); }

        double getFrac();
    };

    class DateTime {
    public:
        // represents both date and time
        explicit DateTime(const Date &date_, const Time &time_) :
                date(date_), time(time_) {}


        ~DateTime() = default;

        DateTime &operator=(const DateTime &rsv);

        bool const operator==(const DateTime &rsv);

        bool const operator!=(const DateTime &rsv);

        bool const operator<(const DateTime &rsv);

        bool const operator>(const DateTime &rsv);

        std::int32_t dayOfWeek() const;

        std::uint16_t Month() const { return date.Month(); }

        std::uint16_t Day() const { return date.Day(); }

        std::uint16_t Year() const { return date.Year(); }

        std::uint16_t Hour() const { return time.Hour(); }

        std::uint16_t Minute() const { return time.Minute(); }

        std::uint16_t Seconds() const { return time.Seconds(); }

        void print() const;

    private:

        Time time;
        Date date;
    };
}


//#endif //GRAPHTREE_DATETIME_H
