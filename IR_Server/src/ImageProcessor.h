
#ifndef IMAGE_PROCESSOR_H
#define IMAGE_PROCESSOR_H

//#include "opencv2/opencv.hpp"

#include "IR_Image.h"


#include <string>
#include <fstream>





class ImageProcessor
{


public:
	ImageProcessor(const std::string& fileName="");
	const char * GetNextFrameFragment(int& size, bool& isLastFragment, unsigned short & width, unsigned short & height, unsigned char & pixelSize);
	


private:
	virtual const char * GetNextFrame(int& size, unsigned short & width, unsigned short & height, unsigned char & pixelSize);

	bool getNewImage;
	unsigned int fragmentIndex;
	const char * imageData;
	int imageSize;
//	cv::VideoCapture cap;
	

	
};


class MovieProcessor : public ImageProcessor
{
public:

	MovieProcessor(const std::string& fileName="");
	~MovieProcessor();
	
private:

	const char * GetNextFrame(int& size);

	std::ifstream movieFile;
	

};

#endif
