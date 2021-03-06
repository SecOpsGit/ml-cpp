/*
 * Copyright Elasticsearch B.V. and/or licensed to Elasticsearch B.V. under one
 * or more contributor license agreements. Licensed under the Elastic License;
 * you may not use this file except in compliance with the Elastic License.
 */
#include "CHexUtilsTest.h"

#include <core/CHexUtils.h>
#include <core/CLogger.h>

#include <sstream>

#include <stdlib.h>
#include <time.h>

CppUnit::Test* CHexUtilsTest::suite() {
    CppUnit::TestSuite* suiteOfTests = new CppUnit::TestSuite("CHexUtilsTest");

    suiteOfTests->addTest(new CppUnit::TestCaller<CHexUtilsTest>(
        "CHexUtilsTest::testHexOutput", &CHexUtilsTest::testHexOutput));

    return suiteOfTests;
}

void CHexUtilsTest::testHexOutput() {
    // Seed the random number generator
    ::srand(static_cast<unsigned int>(::clock()));

    // Test empty output
    {
        ml::core::CHexUtils::TDataVec noData;

        std::ostringstream strm1;
        strm1 << ml::core::CHexUtils(noData);

        std::ostringstream strm2;
        strm2 << ml::core::CHexUtils(noData, false);

        std::ostringstream strm3;
        strm3 << ml::core::CHexUtils(noData, false, false);

        std::ostringstream strm4;
        strm4 << ml::core::CHexUtils(nullptr, 0);

        std::ostringstream strm5;
        strm5 << ml::core::CHexUtils(nullptr, 0, false);

        std::ostringstream strm6;
        strm6 << ml::core::CHexUtils(nullptr, 0, false, false);

        CPPUNIT_ASSERT(strm1.str() == strm4.str());
        CPPUNIT_ASSERT(strm2.str() == strm5.str());
        CPPUNIT_ASSERT(strm3.str() == strm6.str());

        CPPUNIT_ASSERT(strm1.str().find("DataSize: 0") != std::string::npos);
        CPPUNIT_ASSERT(strm2.str().find("DataSize:") == std::string::npos);

        // Since there's no data, it shouldn't matter whether ASCII output is
        // selected
        CPPUNIT_ASSERT(strm2.str() == strm3.str());
        CPPUNIT_ASSERT(strm5.str() == strm6.str());

        LOG_DEBUG(<< "Empty test output is:\n" << strm1.str());
    }

    // Test random data
    {
        ml::core::CHexUtils::TDataVec randomData;
        randomData.reserve(100);

        for (size_t count = 0; count < 100; ++count) {
            randomData.push_back(static_cast<uint8_t>(::rand()));
        }

        std::ostringstream strm1;
        strm1 << ml::core::CHexUtils(randomData);

        std::ostringstream strm2;
        strm2 << ml::core::CHexUtils(randomData, false);

        std::ostringstream strm3;
        strm3 << ml::core::CHexUtils(randomData, false, false);

        std::ostringstream strm4;
        strm4 << ml::core::CHexUtils(&randomData[0], randomData.size());

        std::ostringstream strm5;
        strm5 << ml::core::CHexUtils(&randomData[0], randomData.size(), false);

        std::ostringstream strm6;
        strm6 << ml::core::CHexUtils(&randomData[0], randomData.size(), false, false);

        CPPUNIT_ASSERT(strm1.str() == strm4.str());
        CPPUNIT_ASSERT(strm2.str() == strm5.str());
        CPPUNIT_ASSERT(strm3.str() == strm6.str());

        CPPUNIT_ASSERT(strm1.str().find("DataSize: 100") != std::string::npos);
        CPPUNIT_ASSERT(strm2.str().find("DataSize:") == std::string::npos);

        // Since there's data, it should matter whether ASCII output is
        // selected
        CPPUNIT_ASSERT(strm2.str() != strm3.str());
        CPPUNIT_ASSERT(strm5.str() != strm6.str());

        LOG_DEBUG(<< "Random test output is:\n" << strm1.str());
    }
}
