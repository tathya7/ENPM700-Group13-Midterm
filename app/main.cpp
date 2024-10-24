// #include "lib.hpp"
// #include "lib1.hpp"
// #include "lib2.hpp"

// #include <iostream>
// #include <opencv2/core/utility.hpp>
// #include "opencv2/opencv.hpp"
// #include "detector.hpp"


// const char* keys =
//     "{help h usage ? | | Usage examples: "
//     "\n\t\t./app/app --image=../input/1.png"
//     "{image img||input image}";


// int main(int argc, char** argv) {
 
//  Detector detect_human;

//  cv::CommandLineParser parser(argc, argv,"");

// detect_human.detect(parser);
// return 0;
// }

#include <iostream>
#include <opencv2/opencv.hpp>
#include <detector.hpp>

const char* keys =
    "{help h usage ? | | Usage examples: "
    "\n\t\t./app/app --image=../input/1.png"
    "\n\t\t./app/app --video=../input/video.mp4}"
    "{image img||input image}";

    
int main(int argc, char** argv) {
  Detector detection;

  cv::CommandLineParser parser(argc, argv, keys);
  if (parser.has("help")) {
    parser.printMessage();
    return 0;
  }
  /**
   * @brief Starting the detection algorithm
   *
   */
  detection.detect(parser);
  return 0;
}