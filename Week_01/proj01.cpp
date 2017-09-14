#include <iostream>
using std::cout; using std::cin; using std::endl; using std::fixed;
#include<iomanip>
using std::setprecision;

int main() {
    double a, b, c, d;
    double sum1, sum2;
    double dif1, dif2;
    double mult1, mult2;
    double quot1, quot2;
    cin >> a;
    cin >> b;
    cin >> c;
    cin >> d;
    

    sum1 = a + c;
    sum2 = b + d;
    dif1 = a - c;
    dif2 = b - d;
    mult1 = (a * c) - (b * d);
    mult2 = (b * c) + (a * d);
    quot1 = ((a * c) + (b * d)) / ((c * c) + (d * d));
    quot2 = ((b * c) - (a * d)) / ((c * c) + (d * d));
    cout << setprecision(2) << fixed << sum1 << " + " << sum2 << "i" << endl;
    cout << setprecision(2) << fixed << dif1 << " + " << dif2 << "i" << endl;
    cout << setprecision(2) << fixed << mult1 << " + " << mult2 << "i" << endl;
    cout << setprecision(2) << fixed << quot1 << " + " << quot2 << "i" << endl;
    
    return 0;
}
