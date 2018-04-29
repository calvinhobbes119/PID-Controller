## Project: PID-Controller [![Udacity - Self-Driving Car NanoDegree](https://s3.amazonaws.com/udacity-sdc/github/shield-carnd.svg)](http://www.udacity.com/drive)

Overview
---
This project implements the PID controller for Udacity's Self Driving Car Nanodegree. It uses two Proportional-Integral-Differential (PID) controllers to continually adjust the steering angle and throttle to minimize the cross-track error (CTE)

Code changes
---
For this project I made the following changes to the starter code.

__*main.cpp*__

1. I instatiated two PID controller objects for updating the steering value and throttle.
2. I manually tuned the PID parameters for _Kp_, _Kd_ and _Ki_ to achieve acceptable performance. The performance was assessed by using a combination of the following factors: How much CTE or deviation from the center of the lane existed, how much the car oscillated about the lane center and how much CTE bias was present. See discussion below for more details.
3. To eliminate sudden changes to steering value or throttle position from one measurement to the next, I smoothed the CTE measurements by taking the average with the previous CTE measurement. See discussion below for more details.
4. I fed the smoothed CTE value to the PID controller which adjusted steering value. I thresholded the steering value returned by my PID controller so that the steering value is always in the range [-1.0, +1.0].
5. I fed the absoulte value of the smoothed CTE to another PID contorller which adjusted the speed. The reason for using the absolute CTE value is because the throttle should be increased whenever the CTE is close to zero (irrespective of whether it is positive or negative), and lowered whenever the CTE deviates from zero (again irrespective of whether it is positive or negative). The throttle value returned by this PID controller is then applied as an offset to the nominal throttle position of 0.3 provided in the starter code.

__*PID.cpp*__

1. I updated the Init method to initialize the PID controller tune parameters _Kp_, _Kd_ and _Ki_ to the tuned values.
2. I updated the UpdateError method to update the proportional, derivative and integral error terms (_p_error_, _d_error_, _i_error_) based on previous CTE and current CTE.
3. I updated the TotalError method to retun the total error as the scalar product of [_Kp_, _Kd_ and _Ki_] with [_p_error_, _d_error_, _i_error_]. The total error is the output of the PID controller which is used to control steering angle or throttle position.

Tuning
---
I manually tuned the  PID parameters for steer value _Kp_, _Kd_ and _Ki_ assuming a fixed throttle position of 0.3. The procedure I followed for tuning _Kp_, _Kd_ and _Ki_.

1. Assume _Kd_ and _Ki_ are zero. Choose a value of _Kp_ which causes the car to remain on track for a reasonable length of time, say several seconds. This results in a plot of CTE as shown below with a value of _Kp_ = -0.3.

![Vary_Kp_alone](https://github.com/calvinhobbes119/PID-Controller/blob/master/figures/Kp_-0.3_Kd_0.0_Ki_0.0.png)
