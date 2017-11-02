//Project 8 2D methods
//uses 2D struct to calculate different methods

#include "proj08_twod.h"//includes given header
#include<string>//for building string outputs
using std::string;
#include<sstream>//for building string outputs
using std::ostringstream;
#include <iomanip> //for building string outputs
using std::setprecision;
using std::fixed;
#include<math.h>//for pow

TwoD::TwoD(double xval, double yval){//constructor
    x = xval;
    y = yval;
}

string TwoD::to_string(){//converts the 2d struct to a string
	ostringstream oss;//uses stringstream to build string
	oss << setprecision(2) << fixed;//setprecision for desired formatting
	oss << "(" << x << ", " << y << ")";
	return oss.str();//returns the string type
}

TwoD TwoD::diff(TwoD td){//subtracts a 2d struct from another 2d struct
	return TwoD(x-td.x, y-td.y);//constructs and returns new 2d
}

TwoD TwoD::mult(double D){//multiplies a double by a 2d struct
	return TwoD(x*D, y*D);//constructs and returns new 2d
}

double TwoD::dot_product(TwoD td){//dot product of two 2ds
	return (x * td.x) + (y * td.y);//calculates and returns double
}

double TwoD::magnitude_squared(){//squares the magnitude
	return (x*x) + (y*y);//calculates and returns doublea
}