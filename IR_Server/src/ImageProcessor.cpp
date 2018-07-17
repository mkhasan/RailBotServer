


#include "ImageProcessor.h"
#include "utils.h"

using namespace std;



extern ACE_SV_Semaphore_Complex mutex;
extern IR_Image *pImage;

using namespace RB_ROBOT_UTILS;

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


	Squeezer *p = Squeezer::Instance();


	int ret = p->Initialize();
	RB_ASSERT(ret == 0);



}


const char* ImageProcessor::GetNextFrameFragment(int& size, bool& isLastFragment, unsigned short & width, unsigned short & height, unsigned char & pixelSize)
{

	const char* buf;
	static int testCount=0;
	static unsigned char _pixelSize=0;
	static unsigned short _width=0, _height=0;

	
	if (getNewImage)
	{
		imageData = GetNextFrame(imageSize, _width, _height, _pixelSize);
		fragmentIndex = 0;
		
		if (imageSize == -1)
		{
			getNewImage = false;
			size = -1;
			return NULL;
		}

		RB_DEBUG("Image size %d PACK_SIZE %d \n", imageSize, PACK_SIZE);
		if (imageSize <= PACK_SIZE)
		{
			
			isLastFragment = true;
			size = imageSize;
			return imageData;
		}

		getNewImage = isLastFragment = false;
		fragmentIndex++;
		size = PACK_SIZE;
		width = _width;
		height = _height;
		pixelSize = _pixelSize;
		return imageData;
	}

	if (fragmentIndex == 0)
	{
		size = -1;
		return NULL;
	}

	width = _width;
	height = _height;
	pixelSize = _pixelSize;

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



const char * ImageProcessor::GetNextFrame(int& size, unsigned short & width, unsigned short & height, unsigned char & pixelSize)
{
	static char data[IR_Image::SIZE];
	static char compData[IR_Image::SIZE];
	size_t compSize = sizeof(compData);
	size_t uncompSize;
	size = 0;

	RB_INFO("getting next fram ...\n");

	if (mutex.acquire () == -1) {
		RB_ERROR(("ImageProcessor::GetNextFrame: Error in acquiring mutex\n"), -1);
		exit(-1);
	}


	if(pImage) {
		size = pImage->width*pImage->height*pImage->pixelSize;

		//RB_DEBUG("size is %d \n", size);

		RB_ASSERT(size <= sizeof(data));
		memcpy(data, pImage->data, size);
		width = pImage->width;
		height = pImage->height;
		pixelSize = pImage->pixelSize;

	}

	if (mutex.release () == -1) {
		RB_ERROR(("ImageProcessor::GetNextFrame: Error in releasing mutex\n"), -1);
		exit(-1);
	}

	if(size > 0) {
		uncompSize = size;

		Squeezer *p = Squeezer::Instance();
		int ret = p->Compress((lzham_uint8 *)compData, &compSize, (const lzham_uint8 *)data, uncompSize);

		RB_ASSERT(ret == 0);

		size = compSize;

		return compData;

	}

	//int ret = p->Compress((lzham_uint8 *)dest, &destLength, (const lzham_uint8 *)str, length);

	return NULL;


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


