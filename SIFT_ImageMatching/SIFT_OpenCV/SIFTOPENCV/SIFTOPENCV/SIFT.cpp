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

	char* img1_file = "C:/images/box2.png"; // "./b/7.bmp"�Ƃ�  ;
	char* img2_file = "C:/images/box_in_scene.png"; // "./in/7.bmp"�Ƃ� ;

	// �摜1��2�̓ǂݍ���
	Mat tmp = cv::imread( img1_file, 1 );
	Mat in  = cv::imread( img2_file, 1 );

	/* threshold      = 0.04;
	   edge_threshold = 10.0;
	   magnification  = 3.0;	*/

	// SIFT�̓����_���o�E�����ʒ��o��
	cv::SiftFeatureDetector detector( 0.05, 5.0 );
	cv::SiftDescriptorExtractor extractor( 3.0 );
	
	//SURF�̏ꍇ
	/*cv::SurfFeatureDetector detector();
	cv::SurfDescriptorExtractor extractor();*/
	
	// �����_�����o
	std::vector<cv::KeyPoint> keypoints1, keypoints2;
	detector.detect( tmp, keypoints1 );
	detector.detect( in, keypoints2 );

	// �����_��`��
	Mat feat1,feat2;
	drawKeypoints(tmp,keypoints1,feat1,Scalar(255, 255, 255),DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	drawKeypoints(in,keypoints2,feat2,Scalar(255, 255, 255),DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	imwrite( "feat1.bmp", feat1 );
	imwrite( "feat2.bmp", feat2 );
	int key1 = keypoints1.size();
	int key2 = keypoints2.size();
	printf("Keypoint1=%d \nKeypoint2=%d", key1, key2);

	// �����_�ɂ���������ʂ𒊏o
	Mat descriptor1,descriptor2;
	extractor.compute( tmp, keypoints1, descriptor1 );
	extractor.compute( in, keypoints2, descriptor2 );
	/*int desc1 = descriptor1.size; 
	int desc2 = descriptor2.size;
	printf("Descriptor1=%d \nDescriptor2=%d", desc1, desc2);*/

	// �Ή��_�����߂�
	std::vector<cv::DMatch> matches;

	// L2������p�����S�T���Ή��t��
	BruteForceMatcher<L2<float> > matcher;
	// Flann�x�[�X�̑Ή��t��
	//FlannBasedMatcher matcher;

	// �����ʔ�r�ɂ������_�̑Ή��t��
	matcher.match( descriptor1, descriptor2, matches );

	// sort matches
	int num_val = 80;
	nth_element(matches.begin(),matches.begin()+num_val-1,matches.end());
	matches.erase(matches.begin()+num_val,matches.end());
	
	// ���ʂ�`��
	Mat result;
	drawMatches( tmp, keypoints1, in, keypoints2, matches, result );

	// ���ʂ��o��
	imwrite( "result.bmp", result );
	
	// ���ʂ�\��
	namedWindow("SIFT", CV_WINDOW_AUTOSIZE );
	imshow("SIFT", result);
	waitKey(0); //�����L�[�������ƏI��

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


//	// �摜1�̓ǂݍ���
//	Mat img1 = imread( "in1.jpg" );
//
//	// �摜2�̓ǂݍ���
//	Mat img2 = imread( "in2.jpg" );
//
//	// SIFT�p�̃f�t�H���g�p�����[�^��ݒ�
//	double threshold = SIFT::DetectorParams::GET_DEFAULT_THRESHOLD();
//	double edge_threshold = SIFT::DetectorParams::GET_DEFAULT_EDGE_THRESHOLD();
//	double magnification = SIFT::DescriptorParams::GET_DEFAULT_MAGNIFICATION();
//
//	// SIFT�̓����_���o�E�����ʒ��o���p��
//	SiftFeatureDetector detector( threshold, edge_threshold );
//	SiftDescriptorExtractor extractor( magnification );
//	/*
//	// SURF�̏ꍇ
//	SurfFeatureDetector detector();
//	SurfDescriptorExtractor extractor();
//	*/
//
//	// �摜1��������_�����o
//	std::vector keypoints1;
//	detector.detect( img1, keypoints1 );
//
//	// �摜2��������_�����o
//	std::vector keypoints2;
//	detector.detect( img2, keypoints2 );
//
//	// �摜1�̓����_�ɂ���������ʂ𒊏o
//	Mat descriptor1;
//	extractor.compute( img1, keypoints1, descriptor1 );
//
//	// �摜2�̓����_�ɂ���������ʂ𒊏o
//	Mat descriptor2;
//	extractor.compute( img2, keypoints2, descriptor2 );
//
//	// �Ή��_�����߂�
//	std::vector matches;
//
//	// L2������p�����S�T���Ή��t��
//	BruteForceMatcher&lt; L2 &gt; matcher;
//	// Flann�x�[�X�̑Ή��t��
////	FlannBasedMatcher matcher;
//
//	// �����ʔ�r�ɂ������_�̑Ή��t��
//	matcher.match( descriptor1, descriptor2, matches );
//
//	// ���ʂ�`��
//	Mat result;
//	drawMatches( img1, keypoints1, img2, keypoints2, matches, result );
//
//	// ���ʂ��o��
//	imwrite( "result.jpg", result );
//
//	return 0;

