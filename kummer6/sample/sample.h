/*
    Created by Alejandro Daniel Noel on 30/10/2018.
*/

#include <vector>
#include <list>

template<typename T>
class CategorisedList 
{
	public:
		class iterator;
		CategorisedList() : CategorisedList(1) {};

		explicit CategorisedList(unsigned int category_count)
		{
			// Initialise the data structure
			for (int i = 0; i < category_count; i++)
				data.emplace_back(std::list<T>());
		}

		void push_back(T value, unsigned int category) 
		{
			data[category].push_back(value);
		}

		void clear() 
		{
			for (auto &category: data) category.clear();
		}

		/**
		 * Deletes the object pointed by the iterator and returns an iterator
		 * at the next object.
		 */
		iterator erase(iterator it) 
		{
			data[it.get_category()].erase(it.element);
			++it;
			return it;
		}

		bool empty() const 
		{
			for (auto &category : data) 
			{
				if (!category.empty()) return false;
			}
			return true;
		}

		T& front() 
		{
			return data.front().front();
		}

		size_t size() const 
		{
			size_t sum = 0;
			for (auto &category: data) sum += category.size();
			return sum;
		}

	private:
		std::vector<std::list<T>> data;

	public:
		class iterator
		{
			private:
				typedef typename std::list<T>::iterator ListIT;
				friend class CategorisedList;
				CategorisedList* cl;
				size_t category;
				ListIT element;

				class postinc_return
				{
					private:
						T value;
					public:
						postinc_return(T value_)
						{
							value = std::move(value_);
						}

						T operator*()
						{
							return std::move(value);
						}
				};

			public:
				using value_type = T;
				using reference = T;
				using iterator_category=std::input_iterator_tag;
				using pointer = T*;
				using difference_type = void;

				explicit iterator(CategorisedList* cl): cl(cl) 
				{
					if (cl) 
					{
						category = 0;
						element = cl->data.begin()->begin();
					}
				}

				value_type operator*() const
				{
					return *element;
				}

				value_type * operator->() const
				{
					return &(*element);
				}

				iterator& operator++()
				{
					if (cl) 
					{   // Only increment if it didn't reach the end
						element++;
						// When the iterator reaches the end of a category, jumps to the start of the next
						if (element == cl->data[category].end()) 
						{
							// Only if this is not the last category
							if (category == cl->data.size() - 1) 
							{
								cl = nullptr;
							}
							else 
							{
								category++;
								element = cl->data.at(category).begin();
							}
						}
					}
					return *this;
				}

				postinc_return operator++(int)
				{
					postinc_return temp(**this);
					++*this;
					return temp;
				}

				friend bool operator==(iterator const& lhs,iterator const& rhs)
				{
					if (!lhs.cl || !rhs.cl) return lhs.cl == rhs.cl;   // If they are end iterators, compare that they both are at the end
					else return lhs.element==rhs.element;   // Else compare that they both point to the same element
				}

				friend bool operator!=(iterator const& lhs,iterator const& rhs)
				{
					return !(lhs==rhs);
				}

				size_t get_category() 
				{
					return category;
				}
				
		};

		iterator begin() 
		{
			return iterator(this);
		}

		iterator end() 
		{
			return iterator(nullptr);
		}
};