#include <opencv2/opencv.hpp>
#include <opencv2/legacy/legacy.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/nonfree/features2d.hpp>

#ifdef _DEBUG
    //Debugモードの場合
    #pragma comment(lib,"opencv_core243d.lib")
    #pragma comment(lib,"opencv_imgproc243d.lib")
    #pragma comment(lib,"opencv_highgui243d.lib")
    #pragma comment(lib,"opencv_objdetect243d.lib")
    #pragma comment(lib,"opencv_contrib243d.lib")
    #pragma comment(lib,"opencv_features2d243d.lib")
    #pragma comment(lib,"opencv_flann243d.lib")
    #pragma comment(lib,"opencv_gpu243d.lib")
    #pragma comment(lib,"opencv_haartraining_engined.lib")
    #pragma comment(lib,"opencv_legacy243d.lib")
    #pragma comment(lib,"opencv_ts243d.lib")
    #pragma comment(lib,"opencv_video243d.lib")
	#pragma comment(lib,"opencv_nonfree243d.lib")
#else
    //Releaseモードの場合
    #pragma comment(lib,"opencv_core243.lib")
    #pragma comment(lib,"opencv_imgproc243.lib")
    #pragma comment(lib,"opencv_highgui243.lib")
    #pragma comment(lib,"opencv_objdetect243.lib")
    #pragma comment(lib,"opencv_contrib243.lib")
    #pragma comment(lib,"opencv_features2d243.lib")
    #pragma comment(lib,"opencv_flann243.lib")
    #pragma comment(lib,"opencv_gpu243.lib")
    #pragma comment(lib,"opencv_haartraining_engined.lib")
    #pragma comment(lib,"opencv_legacy243.lib")
    #pragma comment(lib,"opencv_ts243.lib")
    #pragma comment(lib,"opencv_video243.lib")
	#pragma comment(lib,"opencv_nonfree243.lib")
#endif

using namespace cv;
using namespace std;

int main(int argc, char **argv){

	Mat img1 = imread("box.png",1);
	Mat img2 = imread("box_in_scene.png",1);
	Mat gray1, gray2;
	cvtColor(img1,gray1,CV_BGR2GRAY);
	cvtColor(img2,gray2,CV_BGR2GRAY);
	
	/*//////////////////////////////////////////////////////////////////////////////
	// The number of best features to retain.
	// The features are ranked by their scores.
	// (measured in SIFT algorithm as the local contrast)
	//////////////////////////////////////////////////////////////////////////////*/
	int nFeatures = 0;
	/*//////////////////////////////////////////////////////////////////////////////
	// The number of layers in each octave. 
	// 3 is the value used in D. Lowe paper.
	// "The number of octaves is computed automatically from the image resolution."
	//////////////////////////////////////////////////////////////////////////////*/
	int nOctaveLayers = 3; 
	/*//////////////////////////////////////////////////////////////////////////////
	// The contrast threshold used to filter out weak features.
	// in semi-uniform (low-contrast) regions. 
	// The larger the threshold, the less features are produced by the detector.
	//////////////////////////////////////////////////////////////////////////////*/
	double contrastThreshold = 0.04; 
	/*//////////////////////////////////////////////////////////////////////////////
	// The threshold used to filter out edge-like features. 
	// the larger the edgeThreshold, the less features are filtered out.
	//////////////////////////////////////////////////////////////////////////////*/
	double edgeThreshold = 10.0; 
	/*//////////////////////////////////////////////////////////////////////////////
	// The sigma of the Gaussian applied to the input image at the octave #0.
	// If your image is captured with a weak camera with soft lenses, 
	// you might want to reduce the number.
	//////////////////////////////////////////////////////////////////////////////*/
	double sigma = 1.6;
	//SIFT Constructor
	SIFT sift = SIFT(nFeatures, nOctaveLayers, contrastThreshold, edgeThreshold, sigma);
	// Keypoint detection.
	vector<KeyPoint> key1;
	Mat desc1;
	vector<KeyPoint> key2;
	Mat desc2;
	// Calculate keypoints and desctiptors
	sift(gray1, Mat(), key1, desc1, false);
	sift(gray2, Mat(), key2, desc2, false);
	// Draw Key points
	Mat drawImg1, drawImg2;
	drawKeypoints(img1, key1, drawImg1, CV_RGB(255,255,0), DrawMatchesFlags::DEFAULT);
	drawKeypoints(img2, key2, drawImg2, CV_RGB(255,255,0), DrawMatchesFlags::DEFAULT);
	imwrite("save1.bmp", drawImg1);
	imwrite("save2.bmp", drawImg2);

	// Keypoint matching
	vector<DMatch> matches;
	BruteForceMatcher< L2<float> > matcher;
	matcher.match(desc1,desc2,matches);

	// sort matches
	int num_val = 80;
	nth_element(matches.begin(),matches.begin()+num_val-1,matches.end());
	matches.erase(matches.begin()+num_val,matches.end());

	// draw matches
	Mat matchim;
	//vector<char> dmy;
	drawMatches(img1,key1,img2,key2,matches,matchim,Scalar::all(-1),Scalar(200,200,200));
	imwrite("match.bmp",matchim);

	return 0;
}