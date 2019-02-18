all: keypoint sift

keypoint: keypoint.cpp
	g++ -o keypoint keypoint.cpp `pkg-config opencv --cflags --libs`

sift: sift.cpp
	g++ -o sift sift.cpp `pkg-config opencv --cflags --libs`
