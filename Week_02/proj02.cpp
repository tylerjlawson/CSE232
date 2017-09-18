//Project 2
//Highly Composite Number Test
//Takes input, tests for error then tests for highly composite or not


#include <iostream>//uses iostream for the in and output of the test cases
using std::cout; using std::cin; using std::endl;

int main () {//initialize main function

  long num;//initialize useful variables
  cin >> num;//give input to variable

  if (num <= 0){//check for 0 or negative number Error
    cout << "Error" << endl;
  }

  else{//run the test if valid input

    int d1,d2=0,hcn=0;//initialize test variables

    for (int i=2; i<=num; ++i){//starts counter at 2 and tests all 
    						   //numbers including test case for the highly composite number

      d1=1;//

      for (int x=1; x<num; ++x)//tests for divisors in each number
      {
        if (i%x==0){
          ++d1;
        }
      }

      if (d1>d2)
      {
        d2=d1;
        hcn=i;
      }  

    }

    if (hcn==num)//output for highly composite numbers
    {
      cout << "True " << num << " " << d2 << endl;
    }
    else{//output for test cases that are not highly composite
      cout << "False " << num << " " << hcn << " " << d1 << endl;
    }
  }
  return 0;//end function
}