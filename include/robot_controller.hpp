#pragma once
#include <utility>

/**
 * @brief RobotController class to control robot movement based on avoidance strategy
 */
class RobotController {
 private:
  /**
   * @brief Current position of the robot
   */
  std::pair<double, double> current_position;

  /**
   * @brief Target position of the robot
   */
  std::pair<double, double> target_position;

  /**
   * @brief Maximum allowable speed for the robot
   */
  double max_speed;

  /**
   * @brief Function to adjust the robot's path based on avoidance requirements
   * 
   * @param is_avoidance_required Indicates if avoidance is necessary
   */
  void adjust_path(bool is_avoidance_required);

 public:
  /**
   * @brief Construct a new RobotController object
   * 
   * @param start_position Initial position of the robot
   * @param max_speed Maximum allowable speed
   */
  RobotController(const std::pair<double, double>& start_position, double max_speed);

  void set_target_position(const std::pair<double, double>& target);

  std::pair<double, double> move_robot(bool is_avoidance_required);
};
