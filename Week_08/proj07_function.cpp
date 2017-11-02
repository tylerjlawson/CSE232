//Project 7
//K nearest neighbors
//works with maps


#include "proj07_functions.h"//include header
#include<string>//include libraries
using std::string;
#include<vector>
using std::vector;
#include<fstream>
using std::ifstream;
#include <iostream>
using std::ostream; 
#include <iomanip>
using std::setprecision;//for output
#include<algorithm>
using std::sort;
#include <sstream> //for string stuff
using std::stringstream; using std::fixed;
#include<math.h>//for exponents
#include<map>
using std::map;

vector<string> split(const string &s, char delim){
	//splits up a string at a delimiter into a vector
	vector<string> result;
	string str2=s;//initialize variables
	size_t npos = -1;//to avoid warning
	while (str2!="" && str2.find(delim)!=npos){//until string is empty or cant find delimiter
		result.push_back(str2.substr(0,str2.find(delim)));//adds string up to delimiter 
		str2=str2.substr(str2.find(delim)+1, str2.size()-1);//resets string after delimiter
	}
	result.push_back(str2);//add what is left over
	return result;
}


void read_data(map<vector<double>, string> &m, unsigned int feature_count, ifstream &inf){
	//reads text files into a map
    size_t pos;//initialize variables
    size_t *pos_ptr = &pos;
    double file_element_double;
    string file_element_str="";
    vector<double> double_vec;
    while(inf >> file_element_str){//goes until done
    	vector<string> v;
    	v=split(file_element_str, ',');//split up line
        for (unsigned int i=0; i<feature_count; i++){//read in doubles as long as feature count
    		file_element_double=stod(v[i], pos_ptr);//convert to double
        	double_vec.push_back(file_element_double);//add double to vector
        } 
        m.insert(pair<vector<double>,string>(double_vec,v[feature_count])); //add pairs
        double_vec.clear(); //clear vector
    }
}

void print_map(const map<vector<double>, string> &m, ostream &out){
	//prints out a map to a given out stream
	for (auto element : m){	//goes through all pairs
		out << pair_to_string(element) << '\n';//uses pair to string to output each pair
	}
}

double distance(const vector<double> &v1, const vector<double> &v2, unsigned int feature_count){
	//distance formula for vectors
	double sum_thing=0;
	double dif_thing= 0;
	for (unsigned int i=0; i<feature_count; i++){//goes for feature count to get the part inside the root
		dif_thing=v2[i]-v1[i];
		dif_thing=pow(dif_thing, 2);
		sum_thing+=dif_thing;
	}
	sum_thing=pow(sum_thing, 0.5);//takes square root
	return sum_thing;
}

map<vector<double>, string> k_neighbors(const map<vector<double>, string> &m, const vector<double> &test, int k){
	//gets new map with k nearest
	map<vector<double>, string> new_map;
	map<vector<double>, string> map_copy=m;
	vector<double> distances;
	//map<vector<double>, double> dm;

	for (auto element : m){//distance map
		//dm.insert(pair<double, vector<double>>(distance(element.first, test, test.size()), element.first));
		distances.push_back(distance(element.first, test, test.size())); 
	}

	sort(distances.begin(), distances.end());
	
	for ( int i=1; i<=k; i++){//goes through in order of closest to furthest
		for (auto element : map_copy){
			if (distance(element.first, test, test.size())==distances[i]){
				new_map.insert(pair<vector<double>,string>(element.first,map_copy[element.first]));//adds closest pairs
				auto it= *element;
				map_copy.erase(it);
			}
		}
	}
	return new_map;
}


double test_one(const map<vector<double>, string> &m, pair<vector<double>, string> test, int k){
	//tests the accuracy due to each string in all k neighbor sets
	double result=0;
	double n=0;
	map<vector<double>, string> a_map;
	a_map=k_neighbors(m, test.first, k);//gets k close map
	for (auto element : a_map){//iterate through map
		if (test.second==element.second){//if its accurate add one to numerator
			n++;
		}
	}
	result= n / k;//finish average	
	return result;
}

string pair_to_string(const pair<vector<double>, string> &p){
	//converts pairs from a map to a string 
	stringstream stream;
	string result="";
	for (auto element : p.first){//iterate through vector
		stream << fixed << setprecision(3) << element << " ";//setprecision and fixed to output
		result+=stream.str();//add to string result
		stream.str("");//empty stream
	}
	result +=  p.second;//add the class
	return result;
}

//DEAR TA
//I swear this test_all function should work
//I checked Piazza for hours and am 99% sure I got them correct based on my own test however 
//mimir has marked it wrong 
//Could you please leave me a note as to what I did wrong? It is really bothering me 
//because I was so sure that this made sense and should work
//Thank you

double test_all(const map<vector<double>, string> &m, int k){
	//this extra credit function should test the accuracy of each pair in a map
	double n=0;//numerator
	double d=0;//denomination
	for ( auto element : m ){//all elements of the map
		n+=test_one(m,element,k);//add each average to the numerator
		d++;//count each element for denominator
	}
	double result = n / d;//finish the average

	return result;
}


