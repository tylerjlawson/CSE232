#include <iostream>
using std::cout; using std::cin; using std::endl;
#include<iomanip>

int main () {

	long num;
	cin >> num;
	if (num <= 0){
		cout << "Error" << endl;
	}
	else{
		int d1,d2=0,hcn=0;
		for (int i=2; i<=num; ++i){
			d1=1;
			for (int x=1; x<num; ++x){
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
		if (hcn==num)
		{
			cout << "True " << num << " " << d2 << endl;
		}
		else{
			cout << "False " << num << " " << hcn << " " << d1 << endl;
		}
	}
	return 0;
}