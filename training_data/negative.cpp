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

Mat image;
const char* namedwindow = "Image";
int ch_flag =1;
int n=1;
int check =3;
int click_monitor=1;
CvRect Box;
int selection = 0;

void CallBackFunc(int event, int x, int y, int flags, void* param)
{ 
     
     Mat img_new=image.clone();
     Mat Roi;
     if  ( event == 1 )
     {
        if (x-64<0 || y-128<0) return;
	else {
	rectangle (img_new,cvRect( x-64, y-128, 128, 256 ),Scalar( 0, 255, 255 ),1,8) ;
	Box=cvRect( x-64, y-128, 128, 256 );
	imshow("Image", img_new);
	click_monitor=0;
	waitKey(2);
	}
     }

     
     else if  ( event == EVENT_RBUTTONDOWN )
     {    
	if (click_monitor == 0)
	  {
		Roi = image(Box).clone();
		  string save_name="/home/mayank/sports_analysis/training_data/neg1/";
		  stringstream ss;
		  ss << n*4;
		  string num1 = ss.str();
		  save_name.append(num1);
		  save_name.append(".jpg");
		  resize(Roi, Roi, Size(64,128), 0.5, 0.5, INTER_CUBIC);
		  imwrite(save_name,Roi);
		  cout << "Saved the cropped image "<<num1 << endl;
	}
	  n++;
	  ch_flag=1;
	  click_monitor=1;
     }
     else if  ( event == EVENT_MBUTTONDOWN )
     {
          cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
     }
	waitKey(2);
     
}

int main() {
    	cout << "Enter the number to start from (if do not know then set it as 1)  "; 
	int n_new;
	cin >> n_new;
	n=n_new/4;
	cout << endl;
	while (1){
	setMouseCallback("Image", CallBackFunc,  NULL);	
	namedWindow("Image", CV_WINDOW_AUTOSIZE );
		if (ch_flag==1){
			check=4;
			string open_name;
			stringstream os;
			os << n*4;
			string num = os.str();
			open_name.append("/home/mayank/sports_analysis/frame_extract/frames1/");				
			open_name.append(num);
			open_name.append(".jpg");
			image = imread(open_name);
			imshow("Image", image);
			ch_flag=0;
			}
			//set the callback function for any mouse event		
		waitKey(2);
	}
	return 0;
 }
