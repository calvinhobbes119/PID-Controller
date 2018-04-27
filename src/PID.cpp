#include "PID.h"

using namespace std;

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_in, double Ki_in, double Kd_in) {
    Kp = Kp_in;
    Ki = Ki_in;
    Kd = Kd_in;
}

void PID::UpdateError(double cte) {
    d_error = cte - p_error; // NOTE: p_error holds previous CTE value
    p_error = cte;
    i_error += cte;
}

double PID::TotalError() {
    // Calculate the total error
    double total_error = Kp * p_error + Kd * d_error + Ki * i_error;
    return total_error;
}
