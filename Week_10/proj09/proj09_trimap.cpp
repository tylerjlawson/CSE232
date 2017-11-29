#include "proj09_trimap.h"
#include <string>
using std::string;
#include<sstream>//for building string outputs
using std::ostringstream;
#include<initializer_list>
using std::initializer_list;
#include<iostream>
using std::endl; using std::cout;
#include<algorithm>
using std::upper_bound;
#include<vector>
using std::vector;


ostream& operator<<(ostream& os, const Element& e){
	//this takes an element and sends it to an out string
	os << e.key_ << ":" << e.value_ << ":" << e.index_;
	return os;
}

TriMap::TriMap(const Element& e){
	//constructs a trimap from a single element
	vec_.push_back(e);//adds to back of vector
} 

TriMap::TriMap(initializer_list<Element> l){
	//this constructs a trimap from an initilizer list
	for (auto e : l){
		vec_.push_back(e);
	}
}

ostream& operator<<(ostream& os, const TriMap& tm){
	//takes a trimap and sends it to an ostream
	ostringstream oss;//use string stream so I can remove last comma
	for (auto e : tm.vec_){
		oss << e << ", ";
	}
	string str = oss.str();
	str = str.substr(0,str.size()-2);//remove last comma
	os << str;//send to ostream
	return os;
}

size_t TriMap::size(){//gets size of trimap
	return vec_.size();
}

bool TriMap::insert(string key, string value){
	//inserts a new key into map if not already in map
	bool result=1;
	for ( auto e : vec_){//checks if key in map
		if (key == e.key_){
			result=0;
		}
	}
	if (result==1){//if not in map, insert
		long index = vec_.size();
		for ( long count=0; count < index; count++ ){//finds space in order to insert
			if (key < vec_[count].key_){//inserts
				vec_.insert(vec_.begin()+count, Element(key, value, index));
				break;//ends after inserted
			}
		}
		unsigned int z = index;//to avoid warning
		if (z == vec_.size()){//adds if key is last ordered key
			vec_.push_back(Element(key, value, index));
		}
	}
	return result;
}

bool TriMap::remove(string key){
	//returns boolean of the existence f the key in the map
	//removes key if it is in the map
	bool result = 0;
	size_t z=0;
	for ( size_t x=0; x < vec_.size(); x++){
		//finds the key
		if (key == vec_[x].key_){
			result=1;
			z = vec_[x].index_;
			vec_.erase(vec_.begin() + x);//removes element at key
		}
	}
	if (result==1){//adjusts the indexes if necessary
		for ( size_t j=0; j < vec_.size(); j++){
			if (vec_[j].index_ > z){
				vec_[j].index_ -= 1;
			}
		}
	}
	return result;
}



Element* TriMap::find_key(const string& key){
	//method finds the key pointer in the map using a binary search
	vector<Element>::iterator pos;
	bool result=0;
	for ( auto e : vec_){//checks the existence using linear search
		if (key == e.key_){
			result=1;
			break;
		}
	}
	
	if(result){//if it is in there, find the pointer
	    Element e2(key, "t", 1);//new element to use as a test
		pos = upper_bound(vec_.begin(), vec_.end(), e2, 
			[](Element e2, Element e)
			{return e2.key_ < e.key_;})-1;//uses upper bound to search and 
							//utilizes a lambda function to help the search
		return &(*pos);//returns the pointer when there is one
	}
    return nullptr;//the return if no pointer was found
}

Element* TriMap::find_value(const string& val){
	//searches map for a value
	string str="";
	for (auto e : vec_){//search for value
		if ( val == e.value_){
			str=e.key_;
		}
	}
	if (str!=""){//if found, return the element*
		return find_key(str);
	}
	return nullptr;//if not found 
}

Element* TriMap::find_index(size_t index){
	//searches map for an index
	string str="";
	for (auto e : vec_){//searches map for existence
		if ( index == e.index_){
			str=e.key_;
		}
	}
	if (str!=""){//if its in there return the element*
		return find_key(str);
	}
	return nullptr;//if not found
}
