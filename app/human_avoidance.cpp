#include "../include/human_avoidance.hpp"

#include <vector>

// Constructor
HumanAvoidance::HumanAvoidance() : averageHeight(175) {
  std::cout << "HumanAvoidance initialized with default values." << std::endl;
}

// Calculates the distance of a detected human from the camera
float HumanAvoidance::calculate_distance(int box_h, int frame_h) {
  int focal_length = 16;   // Assumed focal length in mm
  int sensor_height = 25;  // Assumed sensor height in mm

  double height_mm =
      (sensor_height * box_h) / frame_h;  // Convert pixel height to mm
  double z = (averageHeight * focal_length) / height_mm;  // Calculate distance
  double z_meters = z / 100;
  std::cout << "Distance between robot and the human detected" << z_meters
            << std::endl;
  return (z_meters);  // Convert to meters
}

// Transforms detected human coordinates to robot coordinate system
std::vector<float> HumanAvoidance::camera2robot(float z, cv::Rect box,
                                                cv::Mat frame) {
  std::vector<double> pos;
  int sensor_w = 24;  // Assumed sensor width in mm
  int sensor_h = 35;  // Assumed sensor height in mm
  double x =
      (sensor_w * ((box.x + box.width / 2) - (frame.cols / 2))) / frame.rows;
  double y =
      (sensor_h * ((box.y + box.height / 2) - (frame.rows / 2))) / frame.cols;

  pos.push_back(x);
  pos.push_back(y);
  pos.push_back(z);
  pos.push_back(1.0);

  std::vector<std::vector<double>> T = {
      {1, 0, 0, 1}, {0, 1, 0, 1}, {0, 0, 1, -2}, {0, 0, 0, 1}};

  std::vector<float> out;
  double res = 0.0;
  for (int i = 0; i < 3; i++) {
    res = 0;
    for (int j = 0; j < 4; j++) {
      res += T[i][j] * pos[j];
    }
    out.push_back(static_cast<float>(res));
  }

  // Output transformed coordinates (x, y, z) for debugging
  std::cout << "Transformed Coordinates: X=" << out[0] << " Y=" << out[1]
            << " Z=" << out[2] << std::endl;
  return out;
}

// Destructor
HumanAvoidance::~HumanAvoidance() {}
