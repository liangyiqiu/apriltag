QT += core
QT -= gui

TARGET = droneCV
CONFIG += console
CONFIG -= app_bundle

INCLUDEPATH += /usr/local/include \
                /usr/local/include/opencv \
                /usr/local/include/opencv2\
                /home/pi/droneCV\
                /home/pi/Downloads/apriltag-master/core\
                /home/pi/Downloads/apriltag-master/core/common\
                /home/pi/Downloads/apriltag-master/core/contrib\


LIBS += -lwiringPi
LIBS += -lncurses
LIBS += /usr/local/lib/libopencv_calib3d.so \
/usr/local/lib/libopencv_core.so \
/usr/local/lib/libopencv_features2d.so \
/usr/local/lib/libopencv_flann.so \
/usr/local/lib/libopencv_highgui.so \
/usr/local/lib/libopencv_imgcodecs.so \
/usr/local/lib/libopencv_imgproc.so \
/usr/local/lib/libopencv_ml.so \
/usr/local/lib/libopencv_objdetect.so \
/usr/local/lib/libopencv_photo.so \
/usr/local/lib/libopencv_shape.so \
/usr/local/lib/libopencv_stitching.so \
/usr/local/lib/libopencv_superres.so \
/usr/local/lib/libopencv_videoio.so \
/usr/local/lib/libopencv_video.so \
/usr/local/lib/libopencv_videostab.so\
/usr/local/lib/libapriltag_opencv.so\
/usr/local/lib/libapriltag.so

TEMPLATE = app

SOURCES += \
    main.cpp \
    ../../../../Downloads/apriltag-master/core/common/getopt.c \
    ../../../../Downloads/apriltag-master/core/tag36h11.c \
    ../../../../Downloads/apriltag-master/core/tag36h10.c \
    ../../../../Downloads/apriltag-master/core/tag36artoolkit.c \
    ../../../../Downloads/apriltag-master/core/tag25h9.c \
    ../../../../Downloads/apriltag-master/core/tag25h7.c \
    ../../../../Downloads/apriltag-master/core/tag16h5.c \
    ../../../../Downloads/apriltag-master/core/g2d.c \
    ../../../../Downloads/apriltag-master/core/apriltag.c \
    ../../../../Downloads/apriltag-master/core/apriltag_quad_thresh.c \
    ../../../../Downloads/apriltag-master/core/apriltag_family.c \
    ../../../../Downloads/apriltag-master/core/contrib/pose.c \
    ../../../../Downloads/apriltag-master/core/contrib/pdfutil.c \
    ../../../../Downloads/apriltag-master/core/contrib/lm.c \
    ../../../../Downloads/apriltag-master/core/contrib/contour.c \
    ../../../../Downloads/apriltag-master/core/contrib/box.c \
    ../../../../Downloads/apriltag-master/core/contrib/apriltag_vis.c \
    ../../../../Downloads/apriltag-master/core/contrib/apriltag_quad_contour.c \
    ../../../../Downloads/apriltag-master/core/common/zmaxheap.c \
    ../../../../Downloads/apriltag-master/core/common/zhash.c \
    ../../../../Downloads/apriltag-master/core/common/zarray.c \
    ../../../../Downloads/apriltag-master/core/common/workerpool.c \
    ../../../../Downloads/apriltag-master/core/common/unionfind.c \
    ../../../../Downloads/apriltag-master/core/common/time_util.c \
    ../../../../Downloads/apriltag-master/core/common/svd22.c \
    ../../../../Downloads/apriltag-master/core/common/string_util.c \
    ../../../../Downloads/apriltag-master/core/common/pnm.c \
    ../../../../Downloads/apriltag-master/core/common/matd.c \
    ../../../../Downloads/apriltag-master/core/common/image_u32.c \
    ../../../../Downloads/apriltag-master/core/common/image_u8.c \
    ../../../../Downloads/apriltag-master/core/common/image_f32.c \
    ../../../../Downloads/apriltag-master/core/common/homography.c \
    apriltag_opencv.cpp
