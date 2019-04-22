//
// DT module
// Created by sju on 24.09.18.
//

#include "DateTime.h"

#include<ctime>


namespace DT {

    Time::Time(const std::int32_t h, const std::int32_t m, const std::int32_t s) {

        if (checkInRange(h, 0, 23))
            hour = h;
        else
            throw std::range_error("Hour val must be between 0 and 23");

        if (checkInRange(m, 0, 59))
            minute = m;
        else
            throw std::range_error("Minute val must be between 0 and 60");

        if (checkInRange(s, 0, 60))
            seconds = s;
        else
            throw std::range_error("Second value must be between 0 and 60");
    }

    double Time::getFrac() {
        double days = seconds;
        days = minute + days / 60.0;
        days = hour + days / 60.0;
        return days / 24.0;
    }

    bool Time::operator==(const Time &rsv) const {
        return ((hour == rsv.hour) && (minute == rsv.minute) && (seconds == rsv.seconds));
    }

    bool  Time::operator<(const Time &rsv) const{
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

    bool Time::operator!=(const Time &rsv) const {
        return (!(*this == rsv));
    }

    bool Time::operator>(const Time &rsv) const{
        if (*this == rsv)
            return false;
        if (*this < rsv)
            return false;
        else
            return true;
    }

    Time &Time::operator=(const Time &rhs) {
        if (*this == rhs)
            return *this;
        hour = rhs.hour;
        minute = rhs.minute;
        seconds = rhs.seconds;
        return *this;
    }

    void Time::print() const {
        using std::cout;
        cout << toString();
    }

    void Time::println() const {
        print();
        std::cout << std::endl;
    }

    std::string Time::toString() const {
        std::string res = "";
        if (hour < 10)
            res += "0";
        res += std::to_string(hour) + ":";
        if (minute < 10)
            res += "0";
        res += std::to_string(minute) + ":";
        if (seconds < 10)
            res += "0";
        res += std::to_string(seconds);
        return res;
    }


    bool validateDate(const std::int32_t d, const std::int32_t m, const std::int32_t y) {
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

    std::int32_t DayOfWeekNumber(std::int32_t d, std::int32_t m, std::int32_t y) {
        if (!validateDate(d, m, y)) {
            return -1;
        }
        // 1990, Michael Keith and Tom Craver expression.
        std::int32_t day = (d += m < 3 ? y-- : y - 2, 23 * m / 9 + d + 4 + y / 4 - y / 100 + y / 400) % 7;
        // To make Sun week day number 7 not 0.
        return (day == 0 ? 7 : day);
    }

    bool checkInRange(const std::int32_t val, const std::int32_t a, const std::int32_t b) {
        return (val >= a && val <= b);
    }

    Date::Date(const std::int32_t d, const std::int32_t m, const std::int32_t y) {
        if (validateDate(d, m, y)) {
            month = m;
            day = d;
            year = y;
        } else
            throw std::range_error("Invalid Date");
    }

    bool Date::operator==(const Date &rsv) const {
        return ((month == rsv.month) && (day == rsv.day) && (year == rsv.year));
    }

    bool Date::operator<(const Date &rsv) const {
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

    bool Date::operator!=(const Date &rsv) const {
        return (!(*this == rsv));
    }

    bool Date::operator>(const Date &rsv) const {
        if (*this == rsv)
            return false;
        if (*this < rsv)
            return false;
        else
            return true;
    }

    Date &Date::operator=(const Date &rsv) {
        if (*this == rsv)
            return *this;
        day = rsv.day;
        month = rsv.month;
        year = rsv.year;

        return *this;
    }

    void Date::print() const {
        using std::cout;
        cout << toString();
    }

    void Date::println() const {
        print();
        std::cout << std::endl;
    }

    std::string Date::toString() const {
        std::string res = "";
        if (day < 10)
            res += "0";
        res += std::to_string(day) + "/";
        if (month < 10)
            res += "0";
        res += std::to_string(month) + "/" + std::to_string(year);
        return res;
    }

    void DateTime::print(bool useDayOfWeek) const {
        using std::cout;
        cout << toString(useDayOfWeek);
    }

    std::int32_t DateTime::dayOfWeek() const {
        return DT::DayOfWeekNumber(date.Day(), date.Month(), date.Year());
    }

    DateTime &DateTime::operator=(const DateTime &rsv) {
        if (*this == rsv)
            return *this;

        date = Date(rsv.Day(), rsv.Month(), rsv.Year());
        time = Time(rsv.Hour(), rsv.Minute(), rsv.Seconds());
        return *this;
    }

    bool DateTime::operator==(const DateTime &rsv) const {

        return ((time == rsv.time) && (date == rsv.date));
    }

    bool DateTime::operator<(const DateTime &rsv) const {
        if (date < rsv.date)
            return true;
        if (date == rsv.date) {
            if (time < rsv.time)
                return true;
            return false;
        } else
            return false;
    }

    bool DateTime::operator!=(const DateTime &rsv) const {
        return (!(*this == rsv));
    }

    bool DateTime::operator>(const DateTime &rsv) const {
        if (*this == rsv)
            return false;
        if (*this < rsv)
            return false;
        else
            return true;
    }

    DateTimeDelta DateTime::operator-(const DateTime &rsv) const {
        return DateTimeDelta(*this, rsv);
    }

    DateTime DateTime::operator+(const DateTimeDelta &rsv) {
        std::int64_t newDays = numberOfDays(*this) + rsv.TotalDays();
        std::int64_t newSeconds = LastDaySeconds() + rsv.LastDaySeconds();

        newDays += (newSeconds / 3600) / 24;
        newSeconds = newSeconds - ((newSeconds / 3600) / 24) * 3600 * 24;

        return DateTime(daysToDate(newDays), secondsToTime(newSeconds));
    }

    std::int64_t DateTime::LastDaySeconds() const {
        return (time.Hour() * 3600 + time.Minute() * 60 + time.Seconds());
    }

    DateTime DateTime::operator-(const DateTimeDelta &rsv) const {
        std::int64_t newDays = numberOfDays(*this) - rsv.TotalDays();
        std::int64_t newSeconds = LastDaySeconds() - rsv.LastDaySeconds();
        if (newDays <= 0 || (newDays == 1 && newSeconds < 0)) {
            return DateTime(Date(1, 1, 0), Time(0, 0, 0));
        }

        if (newSeconds < 0) {
            std::int64_t absSeconds = -newSeconds;
            newDays -= (absSeconds / 3600) / 24;
            absSeconds = 3600 * 24 - absSeconds + ((absSeconds / 3600) / 24) * 3600 * 60;

            return DateTime(daysToDate(newDays), secondsToTime(absSeconds));
        }

        return DateTime(daysToDate(newDays), secondsToTime(newSeconds));
    }

    void DateTime::println(bool useDayOfWeek) const {
        print(useDayOfWeek);
        std::cout << std::endl;
    }

    std::string DateTime::dayOfWeekString() const {
        return DayOfWeekString(dayOfWeek());
    }

    std::string DateTime::toString(bool useDayOfWeek) const {
        std::string res = "";
        if (useDayOfWeek)
            res += DayOfWeekString(DayOfWeekNumber(date.Day(), date.Month(), date.Year())) + " ";
        res += date.toString() + " ";
        res += time.toString();
        return res;
    }


    std::string DayOfWeekString(int32_t day) {
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

    std::string DayOfWeekString(std::int32_t d, std::int32_t m, std::int32_t y) {
        return DayOfWeekString(DayOfWeekNumber(d, m, y));
    }

    bool isLeapYear(std::int32_t year) {
        if (year % 4 == 0)
            return true;
        else if ((year % 100 == 0) && (year % 400 == 0))
            return true;
        else
            return false;
    }

    std::int64_t numberOfDays(const DateTime &dt) {
        std::int64_t y, m;

        m = (dt.Month() + 9) % 12;
        y = dt.Year() - m / 10;
        return y * 365 + y / 4 - y / 100 + y / 400 + (m * 306 + 5) / 10 + (dt.Day() - 1);
    }

    Date daysToDate(std::int64_t daysCount) {
        std::int64_t y, ddd, mi, mm, dd;
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
        Date res(static_cast<int32_t>(dd),
                 static_cast<int32_t>(mm),
                 static_cast<int32_t>(y));
        return res;

    }

    std::int64_t numberOfSeconds(const DateTime &dt) {
        std::int64_t res = numberOfDays(dt) * 3600 * 24;
        res += dt.Hour() * 3600 + dt.Minute() * 60 + dt.Seconds();
        return res;
    }

    Time secondsToTime(std::int64_t secondsCount) {
        std::int64_t newHour = secondsCount / 3600;
        std::int64_t newMinute = (secondsCount - newHour * 3600) / 60;
        std::int64_t newSeconds = secondsCount % (60);
        Time res(static_cast<int32_t>(newHour),
                 static_cast<int32_t>(newMinute),
                 static_cast<int32_t>(newSeconds));
        return res;
    }

    Date randomDate(const Date &d1, const Date &d2) {
        std::int64_t v1 = numberOfDays(DateTime(d1, Time(0, 0, 0)));
        std::int64_t v2 = numberOfDays(DateTime(d2, Time(0, 0, 0)));
        if (v1 > v2) {
            std::int64_t tmp = v2;
            v2 = v1;
            v1 = v2;
        }
        //std::srand(std::time(0));
        return (daysToDate(rand() % v2 + v1));
    }

    Time randomTime(const Time &t1, const Time &t2) {
        std::int64_t v1 = t1.Hour() * 3600 + t1.Minute() * 60 + t1.Seconds();
        std::int64_t v2 = t2.Hour() * 3600 + t2.Minute() * 60 + t2.Seconds();

        if (v1 > v2) {
            std::int64_t tmp = v2;
            v2 = v1;
            v1 = v2;
        }
        // std::srand(std::time(0));
        return (secondsToTime(rand() % v2 + v1));
    }
}