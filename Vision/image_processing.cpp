#include "vision_includes.hpp"
#include "image_processing.hpp"

/* Utility functions only used here */

double angle(Point pt1, Point pt2, Point pt0) {
  double dx1 = pt1.x - pt0.x;
  double dy1 = pt1.y - pt0.y;
  double dx2 = pt2.x - pt0.x;
  double dy2 = pt2.y - pt0.y;
  return (dx1*dx2 + dy1*dy2)/
    sqrt((dx1*dx2 + dy1*dy2)*
	 (dx2*dx2 + dy2*dy2) + 1e-10);
}

/* End utility functions */

void process_image(YAML::Node *config, Mat &image_in, Mat &image_out) {
  // image_1 and image_2 are used as
  // intermediaries for the image
  // processing
  Mat image_1, image_2, element;
  vector<Mat> image_split;
  const int dilateElementSize = config->FindValue("dilateElementSize")->to<int>();
  const int HSVThresholdMin = config->FindValue("HSVThresholdMin")->to<int>();
  const int HSVThresholdMax = config->FindValue("HSVThresholdMax")->to<int>();
  const int CannyThreshold1 = config->FindValue("CannyThreshold1")->to<int>();
  const int CannyThreshold2 = config->FindValue("CannyThreshold2")->to<int>();
  const int CannyAperatureSize = config->FindValue("CannyAperatureSize")->to<int>();
  element = getStructuringElement(MORPH_RECT,
				  Size(dilateElementSize*2 + 1,
				       dilateElementSize*2 + 1),
				  Point(dilateElementSize, dilateElementSize));
  // change colorspace to HSV
  cvtColor(image_in, image_1, CV_RGB2HSV);
  // only keep brightness value of HSV, equivalent to grayscale
  split(image_1, image_split);
  image_2 = image_split.at(2);
  threshold(image_2, image_1, HSVThresholdMin,
	    HSVThresholdMax,THRESH_BINARY);

  // series of scaling up and down to blur to decrease noise
  // probably can directly apply Gaussian blur or something similar instead
  dilate(image_1, image_2, element);
  pyrDown(image_2, image_1,
	  Size(image_2.cols/2, image_2.rows/2));
  pyrUp(image_1, image_2, image_in.size());

  // create image showing straight edges to find targets
  Canny(image_2, image_out, CannyThreshold1,
	CannyThreshold2, CannyAperatureSize);
  image_split.clear();
  image_1.release();
  image_2.release();
  element.release();
}

// finds rectangles given the edges
void find_rectangles (YAML::Node *config,
		      vector<vector<Point> > &contours,
		      vector<vector<Point> > &rectangles) {
  vector<Point> approx;
  double maxCosine, cosine;

  const int MinRectangleArea = config->FindValue("MinRectangleArea")->to<int>();
  const double PolyEpsilonFactor = config->FindValue("PolyEpsilonFactor")->to<double>();
  const double MaxRectangleCosine = config->FindValue("MaxRectangleCosine")->to<double>();

  for (size_t i=0; i < contours.size(); i++) {
    approxPolyDP(Mat(contours[i]), approx,
		 arcLength(Mat(contours[i]),
			   true)*PolyEpsilonFactor, true);
    if (approx.size() == 4 &&
	fabs(contourArea(Mat(approx))) > MinRectangleArea &&
	isContourConvex(Mat(approx))) {
      maxCosine = 0;
      for (int j=2; j<5; j++) {
	cosine = fabs(angle(approx[j%4], approx[j-2], approx[j-1]));
	maxCosine = MAX(maxCosine, cosine);
      }
      if (maxCosine < MaxRectangleCosine)
	rectangles.push_back(approx);
    }
  }
}
