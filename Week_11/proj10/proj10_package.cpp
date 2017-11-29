#include "proj10_package.h"
//functions for package struct

ostream& operator<<(ostream& out, Package& p){
	//allows package to be nicely outputted to an outstream
	out << p.weight_ << ":" << p.priority_;//weight:priority format
	return out;
}

bool package_compare(const Package &p1, const Package &p2){
	//compares two packages by their priority to weight ratio and returns boolean
	//uses static cast in order to capture the fractions
	double a = (static_cast<double>(p1.priority_))/(static_cast<double>(p1.weight_));
	double b = (static_cast<double>(p2.priority_))/(static_cast<double>(p2.weight_));
	return a > b;//returns truth of comparison
}