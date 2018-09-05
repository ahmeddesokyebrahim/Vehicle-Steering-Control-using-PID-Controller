# **Vehicle Control Using PID Controller**
---

**In this project, I have worked on a PID controller to control the vehicle's steering angle .**

## Project Introduction:
---
In this project, we are controlling the vehicle's steering angle to be within the road using one of the most common and fundamental controllers which is the PID (Proportional, Integral, Differtial) controller. For doing this, we use the Cross Track Error (CTE) which the lateral distance between the vehicle and the reference trajectory provided from the simulator to control the steering angle and have the vehicle in the road.


## Environment:
---
* Ubuntu 16.04 LTS
* Udacity Self-Driving Car Nano-Degree Term2 Simulator
* cmake >= 3.5
* make >= 4.1
* gcc/g++ >= 5.4

## Parameters Discussion
---
### Proportional Term (Kp)
The proportional term is simply multiplying a factor (constant) by the error value (CTE in our case) to compensate the drift happened in the steering angle due to this error (CTE).

The following equation summerizes the proportional term:
` steering_angle = - Kp * CTE`

Applying the proportional term (P-Controller) to the vehicle, it will act like this:

![p-controller](https://i.imgur.com/UcCq2Dm.png)

It will be overshooting overtime .. sometimes this overshooting will be slightly small and it may be OK, but even if it is small, it will never really converge, It will be what is called "marginally stable" or "stable"

We can consider this overshooting as oscillation for our control process. When Kp is large, the oscillation is faster, and vise versa.

### Differential Term (Kd)
The previous discussion turns to the P-term is usually is not enough due to the overshooting probelm and oscillation. The differential term allow to gracefully approach our target trajectory by having the steering angle not only proportional to the error itself, but also to the difference of the error using another factor (Kd).

**How we compute the derivative `d/dt CTE` ?**

`d/dt CTE = ( current_CTE - previosu_CTE ) / delta_t`

When `delta_t = 1` :
`d/dt CTE = current_CTE - previosu_CTE`


The following equation summerizes the PD-Controller:
`steering_agnle = - Kp * CTE - Kd * (CTE - previous_CTE)`

The following figure from my Udacilty lesson illustrates the impact of the D-term for having more smooth controller rather than P-controller only.

![PD-controller](https://i.imgur.com/LxTHRHm.png)


### Integral Term (Ki)
The integral term tackles problems what is called in robotics **Systematic Bias**. To explain this problem with an example related to our case, assume that you receive your car with wheels 100% aligned straight. But in reality due to some mechanical offsets and errors, they are not alighned. When running our controller, this error will accumulate over time turning to a big error in CTE

The following image illustraces the systematic bias:

![sys-bias](https://i.imgur.com/ycL1Sb2.png)

Even the controller is stable at the end (in blue), it far away from the set point we need to achieve (yellow)

The I-term solves for this problem by having the sum of all cross track errors you have ever observed. It will evetually correct the vehicle's motion

The following summerizes how we calculate the integral term:
`integral_CTE += CTE`

So, the final equation for having a PID controller:
`steering_angle = - Kp * CTE - Kd * (CTE - previous_CTE) - Ki * integral_CTE`


## Parameters Tuning (Kp, Ki, Kd)
---
I followed a manual approach for tuning the PID parameters.

I have followed the following strategy:
- Firstly and initially, for the integral term, the Systematic bias does not appear in simulation, so I set `Ki = 0.0`
- I started with setting the prortional term `Kp` with low values. I got the feeling that car is not that responsive (oscillation is very slow).
- Then I have increased the `Kp` with trial after another. Here I got to the car keeps oscillating
- Then I started introducing the `Kd` term to have a more smooth and graceful driving
- With many trial, I found the following:
  - `Kp` values less than 0.9 get to very poor response to the car specially in curves
  - `kp` is very acceptable in 0.1
  - `kd` values less than 0.35 allow the propostional term to have dominant impact so the car still osciallting
  - `kd` with high values (2.5, 3.0, .. ) are Ok in sometimes but it gave me the feeling of continuous smooting for steeting so I felt that it is not safe driving

**Parameters Tuning Conclusion:** 
  
 - I found `Kp = 0.11` and `kd = 0.47` achieves one of the best safe driving for parameters tuning. 
 - Yes, it  may be two times the car touches the ledges, but on the other hand the car was moving very smoothly and gracefully all over the track with very acceptable performace.
 - The following video is a demo for my project, [here](https://youtu.be/hOGo_fkgdsE)

## Running the Code
---
This project involves the Term 2 Simulator which can be downloaded [here](https://github.com/udacity/self-driving-car-sim/releases)


This repository includes two files that can be used to set up and install uWebSocketIO for either Linux or Mac systems. For windows you can use either Docker, VMware, or even Windows 10 Bash on Ubuntu to install uWebSocketIO.

Once the install for uWebSocketIO is complete, the main program can be built and ran by doing the following from the project top directory.

1. mkdir build
2. cd build
3. cmake ..
4. make
5. ./pid

## Conclusion
---
  * The PID controller is on the common and fundametal controllers that can be used in for controlling the vehicle steering and brakes.
  * PID parameters tuning needs a lot of intution and understanding of them impact.
  * There are some methods to tune these parameters automatically rather than manually, for example the twiddle (or coordinate ascent) algorithm. It may be a furhter improvement for my project to use on of these algorithms for parameters tuning.

