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

TEST(GraphTimeTests, Creation) {
    std::vector<DT::DateTime> dateTimeVec = {DT::DateTime(DT::Date(1, 1, 0), DT::Time(0, 0, 0)),
                                             DT::DateTime(DT::Date(10, 1, 0), DT::Time(0, 0, 0)),
                                             DT::DateTime(DT::Date(3, 1, 0), DT::Time(0, 0, 0)),
                                             DT::DateTime(DT::Date(5, 1, 0), DT::Time(0, 0, 0))};
    GraphTree::Graph<DT::DateTime> g1;
    for (int i = 0; i < 4; i++)
        g1.addVertex(GraphTree::Vertex(dateTimeVec[i]));

    auto expZero = g1[3].data() - g1[2].data();
    ASSERT_EQ(3600 * 24 * 2, expZero.TotalSeconds());
    auto t = expZero - (g1[1].data() - g1[0].data());
    ASSERT_EQ(-7 * 24 * 3600, t.TotalSeconds());
}

