#include "opencv2\opencv.hpp"

#include <stdio.h>
#include <opencv2/legacy/legacy.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/nonfree/features2d.hpp>

using namespace std;
using namespace cv;

//
int main( int argc, char* argv[] )
{

	char* img1_file = "C:/images/box2.png"; // "./b/7.bmp"とか  ;
	char* img2_file = "C:/images/box_in_scene.png"; // "./in/7.bmp"とか ;

	// 画像1と2の読み込み
	Mat tmp = cv::imread( img1_file, 1 );
	Mat in  = cv::imread( img2_file, 1 );

	/* threshold      = 0.04;
	   edge_threshold = 10.0;
	   magnification  = 3.0;	*/

	// SIFTの特徴点検出・特徴量抽出器
	cv::SiftFeatureDetector detector( 0.05, 5.0 );
	cv::SiftDescriptorExtractor extractor( 3.0 );
	
	//SURFの場合
	/*cv::SurfFeatureDetector detector();
	cv::SurfDescriptorExtractor extractor();*/
	
	// 特徴点を検出
	std::vector<cv::KeyPoint> keypoints1, keypoints2;
	detector.detect( tmp, keypoints1 );
	detector.detect( in, keypoints2 );

	// 特徴点を描画
	Mat feat1,feat2;
	drawKeypoints(tmp,keypoints1,feat1,Scalar(255, 255, 255),DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	drawKeypoints(in,keypoints2,feat2,Scalar(255, 255, 255),DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	imwrite( "feat1.bmp", feat1 );
	imwrite( "feat2.bmp", feat2 );
	int key1 = keypoints1.size();
	int key2 = keypoints2.size();
	printf("Keypoint1=%d \nKeypoint2=%d", key1, key2);

	// 特徴点における特徴量を抽出
	Mat descriptor1,descriptor2;
	extractor.compute( tmp, keypoints1, descriptor1 );
	extractor.compute( in, keypoints2, descriptor2 );
	/*int desc1 = descriptor1.size; 
	int desc2 = descriptor2.size;
	printf("Descriptor1=%d \nDescriptor2=%d", desc1, desc2);*/

	// 対応点を求める
	std::vector<cv::DMatch> matches;

	// L2距離を用いた全探索対応付け
	BruteForceMatcher<L2<float> > matcher;
	// Flannベースの対応付け
	//FlannBasedMatcher matcher;

	// 特徴量比較による特徴点の対応付け
	matcher.match( descriptor1, descriptor2, matches );

	// sort matches
	int num_val = 80;
	nth_element(matches.begin(),matches.begin()+num_val-1,matches.end());
	matches.erase(matches.begin()+num_val,matches.end());
	
	// 結果を描画
	Mat result;
	drawMatches( tmp, keypoints1, in, keypoints2, matches, result );

	// 結果を出力
	imwrite( "result.bmp", result );
	
	// 結果を表示
	namedWindow("SIFT", CV_WINDOW_AUTOSIZE );
	imshow("SIFT", result);
	waitKey(0); //何かキーを押すと終了

	return 0;
}









//#include <opencv2/opencv.hpp>
//#include <opencv2/nonfree/nonfree.hpp>
//
//
//using namespace cv;
//using namespace std;
//
////
//int main(const char* fName)
//{
//int featureNum = 0;
//	char tmp[250] = {0};
//
//	Mat src = imread(fName,1);
//	Mat gray;
//
//	cvtColor(src,gray,CV_BGR2GRAY);
//
//	SIFT calc_sift = SIFT();
//	vector<KeyPoint> siftKeyVector;
//
//	Mat siftDescriptor = Mat();
//
//	calc_sift(gray,Mat(),siftKeyVector,siftDescriptor);
//
//	vector<KeyPoint>::iterator it = siftKeyVector.begin();
//	vector<KeyPoint>::iterator it_end = siftKeyVector.end();
//
//	for(; it!= it_end; ++it){
//		featureNum++;
//		circle(src,Point(it->pt.x, it->pt.y),saturate_cast<int>(it->size*0.25),Scalar(0,255,255));
//	}
//	
//	int len = strlen(fName);
//	strncpy(tmp,fName,len-4);
//	strcat(tmp,"_SIFT.png");
//	imwrite(tmp,src);
//
//	return 0;
//
//}


//	// 画像1の読み込み
//	Mat img1 = imread( "in1.jpg" );
//
//	// 画像2の読み込み
//	Mat img2 = imread( "in2.jpg" );
//
//	// SIFT用のデフォルトパラメータを設定
//	double threshold = SIFT::DetectorParams::GET_DEFAULT_THRESHOLD();
//	double edge_threshold = SIFT::DetectorParams::GET_DEFAULT_EDGE_THRESHOLD();
//	double magnification = SIFT::DescriptorParams::GET_DEFAULT_MAGNIFICATION();
//
//	// SIFTの特徴点検出・特徴量抽出器を用意
//	SiftFeatureDetector detector( threshold, edge_threshold );
//	SiftDescriptorExtractor extractor( magnification );
//	/*
//	// SURFの場合
//	SurfFeatureDetector detector();
//	SurfDescriptorExtractor extractor();
//	*/
//
//	// 画像1から特徴点を検出
//	std::vector keypoints1;
//	detector.detect( img1, keypoints1 );
//
//	// 画像2から特徴点を検出
//	std::vector keypoints2;
//	detector.detect( img2, keypoints2 );
//
//	// 画像1の特徴点における特徴量を抽出
//	Mat descriptor1;
//	extractor.compute( img1, keypoints1, descriptor1 );
//
//	// 画像2の特徴点における特徴量を抽出
//	Mat descriptor2;
//	extractor.compute( img2, keypoints2, descriptor2 );
//
//	// 対応点を求める
//	std::vector matches;
//
//	// L2距離を用いた全探索対応付け
//	BruteForceMatcher&lt; L2 &gt; matcher;
//	// Flannベースの対応付け
////	FlannBasedMatcher matcher;
//
//	// 特徴量比較による特徴点の対応付け
//	matcher.match( descriptor1, descriptor2, matches );
//
//	// 結果を描画
//	Mat result;
//	drawMatches( img1, keypoints1, img2, keypoints2, matches, result );
//
//	// 結果を出力
//	imwrite( "result.jpg", result );
//
//	return 0;

