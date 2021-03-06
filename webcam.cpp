#include <unistd.h>
#include <iostream>

#include "V4L2.h"
#include "SUR40.h"
#include "VirtualCam.h"

#define IN_W 1280
#define IN_H  720

int get_v4l_devnum(const char* path) {
  char buf[128]; if (!path) path = "/dev/video0";
  int num,res = readlink(path,buf,sizeof(buf));
  if (res == -1) { strncpy(buf,path,sizeof(buf)); res = strlen(buf); }
  num = (int)(buf[res-1] - '0');
  std::cout << "path " << path << " maps to " << buf << ", devnum " << num << std::endl;
  return num;
}

int main(int argc, char* argv[]) {

  if (argc < 2) {
    std::cout << "usage: webcam <mode> <videodev> [gstpipe]\n" << std::endl;
    std::cout << "       mode == v4l2|sur40|virtcam" << std::endl;
    return 1;
  }

  char* gstpipe = nullptr;
  if (argc > 3) gstpipe = argv[3];

  Camera* cam = nullptr;

  if (std::string(argv[1]) ==    "v4l2") cam = new V4L2(gstpipe,get_v4l_devnum(argv[2]),IN_W,IN_H);
  if (std::string(argv[1]) ==   "sur40") cam = new SUR40(gstpipe,get_v4l_devnum(argv[2]));
  if (std::string(argv[1]) == "virtcam") cam = new VirtualCam(gstpipe);

  while (!cam->do_quit) {

    cam->retrieve_frames();

    cam->remove_background();

    cam->send_buffer();
  }

  return 0;
}
