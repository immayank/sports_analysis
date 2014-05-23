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
	VideoCapture feed( "/media/Work-sony/Sports_analysis/TT/4.MPG");
	Mat check;
	int n=1;

   while(feed.isOpened()){
	feed >> check;
	if (check.rows==0){
		cout << "End of file reached \n";	
		break;
	}
	if (n%4 == 0){	
		string filename;
		filename.append("frames4/");
		stringstream ss;
		ss << n;
		string num = ss.str();
	   	filename.append(num);
	   	filename.append(".jpg");
		imwrite(filename,check);
	}
	imshow("video_view",check);
	n++;	
	waitKey(2);
	}
    return 0;
 }
