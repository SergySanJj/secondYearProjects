//
// Created by isara on 22-Apr-19.
//
#include "gtest/gtest.h"

#include "Graph.h"
#include "DateTime.h"
#include "DateTimeDelta.h"

#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

#include <cstdlib>

void dateTimePrintHelper(DT::DateTime val) {
    val.print();
    std::cout << " ";
}

void DateGraphSample() {

    std::cout << "\n--DateGraphSample--" << std::endl;
    // Make vector of random DateTimes:
    std::vector<DT::DateTime> dtVec;
    DT::DateTime startdt(DT::Date(1, 1, 1), DT::Time(0, 0, 0));
    DT::DateTime enddt(DT::Date(28, 12, 9999), DT::Time(23, 59, 59));
    for (std::size_t i = 0; i < 10; i++) {
        dtVec.push_back(DT::DateTime(DT::randomDate(startdt.getDate(), enddt.getDate()),
                                     DT::randomTime(startdt.getTime(), enddt.getTime())));
    }

    // init graph with dtVec.
    GraphTree::Graph<DT::DateTime> gDates(dtVec);
    gDates.print(dateTimePrintHelper);

}
