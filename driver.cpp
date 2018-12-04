#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <string>
#include <cstdio>
#include <math.h>
#include <string> 
#include <vector>
#include "Panorama.h"

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	
	Panorama p;

	Mat original, image1, image2, image3, image4, panorama;
	Mat images[] = { image1, image2, image3, image4};
	vector<Mat>imgs;

	// Load image and clone to Mat
	p.setOriginalImage(original);

	p.splitImage(original, image1, image2, image3, image4);

	p.resizeImages(image1, image2, image3, image4);

	p.stitcher(panorama, image1, image2, image3, image4);

	waitKey(0); // Wait for a keystroke in the window
	return(EXIT_SUCCESS);
}



