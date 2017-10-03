#include <iostream>//uses iostream for the in and output of the test cases
using std::cout; using std::cin; using std::endl;using std::boolalpha;
#include <cmath>
using std::sqrt;

bool is_prime(long n){ 
  int i;
  for (i=2; i<n; i++){
    if (n % i == 0){
      return false;
    }
  }
  return true;  
}

long biggest_prime ( long n ) {
  long Lprime;

  for(int i = 2; i <= n; i++){
    if(n % i == 0){
    //   if (is_prime(n)){
        n/=i;
        Lprime=i;
      //}
    }
    if (n==1){
      break;
    }
  }
    return Lprime;
}



long sum_of_divisors (long n) {
  long sum= n+1;
  for(int i = 2; i <= sqrt(n); i++){
    if (n % i == 0) {
      sum+=i;
      sum+=n/i;
    }
  }
  return sum;
}

long k_hyperperfect (long n, long k_max){
  long k;
  for (k = 0; k < k_max + 1; k++ ){
    if (n == (1 + k*(sum_of_divisors(n)-n-1))) {
      break;
    }
  }
  return k;
}

bool b_smooth (long n, long b){
  bool smooth=false;
  if (b>=biggest_prime(n)){
    smooth=true;
  }
  return smooth;
}

int main (){

  long n, k_max, b;
  cin >> n;
  cin >> k_max;
  cin >> b;
  cout << biggest_prime(n) << " ";
  cout << sum_of_divisors(n) << " ";
  cout << k_hyperperfect(n, k_max) << " ";
  cout << boolalpha;
  cout << b_smooth(n,b) << endl;

  return 0;
}