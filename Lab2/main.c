#include "lcd.h"
#include "movement.h"

/**
 * @file main.c
 *
 * Makes the robot move 1m
 *
 * @author Axel Zumwalt, Allan Juarez
 * @date 2/7/19
 */
int main(void)
{
    lcd_init();

    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

	move_forward(sensor_data, 50);
    turn_right(sensor_data, 90);
    move_forward(sensor_data, 50);
    turn_right(sensor_data, 90);
    move_forward(sensor_data, 50);
    turn_right(sensor_data, 90);
    move_forward(sensor_data, 50);


    oi_free(sensor_data);

	return 0;
}
