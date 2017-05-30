#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
	this->Kp = Kp;
	this->Ki = Ki;
	this->Kd = Kd;

	p_error = 0;
	i_error = 0;
	d_error = 0;
}

void PID::UpdateError(double cte) {
	//const double ktwiddle_tol = 0.02;
	//static double p[3] = { Kp, Ki, Kd };
	//static double dp[3] = { 0.1, 0.1, 0.1 };
	//static int currentIndex = 0;
	//static int currentStep = 0; // 0: Increment, 1: Check increment result,
	////2: Check decrement result
	//static double bestCte = cte;
	//
	//if (dp[0] + dp[1] + dp[2] > ktwiddle_tol)
	//{
	//	if (currentStep == 0)
	//	{
	//		p[currentIndex] += dp[currentIndex];
	//		currentStep = 1;
	//	}
	//	else if (currentStep == 1)
	//	{
	//		if (cte < bestCte)
	//		{
	//			bestCte = cte;
	//			dp[currentIndex] *= 1.1;
	//			currentStep = 0;
	//		}
	//		else
	//		{
	//			p[currentIndex] -= 2 * dp[currentIndex];
	//			currentStep = 2;
	//		}
	//	}
	//	else if (currentStep == 2)
	//	{
	//		if (cte < bestCte)
	//		{
	//			bestCte = cte;
	//			dp[currentIndex] *= 1.1;
	//		}
	//		else
	//		{
	//			p[currentIndex] += dp[currentIndex];
	//			dp[currentIndex] *= 0.9;
	//		}
	//		currentStep = 0;
	//		currentIndex++;
	//		if (currentIndex == 3)
	//			currentIndex = 0;
	//	}
	//}

	//Kp = p[0];
	//Kd = p[1];
	//Ki = p[2];
	// Control Part
	static bool isFirstTime = true;
	if (isFirstTime)
	{
		d_error = 0;
		isFirstTime = false;
	}
	else
		d_error = cte - p_error;
	p_error = cte;
	i_error += cte;

	steer = -Kp * p_error - Kd * d_error - Ki * i_error;
	if (steer > 1)
		steer = 1;
	else if (steer < -1)
		steer = -1;
}

double PID::TotalError() {
	return i_error;
}

