#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>

using namespace cv;
using namespace std;

void findRec(Mat img);
void findcorner(Mat img);
void findRedball(Mat img);
void findYellowball(Mat img);
void findWhiteball(Mat img);
void convertfinalcoord(int x, int y, float &resultx, float &resulty);

int my;
int mx;
int dry;
int drx;
int dly;
int dlx;
int ury;
int urx;
int uly;
int ulx;
int rby;
int rbx;
int yby;
int ybx;
int wby;
int wbx;

Mat linepic;

int main(int argc, char* argv[]) {
	
	float yx, yy;	// 노란공 좌표
	float rx, ry;	// 빨간공 좌표
	float wx, wy;	// 흰색공 좌표

	string filename;
	cout << "type the file name [xxx.jpg] : ";
	cin >> filename;
	
	
	Mat image = imread(filename);		//이미지 로드
	if (image.empty()) {				//예외처리
		cout << "file doesn't exist!" << endl;
		return -1;
		exit(1);
	}

	imshow("original", image);	//원본 이미지 표시
	
	findRec(image);			//당구대 검출
	findRedball(image);		//빨간공 검출
	findYellowball(image);	//노란공 검출
	findWhiteball(image);	//흰공 검출

	cout << "white ball coord" << endl;
	convertfinalcoord(wbx, wby, wx, wy);

	cout << "red ball coord" << endl;
	convertfinalcoord(rbx, rby, rx, ry);

	cout << "yellow ball coord" << endl;
	convertfinalcoord(ybx, yby, yx, yy);


	waitKey();
}
void convertfinalcoord(int x, int y, float &resultx, float &resulty) {

	int leftcount = 0, rightcount = 0;
	int upcount = 0, downcount = 0;

	for (int i = x; ; i--) {
		if (!((int)linepic.at<uchar>(y, i)))
			break;
		leftcount++;
	}
	//cout << leftcount << endl;
	
	for (int i = x; ; i++) {
		if (!((int)linepic.at<uchar>(y, i)))
			break;
		rightcount++;
	}
	//cout << rightcount << endl;

	for (int i = y;; i--) {
		if (!((int)linepic.at<uchar>(i, x)))
			break;
		upcount++;
	}
	//cout << upcount << endl;

	for (int i = y;; i++) {
		if (!((int)linepic.at<uchar>(i, x)))
			break;
		downcount++;
	}
	
	//cout << downcount << endl;

	// -122.4 ~ 122.4 / -61.2 ~ 61.2

	resultx = ((float)leftcount / (leftcount + rightcount))*122.4;
	resultx -= 61.2;

	
	resulty = ((float)downcount / (upcount + downcount))*244.8;
	resulty -= 122.4;

	cout << fixed;
	cout.precision(1);
	cout << "(" << resultx << ", " << resulty << ")" << endl;

}
void findWhiteball(Mat img) {
	
	Mat imgHSV;
	Mat imgThresholded;

	cvtColor(img, imgHSV, COLOR_BGR2HSV);
	inRange(imgHSV, Scalar(0, 65, 0), Scalar(179, 255, 255), imgThresholded);

	erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	imshow("white ball", imgThresholded);

	for (int y = uly + 3; y <= dly - 3; y++) {

		int x;

		for (x = dlx;; x++) {
			//cout << x << endl;
			if (!((int)linepic.at<uchar>(y, x)))
				break;
		}
		x = x + 3;


		for (; ; x++) {
			//cout << x << endl;

			if (!((int)linepic.at<uchar>(y, x + 3)))
				break;

			if (imgThresholded.at<uchar>(y, x) != 255) {	//white = 255
				if (wby < y) {
					wby = y;
					wbx = x;
				}
			}
		}

	}
	//cout << "white ball y : " << wby << endl;
	//cout << "white ball x : " << wbx << endl;

}
void findYellowball(Mat img) {
	Mat result;

	inRange(img, Scalar(30, 30, 80), Scalar(100, 100, 100), result);
	dilate(result, result, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	
	imshow("yellow ball", result);
	
	

	for (int y = uly + 3; y <= dly - 3; y++) {

		int x;

		for (x = dlx;; x++) {
			//cout << x << endl;
			if (!((int)linepic.at<uchar>(y, x)))
				break;
		}
		x = x + 3;

		
		for (; ; x++) {
			//cout << x << endl;

			if (!((int)linepic.at<uchar>(y, x + 3)))
				break;

			if (result.at<uchar>(y, x) == 255) {	//white = 255
				if (yby < y) {
					yby = y;
					ybx = x;
				}
			}
		}

	}
	//cout << "yellow ball y : " << yby << endl;
	//cout << "yellow ball x : " << ybx << endl;

}
void findRedball(Mat img) {

	Mat imgHSV;
	Mat imgThresholded;

	cvtColor(img, imgHSV, COLOR_BGR2HSV);
	inRange(imgHSV, Scalar(113, 49, 168), Scalar(179, 255, 255), imgThresholded);

	erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	imshow("red ball", imgThresholded);

	/*cout << imgThresholded.cols << endl;
	cout << imgThresholded.rows << endl;*/

	rbx = 0;
	rby = 0;

	

	//imshow("linepic", linepic);
	for (int y = uly; y <= dly; y++) {
		
		int x;
		
		for (x = dlx;; x++) {
			//cout << x << endl;
			if (!((int)linepic.at<uchar>(y, x)))
				break;
		}
		x = x + 1;
		for (; ; x++) {
			//cout << x << endl;
			
			if (!((int)linepic.at<uchar>(y, x)))
				break;

			if (imgThresholded.at<uchar>(y, x) == 255) {	//white = 255
				if (rby < y) {
					rby = y;
					rbx = x;
				}
			}
		}
		
	}
	//cout << "red ball y : " << rby << endl;
	//cout << "red ball x : " << rbx << endl;

}
void findRec(Mat img) {
	
	
	Mat imgHSV;
	Mat imgThresholded;
	Mat drawline(img.size(), CV_8U, Scalar(255));
	Mat drawline2(img.size(), CV_8U, Scalar(255));
	

	cvtColor(img, imgHSV, COLOR_BGR2HSV);

	inRange(imgHSV, Scalar(94, 131, 47), Scalar(118, 253, 255), imgThresholded);
	
	erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

	//imshow("isolate color", imgThresholded);
	
	Canny(imgThresholded, imgThresholded, 125, 250);

	//imshow("result", imgThresholded);


	//vector<Vec4i> lines;
	vector<Vec4f> lines;

	//HoughLinesP(imgThresholded, lines, 1, CV_PI / 180, 100, 1000, 50);
//	HoughLinesP(imgThresholded, lines, 1, CV_PI / 180, 20);


	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		line(drawline, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 1, CV_AA);
	}


	//imshow("line_detect", drawline);
	

	my = img.rows / 2;
	mx = img.cols / 2;
	dry = img.rows / 2;
	drx = img.cols / 2;
	dly = img.rows / 2;
	dlx = img.cols / 2;
	ury = img.rows / 2;
	urx = img.cols / 2;
	uly = img.rows / 2;
	ulx = img.cols / 2;

	
	findcorner(drawline);
	
	imshow("linepic", linepic);



}
void findcorner(Mat mask) {
	Mat out(mask.size(), CV_8U, Scalar(255));
	for (int y = my; y < mask.rows; y++) {
		for (int x = mx; x < mask.cols; x++) {
			if ((mask.at<uchar>(y, x) != 255)) {
			
				int temp1 = (dry - my) * (dry - my) + (drx - mx) * (drx - mx);
				int temp2 = (y - my) * (y - my) + (x - mx) * (x - mx);

				
				if (temp1 < temp2) {
					dry = y;
					drx = x;
				}
			}
		}
	}
	
	for (int y = my; y < mask.rows; y++) {
		for (int x = 1; x < mx; x++) {
			if ((mask.at<uchar>(y, x) != 255)) {
				int temp1 = (dly - my) * (dly - my) + (dlx - mx) * (dlx - mx);
				int temp2 = (y - my) * (y - my) + (x - mx) * (x - mx);

				if (temp1 < temp2) {
					dly = y;
					dlx = x;
				}
			}
		}
	}
	
	int tempmx = mx;

	mx += (drx - dlx) / 6;
	for (int y = 1; y < mask.rows/2; y++) {
		for (int x = mask.cols/3*2; x < mask.cols; x++) {
			if ((mask.at<uchar>(y, x) != 255)) {
				int temp1 = (ury - my) * (ury - my) + (urx - mx) * (urx - mx);
				int temp2 = (y - my) * (y - my) + (x - mx) * (x - mx);

				if (temp1 < temp2) {
					ury = y;
					urx = x;
				}
			}
		}
	}
	mx = tempmx;
	mx -= (drx - dlx) / 6;
	
	for (int y = 1; y < mask.rows / 2; y++) {
		for (int x = 1; x < mask.cols / 3; x++) {
			if ((mask.at<uchar>(y, x) != 255)) {
				int temp1 = (uly - my) * (uly - my) + (ulx - mx) * (ulx - mx);
				int temp2 = (y - my) * (y - my) + (x - mx) * (x - mx);

				if (temp1 < temp2) {
					uly = y;
					ulx = x;
				}
			}
		}
	}
	
	line(out, Point(dlx, dly), Point(drx, dry), Scalar(0, 0, 255), 1);
	line(out, Point(dlx, dly), Point(ulx, uly), Scalar(0, 0, 255), 1);
	line(out, Point(urx, ury), Point(ulx, uly), Scalar(0, 0, 255), 1);
	line(out, Point(urx, ury), Point(drx, dry), Scalar(0, 0, 255), 1);

	linepic = out.clone();
}