QT += quick
CONFIG += c++11
QT += multimedia
QT += network
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += ../../src-gen-cluster/
SOURCES += main.cpp \
    ../../src-gen-cluster/v1/commonapi/ClusterSomeIPDeployment.cpp \
    ../../src-gen-cluster/v1/commonapi/ClusterSomeIPProxy.cpp \
    ../../src-gen-cluster/v1/commonapi/ClusterSomeIPStubAdapter.cpp \
    ClusterStubImpl.cpp \
    include/yolov7/mains.cpp \
    include/yolov7/src/block.cpp \
    include/yolov7/src/calibrator.cpp \
    include/yolov7/src/model.cpp \
    include/yolov7/src/postprocess.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L/usr/local/lib/release/ -lCommonAPI
else:win32:CONFIG(debug, debug|release): LIBS += -L/usr/local/lib/debug/ -lCommonAPI
else:unix: LIBS += -L/usr/local/lib/ -lCommonAPI

INCLUDEPATH += /usr/local/include/CommonAPI-3.2
DEPENDPATH += /usr/local/include/CommonAPI-3.2

win32:CONFIG(release, debug|release): LIBS += -L/usr/local/lib/release/ -lCommonAPI-SomeIP
else:win32:CONFIG(debug, debug|release): LIBS += -L/usr/local/lib/debug/ -lCommonAPI-SomeIP
else:unix: LIBS += -L/usr/local/lib/ -lCommonAPI-SomeIP

INCLUDEPATH += /usr/local/include/CommonAPI-3.2
DEPENDPATH += /usr/local/include/CommonAPI-3.2

win32:CONFIG(release, debug|release): LIBS += -L/usr/local/lib/release/ -lvsomeip3
else:win32:CONFIG(debug, debug|release): LIBS += -L/usr/local/lib/debug/ -lvsomeip3
else:unix: LIBS += -L/usr/local/lib/ -lvsomeip3

INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include

HEADERS += \
    ../../src-gen-cluster/v1/commonapi/Cluster.hpp \
    ../../src-gen-cluster/v1/commonapi/ClusterProxy.hpp \
    ../../src-gen-cluster/v1/commonapi/ClusterProxyBase.hpp \
    ../../src-gen-cluster/v1/commonapi/ClusterSomeIPDeployment.hpp \
    ../../src-gen-cluster/v1/commonapi/ClusterSomeIPProxy.hpp \
    ../../src-gen-cluster/v1/commonapi/ClusterSomeIPStubAdapter.hpp \
    ../../src-gen-cluster/v1/commonapi/ClusterStub.hpp \
    ../../src-gen-cluster/v1/commonapi/ClusterStubDefault.hpp \
    ClusterStubImpl.hpp \
    include/yolov7/mains.h \
    include/yolov7/include/block.h \
    include/yolov7/include/calibrator.h \
    include/yolov7/include/config.h \
    include/yolov7/include/cuda_utils.h \
    include/yolov7/include/logging.h \
    include/yolov7/include/macros.h \
    include/yolov7/include/model.h \
    include/yolov7/include/types.h \
    include/yolov7/include/utils.h \
    include/yolov7/plugin/yololayer.h \
    include/yolov7/include/postprocess.h \
    include/yolov7/include/preprocess.h

INCLUDEPATH += /usr/include/opencv4/
DEPENDPATH += /usr/include/opencv4/

LIBS += -L/usr/lib/x86_64-linux-gnu/
LIBS += \
-lopencv_core \
-lopencv_videoio \
-lopencv_ml \
-lopencv_objdetect \
-lopencv_stitching \
-lopencv_calib3d \
-lopencv_photo \
-lopencv_video \
-lopencv_dnn \
-lopencv_imgcodecs \
-lopencv_flann \
-lopencv_features2d \
-lopencv_imgproc \
-lopencv_highgui

# 라이브러리와 헤더 경로 설정
INCLUDEPATH += $${CUDA_DIR}/include
INCLUDEPATH += include
INCLUDEPATH += include/yolov7
INCLUDEPATH += include/yolov7/include
INCLUDEPATH += include/yolov7/src
INCLUDEPATH += include/yolov7/plugin
INCLUDEPATH += /usr/local/cuda/include
INCLUDEPATH += /usr/include/aarch64-linux-gnu/
LIBS += -L/usr/lib/aarch64-linux-gnu \
        -lnvinfer \
        -lnvparsers \
        -lnvinfer_plugin \

DISTFILES += \
    coco.names \
    include/yolov7/CMakeLists.txt \
    include/yolov7/README.md \
    include/yolov7/gen_wts.py \
    include/yolov7/yolov7_trt.py \
    yolov4-tiny.cfg \
    yolov4-tiny.weights \
    yolov7.engine

INCLUDEPATH += /usr/local/cuda/include
LIBS += -L/usr/local/cuda/lib64
LIBS += -lcudart


# CUDA Toolkit 경로
CUDA_DIR = /usr/local/cuda
SYSTEM_TYPE = 64 # 32 for 32-bit system

# nvcc 컴파일러 설정
CUDA_SOURCES += include/yolov7/plugin/yololayer.cu \
                include/yolov7/src/preprocess.cu

CUDA_NVCC_FLAGS = --compiler-options -fno-strict-aliasing -use_fast_math -arch=sm_52 $$join(INCLUDEPATH,' -I','-I',' ')

# qmake 사용자 정의 컴파일러 추가
cuda.input = CUDA_SOURCES
cuda.output = ${OBJECTS_DIR}${QMAKE_FILE_BASE}.o
cuda.commands = $${CUDA_DIR}/bin/nvcc -c $${CUDA_NVCC_FLAGS} ${QMAKE_FILE_NAME} -o ${QMAKE_FILE_OUT} $$join(INCLUDEPATH,' -I','-I',' ')
cuda.dependency_type = TYPE_C
QMAKE_EXTRA_COMPILERS += cuda



QMAKE_LIBDIR += $${CUDA_DIR}/lib${SYSTEM_TYPE}
LIBS += -lcudart


