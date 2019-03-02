#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

const int fps = 30;

int main()
{
	// initialize and allocate memory to load the video stream from camera
	VideoCapture cam_0(0);
	VideoCapture cam_1(1);

	// check that the camera is open
	if (!cam_0.isOpened()) { return -1; }
	if (!cam_1.isOpened()) { return -1; }

	// store resolution of the video
	int frameWidth_0 = cam_0.get(CAP_PROP_FRAME_WIDTH);
	int frameHeight_0 = cam_0.get(CAP_PROP_FRAME_HEIGHT);
	int frameWidth_1 = cam_1.get(CAP_PROP_FRAME_WIDTH);
	int frameHeight_1 = cam_1.get(CAP_PROP_FRAME_HEIGHT);

	// create video writer
	VideoWriter output_0("output_0.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, Size(frameWidth_0, frameHeight_0));
	VideoWriter output_1("output_1.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, Size(frameWidth_1, frameHeight_1));

	while (true)
	{
		// grab and retrieve each frame of the video sequentially
		Mat frame_0;
		cam_0 >> frame_0;
		Mat frame_1;
		cam_1 >> frame_1;

		// display the frame
		imshow("Cam 0", frame_0);
		imshow("Cam 1", frame_1);

		// write video frame
		output_0.write(frame_0);
		output_1.write(frame_1);

		// wait for keypress to exit
		int c = waitKey(40);			// wait 40 milliseconds
		if (27 == char(c)) { break; }	// exit loop if user pressed "esc" key
	}

	// release video capture and writer
	output_0.release();
	cam_0.release();
	output_1.release();
	cam_1.release();

	// destroy all windows
	destroyAllWindows();

	return 1;
}