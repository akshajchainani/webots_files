#include <webots/robot.h>
#include <webots/motor.h>
#include <math.h>

#define TIME_STEP 64

int main(int argc, char **argv) {
  wb_robot_init();

  // Setup wheels
  WbDeviceTag wheels[4];
  char wheels_names[4][8] = {"wheel1", "wheel2", "wheel3", "wheel4"};
  for (int i = 0; i < 4; i++) {
    wheels[i] = wb_robot_get_device(wheels_names[i]);
    wb_motor_set_position(wheels[i], INFINITY); // Set infinite position to control speed
  }

  double speed = 2.0;          // Speed in radians per second
  double rotation_speed = 2.0; // Rotation speed in radians per second

  double time_to_rotate_30 = 30.0 * M_PI / 180.0 / rotation_speed; // Time to rotate 30 degrees
  double time_to_rotate_90 = 480.0 * M_PI / 180.0 / rotation_speed; // Time to rotate 90 degrees
  double straight_time = 4.0; // Time to move straight

  double start_time = wb_robot_get_time();

  while (wb_robot_step(TIME_STEP) != -1) {
    double elapsed_time = wb_robot_get_time() - start_time;

    if (elapsed_time < time_to_rotate_30) {
      // Rotate 30 degrees
      wb_motor_set_velocity(wheels[0], -rotation_speed);
      wb_motor_set_velocity(wheels[2], -rotation_speed);
      wb_motor_set_velocity(wheels[1], rotation_speed);
      wb_motor_set_velocity(wheels[3], rotation_speed);
    } else if (elapsed_time < time_to_rotate_30 + straight_time) {
      // Move straight for 3 seconds
      wb_motor_set_velocity(wheels[0], speed);
      wb_motor_set_velocity(wheels[2], speed);
      wb_motor_set_velocity(wheels[1], speed);
      wb_motor_set_velocity(wheels[3], speed);
    } else if (elapsed_time < time_to_rotate_30 + straight_time + time_to_rotate_90) {
      // Rotate 90 degrees
      wb_motor_set_velocity(wheels[0], -rotation_speed);
      wb_motor_set_velocity(wheels[2], -rotation_speed);
      wb_motor_set_velocity(wheels[1], rotation_speed);
      wb_motor_set_velocity(wheels[3], rotation_speed);
    } else if (elapsed_time < time_to_rotate_30 + straight_time + time_to_rotate_90 + straight_time) {
      // Move straight for 3 seconds
      wb_motor_set_velocity(wheels[0], speed);
      wb_motor_set_velocity(wheels[2], speed);
      wb_motor_set_velocity(wheels[1], speed);
      wb_motor_set_velocity(wheels[3], speed);
    } else if (elapsed_time < time_to_rotate_30 + straight_time + 2 * time_to_rotate_90 + straight_time) {
      // Rotate another 90 degrees
      wb_motor_set_velocity(wheels[0], rotation_speed);
      wb_motor_set_velocity(wheels[2], rotation_speed);
      wb_motor_set_velocity(wheels[1], -rotation_speed);
      wb_motor_set_velocity(wheels[3], -rotation_speed);
    } else if (elapsed_time < time_to_rotate_30 + 2 * straight_time + 2 * time_to_rotate_90 + straight_time) {
      // Move straight for 3 seconds
      wb_motor_set_velocity(wheels[0], speed);
      wb_motor_set_velocity(wheels[2], speed);
      wb_motor_set_velocity(wheels[1], speed);
      wb_motor_set_velocity(wheels[3], speed);
    } else {
      // Stop the robot after completing the sequence
      for (int i = 0; i < 4; i++) {
        wb_motor_set_velocity(wheels[i], 0.0);
      }
      break;
    }
  }

  wb_robot_cleanup();
  return 0; // EXIT_SUCCESS
}
