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
    int monthDay[] = {31, -1, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (dt1 > dt2) {
        fromDate = dt2;
        toDate = dt1;
    } else {
        fromDate = dt1;
        toDate = dt2;
    }

    int increment = 0;
    int _day = 0;
    int _month = 0;
    int _year = 0;

    // Day calc.
    if (fromDate.Day() > toDate.Day()) {
        increment = monthDay[fromDate.Month() - 1];
    }

    if (increment == -1) {
        if (isLeapYear(fromDate.Year())) {
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
    this->day = static_cast<uint16_t>(_day);
    this->month = static_cast<uint16_t>(_month);
    this->year = static_cast<uint16_t>(_year);


    // Time part.

    int totSec1 = fromDate.Hour() * 3600 + fromDate.Minute() * 60 + fromDate.Seconds();
    int totSec2 = toDate.Hour() * 3600 + toDate.Minute() * 60 + toDate.Seconds();

    int timeDiff = abs(totSec1 - totSec2);
    this->hour = timeDiff / 3600;
    this->minute = ((timeDiff - ((this->hour) * 3600)) / 60);
    this->seconds = (timeDiff - ((this->hour) * 3600) - (this->minute) * 60);
}

void DT::DateTimeDelta::print() {
    using std::cout;
    cout << year << " Year(s) " << month << " Month(s) " << day << " Day(s) | ";
    cout << hour << " Hour(s) " << minute << " Minute(s) " << seconds << " Second(s)\n";
}
