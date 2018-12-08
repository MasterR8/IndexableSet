#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "IndexableSet.h"

#include <algorithm>

#include <cctype>
#include <string>
#include <vector>

void positivIndexTest() {
	IndexableSet<std::string> mySet { };
	mySet.insert("a first");
	mySet.insert("b second");
	mySet.insert("d forth");
	mySet.insert("c third");
	ASSERT_EQUAL(std::string { "c third" }, mySet[2]);
}

void positivIndexAtTest() {
	IndexableSet<std::string> mySet { };
	mySet.insert("a first");
	mySet.insert("b second");
	mySet.insert("d forth");
	mySet.insert("c third");
	ASSERT_EQUAL(std::string { "c third" }, mySet.at(2));
}

void negativeIndexTest() {
	IndexableSet<std::string> mySet { };
	mySet.insert("a first");
	mySet.insert("b second");
	mySet.insert("d forth");
	mySet.insert("c third");
	ASSERT_EQUAL(std::string { "d forth" }, mySet[-1]);
}

void negativeIndexAtTest() {
	IndexableSet<std::string> mySet { };
	mySet.insert("a first");
	mySet.insert("b second");
	mySet.insert("d forth");
	mySet.insert("c third");
	ASSERT_EQUAL(std::string { "d forth" }, mySet.at(-1));
}

void firstNegativeEqualsLastPositiveTest(){
	IndexableSet<std::string> mySet { };
	mySet.insert("a first");
	mySet.insert("b second");
	mySet.insert("d forth");
	mySet.insert("c third");
	ASSERT_EQUAL(mySet.at(mySet.size()-1), mySet.at(-1));
}

void lastNegativeEqualsFirstPositiveTest(){
	IndexableSet<std::string> mySet { };
	mySet.insert("a first");
	mySet.insert("b second");
	mySet.insert("d forth");
	mySet.insert("c third");
	ASSERT_EQUAL(mySet.at(0), mySet.at(-mySet.size()));
}

void highNegativeIndexThrowsTest() {
	IndexableSet<std::string> mySet { };
	ASSERT_THROWS(mySet[1], std::out_of_range);
}

void intMaxIndexThrowsTest(){
	IndexableSet<std::string> mySet{};
	ASSERT_THROWS(mySet[INT_MAX], std::out_of_range);
}

void intMinIndexThrowsTest(){
	IndexableSet<std::string> mySet{};
	ASSERT_THROWS(mySet[INT_MIN], std::out_of_range);
}

void createWithIteratorsTest(){
	std::vector<int> vector{2,3,4,5,6};
	IndexableSet<int> mySet {vector.begin(), vector.end()};
	ASSERT_EQUAL(5, mySet.size());
}

void frontEqualsFirstPositiveTest(){
	IndexableSet<std::string> mySet { };
	mySet.insert("a first");
	mySet.insert("b second");
	mySet.insert("d forth");
	mySet.insert("c third");
	ASSERT_EQUAL(mySet.at(0), mySet.front());
}

void backEqualsFirstNegativeTest(){
	IndexableSet<std::string> mySet { };
	mySet.insert("a first");
	mySet.insert("b second");
	mySet.insert("d forth");
	mySet.insert("c third");
	ASSERT_EQUAL(mySet.at(-1), mySet.back());
}

void caseLessCompareTest(){
	struct caseLessComp{
		int operator ()(std::string const & first, std::string const & second) const{
			std::string firstLower{};
			firstLower.reserve(first.size());
			std::transform(
					first.begin(),
					first.end(),
					firstLower.begin(),
					[](unsigned char c){
						return std::tolower(c);
			});
			std::string secondLower{};
			secondLower.reserve(second.size());
			std::transform(
					second.begin(),
					second.end(),
					secondLower.begin(),
					[](unsigned char c){
						return std::tolower(c);
			});
			return firstLower.compare(secondLower);
		}
	};

	IndexableSet<std::string, caseLessComp> mySet { };
	mySet.insert("A first");
	mySet.insert("b second");
	mySet.insert("d forth");
	mySet.insert("C third");
	ASSERT_EQUAL("A first", mySet.front());
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	s.push_back(CUTE(highNegativeIndexThrowsTest));
	s.push_back(CUTE(negativeIndexTest));
	s.push_back(CUTE(negativeIndexAtTest));
	s.push_back(CUTE(positivIndexTest));
	s.push_back(CUTE(positivIndexAtTest));
	s.push_back(CUTE(firstNegativeEqualsLastPositiveTest));
	s.push_back(CUTE(lastNegativeEqualsFirstPositiveTest));
	s.push_back(CUTE(intMaxIndexThrowsTest));
	s.push_back(CUTE(intMinIndexThrowsTest));
	s.push_back(CUTE(createWithIteratorsTest));
	s.push_back(CUTE(frontEqualsFirstPositiveTest));
	s.push_back(CUTE(backEqualsFirstNegativeTest));
	s.push_back(CUTE(caseLessCompareTest));

	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
	return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
