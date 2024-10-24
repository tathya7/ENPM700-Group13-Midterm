#include <iostream>
#include <opencv2/opencv.hpp>
#include <detector.hpp>


/**
 * @brief Command line options for the application.
 * 
 * Usage examples:
 * \code{.cpp}
 * ./app/app --image=../input/1.png
 * ./app/app --video=../input/video.mp4
 * \endcode
 */

const char* keys =
    "{help h usage ? | | Usage examples: "
    "\n\t\t./app/app --image=../input/1.png"
    "\n\t\t./app/app --video=../input/video.mp4}"
    "{image img||input image}";


/**
 * @brief Main function to start the detection process.
 * 
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return int Exit status of the program.
 */

int main(int argc, char** argv) {
  Detector detection;

  cv::CommandLineParser parser(argc, argv, keys);
  if (parser.has("help")) {
    parser.printMessage();
    return 0;
  }
  
  /**
   * @brief Starting the detection algorithm.
   */
  detection.detect(parser);

  /**
   * @brief Starting the detection algorithm
   *
   */
  detection.detect(parser);

  return 0;
}