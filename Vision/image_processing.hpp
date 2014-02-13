#ifndef __image_processing_hpp__
#define __image_processing_hpp__
#include "vision_includes.hpp"

/* This function processes the input image to ready it
   for edge finding */
void process_image(YAML::Node *config, Mat &image_in, Mat &image_out);

/* This function takes the object contours and
   figures out which ones are probably rectangles */
void find_rectangles (YAML::Node *config,
		      vector<vector<Point> > &contours,
		      vector<vector<Point> > &rectangles);

#endif
