#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "IndexableSet.h"
#include <string>

void positivIndexTest() {
	IndexableSet<std::string> mySet { };
	mySet.insert("a first");
	mySet.insert("b second");
	mySet.insert("d forth");
	mySet.insert("c third");
	ASSERT_EQUAL(std::string { "c third" }, mySet[2]);
}

void negativeIndexTest() {
	IndexableSet<std::string> mySet { };
	mySet.insert("a first");
	mySet.insert("b second");
	mySet.insert("d forth");
	mySet.insert("c third");
	ASSERT_EQUAL(std::string { "d forth" }, mySet[-1]);
}

void highNegativeIndexThrowsTest() {
	IndexableSet<std::string> mySet { };
	ASSERT_THROWS(mySet[1], std::invalid_argument);
}

void intMaxIndexThrowsTest(){
	IndexableSet<std::string> mySet{};
	ASSERT_THROWS(mySet[INT_MAX], std::invalid_argument);
}

void intMinIndexThrowsTest(){
	IndexableSet<std::string> mySet{};
	ASSERT_THROWS(mySet[INT_MIN], std::invalid_argument);
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	s.push_back(CUTE(highNegativeIndexThrowsTest));
	s.push_back(CUTE(negativeIndexTest));
	s.push_back(CUTE(positivIndexTest));
	s.push_back(CUTE(intMaxIndexThrowsTest));
	s.push_back(CUTE(intMinIndexThrowsTest));

	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
	return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
