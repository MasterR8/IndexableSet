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

	T at(int index) const {
		auto size = this->size();
		if(index < 0){
			index = index + size;
		}
		size_type indexSizeType = static_cast<size_type>(index);
		if(index < 0 || indexSizeType >= size){
			throw std::out_of_range("index");
		}
		if(indexSizeType < this->size()/2){
			auto iter = this->begin();
			std::advance(iter, indexSizeType);
			return *iter;
		} else {
			auto iter = this->rbegin();
			std::advance(iter, indexSizeType);
			return *iter;
		}
	}

	T operator[](int index) const {
		return this->at(index);
	}

	T front() const {
		return this->at(0);
	}

	T back() const {
		return this->at(-1);
	}
};

#endif /* INDEXABLESET_H_ */
