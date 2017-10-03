// Project 4
// Drome tester
// take string and base then return results of each test

#include<iostream>
using std::cout; using std::cin; using std::endl; using std::boolalpha;
#include<string>
using std::string;
// meta, strictly increase
// plain, non-strictly increase
// kata, strictly decrease
// nialp, non-strictly decrease
// non, none of the above

const string base_vals = "0123456789abcdefghijklmnopqrstuvwxyz";

bool metadrome(string n, long base) {
  //test if it is a metadrome or not
  long length=0;
  bool result=true;
  length=n.length();//length of input
 
  for (int i=0; i < length-1; i++) {//iterate through string
    
    if ((base_vals.find(n[i])!=(base_vals.find(n[i+1])-1)) || (base_vals.find(n[i]) > base)){
      //if statement for test
      result=false;
      break;
    }
  }
  return result;
}

bool plaindrome(string n, long base){
  //test if plaindrome
  bool result=true;
  long length=n.length();//get length of input
  for (int i=0; i < length-1; i++) {
    //iterate through input
    if (((base_vals.find(n[i])!=(base_vals.find(n[i+1])-1)) && (n[i])!=(n[i+1]))  || (base_vals.find(n[i]) > base)){
      //if statement to test if it breaks
      result= false;
      break;
    }
  }
  return result;
}

bool katadrome(string n, long base) {
  //test if katadrome
  long length=0;
  bool result=true;
  length=n.length();//length of input
  
  for (int i=0; i < length-1; i++) {
    //iterate through input
    if ((base_vals.find(n[i])!=(base_vals.find(n[i+1])+1)) || (base_vals.find(n[i]) > (base))){
      //test if it breaks
      result=false;
      break;
    }
  }
  return result;
}

bool nialpdrome(string n, long base){
  //test if it is a nialpdrome in the base
  bool result=true;
  long length=n.length();//get length
  for (int i=0; i < length-1; i++) {
    //iterate through input
    if (((base_vals.find(n[i])!=(base_vals.find(n[i+1])+1)) && (n[i])!=(n[i+1]))  || (base_vals.find(n[i]) > base)){
      //test if it breaks
      result= false;
      break;
    }
  }
  return result;
}

string classify(string n, long base){
  //function to return what type of drome the input is
  if (metadrome (n, base)){
    return "metadrome";
  }
  if (plaindrome(n, base)){
    return "plaindrome";
  }
  if (katadrome(n, base)){
    return "katadrome";
  }
  if (nialpdrome(n, base)){
    return "nialpdrome";
  }
  return "nondrome";//if all others fail it will return nondrome
}

int main (){
  //main function
  string num;
  long base;
  cout << boolalpha;
  cin >> num >> base;
  cout << metadrome (num, base) << " "
       << plaindrome (num, base) << " "
       << katadrome (num, base) << " "
       << nialpdrome (num, base) << " "
       << classify(num, base) << endl;
}
    


