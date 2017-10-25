// beaufort cipher, http://practicalcryptography.com/ciphers/classical-era/beaufort/
// Project 5: Ciphers
// Section 06

#include<iostream>//for standard input and output
using std::cout; using std::cin; using std::endl;
#include<string>//for using strings
using std::string; 
#include <algorithm>//for using the rotate function
using std::rotate;
#include <cctype>//for using islower()


const string alphabet = "abcdefghijklmnopqrstuvwxyz";

string rotate_left(long amount, string str){
  //more or less a caesar cypher
  //shifts the string by a given amount
  if (amount>0){
    rotate(str.begin(),str.begin()+amount,str.end());
    //uses rotate function in order to do the shift
  }
  return str;
}

char beaufort_letter(char plain_letter, char key_letter){
  //finds the corresponding letter for the beaufort cypher 
  //when it is given a key letter to go off of
  char result;
  if (islower(plain_letter) && islower(key_letter)){
    //error check to make sure lower case letters
    long shift=plain_letter-'a';//find its index
    string new_abc=rotate_left(shift, alphabet);
    //get shifted string
    long index=new_abc.find(key_letter);
    //find the letter
    result=alphabet[index];
    //set the result as the letter
  }
  else{
    result=plain_letter;//error case
  }
  return result;
}

char vigenere_letter(char plain_letter, char key_letter){
  //finds the corresponding letter for the vigenere cypher 
  //when it is given a key letter to go off of
  char result;
  if (islower(plain_letter) && islower(key_letter)){
    //error check to make sure lower case letters
    long shift=plain_letter-'a';//find its index
    string new_abc=rotate_left(shift, alphabet);
    //get shifted string
    long index= alphabet.find(key_letter);
    //find the corresponding letter
    result=new_abc[index];//set result as what I found
  }
  else{
    result=plain_letter;//error case
  }
  return result;
}

string encode_beaufort(string plain_text, string key){
  //function will encode a given string with the beaufort cypher method
  string result, new_text;//instantiate strings
  for (char a : plain_text){
    //removes all characters that are not lowercase letters from the input
    if (islower(a)){
      new_text+=a;
    }
  }
  plain_text=new_text;//reassigns string to the plain text variable
  if (key.size() < plain_text.size()){
    //repeat first letters, for ex (fredfr)
    unsigned int x=0;
    while (key.size() < plain_text.size()){
      //loop to repeat letters in key until it is long enough
      key+=(key[x]);
      x++;
      if(x == key.size()){//repeats if at the end of the key
        x=0;
      }
    }
  }
  for (unsigned int i=0; i < plain_text.size(); i++){
    //loop through plain text to encode it
    result+=beaufort_letter(plain_text[i], key[i]);
  }
  return result;
}

string encode_vigenere(string plain_text, string key){
  //function will encode a given string with the vigenere cypher method
  string result, new_text;//instantiate strings
  for (char a : plain_text){
    //removes all characters that are not lowercase letters from the input
    if (islower(a)){
      new_text+=a;
    }
  }
  plain_text=new_text;//reassigns string to the plain text variable
  if (key.size() < plain_text.size()){
    //repeat first letters, for ex (fredfr)
    unsigned int x=0;
    while (key.size() < plain_text.size()){
      key+=(key[x]);
      x++;
      if(x == key.size()){//repeats if at the end of the key
        x=0;
      }
    }
  }
  for (unsigned int i=0; i < plain_text.size(); i++){
    //loop through plain text to encode it
    result+=vigenere_letter(plain_text[i], key[i]);
  }
  return result;
}

int main (){//main function given by professor to run tests
  int case_number;
  cin >> case_number;

  switch (case_number){

  case 1: {
    int rotations;
    cin >> rotations;
    string s;
    cin >> s;
    cout << rotate_left(rotations, s) << endl;
    break;
  }
    
  case 2: {
    char plain_letter;
    char key_letter;
    cin >> plain_letter >> key_letter;
    cout << beaufort_letter(plain_letter, key_letter) << endl;
    break;
  }

  case 3:{
    char plain_letter;
    char key_letter;
    cin >> plain_letter >> key_letter;
    cout << vigenere_letter(plain_letter, key_letter) << endl;
    break;
  }

  case 4:{
    string plain_text;
    string key;
    cin.ignore(100, '\n');
    getline(cin, plain_text);
    getline(cin, key);
    cout << encode_beaufort(plain_text, key) << endl;
    break;
  }

  case 5:{
    string plain_text;
    string key;
    cin.ignore(100, '\n');
    getline(cin, plain_text);
    getline(cin, key);
    cout << encode_vigenere(plain_text, key) << endl;
    break;
  }

  } // of switch
} // of main