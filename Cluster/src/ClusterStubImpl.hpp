#ifndef CLUSTERSTUBIMPL_H_
#define CLUSTERSTUBIMPL_H_
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/ClusterStubDefault.hpp>
#include <QObject>
#include <opencv2/dnn.hpp>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <NvInfer.h>

//
// TensorRT
#include "config.h"
#include "model.h"
#include "cuda_utils.h"
#include "logging.h"
#include "utils.h"
#include "preprocess.h"
#include "postprocess.h"
#include "yolov7/mains.h"
//

using namespace nvinfer1;


extern IExecutionContext* context1;
extern cudaStream_t stream1;
extern float* device_buffers1[2];
extern float* output_buffer_host1;

extern IExecutionContext* context2;
extern cudaStream_t stream2;
extern float* device_buffers2[2];
extern float* output_buffer_host2;



class ClusterStubImpl: public QObject, public v1_0::commonapi::ClusterStubDefault {
    Q_OBJECT
public:
    ClusterStubImpl();
    virtual ~ClusterStubImpl();
    virtual void sendImage1(const std::shared_ptr<CommonAPI::ClientId> _client, std::vector< uint8_t > _image1);
    virtual void sendImage2(const std::shared_ptr<CommonAPI::ClientId> _client, std::vector< uint8_t > _image2);
    virtual void sendImage3(const std::shared_ptr<CommonAPI::ClientId> _client, std::vector< uint8_t > _image3);
    virtual void sendImage4(const std::shared_ptr<CommonAPI::ClientId> _client, std::vector< uint8_t > _image4);
    int frame_counter = 0;
private:
    static std::chrono::high_resolution_clock::time_point lastTimestamp1;
    static std::chrono::high_resolution_clock::time_point lastTimestamp2;
    static std::chrono::high_resolution_clock::time_point lastTimestamp3;
    static std::chrono::high_resolution_clock::time_point lastTimestamp4;
    static double totalFPS1, totalFPS2, totalFPS3, totalFPS4;
    static int frameCount1, frameCount2, frameCount3, frameCount4;


//signals:
//    void signalSpeed(int);
//    void signalRPM(int);
//    void signalButtons(std::string);
};
#endif /* CLUSTERSTUBIMPL_H_ */