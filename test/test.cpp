#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>

#include <cstring>

#include "ciff_test.hpp"

#define DUMMY 1

int main(int argc, char* argv[]) {
    CPPUNIT_NS::TestResult testresult;
    CPPUNIT_NS::TestResultCollector collectedresults;
    testresult.addListener (&collectedresults);

    CPPUNIT_NS::BriefTestProgressListener progress;
    testresult.addListener (&progress);

    CPPUNIT_NS::TestRunner testrunner;
    if(argc < 2 || (argc == 2 && std::strcmp(argv[1], "all") == 0)) {
        testrunner.addTest (CiffTest::suite());
    }
    else if(argc == 2 && std::strcmp(argv[1], "ciff") == 0) {
        testrunner.addTest (CiffTest::suite());
    }
    else {
        std::cerr << "Invalid setting" << std::endl;
        return 1;
    }
    testrunner.run(testresult);

    CPPUNIT_NS::CompilerOutputter compileroutputter(&collectedresults, std::cerr);
    compileroutputter.write();

    std::ofstream xmlFileOut("report/cppunit.xml");
    CPPUNIT_NS::XmlOutputter xmlOut(&collectedresults, xmlFileOut);
    xmlOut.write();

    return collectedresults.wasSuccessful() ? 0 : 1;
}



