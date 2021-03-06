// based on: https://github.com/microsoft/Azure-Kinect-Sensor-SDK/blob/develop/examples/viewer/opengl/main.cpp
// based on: https://github.com/microsoft/Azure-Kinect-Sensor-SDK/blob/develop/examples/transformation/main.cpp
// tested with: libk4a1.4-1.4.1

#include <iostream>
#include "KinectAzure.h"

int main( int argc, char* argv [] ) {

	const char* gstpipe = nullptr;
	if (argc >= 2) gstpipe = argv[1];

	KinectAzure cam(gstpipe);

	while (!cam.do_quit) {

		cam.retrieve_frames();

		if (cam.find_plane) {
			cam.ransac_plane();
			cam.find_plane = false;
		}

		cam.remove_background();

		cam.send_buffer();
	}
}
