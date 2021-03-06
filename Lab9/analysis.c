/*
 * @file analysis.c
 *
 * @brief Contains the functions called by main to analyze sensor data
 *
 * @author Axel Zumwalt, Allan Juarez
 * @date 4/4/2019
 */

#include "analysis.h"
#include "servo.h"
#include "lcd.h"
#include <math.h>


/**
 * Finds and indexs all objects in the dataset
 *
 * @author Axel Zumwalt, Allan Juarez
 * @param
 *   reading_array: Array containing dataset to detect
 *   object_array: Array that detected objects will be written to
 * @return total number of objects detected
 *
 * @date 4/4/19
 *
 */
int detect_objects(struct reading *reading_array, struct object *object_array) {

    int i;
    int object_array_index = 0;
    int object_detected = 0;

    //size_t reading_size = sizeof(reading_array) / sizeof(reading_array[0]);
    for (i = 0; i < 175; i++) {

        //Take a running average of the distance
        double ir_average = 0;
        int j;
        for (j = i; j < (i + 5); j++) {
            ir_average += reading_array[j].ir_distance;
        }
        ir_average /= 5;

        //Start Object detection if, no current object and distance is less than 70
        if (ir_average < 50 && object_detected == 0) {

            object_detected = 1;
            object_array[object_array_index].degree_start = reading_array[i].degrees;
            //object_array[object_array_index].ir_start = reading_array[i].ir_distance;
            //object_array[object_array_index].sonar_start = reading_array[i].sonar_distance;

        }
        //End objects if distance is greater than 70.
        else if (ir_average > 50 && object_detected == 1) {

            //end object
            object_detected = 0;
            object_array[object_array_index].degree_stop = reading_array[i].degrees;
            //object_array[object_array_index].ir_stop = reading_array[i].ir_distance;
            //object_array[object_array_index].sonar_stop = reading_array[i].sonar_distance;
            object_array_index++;
        }
        if (object_array_index > 10) {
            break;
        }
    }
    //If the sweep ends on an object, end the object there
    if (object_detected == 1) {
        object_detected = 0;
        object_array[object_array_index].degree_stop = reading_array[i].degrees;
        //object_array[object_array_index].ir_stop = reading_array[i].ir_distance;
        //object_array[object_array_index].sonar_stop = reading_array[i].sonar_distance;
        object_array_index++;
    }

    return object_array_index;
}

/**
 * Calculates size of objects in an array and displays the smallest
 *
 * @author Axel Zumwalt, Allan Juarez
 * @param
 *   reading_array: Data array to pull distance from
 *   object_array: Array of objects to analyze
 *   num_objects: the size of object_array
 *
 * @date 4/4/19
 *
 */
void find_smallest(struct reading *reading_array, struct object *object_array, int num_objects) {
    int index;
    int smallest_index = 0;
    double smallest_width = 500;
    int smallest_location;
    double smallest_average_distance;

    //Test size of each object in array
    for(index = 0; index < num_objects; index++) {
        int i;
        double average_distance = 0;
        int radial_size = (object_array[index].degree_stop - object_array[index].degree_start);
        //If the object is really small its probably not real
        if (radial_size < 2) {
            continue;
        }

        for (i = object_array[index].degree_start; i < object_array[index].degree_stop; i++) {
            average_distance += reading_array[i].sonar_distance;
        }
        average_distance /= radial_size;

        double width = tan((radial_size * 3.1415) / (2 * 180)) * 2 * average_distance;

        if (width < smallest_width) {
            smallest_index = index;
            smallest_width = width;
            smallest_location = (object_array[index].degree_stop + object_array[index].degree_start) / 2;
            smallest_average_distance = average_distance;
        }

    }

    lcd_printf("Index:%d\nDist:%.3f\nLoc:%d\nWidth:%.3f", smallest_index+1, smallest_average_distance, smallest_location, smallest_width);

    servo_position = servo_move(0);
    servo_position = servo_move(smallest_location);
}


