#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <qqml.h>
#include <QMetaType>
#include <string>
#include <iostream>
#include <thread>
#include <CommonAPI/CommonAPI.hpp>
#include "ClusterStubImpl.hpp"
#include <fstream>

// //
// // TensorRT
// #include "config.h"
// #include "model.h"
// #include "cuda_utils.h"
// #include "logging.h"
// #include "utils.h"
// #include "preprocess.h"
// #include "postprocess.h"
#include "yolov7/mains.h"
//

using namespace nvinfer1;
using namespace std;
Q_DECLARE_METATYPE(std::string)



std::mutex mtx;
std::condition_variable condVar;
bool exitFlag = false;

cudaStream_t stream1;
IExecutionContext* context1;
float* device_buffers1[2];
float* output_buffer_host1 = nullptr;

cudaStream_t stream2;
IExecutionContext* context2;
float* device_buffers2[2];
float* output_buffer_host2 = nullptr;

extern int number;
int result1;
std::shared_ptr<ClusterStubImpl> myService;
std::chrono::high_resolution_clock::time_point last_fps_time;


void waitForExitSignal() {
    std::unique_lock<std::mutex> lock(mtx);
    condVar.wait(lock, [] { return exitFlag; });
}

int main(int argc, char *argv[]) {
    qRegisterMetaType<std::string>();

    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    myService = std::make_shared<ClusterStubImpl>();
    runtime->registerService("local", "cluster_service", myService);
    std::cout << "Successfully Registered Service!" << std::endl;

    //
    std::string model_name_1 = "yolov7.engine";
    std::string model_name_2 = "yolov7.engine";
    IRuntime* runtimes1 = nullptr;
    ICudaEngine* engine1 = nullptr;
    IRuntime* runtimes2 = nullptr;
    ICudaEngine* engine2 = nullptr;
    deserialize_engine(model_name_1, &runtimes1, &engine1, &context1);
    deserialize_engine(model_name_2, &runtimes2, &engine2, &context2);     
    CUDA_CHECK(cudaStreamCreate(&stream1));
    CUDA_CHECK(cudaStreamCreate(&stream2));        

    //
    cuda_preprocess_init(kMaxInputImageSize);

    prepare_buffer(engine1, &device_buffers1[0], &device_buffers1[1], &output_buffer_host1);
    prepare_buffer(engine2, &device_buffers2[0], &device_buffers2[1], &output_buffer_host2);
    std::ifstream file;
    std::string line;
    long long prev_rx = 0, prev_tx = 0;
    long check_rx = 0;


    while (true) {
        auto current_time = std::chrono::high_resolution_clock::now();
        auto elapsed_time = std::chrono::duration<double>(current_time - last_fps_time).count();
        // 1초 이상 경과했을 때 FPS 계산 및 출력
        if (elapsed_time >= 1) {

            // // std::cout << "time: " << elapsed_time << std::endl; 
            // std::cout << "FPS: " << frame_counter << std::endl;  // 프레임 카운터 값이 바로 FPS입니다
            file.open("/proc/net/dev");
            if (file.is_open()) {
                while (getline(file, line)) {
                    if (line.find("eth0:") != std::string::npos) { // 'eth0' 대신에 본인의 네트워크 인터페이스 이름으로 바꿔주세요.
                        size_t pos = line.find("eth0:") + 6; // 여기도 마찬가지로 인터페이스 이름에 맞게 조정
                        long long rx_bytes, tx_bytes;
                        sscanf(line.substr(pos).c_str(), "%lld %*d %*d %*d %*d %*d %*d %*d %lld", &rx_bytes, &tx_bytes);

                        // if (prev_rx != 0 && prev_tx != 0) {
                        //     std::cout << "Received: " << rx_bytes - prev_rx << " bytes, Sent: " << tx_bytes - prev_tx << " bytes\n";
                        // }
                        check_rx = rx_bytes - prev_rx;
                        prev_rx = rx_bytes;
                        prev_tx = tx_bytes;
                    }
                }
                file.close();
            }
            //normal : 2067447
            //std::cout << "time: " << elapsed_time << std::endl;
            std::cout << "\n\n\nframe: " << myService->frame_counter << std::endl;  
            std::cout << "Received: " << check_rx << std::endl;
            if (number > 60 && myService->frame_counter < 26 && check_rx > 20674470 && result1 == 0) {
                result1 = 1;
                myService->fireErrorBroadcastEvent(result1);
                std::cout << "Order Emergency1" << std::endl;
            }
            last_fps_time = current_time;
            myService->frame_counter = 0;            
        }

    }
    // GPU 메모리 해제
    // Release stream and buffers
    cudaStreamDestroy(stream1);
    cudaStreamDestroy(stream2);
    CUDA_CHECK(cudaFree(device_buffers1[0]));
    CUDA_CHECK(cudaFree(device_buffers1[1]));
    CUDA_CHECK(cudaFree(device_buffers2[0]));
    CUDA_CHECK(cudaFree(device_buffers2[1]));
    delete[] output_buffer_host1;
    delete[] output_buffer_host2;
    cuda_preprocess_destroy();

    // Destroy the engine
    delete context1;
    delete engine1;
    delete runtimes1;
    delete context2;
    delete engine2;
    delete runtimes2;
    
    return 0;
}