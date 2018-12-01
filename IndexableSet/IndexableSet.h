#ifndef INDEXABLESET_H_
#define INDEXABLESET_H_

#include <functional>
#include <set>
#include <stdexcept>
#include <iterator>
#include <initializer_list>

template <typename T, typename COMPARE=std::less<T>>
class IndexableSet : public std::set<T, COMPARE>
{
	using container = std::set<T, COMPARE>;
	using container::container;
	using size_type = typename std::set<T, COMPARE>::size_type;
	using reference = typename container::reference;
	using const_reference = typename container::const_reference;

public:
	IndexableSet() = default;
	template <typename iter>
	IndexableSet(iter begin, iter end) : container(begin, end){}
	IndexableSet(std::initializer_list<T> list) : container(list){} // @suppress("Non-'explicit' Single Argument Constructor")

	T operator[](int index){
		auto size = this->size();
		if(index < 0){
			index = index + size;
		}
		size_type indexSizeType = static_cast<size_type>(index);
		if(this->empty() || index < 0 || indexSizeType >= size){
			throw std::invalid_argument("index");
		}
		auto iter = this->begin();
		std::advance(iter, indexSizeType);
		return *iter;
	}
};

#endif /* INDEXABLESET_H_ */
