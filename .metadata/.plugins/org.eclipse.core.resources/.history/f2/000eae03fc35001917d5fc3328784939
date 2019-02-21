/*
* @file movement.c
*
* @brief Contains the functions called by main to move the robot.
*
* @author Axel Zumwalt, Allan Juarez
* @date 2/7/2019
*/

#include "movement.h"

/**
* Moves the robot forward the number of centimeters specified.
*
* @author Axel Zumwalt, Allan Juarez
* @param
*   sensor: struct of type oi_t from open_interface
*   centimeters: Number of centimeters to move forward.
*
* @date 2/7/19
*
*/
void move_forward(oi_t *sensor, int centimeters) {

    int sum = 0;

    oi_setWheels(400, 400);

    while (sum < centimeters * 10) {
        oi_update(sensor);
        sum += sensor -> distance;
    }

    oi_setWheels(0,0);

    return;
}
/**
* Moves the robot backward the number of centimeters specified.
*
* @author Axel Zumwalt, Allan Juarez
* @param
*   sensor: struct of type oi_t from open_interface
*   centimeters: Number of centimeters to backward.
*
* @date 2/7/19
*
*/
void move_backward(oi_t *sensor, int centimeters) {

    int sum = 0;

    oi_setWheels(-400, -400);

    while (sum > -1* centimeters * 10) {
        oi_update(sensor);
        sum += sensor -> distance;
    }

    oi_setWheels(0,0);

    return;
}
/**
* Turns the robot right the number of degrees specified.
*
* @author Axel Zumwalt, Allan Juarez
* @param
*   sensor: struct of type oi_t from open_interface
*   centimeters: Number of degrees to turn right.
*
* @date 2/7/19
*
*/
void turn_right(oi_t *sensor, double degrees) {
    double sum = 0;

    degrees = degrees + 4;

    oi_setWheels(-400, 400);

    while (sum > -1 * degrees) {
        oi_update(sensor);
        sum += sensor -> angle;
    }

    oi_setWheels(0,0);

    return;
}
/**
* Turns the robot left the number of degrees specified.
*
* @author Axel Zumwalt, Allan Juarez
* @param
*   sensor: struct of type oi_t from open_interface
*   centimeters: Number of degrees to turn left.
*
* @date 2/7/19
*
*/
void turn_left(oi_t *sensor, double degrees) {
        double sum = 0;

        degrees = degrees + 4;

        oi_setWheels(400, -400);

        while (sum < degrees) {
            oi_update(sensor);
            sum += sensor -> angle;
        }

        oi_setWheels(0,0);

        return;
}
/**
* Drives forward two meters, detecting for any bumps and driving around that.
*
* @author Axel Zumwalt, Allan Juarez
* @param
*   sensor: struct of type oi_t from open_interface
*
* @date 2/7/19
*
*/
void collision(oi_t *sensor) {
    int dist_traveled = 0;

    oi_setWheels(400, 400);

    while (dist_traveled < 2000) {
           oi_update(sensor);
           dist_traveled += sensor -> distance;

          //TODO: check if the actions after bump are adding to total distance traveled.
           if (sensor -> bumpRight == 1) {
               move_backward(sensor, 15);
               turn_left(sensor, 90);
               move_forward(sensor, 25);
               turn_right(sensor, 90);
               oi_setWheels(400, 400);
               //dist_traveled -= sensor -> distance;
           }
           else if (sensor -> bumpLeft == 1) {
               move_backward(sensor, 15);
               turn_right(sensor, 90);
               move_forward(sensor, 25);
               turn_left(sensor, 90);
               oi_setWheels(400, 400);
               //dist_traveled -= sensor -> distance;
           }
    }

    oi_setWheels(0,0);

    return;
}
