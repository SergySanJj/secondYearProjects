//
// DT module
// Created by sju on 24.09.18.
//

#include <DateTime.h>

#include "DateTime.h"


namespace DT {

    Time::Time(const std::uint32_t h, const std::uint32_t m, const std::uint32_t s) {
        try {
            if (checkInRange(h, 0, 23))
                hour = h;
            else
                throw ("Hour val must be between 0 and 23");

            if (checkInRange(m, 0, 59))
                minute = m;
            else
                throw ("Minute val must be between 0 and 60");

            if (checkInRange(s, 0, 60))
                seconds = s;
            else
                throw ("Second value must be between 0 and 60");

        } catch (const char *msg) {
            std::cerr << msg << '\n';
        }
    }

    double Time::getFrac() {
        double days = seconds;
        days = minute + days / 60.0;
        days = hour + days / 60.0;
        return days / 24.0;
    }

    bool const Time::operator==(const Time &rsv) {
        return ((hour == rsv.hour) && (minute == rsv.minute) && (seconds == rsv.seconds));
    }

    bool const Time::operator<(const Time &rsv) {
        if (hour < rsv.hour)
            return true;
        if (hour > rsv.hour)
            return false;

        if (minute < rsv.minute)
            return true;
        if (minute > rsv.minute)
            return false;

        if (seconds < rsv.seconds)
            return true;
        else
            return false;
    }

    bool const Time::operator!=(const Time &rsv) {
        return (!(*this == rsv));
    }

    bool const Time::operator>(const Time &rsv) {
        if (*this == rsv)
            return false;
        if (*this < rsv)
            return false;
        else
            return true;
    }

    Time &Time::operator=(const Time &rhs) {
        hour = rhs.hour;
        minute = rhs.minute;
        seconds = rhs.seconds;
        return *this;
    }


    bool validateDate(const std::uint32_t d, const std::uint32_t m, const std::uint32_t y) {
        if (y >= 0 && y <= 9999) {
            //check month
            if (m >= 1 && m <= 12) {
                //check days
                if ((d >= 1 && d <= 31) && (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12))
                    return true;
                else if ((d >= 1 && d <= 30) && (m == 4 || m == 6 || m == 9 || m == 11))
                    return true;
                else if ((d >= 1 && d <= 28) && (m == 2))
                    return true;
                    // Leap year check.
                else if (d == 29 && m == 2) {
                    if (isLeapYear(y))
                        return true;
                    else {
                        //throw("Day is invalid.\n");
                        return false;
                    }
                } else {
                    return false;
                }
            } else {
                //throw("Month is not valid.\n");
                return false;
            }
        } else {
            //throw("Year is not valid.\n");
            return false;
        }

    }

    std::int32_t getDayOfWeek(std::uint32_t d, std::uint32_t m, std::uint32_t y) {
        if (!validateDate(d, m, y)) {
            return -1;
        }
        // 1990, Michael Keith and Tom Craver expression.
        std::int32_t day = (d += m < 3 ? y-- : y - 2, 23 * m / 9 + d + 4 + y / 4 - y / 100 + y / 400) % 7;
        // To make Sun week day number 7 not 0.
        return (day == 0 ? 7 : day);
    }

    bool checkInRange(const std::uint32_t val, const std::uint32_t a, const std::uint32_t b) {
        return (val >= a && val <= b);
    }

    Date::Date(const std::uint32_t d, const std::uint32_t m, const std::uint32_t y) {
        if (validateDate(d, m, y)) {
            month = m;
            day = d;
            year = y;
        } else
            throw ("Invalid Date\n");
    }

    bool const Date::operator==(const Date &rsv) {
        return ((month == rsv.month) && (day == rsv.day) && (year == rsv.year));
    }

    bool const Date::operator<(const Date &rsv) {
        if (year < rsv.year)
            return true;
        if (year > rsv.year)
            return false;
        // year == rsv.year.
        if (month < rsv.month)
            return true;
        if (month > rsv.month)
            return false;
        // month == rsv.month.
        if (day < rsv.day)
            return true;
        else
            return false;
    }

    bool const Date::operator!=(const Date &rsv) {
        return (!(*this == rsv));
    }

    bool const Date::operator>(const Date &rsv) {
        if (*this == rsv)
            return false;
        if (*this < rsv)
            return false;
        else
            return true;
    }

