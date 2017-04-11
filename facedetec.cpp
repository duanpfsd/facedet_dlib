#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sys/io.h>
#include <sys/time.h>
#include "dirent.h"

#include <opencv/cv.h>
#include <opencv/highgui.h>

#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>

using namespace dlib;
using namespace std;

int main(int argc, char** argv)
{
  frontal_face_detector detector = get_frontal_face_detector();

  std::ofstream infoout;
  infoout.open("./infoout/seetaface.txt", ofstream::out);
  infoout << "0  empty. " << endl;

  struct timeval starttime, endtime;
  gettimeofday(&starttime, 0);

  int ncount = 0;
  string test_dir = "/home/work/duanpengfei/testspeed2/picname.txt";
  ifstream  ist;
  string    st;
  ist.open(test_dir, ios_base::in);
  while (getline(ist, st))
  {
    istringstream iss(st);
    string imgname;
    iss >> imgname;
    imgname = "/home/work/duanpengfei/testspeed2/" + imgname;

    array2d<unsigned char> img_color;
    load_image(img_color, imgname);

    std::vector<rectangle> dets = detector(img_color);
    int face_num =  dets.size();

    cout << face_num << "  good  " << imgname << endl;
    infoout << face_num << "  good  " << imgname << endl;
  }

  gettimeofday(&endtime, 0);
  double timeuse = 1000000 * (endtime.tv_sec - starttime.tv_sec) + endtime.tv_usec - starttime.tv_usec;
  cout    << "Face detection and landmark consuming: " << timeuse / 1000 << "ms" << endl;
  infoout << "Face detection and landmark consuming: " << timeuse / 1000 << "ms" << endl;
  infoout.close();
  return 0;
}

