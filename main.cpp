#include "apriltag_opencv.h"
#include "apriltag_family.h"
//#include "getopt.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

int main(int argc, char** argv) {

//getopt_t *getopt = getopt_create();

//  getopt_add_bool(getopt, 'h', "help", 0, "Show this help");
//  getopt_add_bool(getopt, 'q', "quiet", 0, "Reduce output");
//  getopt_add_string(getopt, 'f', "family", "tag36h11", "Tag family to use");
//  getopt_add_int(getopt, '\0', "border", "1", "Set tag family border size");
//  getopt_add_int(getopt, 't', "threads", "4", "Use this many CPU threads");
//  getopt_add_double(getopt, 'x', "decimate", "1.0", "Decimate input image by this factor");
//  getopt_add_double(getopt, 'b', "blur", "0.0", "Apply low-pass blur to input");
//  getopt_add_bool(getopt, '0', "refine-edges", 1, "Spend more time trying to align edges of tags");
//  getopt_add_bool(getopt, '1', "refine-decode", 0, "Spend more time trying to decode tags");
//  getopt_add_bool(getopt, '2', "refine-pose", 0, "Spend more time trying to precisely localize tags");
//  getopt_add_bool(getopt, 'c', "contours", 0, "Use new contour-based quad detection");

//  if (!getopt_parse(getopt, argc, argv, 1) || getopt_get_bool(getopt, "help")) {
//    printf("Usage: %s [options] Camera index or movie file\n", argv[0]);
//    getopt_do_usage(getopt);
//    exit(0);
//  }

  const char *famname = "tag36h11";
  apriltag_family_t *tf = apriltag_family_create(famname);

  if (!tf) {
    printf("Unrecognized tag family name. Use e.g. \"tag36h11\".\n");
    exit(-1);
  }

  tf->black_border = 1;//getopt_get_int(getopt, "border");

  apriltag_detector_t *td = apriltag_detector_create();
  apriltag_detector_add_family(td, tf);

//  if (getopt_get_bool(getopt, "contours")) {
//    apriltag_detector_enable_quad_contours(td, 1);
//  }

  td->quad_decimate = 1.0;//getopt_get_double(getopt, "decimate");
  td->quad_sigma = 0.0;//getopt_get_double(getopt, "blur");
  td->nthreads = 4;//getopt_get_int(getopt, "threads");
  td->debug = 0;
  td->refine_edges = 1;//getopt_get_bool(getopt, "refine-edges");
  td->refine_decode = 0;//getopt_get_bool(getopt, "refine-decode");
  td->refine_pose = 0;//getopt_get_bool(getopt, "refine-pose");

  //const zarray_t *inputs = getopt_get_extra_args(getopt);

  int camera_index = 1;
  const char* movie_file = NULL;

//  if (zarray_size(inputs) > 1) {
//    printf("Usage: %s [options] Camera index or movie file\n", argv[0]);
//    exit(-1);
//  } else if (zarray_size(inputs)) {
//    char* input;
//    zarray_get(inputs, 0, &input);
//    char* endptr;
//    camera_index = strtol(input, &endptr, 10);
//    if (!endptr || *endptr) {
//      movie_file = input;
//    }
//  }

  cv::VideoCapture* cap;


  if (movie_file) {
    cap = new cv::VideoCapture(movie_file);
  } else {
    cap = new cv::VideoCapture(camera_index);
  }

  const char* window = "Camera";

  cv::Mat frame;

  cv::namedWindow(window);

  while (1) {
    bool ok = cap->read(frame);
    if (!ok) { break; }
    cv::resize(frame,frame,cv::Size(160,120));

    Mat8uc1 gray;

    if (frame.channels() == 3) {
      cv::cvtColor(frame, gray, cv::COLOR_RGB2GRAY);
    } else {
      frame.copyTo(gray);
    }

    image_u8_t* im8 = cv2im8_copy(gray);

    zarray_t *detections = apriltag_detector_detect(td, im8);

    //printf("detected %d tags\n", zarray_size(detections));

    //cv::Mat display = detectionsImage(detections, frame.size(), frame.type());

    for (int i = 0; i < zarray_size(detections); i++) {
      apriltag_detection_t *det;
      zarray_get(detections, i, &det);

//      printf("detection %3d: id (%2dx%2d)-%-4d, hamming %d, "
//             "goodness %8.3f, margin %8.3f\n",
//             i, det->family->d*det->family->d, det->family->h,
//             det->id, det->hamming, det->goodness, det->decision_margin);
      //std::cout<<det->c[0]<<" "<<det->c[1]<<std::endl;
     // std::cout<<det->H->data[0]<<" "<<det->H->data[1]<<" "<<det->H->data[2]<<" "<<det->H->data[3]<<" "<<det->H->data[4]<<" "<<det->H->data[5]<<" "<<std::endl;
      cv::circle(frame,cv::Point(det->c[0],det->c[1]), 2, cv::Scalar(0, 0, 255), 5, cv::FILLED, 0);//draw center
      //std::cout<<" "<<det->p[1][0]<<" "<<det->p[1][1]<<" "<<det->p[1][2]<<" "<<det->p[1][3]<<std::endl;
      cv::circle(frame,cv::Point(det->p[1][0],det->p[1][1]), 2, cv::Scalar(0, 0, 255), 5, cv::FILLED, 0);
      cv::circle(frame,cv::Point(det->p[0][0],det->p[0][1]), 2, cv::Scalar(0, 0, 255), 5, cv::FILLED, 0);

      cv::Point center(det->c[0],det->c[1]);
      cv::Point conner0(det->p[0][0],det->p[0][1]);
      float angle=atan2(conner0.x-center.x,conner0.y-center.y);
      std::cout<<angle*(57.29578049)+135<<std::endl;
    }

    printf("\n");

    apriltag_detections_destroy(detections);

    //display = 0.5*display + 0.5*frame;
    //cv::imshow(window, display);
    image_u8_destroy(im8);
    cv::imshow(window, frame);

    int k = cv::waitKey(1);
    if (k == 27) { break; }


  }

  return 0;

}
