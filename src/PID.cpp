#include "PID.h"
#include <iostream>
#include <numeric>
#include <math.h>



using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
	PID::Kp = Kp;
	PID::Ki = Ki;
	PID::Kd = Kd;

	p_error = 0.0;
	i_error = 0.0;
	d_error = 0.0;
}

void PID::UpdateError(double cte) {
	static double previous_cte = cte;

    p_error = cte;
    d_error = cte - previous_cte;
    i_error += cte;

    previous_cte = cte;

}

double PID::TotalError() {
	return 0.0;
}

