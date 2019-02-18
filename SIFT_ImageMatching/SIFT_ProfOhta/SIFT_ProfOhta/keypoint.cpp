#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
  if(argc != 2) {
    cerr << "usage: " << argv[0] << " image_file" << endl;
    return 1; }

  Mat im = imread(argv[1],0);
  if(im.empty()){
    cerr << "file open error" << endl;
    return 1; }

  // Parameters for both detctor and extractor
  SIFT::CommonParams comprm;
  cout << "Default parameters: " << comprm.nOctaves << " "
       << comprm.nOctaveLayers << " " << comprm.firstOctave << " "
       << comprm.angleMode << endl;

  comprm.nOctaves      =  4;
  comprm.nOctaveLayers =  3;
  comprm.firstOctave   = -1;
  comprm.angleMode     =  0;
  /*
  comprm.nOctaves      = SIFT::CommonParams::DEFAULT_NOCTAVES;       //  4
  comprm.nOctaveLayers = SIFT::CommonParams::DEFAULT_NOCTAVE_LAYERS; //  3
  comprm.firstOctave   = SIFT::CommonParams::DEFAULT_FIRST_OCTAVE;   // -1
  comprm.angleMode     = SIFT::CommonParams::FIRST_ANGLE;            //  0
  // (FIRST_ANGLE = 0, AVERAGE_ANGLE = 1)
  */
  cout << "Set parameters:     " << comprm.nOctaves << " "
       << comprm.nOctaveLayers << " " << comprm.firstOctave << " "
       << comprm.angleMode << endl;

  // Parameters for detctor
  SIFT::DetectorParams detprm;
  cout << "Default parameters: " << detprm.threshold << " "
       << detprm.edgeThreshold << endl;

  detprm.threshold     = 0.04;
  detprm.edgeThreshold = 10.0;
  /*
  detprm.threshold     = SIFT::DetectorParams::GET_DEFAULT_THRESHOLD(); // 0.04
  detprm.edgeThreshold = SIFT::DetectorParams::GET_DEFAULT_EDGE_THRESHOLD(); // 10.0
  */
  cout << "Set parameters:     " << detprm.threshold << " "
       << detprm.edgeThreshold << endl;

  // Detection of keypoints
  vector<KeyPoint> key;
  SiftFeatureDetector siftfd(detprm,comprm);
  siftfd.detect(im,key);

  Mat dspim;
  drawKeypoints(im,key,dspim,Scalar(0,0,255));
  /*
  drawKeypoints(im,key,dspim,Scalar(0,0,255),
                DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
  */

  // draw resultant image
  namedWindow("Keypoints",CV_WINDOW_AUTOSIZE);
  imshow("Keypoints",dspim);
  waitKey(0);
  destroyWindow("Keypoints");

  return 0;
}

