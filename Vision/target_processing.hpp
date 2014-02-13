#ifndef __target_processing_hpp__
#define __target_processing_hpp__
#include "vision_includes.hpp"

/* This function finds targets by looking for rectangles
   inside other rectangles */
void find_targets(YAML::Node *config,
		  vector<vector<Point> > &rectangles,
		  vector<vector<Point> > &targets);


/* This function draws rectangles to an image */
void draw_targets(YAML::Node *config,
		  vector<vector<Point> > &rectangles,
		  vector<vector<Point> > &targets,
		  Mat &image);

/* This function processes targets to figure out
   at what angle it is from straight ahead, and
   what the center is */
void process_target(YAML::Node *config, Size image_size,
		    vector<Point> &target,
		    Point &center, double &hangle,
		    double &vangle, double &distance_cm);

#endif
