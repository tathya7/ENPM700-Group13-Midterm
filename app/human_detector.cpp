/**
 * @file human_detector.cpp
 * @author Tathya Bhatt (tathyab@umd.edu)
 * @brief Adding the detection and tracking functionality for the application
 * @version 1.0
 * @date 2024-10-28
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../include/human_detector.hpp"

#include <fstream>
#include <iostream>
#include <ostream>

#include <opencv4/opencv2/imgcodecs.hpp>
#include "../include/human_avoidance.hpp"

HumanAvoidance avoider;

/**
 * @brief Constructor with default initialization
 *
 * Initializes the HumanDetector with default values for frame dimensions,
 * model input width and height, and various thresholds.
 */
HumanDetector::HumanDetector()
    : frame_width(640),
      yolo_width(640),
      frame_height(480),
      yolo_height(640),
      nmsthresh(0.45),
      confidenceThresh(0.45),
      score_threshold(0.5) {
  std::cout << "HumanDetector initialized with default values." << std::endl;
}

/**
 * @brief Destructor
 *
 * Cleans up resources used by the HumanDetector.
 */
HumanDetector::~HumanDetector() {
  std::cout << "HumanDetector destroyed." << std::endl;
}

/**
 * @brief Sets the image path
 *
 * @param imgpath Reference to the string containing the image path
 * @return std::string The set image path
 */
std::string HumanDetector::getImgPath(std::string &imgpath) {
  image_path = imgpath;
  std::cout << "Image path set to: " << image_path << std::endl;
  return image_path;
}

/**
 * @brief Processes the input frame and outputs the updated frame
 *
 * @param capture_frame Reference to the VideoCapture object
 * @return cv::Mat Processed frame
 */
cv::Mat HumanDetector::ImgProcessor(cv::VideoCapture &capture_frame) {
  capture_frame >> frame;
  if (frame.empty()) {
    std::cout << " Error, Could not load frame" << std::endl;
  }
  return frame;
}

/**
 * @brief Draw bounding box around detected human
 * @param classid ID of the detected class
 * @param confidence Confidence score of the detection
 * @param left Left coordinate of the bounding box
 * @param top Top coordinate of the bounding box
 * @param right Right coordinate of the bounding box
 * @param bottom Bottom coordinate of the bounding box
 * @param frame Reference to the frame to draw on
 * @param classes Vector of class names
 * @param uniq_id Unique identifier for the detection
 */
void HumanDetector::drawBbox(int classid, float confidence, int left, int top,
                             int right, int bottom, cv::Mat &frame,
                             const std::vector<std::string> &classes,
                             int uniq_id) {
  cv::rectangle(frame, cv::Point(left, top), cv::Point(right, bottom),
                cv::Scalar(0, 255, 0), 2);
  std::string label = "Class:" + classes[classid] +
                      "  Confidence:" + cv::format("%.2f", confidence) +
                      "  ID:" + std::to_string(uniq_id);
  int baseLine;
  cv::Size labelSize =
      cv::getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
  top = std::max(top, labelSize.height);
  cv::rectangle(frame, cv::Point(left, top - labelSize.height),
                cv::Point(left + labelSize.width, top + baseLine),
                cv::Scalar(0, 255, 0), cv::FILLED);
  cv::putText(frame, label, cv::Point(left, top), cv::FONT_HERSHEY_SIMPLEX, 0.5,
              cv::Scalar(0, 0, 0), 1);
}

/**
 * @brief Removes overlapped boxes based on NMS
 * @param input_frame Reference to the input frame
 * @param img Size of the image
 * @param out_imgs Vector of output images from YOLO
 * @param classes Lists of class names
 * @return cv::Mat Processed image with non-overlapping bounding boxes
 */
