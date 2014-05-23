#include <iostream>
#include <opencv2/opencv.hpp>
 
using namespace std;
using namespace cv;
 
int main(){
	VideoCapture feed( "/media/Work-sony/Sports_analysis/TT/1.MPG");
	Mat check;
	Mat fgmask;
	BackgroundSubtractorMOG2 mog;
	
   while(feed.isOpened()){
	feed >> check;
//	cout << check.size();    
	mog(check,fgmask,-2);
//	mog.set("nmixtures", 3);
//	mog.set("detectShadows",1);
	imshow("video_view",fgmask);
    	waitKey(20);
	}
return 0;
}
