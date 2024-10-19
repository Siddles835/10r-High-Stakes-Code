#include "main.h"
#include "lemlib/api.hpp"

pros::Controller controller(pros::E_CONTROLLER_MASTER);
pros::Imu imu(10);
lemlib::Drivetrain drivetrain(&leftMotors, &rightMotors, 10, lemlib::Omniwheel::NEW_4, 360, 2);
pros::MotorGroup leftMotors({-1,2,-3}, pros::MotorGearset::blue); //motors 1 and 3 are reversed
pros::MotorGroup rightMotors({4,-5,6}, pros::MotorGearset::blue); //motor 5 is reversed
pros::Rotation horizontalEnc(20);
pros::Rotation verticalEnc(-11);
lemlib::TrackingWheel horizontal(&horizontalEnc, lemlib::Omniwheel::NEW_325, 2);
lemlib::TrackingWheel vertical(&verticalEnc, lemlib::Omniwheel::NEW_325, 2);

lemlib::ControllerSettings linearController(10,0,3,3,1,100,3,500,20);
lemlib::ControllerSettings angularController(2,0,10,3,1,100,3,500,0);
lemlib::OdomSensors sensors(&vertical, nullptr, &horizontal, nullptr, &imu);
lemlib::ExpoDriveCurve throttleCurve(3,10,1.019);
lemlib::ExpoDriveCurve steerCurve(3,10,1.019);

lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors, &throttleCurve, &steerCurve);

lemlib::ControllerSettings angular_controller(2,0,10,3,1,100,3,500,0);
lemlib::ControllerSettings lateral_controller(10,0,3,3,1,100,3,500,20);

void autonomous(){
	chassis.setPose(0,0,0);
	chassis.turnToHeading(90,100000);
}

void opcontrol(){
	while (true){
		int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);

		chassis.tank(leftY, rightY);
		pros::delay(25);
	}
}