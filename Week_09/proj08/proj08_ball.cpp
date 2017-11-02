//Project 08 Ball methods
//uses ball struct to calculate desired methods

#include "proj08_ball.h"//includes given header
#include<string>//used to convert to string
using std::string;
#include<sstream>//used to convert to string
using std::ostringstream;
#include <iomanip> //used to format string
using std::setprecision;
#include<iostream>//used to format string
using std::fixed;
#include<math.h>//used for pow

Ball::Ball(double m, TwoD pos, TwoD speed, double r){//constructor
	mass=m;
	coords=pos;
	velocity=speed;
	radius=r;
}

string Ball::to_string(){//converts the struct to a string
	ostringstream oss;//uses string stream to help build string
	oss << setprecision(2) << fixed;//used to format string
	oss << mass << ", " << coords.to_string() << ", " << velocity.to_string() << ", " << radius;
	return oss.str();//return a string type
}

double distance(TwoD c1, TwoD c2){//I made a distance function to keep things clean
	double d=pow( (c2.x - c1.x) , 2) + pow( (c2.y - c1.y) , 2);
	return pow(d,0.5);
}

bool Ball::contact_ball(Ball b){//sees if two balls are touching
	if (distance(b.coords, coords) < (radius + b.radius))//tests based on distance
		return true;
	else//else case if not touching
		return false;
}

bool Ball::contact_wall(long xdim, long ydim){//sees if a ball is touching a wall
	if ( (coords.y - radius) <= 0)//is it touching the bottom
		return true;
	else if ( (coords.x - radius) <= 0 )//if touching left edge
		return true;
	else if ( (coords.x + radius) >= xdim )//if touching right edge
		return true;
	else if ( (coords.y + radius) >= ydim )//if touching top
		return true;
	else //not touching the wall
		return false;
}

TwoD Ball::update_velocity_wall(long xdim, long ydim){//updates velocity change
	if (((coords.y - radius) <= 0) || ( (coords.y + radius) >= ydim ))
		//if it hit top or bottom, flip sign of y velocity
		return TwoD(velocity.x, (-1)*velocity.y);
	else//if hit right or left flip sign of x velocity
		return TwoD((-1)*velocity.x, velocity.y);
}

TwoD Ball::update_velocity_ball(Ball b){//uses the given equation to calculate
										//elastic reaction with a ball
	if (contact_ball(b)){//if the balls are touching
		double x = (2 * b.mass) / (mass + b.mass);//mass part of equation
		TwoD td = velocity.diff(b.velocity);//new 2d from difference of velocities
		double z = td.dot_product(coords.diff(b.coords));//number z from dot product of
											//velocity difference and position diff
		x *= z;//combines plain doubles to simplify equation
		TwoD a_diff = coords.diff(b.coords);//2d from position difference
		double d = a_diff.magnitude_squared();//number of position diff squared
		x /= d; //simplify numbers
		TwoD v_change = a_diff.mult(x);//multiply integer value calculated by remaining 2d
		return velocity.diff(v_change);//return the final difference
	}
	else{//if they weren't touching, no change in velocity
		return velocity;
	}
}