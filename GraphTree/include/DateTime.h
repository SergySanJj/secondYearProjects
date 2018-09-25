//
// DateTime module
// Created by sju on 24.09.18.
//

#ifndef GRAPHTREE_DATETIME_H
#define GRAPHTREE_DATETIME_H

#include <iostream>
#include <cstdint>
#include <tuple>

namespace DateTime {

    class Month;
    class Day;
    class Year;

    class Time;

    // Return true if date is valid, return false otherwise.
    bool validateDate(std::uint8_t m, std::uint8_t d, std::uint16_t y);

    // Returns an integer that represents week day (Mon=1, Tue=2...)
    std::int32_t getDayOfWeek(std::uint8_t m, std::uint8_t d, std::uint16_t y);

    class DateTime {
    public:
        // represents both date and time
        explicit DateTime(std::uint32_t seconds) :
                total(seconds), justDate(0), justTime(0) {}

        // represents both date and time
        explicit DateTime(const Month m, const Day d, const Year y, const Time t);

        // represents dates only
        explicit DateTime(const Month m, const Day d, const Year y);
        // represents dates only
        explicit DateTime(const Day d, const Month m, const Year y);

        // represents time only
        explicit DateTime(const Time t);

        std::uint8_t month();
        std::uint8_t day();
        std::uint16_t year();

    private:
        std::uint32_t convertToSecons(std::uint8_t m, std::uint8_t d, std::uint16_t y,
                                      std::uint8_t h, std::uint8_t minute, std::uint8_t s);

        double julianFloat(const Month m, const Day d, const Year y)

    protected:
        // Total seconds from Jan 1st, 1970
        uint32_t total = 0;
        bool justDate;
        bool justTime;
    };
}


#endif //GRAPHTREE_DATETIME_H
