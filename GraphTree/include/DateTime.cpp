//
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

    class Day {
    public:
        static Day Mon() { return Day(1); }

        static Day Tue() { return Day(2); }

        static Day Wed() { return Day(3); }

        static Day Thu() { return Day(4); }

        static Day Fri() { return Day(5); }

        static Day Sat() { return Day(6); }

        static Day Sun() { return Day(7); }

    private:
        explicit Day(std::uint8_t d) : val(d) {}

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
            Hour(h);
            Minute(m);
            Second(s);
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
    DateTime::convertToSecons(std::uint8_t m, std::uint8_t d, std::uint16_t y, std::uint8_t h, std::uint8_t minute,
                              std::uint8_t s) {
        std::uint32_t res = s + minute*60 + h*3600;
        return 0;
    }
}