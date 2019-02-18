#include <opencv2/opencv.hpp>
#include <opencv2/legacy/legacy.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/nonfree/features2d.hpp>

#ifdef _DEBUG
    //Debugモードの場合
    #pragma comment(lib,"opencv_core240d.lib")
    #pragma comment(lib,"opencv_imgproc240d.lib")
    #pragma comment(lib,"opencv_highgui240d.lib")
    #pragma comment(lib,"opencv_objdetect240d.lib")
    #pragma comment(lib,"opencv_contrib240d.lib")
    #pragma comment(lib,"opencv_features2d240d.lib")
    #pragma comment(lib,"opencv_flann240d.lib")
    #pragma comment(lib,"opencv_gpu240d.lib")
    #pragma comment(lib,"opencv_haartraining_engined.lib")
    #pragma comment(lib,"opencv_legacy240d.lib")
    #pragma comment(lib,"opencv_ts240d.lib")
    #pragma comment(lib,"opencv_video240d.lib")
	#pragma comment(lib,"opencv_nonfree240d.lib")
#else
    //Releaseモードの場合
    #pragma comment(lib,"opencv_core240.lib")
    #pragma comment(lib,"opencv_imgproc240.lib")
    #pragma comment(lib,"opencv_highgui240.lib")
    #pragma comment(lib,"opencv_objdetect240.lib")
    #pragma comment(lib,"opencv_contrib240.lib")
    #pragma comment(lib,"opencv_features2d240.lib")
    #pragma comment(lib,"opencv_flann240.lib")
    #pragma comment(lib,"opencv_gpu240.lib")
    #pragma comment(lib,"opencv_haartraining_engined.lib")
    #pragma comment(lib,"opencv_legacy240.lib")
    #pragma comment(lib,"opencv_ts240.lib")
    #pragma comment(lib,"opencv_video240.lib")
	#pragma comment(lib,"opencv_nonfree240.lib")
#endif

using namespace cv;
using namespace std;

int main(int argc, char **argv){

	Mat img1 = imread("imageR.jpg",1);
	Mat img2 = imread("imageL.jpg",1);
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
	int num_val = 100;
	nth_element(matches.begin(),matches.begin()+num_val-1,matches.end());
	matches.erase(matches.begin()+num_val,matches.end());

	// draw matches
	Mat matchim;
	//vector<char> dmy;
	drawMatches(img1,key1,img2,key2,matches,matchim,Scalar::all(-1),Scalar(200,200,200));
	imwrite("match.bmp",matchim);

	return 0;
}