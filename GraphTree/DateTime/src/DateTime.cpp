//
// DateTime module
// Created by sju on 24.09.18.
//

#include "../include/DateTime.h"


namespace DateTime {

    class Month {
    public:
        static Month Jan() { return Month(1); }

        static Month Feb() { return Month(2); }

        static Month Mar() { return Month(3); }

        static Month Apr() { return Month(4); }

        static Month May() { return Month(5); }

        static Month Jun() { return Month(6); }

        static Month Jul() { return Month(7); }

        static Month Aug() { return Month(8); }

        static Month Sep() { return Month(9); }

        static Month Oct() { return Month(10); }

        static Month Nov() { return Month(11); }

        static Month Dec() { return Month(12); }

    private:
        explicit Month(std::uint8_t m) : val(m) {}

        std::uint8_t val;

    };

    class Day {
    public:
        explicit Day(std::uint8_t d) {
            if (d > 0 && d < 31)
                val = d;
            else
                throw ("Invalid day");
        }

    private:
        std::uint8_t val;
    };

    class Year {
    public:
        explicit Year(std::uint16_t y) {
            if (y >= 1970 && y <= 2037)
                val = y;
            else
                throw ("\n You can use dates only from "
                       "Jan 1st 1970 to Dec 29th 2037. \n");
        }

    private:
        std::uint16_t val;
    };


    Time::Time(std::uint8_t h, std::uint8_t m, std::uint8_t s) {
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


    bool validateDate(const std::uint8_t m, const std::uint8_t d, const std::uint16_t y) {
        if (y >= 1970 && y <= 2038) {
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
                    if (1 && (y % 400 == 0 || (y % 4 == 0 && y % 100 != 0)))
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

    std::int32_t getDayOfWeek(std::uint8_t m, std::uint8_t d, std::uint16_t y) {
        if (!validateDate(m, d, y)) {
            //std::cerr << "INVALID DATE\n";
            return -1;
        }
        // 1990, Michael Keith and Tom Craver expression.
        return (d += m < 3 ? y-- : y - 2, 23 * m / 9 + d + 4 + y / 4 - y / 100 + y / 400) % 7;
    }

    bool checkInRange(std::uint8_t val, std::uint8_t a, std::uint8_t b) { return (val >= a && val <= b); }

    Date::Date(std::uint8_t m, std::uint8_t d, std::uint16_t y) {
        if (validateDate(m,d,y))
        {
            month = m;
            day = d;
            year = y;
        }
        else
            throw("Invalid Date\n");
    }

}