//
// DT module
// Created by sju on 24.09.18.
// ref: https://alcor.concordia.ca//~gpkatch/gdate-method.html
//

#pragma once

#include <iostream>
#include <cstdint>
#include <tuple>
#include <string>

#include "DateTimeDelta.h"

namespace DT {
    class Time;

    class Date;

    class DateTime;

    class DateTimeDelta;

    // Return true if date is valid, return false otherwise.
    bool validateDate(std::uint32_t d, std::uint32_t m, std::uint32_t y);

    // Returns an integer that represents week day (Mon=1, Tue=2...) if date is invalid return -1.
    std::int32_t getDayOfWeek(std::uint32_t d, std::uint32_t m, std::uint32_t y);

    // Returns day name from integer 1..7
    std::string toDayOfWeek(std::int32_t day);

    // Return true if year is a leap year, false otherwise.
    bool isLeapYear(std::uint32_t year);

    // Return total number of days.
    std::int32_t numberOfDays(const DateTime &dt);

    Date daysToDate(std::uint32_t daysCount);



    class Date {
    public:
        explicit Date(std::uint32_t d, std::uint32_t m, std::uint32_t y);

        ~Date() = default;

        std::uint32_t Month() const { return month; }

        std::uint32_t Day() const { return day; }

        std::uint32_t Year() const { return year; }

        void print();

        Date &operator=(const Date &rsv);

        bool const operator==(const Date &rsv);

        bool const operator!=(const Date &rsv);

        bool const operator<(const Date &rsv);

        bool const operator>(const Date &rsv);

    private:
        std::uint32_t month;
        std::uint32_t day;
        std::uint32_t year;
    };

    class Time {
    public:
        explicit Time(std::uint32_t h, std::uint32_t m, std::uint32_t s);

        ~Time() = default;

        Time &operator=(const Time &rhs);

        bool const operator==(const Time &rsv);

        bool const operator!=(const Time &rsv);

        bool const operator<(const Time &rsv);

        bool const operator>(const Time &rsv);

        std::uint32_t Hour() const { return hour; }

        std::uint32_t Minute() const { return minute; }

        std::uint32_t Seconds() const { return seconds; }


    private:
        std::uint32_t hour, minute, seconds;

        bool checkInRange(std::uint32_t val, std::uint32_t a, std::uint32_t b) { return (val >= a && val <= b); }

        double getFrac();
    };

    class DateTime {
    public:
        // represents both date and time
        explicit DateTime(const Date &date_, const Time &time_) :
                date(date_), time(time_) {}


        ~DateTime() = default;

        std::int32_t dayOfWeek() const;

        std::uint32_t Month() const { return date.Month(); }

        std::uint32_t Day() const { return date.Day(); }

        std::uint32_t Year() const { return date.Year(); }

        std::uint32_t Hour() const { return time.Hour(); }

        std::uint32_t Minute() const { return time.Minute(); }

        std::uint32_t Seconds() const { return time.Seconds(); }

        void print() const;

        DateTime &operator=(const DateTime &rsv);

        bool const operator==(const DateTime &rsv);

        bool const operator!=(const DateTime &rsv);

        bool const operator<(const DateTime &rsv);

        bool const operator>(const DateTime &rsv);

        DateTimeDelta operator-(const DateTime &rsv);

        DateTime operator+(const DateTimeDelta &rsv);

        DateTime operator-(const DateTimeDelta &rsv);

    private:

        Time time;
        Date date;
    };
}