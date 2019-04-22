//
// Created by sergei on 29.09.18.
//

#include "DateTimeDelta.h"
#include "DateTime.h"

#include <cmath>


std::int64_t DT::abs64(std::int64_t val) { return (val > 0 ? val : (-val)); }

DT::DateTimeDelta::DateTimeDelta(const DateTime &dt1, const DateTime &dt2) {
    // Innit with some values.
    DateTime fromDate(Date(1, 1, 0), Time(10, 10, 10));
    DateTime toDate(Date(1, 1, 0), Time(10, 10, 10));


    // Date part.
    static int32_t monthDay[] = {31, 31, -1, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (dt1 > dt2) {
        fromDate = dt2;
        toDate = dt1;
    } else {
        fromDate = dt1;
        toDate = dt2;
    }

    std::int64_t increment = 0;
    std::int64_t _day = 0;
    std::int64_t _month = 0;
    std::int64_t _year = 0;

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
    this->day = static_cast<int32_t>(_day - 1);
    this->month = static_cast<int32_t>(_month);
    this->year = static_cast<int32_t>(_year);


    // Time part.
    std::int64_t totSec1 = 3600 * 24 - (fromDate.Hour() * 3600 + fromDate.Minute() * 60 + fromDate.Seconds());
    std::int64_t totSec2 = toDate.Hour() * 3600 + toDate.Minute() * 60 + toDate.Seconds();

    std::int64_t timeDiff = totSec1 + totSec2;

    this->hour = static_cast<int32_t>
    (timeDiff / 3600);

    this->minute = static_cast<int32_t>
    ((timeDiff - ((this->hour) * 3600)) / 60);

    this->seconds = static_cast<int32_t>
    (timeDiff - ((this->hour) * 3600) - (this->minute) * 60);

    if (this->hour >= 24) {
        this->day = this->day + 1;
        this->hour = this->hour % 24;
    }


    // Total Days

    std::int64_t tot1 = daysIn(fromDate.Day(), fromDate.Month(), fromDate.Year());
    std::int64_t tot2 = daysIn(toDate.Day(), toDate.Month(), toDate.Year());
    this->totalDays = abs64(tot1 - tot2);

    this->totalSeconds = totalDays * 3600 * 24 + LastDaySeconds();
}

void DT::DateTimeDelta::print() const {
    using std::cout;
    cout << year << " Year(s) " << month << " Month(s) " << day << " Day(s) | ";
    cout << hour << " Hour(s) " << minute << " Minute(s) " << seconds << " Second(s)\n";
}

std::int64_t
DT::DateTimeDelta::daysIn(std::int32_t d, std::int32_t m, std::int32_t y) { /* Rata Die day one is 0001-01-01 */
    if (m < 3)
        y--, m += 12;
    return 365 * y + y / 4 - y / 100 + y / 400 + (153 * m - 457) / 5 + d - 306;
}

void DT::DateTimeDelta::println() const {
    print();
    std::cout << '\n';
}

DT::DateTimeDelta::DateTimeDelta(std::int64_t secondsDiff) {
    totalSeconds = secondsDiff;
    totalDays = secondsDiff / (3600 * 24);
}

DT::DateTimeDelta DT::DateTimeDelta::operator-(const DT::DateTimeDelta &rsv) const {
    return DT::DateTimeDelta(totalSeconds - rsv.TotalSeconds());
}





