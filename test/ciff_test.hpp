#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

extern "C" {
#include "ciff_parser.h"
}

class CiffTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(CiffTest);
    CPPUNIT_TEST(testCiff1);
    CPPUNIT_TEST(testCiff2);
    CPPUNIT_TEST(testCiff3);
    CPPUNIT_TEST(testCiff4);
    CPPUNIT_TEST(testCiff5);
    CPPUNIT_TEST(testCiff6);
    CPPUNIT_TEST(testCiff7);
    CPPUNIT_TEST(testCiff8);
    CPPUNIT_TEST(testCiff9);
    CPPUNIT_TEST(testCiff10);
    CPPUNIT_TEST(testCiff11);
    CPPUNIT_TEST(testCiff12);
    CPPUNIT_TEST(testCiff13);
    CPPUNIT_TEST(testCiff14);
    CPPUNIT_TEST(testCiff15);
    CPPUNIT_TEST(testCiff16);
    CPPUNIT_TEST_SUITE_END();

protected:
    void testCiff1() {
        check_ciff("test/ciff/test1.ciff", true);
    }

    void testCiff2() {
        check_ciff("test/ciff/test2.ciff", false);
    }

    void testCiff3() {
        check_ciff("test/ciff/test3.ciff", false);
    }

    void testCiff4() {
        check_ciff("test/ciff/test4.ciff", false);
    }

    void testCiff5() {
        check_ciff("test/ciff/test5.ciff", false);
    }

    void testCiff6() {
        check_ciff("test/ciff/test6.ciff", true);
    }

    void testCiff7() {
        check_ciff("test/ciff/test7.ciff", false);
    }

    void testCiff8() {
        check_ciff("test/ciff/test8.ciff", false);
    }

    void testCiff9() {
        check_ciff("test/ciff/test9.ciff", true);
    }

    void testCiff10() {
        check_ciff("test/ciff/test10.ciff", false);
    }

    void testCiff11() {
        check_ciff("test/ciff/test11.ciff", true);
    }

    void testCiff12() {
        check_ciff("test/ciff/test12.ciff", false);
    }

    void testCiff13() {
        check_ciff("test/ciff/test13.ciff", false);
    }

    void testCiff14() {
        check_ciff("test/ciff/test14.ciff", true);
    }

    void testCiff15() {
        check_ciff("test/ciff/test15.ciff", false);
    }

    void testCiff16() {
        check_ciff("test/ciff/test16.ciff", true);
    }

private:
    void read_ciff(const char *file_name, unsigned char **buffer, unsigned long long *size) {
        FILE *fp = fopen(file_name, "rb");
        fseek(fp, 0, SEEK_END);
        *size = ftell(fp);
        fseek(fp, 0, SEEK_SET);  /* same as rewind(f); */

        *buffer = static_cast<unsigned char *>(malloc(*size + 1));
        fread(*buffer, 1, *size, fp);
        fclose(fp);

        (*buffer)[*size] = '\0';
    }

    void bmp_fo_file(unsigned char *bmp, unsigned long long file_size, const char *file_name) {
        FILE *fp = fopen(file_name, "wb");
        fwrite(bmp, 1, file_size, fp);
        fclose(fp);
    }

    void check_ciff(const char *file_name, bool expected) {
        unsigned char *buffer;
        unsigned long long size;
        read_ciff(file_name, &buffer, &size);

        CIFF *ciff = ciff_parse(buffer, size);

        if(expected) {
            CPPUNIT_ASSERT_MESSAGE("Success expected", ciff != NULL);

            if(ciff->width > 0 && ciff->height > 0) {
                unsigned char *bmp_bufer;
                unsigned long long bmp_size;
                ciff_to_bmp(ciff, &bmp_bufer, &bmp_size);

                char bmp_file[100] = "";
                strcat(bmp_file, file_name);
                strcat(bmp_file, ".bmp");
                bmp_fo_file(bmp_bufer, bmp_size, bmp_file);

                free(bmp_bufer);
            }
        }
        else {
            CPPUNIT_ASSERT_MESSAGE("Failure expected", ciff == NULL);
        }

        ciff_free(ciff);
        free(buffer);
    }
};