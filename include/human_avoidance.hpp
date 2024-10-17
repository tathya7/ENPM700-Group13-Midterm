#pragma once
#include <vector>
#include <utility>

/**
 * @brief Create a HumanAvoidance class to implement human avoidance strategy after detecting humans.
 */
class HumanAvoidance {
 private:
  /**
   * @brief Threshold distance from detected humans to avoid collision.
   */
  double avoidance_threshold;

  /**
   * @brief Flag to indicate if a human is detected within the threshold
   */
  bool is_human_detected;

  /**
   * @brief Coordinates of detected humans in the robot's reference frame
   */
  std::vector<std::pair<double, double>> human_positions;

  /**
   * @brief Function to check if any detected human is within threshold
   */
  void check_avoidance();

 public:
  /**
   * @brief Construct a new HumanAvoidance object
   * 
   * @param threshold Avoidance threshold distance
   */
  HumanAvoidance(double threshold);

  void update_human_positions(const std::vector<std::pair<double, double>>& positions);

  bool is_avoidance_required() const;

  void update_threshold(double threshold);
};
