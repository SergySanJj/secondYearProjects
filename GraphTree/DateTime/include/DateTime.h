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
    bool validateDate(std::int64_t d, std::int64_t m, std::int64_t y);

    // Returns an integer that represents week day (Mon=1, Tue=2...) if date is invalid return -1.
    std::int64_t getDayOfWeek(std::int64_t d, std::int64_t m, std::int64_t y);

    // Returns day name from integer 1..7
    std::string toDayOfWeek(std::int64_t day);

    // Return true if year is a leap year, false otherwise.
    bool isLeapYear(std::int64_t year);

    // Return total number of days.
    std::int64_t numberOfDays(const DateTime &dt);

    Date daysToDate(std::int64_t daysCount);

    std::int64_t numberOfSeconds(const DateTime &dt);

    Time secondsToTime(std::int64_t secondsCount);

    class Date {
    public:
        explicit Date(std::int64_t d, std::int64_t m, std::int64_t y);

        Date() : day(1), month(1), year(0) {}

        ~Date() = default;

        std::int64_t Month() const { return month; }

        std::int64_t Day() const { return day; }

        std::int64_t Year() const { return year; }

        void print();

        Date &operator=(const Date &rsv);

        bool const operator==(const Date &rsv);

        bool const operator!=(const Date &rsv);

        bool const operator<(const Date &rsv);

        bool const operator>(const Date &rsv);

    private:
        std::int64_t month;
        std::int64_t day;
        std::int64_t year;
    };

    class Time {
    public:
        explicit Time(std::int64_t h, std::int64_t m, std::int64_t s);

        Time() : hour(0), minute(0), seconds(0) {}

        ~Time() = default;

        Time &operator=(const Time &rhs);

        void print();

        bool const operator==(const Time &rsv);

        bool const operator!=(const Time &rsv);

        bool const operator<(const Time &rsv);

        bool const operator>(const Time &rsv);

        std::int64_t Hour() const { return hour; }

        std::int64_t Minute() const { return minute; }

        std::int64_t Seconds() const { return seconds; }


    private:
        std::int64_t hour, minute, seconds;

        bool checkInRange(std::int64_t val, std::int64_t a, std::int64_t b) { return (val >= a && val <= b); }

        double getFrac();
    };

    class DateTime {
    public:
        // represents both date and time
        explicit DateTime(const Date &date_, const Time &time_) :
                date(date_), time(time_) {}

        DateTime(): date(), time() {}

        ~DateTime() = default;

        std::int64_t dayOfWeek() const;

        std::int64_t Month() const { return date.Month(); }

        std::int64_t Day() const { return date.Day(); }

        std::int64_t Year() const { return date.Year(); }

        std::int64_t Hour() const { return time.Hour(); }

        std::int64_t Minute() const { return time.Minute(); }

        std::int64_t Seconds() const { return time.Seconds(); }

        void print() const;

        std::int64_t LastDaySeconds() const;

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