#include<iostream>
using std::cout; using std::endl;

int main () {
    char little_c = 'c';
    char big_c = 'C';
    char three = '3';
    int z_num = 122;
    int diff;

    // cast back and forth, int and char
    cout << little_c << endl;    
    cout << static_cast<int>(little_c) << endl;
    cout << z_num << endl;
    cout << static_cast<char>(z_num) << endl;

    // val of 'c' - 'a' (99 - 97)
    diff = little_c - 'a';       // 2
    cout << diff << endl;

    // val of 'C' - 'A' (67 - 65)
    diff = big_c - 'A';          // 2
    cout << diff << endl;

    // val of '3' - '0' (51 - 48)
    diff = three - '0';         // 3
    cout << diff << endl;

    // order is only sensible within sequence (99 - 65)
    diff = little_c - 'A';     // 34!
    cout << diff << endl;    

    // unicode string literal
    const char* phi  = u8"\u03C6";      // lower case greek phi
    const char* smile = u8"\U0001F607"; // smiley with halo
    cout << phi << endl;
    cout << smile << endl;
}

#include<iostream>
using std::cout; using std::endl; using std::cin;
using std::noskipws;
#include<iomanip>
using std::setw;
#include<cctype>  // character operations

/* 
playing with character functions
counts and exchanges upper and lower
wfp 1/21/17
*/

int main () {
  char C;
  long punc_cnt=0, letter_cnt=0, upper_cnt=0,
       lower_cnt=0, digit_cnt=0, other_cnt=0;

  int shift=-10;
  cin >> noskipws;   // get everything, no separators
  while (cin >> C){  // until EOF
    if ( isalnum(C) ){
      if ( isdigit(C) )
	++digit_cnt;
      else if ( isalpha(C) ){
	++letter_cnt;
	if ( isupper(C) ){
	  ++upper_cnt;
	  C = tolower(C);
	}
	else{
	  ++lower_cnt;
	  C = toupper(C);
	}
      } // of isalpha stuff
    } // of isalnum stuff
    else if ( ispunct(C) )
      ++punc_cnt;
    else
      ++other_cnt;
    cout << static_cast<char>(C - shift);
  } // of while

  int wid=4;
 
  cout << endl;
  cout << "Letter count :" << setw(wid) << letter_cnt << endl;
  cout << "Digit count  :" << setw(wid) << digit_cnt << endl;
  cout << "Lower count  :" << setw(wid) << lower_cnt << endl;
  cout << "Upper count  :" << setw(wid) << upper_cnt << endl;
  cout << "Punct count  :" << setw(wid) << punc_cnt << endl;
  cout << "Other count  :" << setw(wid) << other_cnt << endl;  
} // of main

 #include<iostream>
using std::cout; using std::endl; using std::cin;
using std::boolalpha;
#include<string>
using std::string;

int main (){
    // creating a string, constructors
    string first{'H', 'o', 'm', 'e', 'r'}; // enumerate elements
    string last = "Simpson";
    string copy_last = last;  // copy of last 
    string name;	      // default constructor, empty string
    string a_5(5,'a');	      // char count constructor, "aaaaa"
    string sub_last(last,3,3);// substring constructor, pos 3, len 3, "pso"
    string sub_first(first,1);// substring constructor, pos 1 to end of string
                              // "omer"
    cout << sub_first << ":" << sub_last << endl;

    // access char at index, rvalue
    cout << last[1] << endl;     // i
    cout << last.at(3) << endl;  // p

    // lvalue also
    copy_last[1] = 'o';
    copy_last.at(0) = 'T';
    cout << copy_last << endl; // "Tompson"
    
    // only .at reports error in range
    cout << "Char:" << last[15] << endl;
    // cout << last.at(15) << endl;
}

#include<iostream>
using std::cout; using std::cin; using std::endl;
#include<string>
using std::string;

int main (){
  // input
  string temp1_str, temp2_str, temp3_str;
  getline(cin, temp1_str);       // up to CR/LF    
  cin >> temp2_str >> temp3_str; // up to separator
  cout << temp1_str << " - " << temp2_str
       << " - " << temp3_str << endl;
  
  // more complicated than that when noticed
  cin >> temp1_str;
  cin.ignore(1, '\n');
  getline(cin, temp2_str); // up to CR/LF
  getline(cin, temp3_str);
  cout << temp1_str << " - " << temp2_str
	 << " - " << temp3_str << endl;
}

#include<iostream>
using std::cout; using std::cin; using std::endl;
#include<string>
using std::string;

