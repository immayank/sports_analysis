#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

using namespace cv;
using namespace std;


int main() {
   VideoCapture feed( "/media/Work-sony/Sports_analysis/TT/1.MPG");
	Mat check;

   while(feed.isOpened()){
	feed >> check;
   
	cout << check.size();    
	imshow("video_view",check);
    	waitKey(200);
	}
    return 0;
 }
