#include <opencv2/opencv.hpp>

#include <iostream>
#include <stdio.h>
#include <opencv2/legacy/legacy.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/nonfree/features2d.hpp>


using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
  //const char *usg = " [-num num] im1 im2";

  int num_val = 50;
  //const char *prg = argv[0];

  /*while(argc > 3) {
    if(!strcmp(argv[1],"-num")) {
      num_val = atoi(argv[2]); }
    else {
      cerr << "usage: " << prg << usg << endl;
      return 1; }
    argc -= 2; argv += 2; 
  }*/

  /*if(argc != 3) {
      cerr << "usage: " << prg << usg << endl;
      return 1; }*/

  Mat im1 = imread("C:/images/box.png",0);
  Mat im2 = imread("C:/images/box_in_scene.png",0);
  if(im1.empty() || im2.empty()){
    cerr << "file open error" << endl;
    return 1; }

  // Parameters for both detector and extractor
  SIFT::CommonParams comprm;
  // comprm.nOctaves      =  4;
  // comprm.nOctaveLayers =  3;
  // comprm.firstOctave   = -1;
  // comprm.angleMode     =  0;
  cout << "CommonParams:     " << comprm.nOctaves << " "
       << comprm.nOctaveLayers << " " << comprm.firstOctave << " "
       << comprm.angleMode << endl;

  // Parameters for detector
  SIFT::DetectorParams detprm;
  // detprm.threshold     = 0.04;
  // detprm.edgeThreshold = 10.0;
  cout << "DetectorParams:   " << detprm.threshold << " "
       << detprm.edgeThreshold << endl;

  // Parameters for extractor
  SIFT::DescriptorParams desprm;
  desprm.magnification     = 3.0;
  desprm.isNormalize       = true;
  desprm.recalculateAngles = true;
  cout << "DescriptorParams: " << desprm.magnification << " "
       << desprm.isNormalize << " " << desprm.recalculateAngles << endl;

  // SIFT
  SiftFeatureDetector detector(detprm,comprm);
  SiftDescriptorExtractor extractor(desprm,comprm);
  // SURF
  // SurfFeatureDetector detector(1000);
  // SurfDescriptorExtractor extractor;

  // Keypoint detection.
  vector<KeyPoint> key1;
  detector.detect(im1,key1);
  vector<KeyPoint> key2;
  detector.detect(im2,key2);

  // Descriptor computation
  Mat dsr1;    
  extractor.compute(im1,key1,dsr1);
  Mat dsr2;
  extractor.compute(im2,key2,dsr2);  

  // Keypoint matching
  vector<DMatch> matches;
  BruteForceMatcher< L2<float> > matcher;
  matcher.match(dsr1,dsr2,matches);

  // sort matches
  nth_element(matches.begin(),matches.begin()+num_val-1,matches.end());
  matches.erase(matches.begin()+num_val,matches.end());

  // draw matches
  Mat matchim;
  vector<char> dmy;
  // drawMatches(im1,key1,im2,key2,matches,matchim);
  // drawMatches(im1,key1,im2,key2,matches,matchim,
  //             Scalar::all(-1),Scalar::all(-1),dmy,
  //             DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
  drawMatches(im1,key1,im2,key2,matches,matchim,Scalar::all(-1),Scalar(200,200,200));

  // draw resultant image
  namedWindow("Correspondence",CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
  imshow("Correspondence",matchim);
  waitKey(0);
  destroyWindow("Correspondence");

  return 0;
}