#include "vision_includes.hpp"
#include "target_processing.hpp"

#define PI 3.14159265

/* Utility functions only used here */

vector<Point> order_vertices(vector<Point> rect) {
  vector<Point> output;
  Point rect_tl, rect_tr, rect_bl, rect_br;

  // find which vertex is the top left one
  // this means the vertex with the smallest sum
  // of coordinates
  size_t minindex = 0;
  int minsum = rect[0].x+rect[0].y;
  for (size_t i = 1; i < rect.size(); i++) {
    if (rect[i].x+rect[i].y < minsum) {
      minindex = i;
      minsum = rect[i].x+rect[i].y;
    }
  }
  rect_tl = rect[minindex];
  // now find bottom right vertex with same procedure
  size_t maxindex = 0;
  int maxsum = rect[0].x+rect[0].y;
  for (size_t i = 1; i < rect.size(); i++) {
    if (rect[i].x+rect[i].y > maxsum) {
      maxindex = i;
      maxsum = rect[i].x+rect[i].y;
    }
  }
  rect_br = rect[maxindex];
  // now we only have two left, so we can
  // tell which one is which by which is
  // higher
  vector<size_t> remaining_indicies;
  // figure out which indicies are remaining
  for (size_t i = 0; i < 4; i++) {
    if (i != minindex && i != maxindex)
      remaining_indicies.push_back(i);
  }
  // there should be two
  assert(remaining_indicies.size() == 2);
  if (rect[remaining_indicies[0]].y > rect[remaining_indicies[1]].y) {
    rect_bl = rect[remaining_indicies[0]];
    rect_tr = rect[remaining_indicies[1]];
  } else {
    rect_bl = rect[remaining_indicies[1]];
    rect_tr = rect[remaining_indicies[0]];
  }
  output.push_back(rect_tl);
  output.push_back(rect_tr);
  output.push_back(rect_br);
  output.push_back(rect_bl);
  return output;
}

bool check_inside(vector<Point> &recto, vector<Point> &recti) {
  assert(recto.size() == 4);
  assert(recti.size() == 4);
  // NOTE: assuming that vertices are ordered
  if (recto[0].x < recti[0].x &&
      recto[0].y < recti[0].y &&
      recto[1].x > recti[1].x &&
      recto[1].y < recti[1].y &&
      recto[2].x > recti[2].x &&
      recto[2].y > recti[2].y &&
      recto[3].x < recti[3].x &&
      recto[3].y > recti[3].y)
    // recti is inside of recto,
    // assuming that they aren't rotated too much
    return true;
  // else false
  return false;
}

/* end utility functions */

void find_targets(YAML::Node *config,
		  vector<vector<Point> > &rectangles,
		  vector<vector<Point> > &targets) {
  vector<set<size_t> > checked;
  set<size_t> test_case;
  size_t size = rectangles.size();
  vector<Point> rect1, rect2;
  for (size_t i = 0; i < size; i++) {
    rect1 = order_vertices(rectangles[i]);
    for (size_t j = 0; j < size; j++) {
      test_case = {i,j};
      // skip if we're checking a rectangle against itself
      if (i == j) continue;
      // skip if we've already checked this one
      if (count(checked.begin(), checked.end(), test_case) > 0) continue;
      // add this rectangle to the checked list
      checked.push_back(test_case);
      // order the vertices of the rectangles
      rect2 = order_vertices(rectangles[j]);
      // check if one is inside of the other
      // take the one that is inside to be
      // the target rectangle
      if (check_inside(rect1, rect2))
	targets.push_back(rect2);
      else if (check_inside(rect2, rect1))
	targets.push_back(rect1);
    }
  }
}

void process_target(YAML::Node *config, Size image_size,
		    vector<Point> &target,
		    Point &center, double &hangle,
		    double &vangle, double &distance) {
  // NOTE: assuming that target vertices are
  // ordered by ordered_vertices
  const double PixelToCM = config->FindValue("PixelToCM")->to<double>();
  const double TargetWidth = config->FindValue("TargetWidth")->to<double>();
  const double DistanceAtFull = config->FindValue("DistanceAtFull")->to<double>();
  int width = target[1].x - target[0].x;
  double cm_per_pixel = TargetWidth / ((double)width);
  distance = DistanceAtFull / pow((double)width/(double)image_size.width,PixelToCM);
  double m1 = ((double)(target[0].y-target[2].y))/
    ((double)(target[0].x-target[2].x));
  double m2 = ((double)(target[3].y-target[1].y))/
    ((double)(target[3].x-target[1].x));
  double y1 = target[0].y;
  double x1 = target[0].x;
  double y2 = target[3].y;
  double x2 = target[3].x;
  // find the intersection of the two diagonals
  // of the rectangle, this is the "true" center
  // of the target
  double x = (y2-y1+(m1*x1)-(m2*x2))/(m1-m2);
  double y = m1*(x-x1)+y1;
  center.x = x;
  center.y = y;
  double dx = x - ((double)image_size.width/2.0);
  double dy = y - ((double)image_size.height/2.0);
  hangle = atan2((dx*cm_per_pixel),distance)*180 / PI;
  vangle = atan2((dy*cm_per_pixel),distance)*180 / PI;
}

void draw_targets(YAML::Node *config,
		  vector<vector<Point> > &rectangles,
		  vector<vector<Point> > &targets,
		  Mat &image) {
  const Point *points;
  int num_points;
  const Scalar RectangleColor =
    Scalar(config->FindValue("RectangleColor")->FindValue(0)->to<int>(),
	   config->FindValue("RectangleColor")->FindValue(1)->to<int>(),
	   config->FindValue("RectangleColor")->FindValue(2)->to<int>());
  const Scalar TargetColor =
    Scalar(config->FindValue("TargetColor")->FindValue(0)->to<int>(),
	   config->FindValue("TargetColor")->FindValue(1)->to<int>(),
	   config->FindValue("TargetColor")->FindValue(2)->to<int>());
  const int RectangleThickness = config->FindValue("RectangleThickness")->to<int>();

  for (size_t i=0; i < rectangles.size(); i++) {
    if (count(targets.begin(), targets.end(), rectangles[i]) > 0) continue;
    points = &rectangles[i][0];
    num_points = (int)rectangles[i].size();
    polylines(image, &points, &num_points,
	      1, true, RectangleColor,
	      RectangleThickness, CV_AA);
  }

  for (size_t i = 0; i < targets.size(); i++) {
    points = &targets[i][0];
    num_points = (int)targets[i].size();;
    polylines(image, &points, &num_points,
	      1, true, TargetColor,
	      RectangleThickness, CV_AA);
  }
}
