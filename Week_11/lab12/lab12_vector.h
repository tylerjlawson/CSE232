#ifndef VECTOR
#define VECTOR

#include<utility>
using std::initializer_list;
#include<iostream>
#include<stdexcept>
using std::range_error;


namespace student{
	template<typename T>
	class vector{
		private:
			T *data_ = new T[10];//default capacity 10
			size_t capacity_ = 10;
			size_t size_ = 0; //items in vector
		public:
			vector() = default;
			vector(size_t capacity){
				capacity_ = capacity;
				size_ = 0;
				T *temp = new T[capacity];
				data_ = temp;
			}
			vector(initializer_list<T> iList){
				capacity_ = iList.size();
				size_ = capacity_;
				T *temp = new T[capacity_];
				data_ = temp;
				for ( size_t x = 0; x < size_; x++){
					data_[x] = *(iList.begin() + x);
				}
			}

			size_t capacity(){
				return capacity_;
			}
			size_t size(){
				return size_;
			}

			void push_back(T val){
				if (size_ == capacity_){
					capacity_*=2;
					T *temp = new T[capacity_];
					for ( size_t x = 0; x < size_; x++){
						temp[x] = data_[x];
					}
					delete [] data_;
					data_ = temp;
				}
				data_[size_] = val;
				size_++;
			}
			T& operator[](size_t val){
				if ( val >= size_ ){
					throw range_error("Out of Range");
				}
				else{
					return data_[val];
				}
			}
			T& front(){
				if ( size_ )
					return data_[0];
				else
					throw range_error("Data is empty");
			}
			T& back(){
				if ( size_ )
					return data_[size_-1];
				else
					throw range_error("Data is empty");
			}
			vector(vector& v){
				size_ = v.size();
				capacity_ = v.capacity();
				T *temp = new T[capacity_];
				for ( size_t x = 0; x < size_; x++){
					temp[x] = v.data_[x];
				}
				delete [] data_;
				data_ = temp;

			}
			vector& operator=(vector& v){
				size_ = v.size();
				capacity_ = v.capacity();
				T *temp = new T[capacity_];
				for ( size_t x = 0; x < size_; x++){
					temp[x] = v.data_[x];
				}
				delete [] data_;
				data_ = temp;
				return *this;
			}
			~vector(){
				size_ = 0;
				capacity_ = 0;
				delete [] data_;
			}
			void clear(){
				size_ = 0;
				capacity_ = 0;
				delete [] data_;
			}
			T pop_back(){
				
				T result = data_[size_-1];
				size_--;
				if ( capacity_ >= (2*size_)){
					capacity_/=2;
				}
				return result;
			}

			


		
	};
}


#endif