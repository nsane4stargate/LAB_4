#include "Panorama.h"
#include <String>
#include<vector>

using namespace cv;


Panorama::Panorama() {
	setFileName("C:/Users/nsane/Documents/Autumn'18Depaul/CSC_481 Image Processing/Pictures/machuPicchu.jpg");
}

Panorama::~Panorama() {

}

void Panorama::setFileName(const char* s) {
	filename = s;
}

const char* Panorama::getFileName() {
	return filename;
}

void Panorama::display(cv::Mat &image) {

	cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE);// Create a window for display.
	imshow("Display window", image);
}

void Panorama::setOriginalImage(cv::Mat &original){
	string imageName = ("C:/Users/nsane/Documents/Autumn'18Depaul/CSC_481 Image Processing/Pictures/machuPicchu.jpg");
	original = cv::imread(imageName);
}

void Panorama::splitImage(cv::Mat &original, cv::Mat &image1, cv::Mat &image2, cv::Mat &image3, cv::Mat &image4){
	int colStop, colStart;

	int intervals = original.cols / 4;

	int colLimit2 = intervals - 25, colLimit3 = intervals *2 - 50, colLimit4 = intervals*3 - 100;

	image1 = cv::Mat::zeros(300, intervals, CV_8UC3);
	image2 = cv::Mat::zeros(300, intervals, CV_8UC3);
	image3 = cv::Mat::zeros(300, intervals, CV_8UC3);
	image4 = cv::Mat::zeros(300, intervals, CV_8UC3);

	// For 1st image
	for (int row = 0; row < image1.rows; row++) {
		for (int col = 0; col < image1.cols; col++) {
			image1.at<cv::Vec3b>(row, col)[0] = original.at<cv::Vec3b>(row, col)[0];
			image1.at<cv::Vec3b>(row, col)[1] = original.at<cv::Vec3b>(row, col)[1];
			image1.at<cv::Vec3b>(row, col)[2] = original.at<cv::Vec3b>(row, col)[2];
			colStop = col;
		}
	}

	// For 2nd image
	colStart = colLimit2;
	for (int row = 0; row < image2.rows; row++) {
		// Row to continue from the original image
		for (int col = 0; col < image2.cols; col++) {
			image2.at<cv::Vec3b>(row, col)[0] = original.at<cv::Vec3b>(row, colStart)[0];
			image2.at<cv::Vec3b>(row, col)[1] = original.at<cv::Vec3b>(row, colStart)[1];
			image2.at<cv::Vec3b>(row, col)[2] = original.at<cv::Vec3b>(row, colStart)[2];
			colStart++;
		}
		colStart = colLimit2;
	}

	// For 3rd image
	colStart = colLimit3;
	for (int row = 0; row < image3.rows; row++) {
		// Row to continue from the original image
		for (int col = 0; col < image3.cols; col++) {
			image3.at<cv::Vec3b>(row, col)[0] = original.at<cv::Vec3b>(row, colStart)[0];
			image3.at<cv::Vec3b>(row, col)[1] = original.at<cv::Vec3b>(row, colStart)[1];
			image3.at<cv::Vec3b>(row, col)[2] = original.at<cv::Vec3b>(row, colStart)[2];
			colStart++;
		}
		colStart = colLimit3;

	}
	// For 4th image
	colStart = colLimit4;
	for (int row = 0; row < image4.rows; row++) {
		// Row to continue from the original image
		for (int col = 0; col < image4.cols; col++) {
			image4.at<cv::Vec3b>(row, col)[0] = original.at<cv::Vec3b>(row, colStart)[0];
			image4.at<cv::Vec3b>(row, col)[1] = original.at<cv::Vec3b>(row, colStart)[1];
			image4.at<cv::Vec3b>(row, col)[2] = original.at<cv::Vec3b>(row, colStart)[2];
			colStart++;
		}
		colStart = colLimit4;
	}
	writeOutImage(image1, "img1");
	writeOutImage(image2, "img2");
	writeOutImage(image3, "img3");
	writeOutImage(image4, "img4");
}

void Panorama::resizeImages(cv::Mat &img1, cv::Mat &img2, cv::Mat &img3, cv::Mat &img4) {
	
	cv::resize(img1, img1, cv::Size(img1.cols * 5, img1.rows * 5));
	cv::resize(img2, img2, cv::Size(img2.cols * 5, img2.rows * 5));
	cv::resize(img3, img3, cv::Size(img3.cols * 5, img3.rows * 5));
	cv::resize(img4, img4, cv::Size(img4.cols * 5, img4.rows * 5));

	writeOutImage(img1, "img1R");
	writeOutImage(img2, "img2R");
	writeOutImage(img3, "img3R");
	writeOutImage(img4, "img4R");
}

void Panorama::stitcher(cv::Mat &panorama,cv::Mat &img1, cv::Mat &img2, cv::Mat &img3, cv::Mat &img4){

	vector<Mat>imgs;

	// Push images into vector array
	imgs.push_back(img1);
	imgs.push_back(img2);
	imgs.push_back(img3);
	imgs.push_back(img4);

	Stitcher::Mode mode = Stitcher::PANORAMA;
	Ptr<Stitcher> stitcher = Stitcher::create(mode, false);
	Stitcher::Status errorCode = stitcher->stitch(imgs, panorama);

	if (errorCode != Stitcher::OK) {
		// Check if images could not be stiched 
		// status is OK if images are stiched successfully 
		printf("%s/n","Can't stitch images!!!");
	}
	writeOutImage(panorama, "Panorama");
}

void Panorama::writeOutImage(Mat &image, const char* name){

	String writeOutName = "C:/Users/nsane/Documents/Autumn'18Depaul/CSC_481 Image Processing/Pictures/";
	writeOutName += name; writeOutName += ".jpg";

	imwrite(writeOutName.c_str(), image);
}



