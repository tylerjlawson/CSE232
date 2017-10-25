/*
Project 6
Cellular Automation
use a variety of functions in order to automate vectors given a rule number
also practiced reading in from file and assigning to a vector
*/

#include<string>
using std::string; using std::getline; using std::stol; using std::to_string;
//use to string to convert to string and add to strings
#include<vector>
using std::vector;
#include<algorithm>
using std::transform;
#include<iterator>
using std::ostream_iterator;
#include<sstream>
using std::ostringstream;
#include<math.h>//for exponents of 2
#include <fstream>//for reading from a file
using std::ifstream;

// any other includes you need

#include "proj06_functions.h"

// your functions after this

// a freebie!
// takes in a vector of 0,1
// outputs a string of '_' or '*'
string pretty_print(vector<int> & v){
  ostringstream oss;
  transform(v.begin(), v.end(), ostream_iterator<char>(oss),
	    [] (int i) {
	      return (i==0) ? '_' : '*';
	    }
	    );
    return oss.str();
}

string to_binary(int num){
    //function converts decimal numbers to binary form
    string result="";
    int bit=0;
    if ((num >=0) && (num <=255)){//error check
        for (int i=0; i <= 7; i++){//iterates 8 times so the binary is 8 bit
            bit = num%2;//will be 0 or 1
            num/=2;//new number to work with
            result = to_string(bit) + result;//adds the bit to the beginning of the string
        }
        return result;
    }
    else{
        return to_binary(0);//error case
    }
}



vector<int> one_iteration(const vector<int> &v, const string &rule_binary_string){
    //this function will go through the first iteration accourding to wolframs automata
    vector<int> result;//initialize working vectors
    vector<int> temp;

    temp.push_back(0);//case for first spot of vector
    temp.push_back(v[0]);
    temp.push_back(v[1]);
    result.push_back(next_val(temp, rule_binary_string));
    temp.clear();//empties the working vector

    for (int i=1; i<v.size()-1; i++){//iterates through middle of the vector to 
                                    //get their next values
        temp.push_back(v[i-1]);
        temp.push_back(v[i]);
        temp.push_back(v[i+1]);
        result.push_back(next_val(temp, rule_binary_string));
        temp.clear();
    }

    temp.push_back(v[v.size()-2]);//case for last spot of vector
    temp.push_back(v[v.size()-1]);
    temp.push_back(0);
    result.push_back(next_val(temp, rule_binary_string));
    temp.clear();

    return result;
}

string vector_to_string(const vector<int> &v){
    //this will convert a simple integer based vector to a string
    string result="";//initialize the string that will later be returned
    for (int i=0; i < v.size(); i++){//iterate through vector
        result+=to_string(v[i]);//add the elements
        result+=",";//add commas for readability
    }
    return result.substr(0, result.length()-1);//remove the last comma
}

void read_vector(vector<int> &v, string fstring){
    //takes a file and reads it into a vector
    string file_element_str;
    long file_element_long;//initialize variables
    size_t pos;
    size_t *pos_ptr = &pos;
    ifstream in_file;
    in_file.open(fstring);//open file

    if (v.empty()){//error check
        while(in_file >> file_element_str){//goes until done
            file_element_long = stol(file_element_str, pos_ptr);//gets each converted value
            v.push_back(file_element_long);//adds the value
        }
    }
    in_file.close();//close file for good practice
}

int next_val(const vector<int> &v, const string &rule_binary_string){
    //function finds the next value for a given vector of 3 numbers
    int count=2;//initialize variables
    int num=0;
    for (auto element : v){//get the value of the vector
        if (element)
        {
            num+=pow(2, count);
        }
        count-=1;
    }
    int result=0;
    size_t size = rule_binary_string.size();//use the size of the binary rule
    int spot = size-num-1;//calculate real index
    if (rule_binary_string.at(spot)!='0'){//test the value in the rule
        result=1;
    }
    return result;
}