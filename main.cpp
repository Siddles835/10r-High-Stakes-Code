#include "vex.h"
#include <math.h>
using namespace vex;

competition Competition;

void pre_autonomous(void){
    vexcodeInit();
}

double kP = 0.0;
double kI = 0.0;
double kD = 0.0;

int desiredValue = 200;
int desiredTurnValue = 0;

int error; // Sensor Value - Disired Value - Position
int prev_error = 0; // Position 20 milliseconds ago
int derivative;
int totalError = 0;

bool enableDrivePID = true;

int drivePID(){
    while(enableDrivePID){
        int leftMotorPosition = leftMotorPosition;
        int rightMotorPosition = rightMotorPosition;

        int averageposition = (leftMotorPosition + rightMotorPosition) / 2;

        error = averageposition - desiredValue;

        derivative = error - prev_error;

        totalError += error;

        double LateralmotorPower = (error * kP + derivative * kD + totalError * kI) / 12.0;



        LeftMotor.spin(forward, LateralmotorPower + turnVolts, voltageUnits::volt);
        RightMotor.spin(forward, LateralmotorPower - turnVolts, voltageUnits::volt);



        prev_error = error;
        vex::task::sleep(20);
    }

    return 1;
}

void autonomous(void){
    vex::task doTask(drivePID);


}

void usercontrol(void){
    
    enableDrivePID = false;
    double turnImportance = 0.5;

}