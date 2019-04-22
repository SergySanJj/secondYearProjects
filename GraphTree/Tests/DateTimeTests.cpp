//
// Created by isara on 15-Apr-19.
//
#include "gtest/gtest.h"

#include "DateTime.h"
#include "DateTimeDelta.h"


TEST(DateValidationTests, Validation) {
    // To validate date use:
    bool validateRes = DT::validateDate(29, 9, 2018);

    ASSERT_TRUE(validateRes);
    ASSERT_TRUE(DT::validateDate(1, 1, 0001));
    ASSERT_FALSE(DT::validateDate(0, 0, 0));
    ASSERT_FALSE(DT::validateDate(33, 9, 2018));
}

TEST(DayOfWeekTests, WeekDayNumber) {
    // To get number of week day use:
    int day1 = DT::DayOfWeekNumber(22, 4, 2019); // Monday
    ASSERT_EQ(1, day1);
    ASSERT_EQ(2, DT::DayOfWeekNumber(23, 4, 2019));
    ASSERT_EQ(3, DT::DayOfWeekNumber(24, 4, 2019));
    ASSERT_EQ(4, DT::DayOfWeekNumber(25, 4, 2019));
    ASSERT_EQ(5, DT::DayOfWeekNumber(26, 4, 2019));
    ASSERT_EQ(6, DT::DayOfWeekNumber(27, 4, 2019));
    ASSERT_EQ(7, DT::DayOfWeekNumber(28, 4, 2019));
    ASSERT_EQ(1, DT::DayOfWeekNumber(29, 4, 2019)); // Monday again

    // Method also validates date:
    ASSERT_EQ(-1, DT::DayOfWeekNumber(-29, 4, 2019));
}

TEST(DayOfWeekTests, WeekDayString) {
    // To get number of week day use:
    std::string day1_full = DT::DayOfWeekString(22, 4, 2019); // Monday
    std::string day1_composit = DT::DayOfWeekString(DT::DayOfWeekNumber(22, 4, 2019)); // Monday

    ASSERT_EQ("Mon", day1_full);
    ASSERT_EQ(day1_full, day1_composit);

    ASSERT_EQ("Tue", DT::DayOfWeekString(23, 4, 2019));
    ASSERT_EQ("Wed", DT::DayOfWeekString(24, 4, 2019));
    ASSERT_EQ("Thu", DT::DayOfWeekString(25, 4, 2019));
    ASSERT_EQ("Fri", DT::DayOfWeekString(26, 4, 2019));
    ASSERT_EQ("Sat", DT::DayOfWeekString(27, 4, 2019));
    ASSERT_EQ("Sun", DT::DayOfWeekString(28, 4, 2019));
    ASSERT_EQ("Mon", DT::DayOfWeekString(29, 4, 2019)); // Monday again

    // Method also validates date:
    ASSERT_EQ("INVALID", DT::DayOfWeekString(-29, 4, 2019));
}

TEST(DateTests, Creation) {
    // To create Date object use:
    // where values are ordered dd/mm/yy
    // WARNING: works with dates from 01/01/0000 to 31/12/9999
    DT::Date date1(29, 9, 2018);

    ASSERT_EQ("29/09/2018", date1.toString());
    ASSERT_EQ("01/01/0", DT::Date(1, 1, 0).toString());
    ASSERT_EQ("31/12/9999", DT::Date(31, 12, 9999).toString());
    ASSERT_THROW(DT::Date(0, 0, 0), std::range_error);
    ASSERT_THROW(DT::Date(0, 0, 10000), std::range_error);

    // Default date value
    ASSERT_EQ("01/01/0", DT::Date().toString());
}

TEST(TimeTests, Creation) {
    // To create Time object use:
    // where values are ordered hh/mm/ss
    DT::Time time1(10, 25, 56);

    ASSERT_EQ("10:25:56", time1.toString());
    ASSERT_EQ("00:00:00", DT::Time(0, 0, 0).toString());
    ASSERT_EQ("01:05:09", DT::Time(1, 5, 9).toString());
    ASSERT_THROW(DT::Time(-1, 0, 0), std::range_error);
    ASSERT_THROW(DT::Time(25, 0, 0), std::range_error);
    ASSERT_THROW(DT::Time(24, 61, 0), std::range_error);
    ASSERT_THROW(DT::Time(24, 60, -1), std::range_error);

    // Default time value
    ASSERT_EQ("00:00:00", DT::Time().toString());
}

TEST(DateTimeTests, Creation) {
    DT::Date date1(29, 9, 2018);
    DT::Time time1(10, 25, 56);

    // To create DateTime object use:
    DT::DateTime dt1(date1, time1);
    ASSERT_EQ(date1.toString() + " " + time1.toString(), dt1.toString());
    // Or simply:
    DT::DateTime dt2(DT::Date(29, 9, 2018), DT::Time(10, 25, 56));
    ASSERT_EQ("29/09/2018 10:25:56", dt2.toString());
    DT::DateTime dt3(DT::Date(31, 12, 2018), DT::Time(23, 59, 59)); // yeah 1 sec before NY
    ASSERT_EQ("31/12/2018 23:59:59", dt3.toString());

    // Default DateTime value
    ASSERT_EQ("01/01/0 00:00:00", DT::DateTime().toString());
}

