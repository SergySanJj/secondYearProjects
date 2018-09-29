//
// Created by sergei on 29.09.18.
//

#include "DateTimeDelta.h"
#include "DateTime.h"

DT::DateTimeDelta::DateTimeDelta(DateTime dt1, DateTime dt2) {
    DateTime fromDate(Date(1, 1, 0), Time(10, 10, 10));
    DateTime toDate(Date(1, 1, 0), Time(10, 10, 10));

    if (dt1 > dt2) {
        fromDate = dt2;
        toDate = dt1;
    } else {
        fromDate = dt1;
        toDate = dt2;
    }

}