int main (){
  string first{'H', 'o', 'm', 'e', 'r'}; // enumerate elements
  string last = "Simpson";

  // size
  cout << "last size:" << last.size() << endl;
  cout << "first size:" << first.length() << endl;
  cout << "Max size:" << last.max_size() << endl;

  // front and back
  cout << "final char last:"<< last.back() << endl;
  cout << "initial char first:" << first.front() << endl;
    
  // concatenation, creates new copy
  cout << first + last << endl;
  cout << first + " " + last << endl;
  cout << first + '-' + last << endl;
  // cout << first + 27 + last << endl; // only chars and strings
  
  // counting for i has type string::size_type
  for(int i=0; i<last.size(); ++i)
    cout << last[i]<<", ";
  cout << endl;
  
  // range-based for, chr has type char
  for(auto chr: last)
    cout <<chr<<", ";
  cout << endl;
}


#include<iostream>
using std::cout; using std::endl; using std::boolalpha;
#include<string>
using std::string;

int main (){
  cout << boolalpha;
  string smaller = "aabc";
  string larger = "abcd";
  string shorter = "aab";
  
  cout << (smaller < larger) << endl; // true
  cout << (smaller == larger) << endl; // false
  cout << (shorter < smaller) << endl; // true
  cout << (shorter < "efg") << endl;   // true
  // cout << ("abc" < "aab") << endl; // ???

  // some operations
  cout << smaller.empty() << endl; // false
  smaller.clear();
  cout << smaller.empty() << endl; // true

  cout << larger.back() << endl; // 'd'
  larger.push_back('e');
  cout << larger.back() << endl; // 'e'
  larger.pop_back();
  cout << larger.back() << endl; // 'd'

  // npos
  cout << string::npos << endl; // largest size_t

  // insert
  string temp="a";
  string other="zz";
  temp.insert(0,"xxx");  // literal at 0, "xxxa"
  temp.insert(1, 3,'b'); // 3 'b' at 1,  "xbbbxxa"
  temp.insert(2, other); // string other at 2, "xbzzbbxxa"
  cout << temp << endl;
  
  // append
  temp="a";
  other="zz";
  temp.append("xxx"); // "xxx" appended, "axxx"
  temp.append(3,'b'); // 3 'b' append,  "axxxbbb"
  temp.append(other); // append string other,  "axxxbbbzz"
  cout << temp << endl;
  
  // erase
  temp = "abcdefg";
  temp.erase(2,3); // start at 2, length 3, "abfg"
  temp.erase(2) ;  // default length is to the end, "ab";
  cout << temp << endl;

  // substr, temp unchanged
  temp = "abcdefg";

  // start at 1, len 3, return "bcd"
  string s = temp.substr(1,3);
  cout << s << endl;
  
  // start at 4 to the end, return "efg"
  s = temp.substr(4);
  cout << s << endl;  
}


#include<iostream>
using std::cout; using std::endl; using std::boolalpha;
#include<string>
using std::string;

int main () {
    string s = "a1abcabc123a";
    string sub_s = "abc";
    string::size_type result;
    cout << boolalpha;

    cout << s.find(sub_s) << endl;    // string arg, 2
    cout << s.find(sub_s, 3) << endl; // search in s starting at
                                      // index 3,  5
    cout << s.find('2') << endl;      // character, 9
    result = s.find("abd");           // literal, exach match not
                                      // found returns string::npos
    cout << (result  == string::npos) << endl; // true

    cout << s.rfind(sub_s) <<endl;             // 5
    cout << s.find_last_of(sub_s) <<endl;      // 11
    cout << s.find_first_of(sub_s) <<endl;     // 0
    cout << s.find_first_not_of(sub_s) <<endl; // 1
    cout << s.find_last_not_of(sub_s)<<endl;   // 10

    // find all the 'a's
    result = s.find('a');
    while (result != string::npos){
      cout << "a found at:"<< result << endl;
      result = s.find('a', result+1);
    }


}
   

#include<iostream>
using std::cout; using std::endl; using std::cin;
using std::boolalpha;
#include<string>
using std::string; using std::to_string; using std::stol;

long rev_num(long num){
  string rev = "";
  string str = to_string(num);
  for (int i = str.size()-1 ; i >= 0 ; --i){
    rev += str[i];
  }
  return stol(rev);
} 

bool is_palindrome(long n){
  long rnum = rev_num(n);
  return (n == rnum);
}

bool check_lychrel(long n, long limit){
  long cnt = 0;
  long num = n, rnum = 0;
  string rev_str="";
  while (cnt < limit && (!is_palindrome(num))){
    rnum = rev_num(num);
    num = num + rnum;
    cnt++;
    cout << cnt << ":" << num << endl;
  }
  cout << endl;
  return cnt==limit;
}

int main() {
    cout << boolalpha;
    long num;
    long limit = 40;
    cin >> num;
    cout << "checking "<< num << endl;
    bool result = check_lychrel(num, limit);
    if (result)
      cout << num << " is a lychrel number " << endl;
    else
      cout << num << " is NOT a lychrel number " << endl;
}