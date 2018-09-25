//
// DateTime module
// Created by sju on 24.09.18.
//

#include "DateTime.h"


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

    class WeekDay {
    public:

        explicit WeekDay(std::uint8_t d) : val(d) {}

        static WeekDay Mon() { return WeekDay(1); }

        static WeekDay Tue() { return WeekDay(2); }

        static WeekDay Wed() { return WeekDay(3); }

        static WeekDay Thu() { return WeekDay(4); }

        static WeekDay Fri() { return WeekDay(5); }

        static WeekDay Sat() { return WeekDay(6); }

        static WeekDay Sun() { return WeekDay(7); }

    private:
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


    class Time {
    public:
        explicit Time(std::uint8_t h, std::uint8_t m, std::uint8_t s) {
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
                    second = s;
                else
                    throw ("Second value must be between 0 and 60");

            } catch (const char* msg){
                std::cerr << msg << '\n';
            }
        }

        void Hour(std::uint8_t h) {
            if (checkInRange(h, 0, 23))
                hour = h;
            else
                throw ("Hour val must be between 0 and 23");
        }

        void Minute(std::uint8_t m) {
            if (checkInRange(m, 0, 59))
                minute = m;
            else
                throw ("Minute val must be between 0 and 60");
        }

        void Second(std::uint8_t s) {
            if (checkInRange(s, 0, 60))
                second = s;
            else
                throw ("Second value must be between 0 and 60");


        }


    private:
        std::uint8_t hour, minute, second;

        bool checkInRange(std::uint8_t val, std::uint8_t a, std::uint8_t b) { return (val >= a && val <= b); }
    };

    std::uint32_t
    DateTime::convertToSecons(std::uint8_t m, std::uint8_t d, std::uint16_t y,
                              std::uint8_t h, std::uint8_t minute, std::uint8_t s) {
        auto res = static_cast<uint32_t>(s + minute * 60 + h * 3600);
        return 0;
    }

    DateTime::DateTime(const Month m, const Day d, const Year y, const Time t) {

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
}