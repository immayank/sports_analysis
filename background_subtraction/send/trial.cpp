#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
#include<math.h>

using namespace cv;
using namespace std;

int threshold_value = 30;
RNG rng(12345);
Point2f Player1pos;
int check_flag=1;
float alpha = 0;

void CallBackFunc(int event, int x, int y, int flags, void* param){ 
	if (event == 1){
//		if (check_flag==0){
			Player1pos.x=x;
			Player1pos.y=y;
			check_flag=1;
			std::cout <<"Player1 Identified ";
			std::cout << Player1pos.x <<" ";
			std::cout << Player1pos.y <<std::endl;
			waitKey(2);
//		}
	}
}


int main()
{
	VideoCapture feed( "/media/Work-sony/Sports_analysis/TT/1.MPG");
	Mat image;
	Mat background = imread("background1.jpg");
	Mat gray_background;
	cvtColor(background, gray_background, CV_BGR2GRAY);
	// Mat image = imread ( "/home/mayank/Pictures/Webcam/image.jpg");
	Mat foreground,diff;
	BackgroundSubtractorMOG2 mog;
	//namedWindow( "Foreground ", CV_WINDOW_AUTOSIZE );
	feed.set(CV_CAP_PROP_POS_MSEC, 35000); //start the video at 20s
	while(1){
		Mat dst;
		Mat gray_image;
		feed >> image;
		cvtColor(image, gray_image, CV_BGR2GRAY);
		//imshow("video1",diff);

		createTrackbar( "Value","Contours", &threshold_value,200, NULL );
		absdiff(background,image,diff);
		cvtColor(diff, diff, CV_BGR2GRAY);
//		absdiff(gray_background,gray_image,diff);
		threshold(diff,foreground,16,255,THRESH_BINARY);
//		mog(image,foreground,-2);
//		threshold(foreground,foreground,2,255,THRESH_BINARY);
		
		medianBlur(foreground,foreground,7);
//		blur(foreground,foreground,Size(threshold_value,threshold_value));		
//		medianBlur(foreground,foreground,9);
//		erode(foreground,foreground,Mat());
//		dilate(foreground,foreground,Mat());
		imshow("video2",foreground);
		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;
		findContours( foreground, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
		
		vector<vector<Point> > contours_poly( contours.size() );
		vector<Rect> boundRect( contours.size() );
		vector<Point2f>center( contours.size() );
		vector<float>Distance( contours.size() );
		vector<float>radius( contours.size() );

		for( int i = 0; i < contours.size(); i++ ){
			approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
			boundRect[i] = boundingRect( Mat(contours_poly[i]) );
			minEnclosingCircle( (Mat)contours_poly[i], center[i], radius[i] );
		}
		
		//Mat drawing = Mat::zeros( foreground.size(), CV_8UC3 );
		image.copyTo(dst,foreground);

		vector<Rect> newrect;

		for( int i = 0; i< contours.size(); i++ ){
			if (contourArea(contours_poly[i])>3850){
//				Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
//				drawContours( drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
				if (boundRect[i].area()>1000){
					newrect.push_back(boundRect[i]);
					rectangle( image, boundRect[i].tl(), boundRect[i].br(), Scalar(200,200,0), 2, 8, 0 );
//					circle( drawing, center[i], (int)radius[i], color, 2, 8, 0 );
					circle( image, Point2f(boundRect[i].x+(boundRect[i].width)/2,
					boundRect[i].y+(boundRect[i].height)/2), 2, Scalar(200,200,0), 2, 2, 0 );
				}
				
			}
		}
		setMouseCallback("Contours", CallBackFunc,  NULL);		
		
		for( int i = 0; i< newrect.size(); i++ ){
			 Distance[i] =sqrt( pow(Player1pos.x-newrect[i].x-(newrect[i].width)/2,2)+
					pow(Player1pos.y-newrect[i].y-(newrect[i].height)/2,2));
//			cout << pow(Player1pos.x-newrect[i].x-(newrect[i].width)/2,2);
//			std::cout<<Player1pos.x<<" "<<Player1pos.y<<std::endl;
//			std::cout<<newrect[i].x+(newrect[i].width)/2<<" "<<newrect[i].y+(newrect[i].height)/2<<std::endl;
			circle( image, Player1pos, 2, Scalar(0,200,0), 2, 2, 0 );
			if (Distance[i] < 30){
				stringstream os;
				os << i;
				string num = os.str();	
				putText( image,"Player 1", newrect[i].tl(), 1,1.5,Scalar(0,00,200),2,8);
//				std::cout << i <<" "<< Distance[i]<<std::endl;
//				cout << "distance "<<i<<" is "<<Distance[i]<<endl;				
//				Player1pos.x=(1-alpha)*(newrect[i].x+(newrect[i].width)/2)+alpha*(Player1pos.x);
//				Player1pos.y=(1-alpha)*(newrect[i].y+(newrect[i].height)/2)+alpha*(Player1pos.y);
				Player1pos.x=(1-alpha)*(newrect[i].x+(newrect[i].width)/2)+alpha*(Player1pos.x);
				Player1pos.y=(1-alpha)*(newrect[i].y+(newrect[i].height)/2)+alpha*(Player1pos.y);
				
				
			}
		}

		imshow( "Contours", image );
		
		//imshow("video3",dst);
		//imshow("video4",image);
		
		char key = (char) waitKey(20);
		if(key == 32){
		//	imwrite("/home/mayank/dst.jpg",dst);
			}
		}
	   // return 0;
}
