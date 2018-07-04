


#include "ImageProcessor.h"


using namespace std;


ImageProcessor::ImageProcessor(const std::string& fileName)
	: getNewImage(true)
	, fragmentIndex(0)
	, imageSize(-1)
	, imageData(NULL)
{

	if (fileName.length())
	{
		
		//cap = VideoCapture(fileName);
		//assert (cap.isOpened());

	}

}


const char* ImageProcessor::GetNextFrameFragment(int & size, bool& isLastFragment )
{

	const char* buf;
	static int testCount=0;
	
	if (getNewImage)
	{
		imageData = GetNextFrame(imageSize);
		fragmentIndex = 0;
		
		if (imageSize == -1)
		{
			getNewImage = false;
			size = -1;
			return NULL;
		}

		
		if (imageSize <= PACK_SIZE)
		{
			
			isLastFragment = true;
			size = imageSize;
			return imageData;
		}

		getNewImage = isLastFragment = false;
		fragmentIndex++;
		size = PACK_SIZE;
		return imageData;
	}

	if (fragmentIndex == 0)
	{
		size = -1;
		return NULL;
	}
	
	//assert(fragmentIndex*PACK_SIZE < imageSize);
	if (fragmentIndex*PACK_SIZE >= imageSize)
		;//testCount = testCount;
	testCount ++;
	buf = &imageData[fragmentIndex*PACK_SIZE];

	if ((fragmentIndex+1)*PACK_SIZE >= imageSize)
	{
		size = imageSize - fragmentIndex*PACK_SIZE;
		fragmentIndex = 0;
		getNewImage = isLastFragment = true;
		return buf;
	}

	isLastFragment = false;
	fragmentIndex ++;
	size = PACK_SIZE;
	return buf;

	
}

static char data[IR_Image::SIZE];

const char * ImageProcessor::GetNextFrame(int& size)
{
	/*
	const char * buf;
	Mat frame, resizedFrame;
	static vector<uchar> encoded;
	cap >> frame;
	encoded.clear();

	if (frame.size().width == 0)
	{
		size = -1;
		return NULL;
	}
	
	resize(frame, resizedFrame, Size(FRAME_WIDTH, FRAME_HEIGHT), 0, 0, INTER_LINEAR);
	if (resizedFrame.size().width == 0 || resizedFrame.size().height == 0)
	{
		size = -1;
		return NULL;
	}

	vector <int> compressionParams;
	compressionParams.push_back(CV_IMWRITE_JPEG_QUALITY);
	compressionParams.push_back(ENCODE_QUALITY);

	imencode(".jpg", resizedFrame, encoded, compressionParams);
	
	buf = (const char *)encoded.data();
	
	int s = (1+(encoded.size()-1)/PACK_SIZE)*PACK_SIZE;
	
	encoded.resize(s);
	size = encoded.size();
	return buf;

	*/

}

MovieProcessor::MovieProcessor(const string& fileName)
	: ImageProcessor()
{
	/*

	if (fileName.length())
	{

		movieFile.open(fileName, ios::binary);
		
		assert(movieFile);

	}

	*/


}

const char* MovieProcessor::GetNextFrame(int& size)
{



	char *p = new char[100];
	return p;
}
MovieProcessor::~MovieProcessor()
{
	movieFile.close();
}