cv::Mat HumanDetector::rmOverlap(cv::Mat &input_frame, cv::Size &img,
                                 std::vector<cv::Mat> &out_imgs,
                                 std::vector<std::string> &classes) {
  std::vector<int> class_ids;
  std::vector<float> class_confidences;
  std::vector<cv::Rect> boxes;

  cv::Mat boxed_img = input_frame.clone();

  float x_factor =
      static_cast<float>(img.width) / static_cast<float>(yolo_width);
  float y_factor =
      static_cast<float>(img.height) / static_cast<float>(yolo_height);

  float *info = reinterpret_cast<float *>(out_imgs[0].data);

  int rows = 25200;
  int dimensions = 85;

  // Iterate through each row
  for (int i = 0; i < rows; i++) {
    float confidence = info[4];

    if (confidence > confidenceThresh) {
      float classes_scores = info[5];

      cv::Mat scores(1, classes.size(), CV_32FC1, classes_scores);
      cv::Point class_id;
      double max_prob_class;
      cv::minMaxLoc(scores, 0, &max_prob_class, 0, &class_id);

      if (max_prob_class > score_threshold) {
        class_confidences.push_back(confidence);
        class_ids.push_back(class_id.x);

        float centerX = info[0];
        float centerY = info[1];
        float w = info[2];
        float h = info[3];
        int left = static_cast<int>((centerX - 0.5 * w) * x_factor);
        int top = static_cast<int>((centerY - 0.5 * h) * y_factor);
        int width = static_cast<int>(w * x_factor);
        int height = static_cast<int>(h * y_factor);

        boxes.push_back(cv::Rect(left, top, width, height));
      }
    }

    info += classes.size() + 5;
  }

  // Apply NMS
  std::vector<int> indices;
  cv::dnn::NMSBoxes(boxes, class_confidences, score_threshold, nmsthresh,
                    indices);

  for (int i = 0; i < indices.size(); i++) {
    int idx = indices[i];
    cv::Rect box = boxes[idx];
    int left = box.x;
    int top = box.y;
    int width = box.width;
    int height = box.height;
    cv::rectangle(boxed_img, cv::Point(left, top),
                  cv::Point(left + width, top + height),
                  cv::Scalar(255, 178, 50), 4);
    std::string label = cv::format("%.2f", class_confidences[idx]);
    label = classes[class_ids[idx]] + "|" + label;

    int baseLine;
    cv::Size label_size =
        getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
    cv::Point top_left = cv::Point(left, top);
    cv::Point bottom_right =
        cv::Point(left + label_size.width, top + label_size.height + baseLine);

    // ______________________________________________________________________________________________________________________________________________
    std::vector<float> robot_coord =
        avoider.camera2robot(box.height, box, boxed_img);

    std::string coordinates_label =
        "X = " + cv::format("%.2f", robot_coord[0]) +
        " Y = " + cv::format("%.2f", robot_coord[1]) +
        " Z = " + cv::format("%.2f", robot_coord[2]);

    cv::Point c_left = cv::Point(left + label_size.width + 105, top);
    cv::Point c_right = cv::Point(left + label_size.width + 375,
                                  top + label_size.height + baseLine);

    // Draw black rectangle for label background
    cv::rectangle(boxed_img, c_left, c_right, cv::Scalar(0, 0, 0), cv::FILLED);
    // Put the label on the rectangle
    cv::putText(
        boxed_img, coordinates_label,
        cv::Point(left + label_size.width + 105, top + label_size.height),
        cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 255), 1);
    // ______________________________________________________________________________________________________________________________________________

    // --------------------------------------------------------------------------------------------------------------------------------
    double dist2human = avoider.calculate_distance(box.height, img.height);
    std::string dist_label = "D2H = " + cv::format("%.2f", dist2human);
    cv::Point t_left = cv::Point(left + label_size.width + 5, top);
    cv::Point b_right = cv::Point(left + label_size.width + 100,
                                  top + label_size.height + baseLine);
    // Draw black rectangle for label background
    if (dist2human < 1.5) {
      cv::rectangle(boxed_img, t_left, b_right, cv::Scalar(0, 0, 255),
                    cv::FILLED);
      // Put the label on the rectangle
      cv::putText(
          boxed_img, dist_label,
          cv::Point(left + label_size.width + 1, top + label_size.height),
          cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 1);
    } else {
      cv::rectangle(boxed_img, t_left, b_right, cv::Scalar(0, 0, 0),
                    cv::FILLED);
      // Put the label on the rectangle
      cv::putText(
          boxed_img, dist_label,
          cv::Point(left + label_size.width + 1, top + label_size.height),
          cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 255), 1);
    }

    // --------------------------------------------------------------------------------------------------------------------------------

    // Draw black rectangle for label background
    cv::rectangle(boxed_img, top_left, bottom_right, cv::Scalar(0, 0, 0),
                  cv::FILLED);
    // Put the label on the rectangle
    cv::putText(boxed_img, label, cv::Point(left, top + label_size.height),
                cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 255), 1);
  }

  return boxed_img;
}