    Date &Date::operator=(const Date &rsv) {
        day = rsv.day;
        month = rsv.month;
        year = rsv.year;

        return *this;
    }

    void Date::print() {
        using std::cout;
        cout << day << "/" << month << "/" << year << "\n";
    }

    void DateTime::print() const {
        using std::cout;
        cout << toDayOfWeek(getDayOfWeek(date.Day(), date.Month(), date.Year())) << " ";
        cout << date.Day() << "/" << date.Month() << "/" << date.Year() << " ";
        cout << time.Hour() << ":" << time.Minute() << ":";
        if (time.Seconds() < 10)
            cout << "0";
        cout << time.Seconds() << '\n';
    }

    std::int32_t DateTime::dayOfWeek() const {
        return DT::getDayOfWeek(date.Day(), date.Month(), date.Year());
    }

    DateTime &DateTime::operator=(const DateTime &rsv) {
        date = Date(rsv.Day(), rsv.Month(), rsv.Year());
        time = Time(rsv.Hour(), rsv.Minute(), rsv.Seconds());
        return *this;
    }

    bool const DateTime::operator==(const DateTime &rsv) {

        return ((time == rsv.time) && (date == rsv.date));
    }

    bool const DateTime::operator<(const DateTime &rsv) {
        if (date < rsv.date)
            return true;
        if (date == rsv.date) {
            if (time < rsv.time)
                return true;
            return false;
        } else
            return false;
    }

    bool const DateTime::operator!=(const DateTime &rsv) {
        return (!(*this == rsv));
    }

    bool const DateTime::operator>(const DateTime &rsv) {
        if (*this == rsv)
            return false;
        if (*this < rsv)
            return false;
        else
            return true;
    }

    DateTimeDelta DateTime::operator-(const DateTime &rsv) {
        return DateTimeDelta(*this, rsv);
    }

    DateTime DateTime::operator+(const DateTimeDelta &rsv) {
        std::uint32_t newDay = date.Day();
        std::uint32_t newMonth = date.Month();
        std::uint32_t newYear = date.Year();

        std::uint32_t newHour = time.Hour();
        std::uint32_t newMinute = time.Minute();
        std::uint32_t newSeconds = time.Seconds();


        std::uint32_t prevDays = numberOfDays(*this);

        Date newDate(newDay, newMonth, newYear);
        Time newTime(newHour, newMinute, newSeconds);

        DateTime res(newDate, newTime);
        return res;
    }



    std::string toDayOfWeek(const std::int32_t day) {
        switch (day) {
            case -1:
                return "INVALID";
            case 1:
                return "Mon";
            case 2:
                return "Tue";
            case 3:
                return "Wed";
            case 4:
                return "Thu";
            case 5:
                return "Fri";
            case 6:
                return "Sat";
            case 7:
                return "Sun";
            default:
                return "INVALID";
        }
    }

    bool isLeapYear(std::uint32_t year) {
        if (year % 4 == 0)
            return true;
        else if ((year % 100 == 0) && (year % 400 == 0))
            return true;
        else
            return false;
    }

    std::int32_t numberOfDays(const DateTime &dt) {       /* convert date to day number */
        std::int32_t y, m;

        m = (dt.Month() + 9) % 12;                /* mar=0, feb=11 */
        y = dt.Year() - m / 10;                     /* if Jan/Feb, year-- */
        return y * 365 + y / 4 - y / 100 + y / 400 + (m * 306 + 5) / 10 + (dt.Day() - 1);
    }

    Date daysToDate(std::uint32_t daysCount) { /* convert day number to y,m,d format */
        std::uint32_t y, ddd, mi, mm, dd;
        y = (10000 * daysCount + 14780) / 3652425;
        ddd = daysCount - (365 * y + y / 4 - y / 100 + y / 400);
        if (ddd < 0) {
            y = y - 1;
            ddd = daysCount - (365 * y + y / 4 - y / 100 + y / 400);
        }
        mi = (100 * ddd + 52) / 3060;
        mm = (mi + 2) % 12 + 1;
        y = y + (mi + 2) / 12;
        dd = ddd - (mi * 306 + 5) / 10 + 1;
        Date res(dd, mm, y);
        return res;

    }
}