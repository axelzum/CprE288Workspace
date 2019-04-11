/*
 * @file analysis.c
 *
 * @brief Contains the functions called by main to analyze sensor data
 *
 * @author Axel Zumwalt, Allan Juarez
 * @date 4/4/2019
 */

#include "analysis.h"


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
    for (i = 0; i < 165; i++) {

        double ping_average = 0;
        int j;
        for (j = i; j < (i + 5); j++) {
            ping_average += reading_array[j].sonar_distance;
        }
        ping_average /= 5;


        if (ping_average < 70 && object_detected == 0) {

            //start object
            object_detected = 1;
            object_array[object_array_index].degree_start = reading_array[i].degrees;
            object_array[object_array_index].ir_start = reading_array[i].ir_distance;
            object_array[object_array_index].sonar_start = reading_array[i].sonar_distance;

        }
        else if (ping_average > 70 && object_detected == 1) {

            //end object
            object_detected = 0;
            object_array[object_array_index].degree_stop = reading_array[i].degrees;
            object_array[object_array_index].ir_stop = reading_array[i].ir_distance;
            object_array[object_array_index].sonar_stop = reading_array[i].sonar_distance;
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
        object_array[object_array_index].ir_stop = reading_array[i].ir_distance;
        object_array[object_array_index].sonar_stop = reading_array[i].sonar_distance;
        object_array_index++;
    }

    return object_array_index;
}

/**
 * Calculates size of objects in an array and displays the smallest
 *
 * @author Axel Zumwalt, Allan Juarez
 * @param
 *   object_array: Array of objects to analyze
 *
 * @date 4/4/19
 *
 */
void find_smallest(struct object *object_array) {

}


