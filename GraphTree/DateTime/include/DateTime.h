//
// DateTime module
// Created by sju on 24.09.18.
//

#ifndef GRAPHTREE_DATETIME_H
#define GRAPHTREE_DATETIME_H

#include "DateTimeDelta.h"

#include <iostream>
#include <cstdint>
#include <tuple>

namespace DateTime {

    // Return true if date is valid, return false otherwise.
    bool validateDate(std::uint8_t m, std::uint8_t d, std::uint16_t y);

    // Returns an integer that represents week day (Mon=1, Tue=2...) if date is invalid return -1.
    std::int32_t getDayOfWeek(std::uint8_t m, std::uint8_t d, std::uint16_t y);

    class Date {
    public:
        explicit Date(std::uint8_t m, std::uint8_t d, std::uint16_t y);

        std::uint8_t Month() { return month; }

        std::uint8_t Day() { return day; }

        std::uint16_t Year() { return year; }

    private:
        std::uint8_t month;
        std::uint8_t day;
        std::uint16_t year;
    };

    class Time {
    public:
        explicit Time(std::uint8_t h, std::uint8_t m, std::uint8_t s);

        std::uint8_t Hour() { return hour; }

        std::uint8_t Minute() { return minute; }

        std::uint8_t Seconds() { return seconds; }


    private:
        std::uint8_t hour, minute, seconds;

        bool checkInRange(std::uint8_t val, std::uint8_t a, std::uint8_t b) { return (val >= a && val <= b); }

        double getFrac();
    };

    class DateTime {
    public:
        // represents both date and time
        explicit DateTime(Date date_, Time time_) :
                date(date_), time(time_), justDate(false), justTime(false) {}

        // represents dates only
        explicit DateTime(Date date_) :
                date(date_), time(Time(0, 0, 0)), justDate(true), justTime(false) {}

        // represents time only
        explicit DateTime(Time time_) :
                date(Date(1, 1, 1970)), time(time_), justDate(false), justTime(true) {}


        std::uint8_t month() { return date.Month(); }

        std::uint8_t day() { return date.Day(); }

        std::uint16_t year() { return date.Year(); }

        void print();

    private:
        bool justDate;
        bool justTime;

        Time time;
        Date date;

        std::uint32_t convertToSecons(std::uint8_t m, std::uint8_t d, std::uint16_t y,
                                      std::uint8_t h, std::uint8_t minute, std::uint8_t s);

    };
}


#endif //GRAPHTREE_DATETIME_H
