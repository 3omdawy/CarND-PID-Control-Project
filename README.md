# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---

## Dependencies

* cmake >= 3.5
 * Used installer: cmake-3.7.2-win64-x64.msi
* make >= 4.1
  * Used installer: make-3.81.exe
* gcc/g++ >= 5.4
  * Used installer: mingw-get-setup.exe
* uWebSockets: according to the section "Windows Install Instructions" [here](https://github.com/swirlingsand/CarND-PID-Control-Project)
* Simulator: from [project intro page](https://github.com/udacity/CarND-PID-Control-Project/releases) in the classroom.

## Basic Build Instructions

1. Clone this repo.
2. Build the project "pid.vcxproj" using Visual Studio 17 (should work normally using `cmake .. && make` but it did on Windows using the original files in the project directory. I used the files [here](https://github.com/swirlingsand/CarND-PID-Control-Project) after asking on [forum](https://discussions.udacity.com/t/cmake-error-libuv-include-dir-and-libuv-library-not-found/244251/5))
3. Open the simulator in autonomous mode
4. Run pid.exe

## Procedure

* Parameters `Kp`, `Ki`, and `Kd` were manually chosen
* After each message from simulator with current `CTE`, PID control equation is applied: `steering angle = - Kp * CTE - Ki * sum(CTE) - Kd * diff (CTE)
* Where sum(CTE) is the summation of all CTEs (integral part)
* diff(CTE) is the differential part (difference between current CTE and previous CTE)
* After steering angle is calculated, it is passed with a constant throttle (0.3) to control the car in the simulator

## Choosing Parameters
* I tried to obtain the parameters using twiddle (as describes [here](https://github.com/jendrikjoe/UdacityProjects/tree/master/PID-Control-Project) but I could not do it)
* I initially the parameters given [here](https://github.com/thomasantony/CarND-P09-PID-Control/tree/77e672baef99f3c601ed24ff2fe57fbe85acc261) were applied and good results were obtained then some finetuning is done as explained below

### P Parameter
* The P-Value determines the proportionality between current CTE and the output (steering angle). As CTE is given in meters (which is approximatly between -5 and 5 on the pavement) and the steering angle as a value between -1 and 1, the P-value is expected to have an order of magnitude of approximately 0.1 as this would lead a steering angle of approx. 0.5 when being at the edge of the road. 0.5 is the steepest acceptable possible steering value.
* P was chosen to be 0.1
* When trying with P only (Kp = 0.1, Ki = 0, Kd = 0) the oscillations were steep but the car was able to drive till the sharp corner before the bridge

### D Parameter
* The D-Value determines the proportionality between derivative CTE and the output (steering angle). As the derivataive CTE error is approximated by the difference between the last two values which are handed with a difference of approximately 0.1s, the D-value is expected to be ten times bigger than the P-value, with an order of magnitude of 1. This change of the order of magnitude accounts for the normalising time to unit length, as the for the correct derivative the difference has be divided by the length of the integration time, which is times 10.
* D was chosen to be 1
* When trying with P and D (Kp = 0.1, Ki = 0, Kd = 1) the performance was really good, the car was able to complete driving smoothly

### I Parameter
* The I-Value determines the proportionality between integral CTE and the output (steering angle). It has added value to compensate for biases if a zero steering angle does not correspond to a straight trajectory. It was not needed.
* I was chosen to be 0
* When trying with P and D (Kp = 0.1, Ki = 0, Kd = 1) the performance was really good, the car was able to complete driving smoothly

## Simulation
* Check the video in the repository for a complete lap without going out of the lane