TEST(DateTests, GettingComponents) {
    DT::Date date1(29, 9, 2018);

    ASSERT_EQ(29, date1.Day());
    ASSERT_EQ(9, date1.Month());
    ASSERT_EQ(2018, date1.Year());
}

TEST(TimeTests, GettingComponents) {
    DT::Time time1(10, 25, 56);

    ASSERT_EQ(10, time1.Hour());
    ASSERT_EQ(25, time1.Minute());
    ASSERT_EQ(56, time1.Seconds()); // Note Seconds NOT Second.
}

TEST(DateTimeTests, GettingComponents) {
    DT::Date date1(29, 9, 2018);
    DT::Time time1(10, 25, 56);
    DT::DateTime dtd1(date1, time1);

    ASSERT_EQ(29, dtd1.Day());
    ASSERT_EQ(9, dtd1.Month());
    ASSERT_EQ(2018, dtd1.Year());

    ASSERT_EQ(10, dtd1.Hour());
    ASSERT_EQ(25, dtd1.Minute());
    ASSERT_EQ(56, dtd1.Seconds());
}


TEST(DateTimeDeltaTests, CreationFromSeconds) {
    // Create DTD from seconds
    DT::DateTimeDelta dtd1(0);
    ASSERT_EQ(0, dtd1.TotalDays());
    ASSERT_EQ(0, dtd1.TotalSeconds());

    DT::DateTimeDelta dtd2(3600 * 24 * 2 + 3600); // 2 days 1 hour
    ASSERT_EQ(2, dtd2.TotalDays());
    ASSERT_EQ(3600 * 24 * 2 + 3600, dtd2.TotalSeconds());
}

TEST(DateTimeDeltaTests, CreationFromDateTimeOperations) {
    // To store date time difference use DateTimeDelta class
    DT::DateTime DT(DT::Date(31, 12, 2019), DT::Time(10, 10, 10));
    DT::DateTime NY(DT::Date(31, 12, 2019), DT::Time(23, 59, 59));

    DT::DateTimeDelta toNY = NY - DT;

    ASSERT_EQ(0, toNY.TotalDays());

    auto toNY2 = DT::DateTime(DT::Date(31, 12, 2019), DT::Time(23, 59, 59)) -
                 DT::DateTime(DT::Date(28, 12, 2019), DT::Time(23, 59, 59));

    ASSERT_EQ(3, toNY2.TotalDays());

    auto uniYearDelta = DT::DateTime(DT::Date(17, 6, 2019), DT::Time(0, 0, 0)) -
                        DT::DateTime(DT::Date(1, 9, 2018), DT::Time(0, 0, 0));

    ASSERT_EQ(289, uniYearDelta.TotalDays());
    ASSERT_EQ(41, uniYearDelta.TotalWeeks());
}

TEST(DateTimeTests, DateTimeOperations) {
    DT::Date date1(29, 9, 2018);
    DT::Time time1(10, 25, 56);
    DT::DateTime dt1(date1, time1);
    DT::DateTime dt2(DT::Date(29, 9, 2018), DT::Time(10, 25, 56));
    DT::DateTime dt3(DT::Date(31, 12, 2018), DT::Time(23, 59, 59));

    // To add/subtract delta from DateTime use:
    // WARNING: if after subtracting Date goes below 1/1/0000
    // result will be 1/1/0000 00:00:00
    DT::DateTimeDelta toNY = dt3 - dt2;
    ASSERT_EQ(8084043, toNY.TotalSeconds());

    DT::DateTime addDT = dt1 + toNY;
    ASSERT_EQ("31/12/2018 23:59:59", addDT.toString());

    DT::DateTime subDT = dt1 - toNY;
    ASSERT_EQ("28/06/2018 20:51:53", subDT.toString());

    DT::DateTime zeroDate = dt1 - (DT::DateTime() - dt3); // overlap through 1/1/0 00/00/00
    ASSERT_EQ("01/01/0 00:00:00", zeroDate.toString());

    // You can also use ==, !=, <, > for Date, Time, DateTime and DateTimeDelta
    // to compare same type values.

    ASSERT_TRUE(DT::DateTime() == zeroDate);

    ASSERT_TRUE(DT::Date(12, 11, 2019) > DT::Date(13, 12, 2018));
    ASSERT_TRUE(DT::Date(12, 11, 2017) < DT::Date(13, 12, 2018));
    ASSERT_TRUE(DT::Date(12, 12, 12) == DT::Date(12, 12, 12));

    ASSERT_TRUE(DT::Time(23, 55, 56) > DT::Time(23, 54, 56));
    ASSERT_TRUE(DT::Time(2, 55, 56) < DT::Time(10, 20, 30));
    ASSERT_TRUE(DT::Time() == DT::Time());

}