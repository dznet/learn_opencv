#include </opt/opencv/include/opencv2/opencv.hpp>
#include </opt/opencv/include/opencv/highgui.h>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
  string window_name = "cam_rec";
  string filename = "cam_rec.avi";

  namedWindow(window_name, WINDOW_AUTOSIZE);
  VideoCapture cap(CAP_ANY);

  if (!cap.isOpened())
  {
    cout << "Cannot open the video camera" << endl;
    return -1;
  }

  int width = static_cast<int>(cap.get(CAP_PROP_FRAME_WIDTH));
  int height = static_cast<int>(cap.get(CAP_PROP_FRAME_HEIGHT));
  int fps = cap.get(CAP_PROP_FPS);

  printf("[ %d x %d\t%d fps ]\n", width, height, fps );

  Size size(width, height);
  VideoWriter oVideoWriter(filename, VideoWriter::fourcc('M','J','P','G'), fps, size, true);

  if (!oVideoWriter.isOpened())
  {
    cout << "Cannot save the video to a file" << endl;
    return -1;
  }

  while(true)
  {
    Mat frame;
    if (!cap.read(frame))
    {
      cout << "Video camera is disconnected" << endl;
      break;
    }

    oVideoWriter.write(frame);
    imshow(window_name, frame);

    if (waitKey(33) == 27)
    {
      cout << "Esc key is pressed by the user. Stopping the video" << endl;
      break;
    }
  }

  oVideoWriter.release();
  return 0;
}
