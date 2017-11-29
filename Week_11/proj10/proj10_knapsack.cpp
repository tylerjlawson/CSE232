//Project 10 Knapsack methods and functions
#include "proj10_knapsack.h"
#include<sstream>//for removing the comma off the end
using std::ostringstream;
#include<string>
using std::string; using std::stol;
#include<fstream>//files
using std::ifstream;
#include<stdexcept>//error
using std::runtime_error;
#include<vector>
using std::vector;
#include<algorithm>//for sorting the vector 
using std::sort;

Knapsack::Knapsack(size_t max){
	//constructor for one input
	weight_limit_ = max;
	capacity_ = 10;
	size_ = 0;
	Package *temp = new Package[max];
	data_ = temp;
}

Knapsack::Knapsack(size_t wlimit, size_t cap){
	//constructor for two inputs
	weight_limit_ = wlimit;
	capacity_ = cap;
	size_ = 0;
	Package *temp = new Package[cap];
	data_ = temp;
}

long Knapsack::capacity() const{//getter for capacity
	return capacity_;
}

long Knapsack::size() const{//getter of size
	return size_;
}

long Knapsack::weight_limit() const{//getter of weight limit
	return weight_limit_;
}

Knapsack::Knapsack(const Knapsack& k){//copier for knapsacks
	weight_limit_ = k.weight_limit_;
	capacity_ = k.capacity_;
	size_ = k.size_;
	Package *temp = new Package[capacity_];//needs new one to avoid memory location error
	for ( size_t x = 0; x < size_; x++){
		temp[x] = k.data_[x];
	}
	delete [] data_;
	data_ = temp;
}

Knapsack::~Knapsack(){//destructor
	size_ = 0;
	capacity_ = 0;
	weight_limit_ = 0;
	delete [] data_;
}

bool Knapsack::empty() const{//returns wheter or not it is empty
	if (size_)
		return false;
	return true;
}

long Knapsack::weight() const{
	//adds up the sum of weights in the knapsack
	long weight = 0;
	for (size_t x = 0; x < size_; x++){//for all packages
		weight+=data_[x].weight_;
	}
	return weight;
}

long Knapsack::priority() const{
	//adds up all of the priorities
	long priority = 0;
	for (size_t x = 0; x < size_; x++){//for all packages
		priority+=data_[x].priority_;
	}
	return priority;
}

Knapsack& Knapsack::operator=(const Knapsack k){
	//assignment operator
	weight_limit_ = k.weight_limit_;
	capacity_ = k.capacity_;
	size_ = k.size_;
	Package *temp = new Package[capacity_];
	for ( size_t x = 0; x < size_; x++){
		temp[x] = k.data_[x];
	}
	delete [] data_;
	data_ = temp;
	return *this;
	//has a return statement but otherwise is very similar to copy
}

bool Knapsack::add(const Package& p){
	//adds a package to the knapsack if it fits
	//resizes memory if it needs to
	if ((this->weight()+p.weight_) > weight_limit_){
		//if it won't fit return false
		return 0;
	}
	else if (size_==capacity_){//resizing
		capacity_*=2;
		Package *temp = new Package[capacity_];
		for ( size_t x = 0; x < size_; x++){
			temp[x] = data_[x];
		}
		delete [] data_;
		data_ = temp;
	}
	data_[size_]=p;//adding
	size_++;

	return 1;//true
}

ostream& operator<<(ostream& out, Knapsack &k){
	//nicely puts knapsack into output
	ostringstream ss;
	for (size_t x = 0; x < k.size_; x++){
		ss << k.data_[x] << ", ";//builds stringstream
	}
	string str1 = ss.str();//takes it as a string
	str1 = str1.substr(0,str1.size()-2);//cuts off final comma
	out << str1;//sends it to actual ostream
	return out;
}

void solve_KS(string fstring, Knapsack& k){
	//solves the knapsack problem, sorta
	//prioritizes it with our provided algorithm
	ifstream file(fstring);//opens file
	string file_element_str;
	if( file.is_open()){//if open
		vector<Package> vp;//to store packages for sorting
		long weight=0;
		long priority=0;
		while (file >> file_element_str){
			weight = stol(file_element_str);//first is a weight
    		file >> file_element_str;
    		priority = stol(file_element_str);//second element is priority
    		vp.push_back(Package(weight, priority));//adds to vector
		}
		sort(vp.begin(), vp.end(), package_compare);
		//sorts with the function for package sorting
		bool b=true;
		for (size_t x = 0; x < vp.size(); x++){
			b=k.add(vp[x]);//adds sorted packages until it cant no more
			if(b==0){
				break;
			}
		}
		file.close();//closes file for good practice
	}
	else{//when not open throw error
		throw runtime_error("File did not open");
	}
}