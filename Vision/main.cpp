#include "vision_includes.hpp"
#include "image_processing.hpp"
#include "target_processing.hpp"
#include "client.hpp"

/* This function loads the yaml conf file */
void load_conf(string filename, YAML::Node &config) {
  ifstream file(filename.c_str());
  if (file.is_open()) {
    YAML::Parser parser(file);
    if (!parser.GetNextDocument(config)) {
      cerr << "Could not load config" << endl;
      exit(-1);
    }
    file.close();
  } else {
    cerr << "Could not open config file" << endl;
    exit(-1);
  }
}

int main(int argc, char **argv) {

  char *server_ip = "10.0.8.2";
  connect(server_ip);
  // Use webcam as source by default
  VideoCapture capture;
  double rate;
  if (argc < 2) {
    capture.open(0); // Use default webcam if no arguments are provided
    // Get the frame rate
    rate = 30; /* I hardcoded the frame rate for now
		  because my webcam isn't reporting the
		  frame rate correctly. */
  } else if (argc > 1) {
    capture.open(argv[1]); // Use video file if specified
    rate = capture.get(CV_CAP_PROP_FPS); // Use frame rate from video file
  }

  // check if video successfully opened
  if (!capture.isOpened())
    cerr << "No input stream" << endl;
  bool stop(false);
  int delay = 1000 / rate;

  Mat image;

  /*
  // read image from cli arguments
  image = imread(argv[1], 1);

  if (!image.data) {
  cerr << "No image data" << endl;
  return -1;
  }
  */

  Mat image_processed;
  vector<vector<Point> > contours, rectangles, targets;
  YAML::Node config;
  Point center;
  double hangle, vangle, distance;

  // load config file
  load_conf("conf.yaml", config);

  //int counter = 0; //counter for the while loop for debugging purposes

  while (!stop) {
    //cout << "\n\ncounter: " << counter << endl;
    // read next frame if any
    if (!capture.read(image))
      break;

    // process image for edge finding
    process_image(&config, image, image_processed);
    // find edges
    findContours(image_processed, contours, CV_RETR_LIST,
		 CV_CHAIN_APPROX_SIMPLE);
    // find rectangles from edges
    find_rectangles(&config, contours, rectangles);
    // find targets
    find_targets(&config, rectangles, targets);
    // draw rectangles
    draw_targets(&config, rectangles, targets, image);

    cout << "Image width:" << image.cols << endl;
    cout << "Image height:" << image.rows << endl;
    cout << "Image center x:" << (image.cols/2) << endl;

    cout << "Found " << contours.size() << " contours" << endl;
    cout << "Found " << rectangles.size() << " rectangles" << endl;
    cout << "Found " << targets.size() << " targets" << endl;

    for (size_t i = 0; i < targets.size(); i++) {
      // process targets
      process_target(&config, image.size(), targets[i], center, hangle,
		     vangle, distance);
      cout << "Target " << i << ":" << endl;
      cout << "Center: (" << center.x << ", " << center.y << ")" << endl;
      cout << "Distance: " << distance << " cm" << endl;
      cout << "Horizontal angle: " << hangle << " degrees" << endl;
      cout << "Vertical angle: " << vangle << " degrees" << endl;

      if (center.x >= ((image.cols)/2 + 5))
    	  cout << "Target is on the right" << endl;
      else if (center.x <= ((image.cols)/2 -5))
    	  cout << "Target is on the left" << endl;
      else // +-5 pixel threshold for being aligned
    	  cout << "Target is aligned" << endl;
    }

    // show the result
    imshow("Detected Lines", image);

    // save result to file
    //imwrite("result.jpg", image);

    contours.clear(); // clear these after each iteration of the while loop or else they will increase exponentially
    rectangles.clear();
    targets.clear();

    //waitKey(0);
    if (waitKey(delay) >= 0)
      stop = true;

    //counter++;
  }

  // Close the video file
  capture.release();
  return 0;
}
