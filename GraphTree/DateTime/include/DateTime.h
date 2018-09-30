//
// DT module
// Created by sju on 24.09.18.
// ref doc for conversion: https://alcor.concordia.ca//~gpkatch/gdate-method.html
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

    /// Return true if date is valid, return false otherwise.
    bool validateDate(std::int32_t d, std::int32_t m, std::int32_t y);

    /// Returns an integer that represents week day (Mon=1, Tue=2...) if date is invalid return -1.
    std::int32_t getDayOfWeek(std::int32_t d, std::int32_t m, std::int32_t y);

    /// Returns day name from integer 1..7.
    std::string toDayOfWeek(std::int32_t day);

    /// Return true if year is a leap year, false otherwise.
    bool isLeapYear(std::int32_t year);

    /// Return total number of days.
    std::int64_t numberOfDays(const DateTime &dt);

    /// Returns date equivalent to daysCount.
    Date daysToDate(std::int64_t daysCount);

    /// Returns number of seconds equivalent to DateTime value.
    std::int64_t numberOfSeconds(const DateTime &dt);

    /// Returns time equivalent to secondsCount.
    Time secondsToTime(std::int64_t secondsCount);

    /// Returns absolute value.
    std::int64_t abs64(std::int64_t val);

    class Date {
    public:
        explicit Date(std::int32_t d, std::int32_t m, std::int32_t y);

        Date() : day(1), month(1), year(0) {}

        ~Date() = default;

        std::int32_t Month() const { return month; }

        std::int32_t Day() const { return day; }

        std::int32_t Year() const { return year; }

        void print() const;

        void println() const;

        Date &operator=(const Date &rsv);

        bool const operator==(const Date &rsv);

        bool const operator!=(const Date &rsv);

        bool const operator<(const Date &rsv);

        bool const operator>(const Date &rsv);

    private:
        std::int32_t month;
        std::int32_t day;
        std::int32_t year;
    };

    class Time {
    public:
        explicit Time(std::int32_t h, std::int32_t m, std::int32_t s);

        Time() : hour(0), minute(0), seconds(0) {}

        ~Time() = default;

        Time &operator=(const Time &rhs);

        void print() const;

        void println() const;

        bool const operator==(const Time &rsv);

        bool const operator!=(const Time &rsv);

        bool const operator<(const Time &rsv);

        bool const operator>(const Time &rsv);

        std::int32_t Hour() const { return hour; }

        std::int32_t Minute() const { return minute; }

        std::int32_t Seconds() const { return seconds; }


    private:
        std::int32_t hour, minute, seconds;

        bool checkInRange(std::int32_t val, std::int32_t a, std::int32_t b) { return (val >= a && val <= b); }

        double getFrac();
    };

    class DateTime {
    public:
        /// represents both date and time
        explicit DateTime(const Date &date_, const Time &time_) :
                date(date_), time(time_) {}

        DateTime() : date(), time() {}

        ~DateTime() = default;

        /// Return integer that represents day of week of .this date.
        std::int32_t dayOfWeek() const;

        /// Return string day of week of .this date.
        std::string dayOfWeekString() const;

        std::int32_t Month() const { return date.Month(); }

        std::int32_t Day() const { return date.Day(); }

        std::int32_t Year() const { return date.Year(); }

        std::int32_t Hour() const { return time.Hour(); }

        std::int32_t Minute() const { return time.Minute(); }

        std::int32_t Seconds() const { return time.Seconds(); }

        Date getDate() const { return date; }

        Time getTime() const { return time; }

        void print() const;

        void println() const;

        /// Return number of seconds that passed from the beginning of the .this date.
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