/**
 * @brief Detection on the given input type of source
 *
 * This method processes an input source (image, video, or camera stream) to
 * detect humans. It handles different input types.
 *
 * @param input_source Reference to a string containing the path to the input
 * source
 *
 * The method continues processing frames until the user presses 'Esc' or 'q' to
 * exit.
 *
 */
void HumanDetector::detect(std::string &input_source) {
  cv::VideoCapture cap(input_source);
  cv::Mat frame, blob_img;
  bool is_img = false;

  if (input_source.find("dev/video0") != std::string::npos) {
    cap.open(0);

  } else if (input_source.find(".jpeg") != std::string::npos ||
             input_source.find(".jpg") != std::string::npos ||
             input_source.find(".png") != std::string::npos) {
    frame = cv::imread(input_source);
    is_img = true;

  } else {
    cap.open(input_source);
  }

  if (!is_img && !cap.isOpened()) {
    std::cout << "Error opening input image" << std::endl;
    // return;
  }

  if (!is_img) {
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
  }

  std::vector<std::string> classes;
  std::string class_path = "../../models/coco.names";
  std::string model_path = "../../models/yolov5s.onnx";

  // Read class names from the file
  std::ifstream read_input(class_path);
  std::string text;
  while (read_input >> text) {
    getline(read_input, text);
    classes.push_back(text);
  }

  // Load the YOLO model
  cv::dnn::Net yolo_model = cv::dnn::readNet(model_path);

  HumanDetector input;  // Ensure StreamData is defined and accessible
  cv::VideoCapture capture;

  while (1) {
    if (!is_img) {
      frame = input.ImgProcessor(cap);
    }

    cv::Mat input_img = frame;

    // Prepare the image for the model
    cv::dnn::blobFromImage(input_img, blob_img, 1 / 255.0,
                           cv::Size(yolo_width, yolo_height), cv::Scalar(),
                           true, false);

    // Set the input to the model
    yolo_model.setInput(blob_img);

    std::vector<cv::Mat> out_imgs;
    std::vector<cv::Mat> detections;
    yolo_model.forward(out_imgs, yolo_model.getUnconnectedOutLayersNames());

    // detections = out_imgs;

    cv::Size frame_size = cv::Size(input_img.cols, input_img.rows);

    // Call the method to remove overlaps
    cv::Mat final_img = rmOverlap(input_img, frame_size, out_imgs, classes);

    // Performance measurement
    std::vector<double> layer_time;
    double freq = cv::getTickFrequency() / 1000;
    double time = yolo_model.getPerfProfile(layer_time) / freq;
    std::string label = cv::format("Inference time: %.2f ms", time);
    cv::putText(final_img, label, cv::Point(0, 15), cv::FONT_HERSHEY_SIMPLEX,
                0.5, cv::Scalar(0, 0, 255));

    // Display the result
    cv::imshow("Human Detection", final_img);
    char c = static_cast<char>(cv::waitKey(25));
    if (c == 27 || c == 'q') {  // 27 is the ASCII code for 'Esc'
      break;
    }
  }

  cap.release();
  cv::destroyAllWindows();
}
