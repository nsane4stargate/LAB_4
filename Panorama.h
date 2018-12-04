#pragma once
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include "opencv2/stitching.hpp" 
#include <string>
#include <vector>

using namespace std;

class Panorama {

	const char* filename;
	

public:
	// Construtor
	Panorama();

	// Destructor
	~Panorama();

	void setFileName(const char*);

	const char* getFileName();

	void display(cv::Mat&);

	void setOriginalImage(cv::Mat &);

	void splitImage(cv::Mat &, cv::Mat &, cv::Mat &, cv::Mat &, cv::Mat &);
	
	void resizeImages(cv::Mat &, cv::Mat &, cv::Mat &, cv::Mat &);

	void stitcher(cv::Mat &, cv::Mat &, cv::Mat &, cv::Mat &, cv::Mat &);

	void writeOutImage(cv::Mat &, const char* name);
};