add_test( ContenderTest.ValidConstructorTest /mnt/c/Users/atlas1323/CLionProjects/SymReg/cmake-build-debug/gtests/ContenderTest [==[--gtest_filter=ContenderTest.ValidConstructorTest]==] --gtest_also_run_disabled_tests)
set_tests_properties( ContenderTest.ValidConstructorTest PROPERTIES WORKING_DIRECTORY /mnt/c/Users/atlas1323/CLionProjects/SymReg/cmake-build-debug/gtests)
add_test( ContenderTest.EqParseTest /mnt/c/Users/atlas1323/CLionProjects/SymReg/cmake-build-debug/gtests/ContenderTest [==[--gtest_filter=ContenderTest.EqParseTest]==] --gtest_also_run_disabled_tests)
set_tests_properties( ContenderTest.EqParseTest PROPERTIES WORKING_DIRECTORY /mnt/c/Users/atlas1323/CLionProjects/SymReg/cmake-build-debug/gtests)
add_test( ContenderTest.ErrorTest /mnt/c/Users/atlas1323/CLionProjects/SymReg/cmake-build-debug/gtests/ContenderTest [==[--gtest_filter=ContenderTest.ErrorTest]==] --gtest_also_run_disabled_tests)
set_tests_properties( ContenderTest.ErrorTest PROPERTIES WORKING_DIRECTORY /mnt/c/Users/atlas1323/CLionProjects/SymReg/cmake-build-debug/gtests)
add_test( ContenderTest.ToStringTest /mnt/c/Users/atlas1323/CLionProjects/SymReg/cmake-build-debug/gtests/ContenderTest [==[--gtest_filter=ContenderTest.ToStringTest]==] --gtest_also_run_disabled_tests)
set_tests_properties( ContenderTest.ToStringTest PROPERTIES WORKING_DIRECTORY /mnt/c/Users/atlas1323/CLionProjects/SymReg/cmake-build-debug/gtests)
set( ContenderTest_TESTS ContenderTest.ValidConstructorTest ContenderTest.EqParseTest ContenderTest.ErrorTest ContenderTest.ToStringTest)
