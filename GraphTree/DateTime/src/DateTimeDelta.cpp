//
// Created by sergei on 29.09.18.
//

#include "DateTimeDelta.h"
#include "DateTime.h"

#include <cmath>
#include <DateTimeDelta.h>


DT::DateTimeDelta::DateTimeDelta(DateTime dt1, DateTime dt2) {
    // Innit with some values.
    DateTime fromDate(Date(1, 1, 0), Time(10, 10, 10));
    DateTime toDate(Date(1, 1, 0), Time(10, 10, 10));


    // Date part.
    int monthDay[] = {31, 31, -1, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (dt1 > dt2) {
        fromDate = dt2;
        toDate = dt1;
    } else {
        fromDate = dt1;
        toDate = dt2;
    }

    std::int32_t increment = 0;
    std::int32_t _day = 0;
    std::int32_t _month = 0;
    std::int32_t _year = 0;

    // Day calc.

    if (fromDate.Day() > toDate.Day()) {
        increment = monthDay[toDate.Month() - 1];

    }
    if (increment == -1) {
        if (isLeapYear(toDate.Year())) {
            // leap year february contain 29 days
            increment = 29;
        } else {
            increment = 28;
        }
    }

    if (increment != 0) {
        _day = (toDate.Day() + increment) - fromDate.Day();
        increment = 1;
    } else {
        _day = toDate.Day() - fromDate.Day();
    }

    // Month calc.
    if ((fromDate.Month() + increment) > toDate.Month()) {
        _month = (toDate.Month() + 12) - (fromDate.Month() + increment);
        increment = 1;
    } else {
        _month = (toDate.Month()) - (fromDate.Month() + increment);
        increment = 0;
    }

    // Year calc.
    _year = toDate.Year() - (fromDate.Year() + increment);


    // Final assignment.
    this->day = (_day - 1);
    this->month = (_month);
    this->year = (_year);


    // Time part.

    std::uint32_t totSec1 = 3600 * 24 - (fromDate.Hour() * 3600 + fromDate.Minute() * 60 + fromDate.Seconds());
    std::uint32_t totSec2 = toDate.Hour() * 3600 + toDate.Minute() * 60 + toDate.Seconds();

    std::uint32_t timeDiff = totSec1 + totSec2;
    this->hour = timeDiff / 3600;
    this->minute = ((timeDiff - ((this->hour) * 3600)) / 60);
    this->seconds = (timeDiff - ((this->hour) * 3600) - (this->minute) * 60);

    if (this->hour == 24) {
        this->day = this->day + 1;
        this->hour = 0;
    }
}

void DT::DateTimeDelta::print() const {
    using std::cout;
    cout << year << " Year(s) " << month << " Month(s) " << day << " Day(s) | ";
    cout << hour << " Hour(s) " << minute << " Minute(s) " << seconds << " Second(s)\n";
}
