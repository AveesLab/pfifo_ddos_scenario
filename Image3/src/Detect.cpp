#include <fstream>
#include "Detect.h"
#include <opencv2/dnn.hpp>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>



Detect::Detect(QObject *parent) : QObject(parent)
{
   runtime = CommonAPI::Runtime::get();
    myProxy = runtime->buildProxy<ClusterProxy>("local", "cluster_service");

    while (!myProxy->isAvailable())
        usleep(10);
}


void Detect::startCamera() {
    std::vector<uchar> encoded_image;
    CommonAPI::CallStatus callStatus;
    uint8_t tos_value3 = 0x00;
    setsockopt(15, IPPROTO_IP, IP_TOS, &tos_value3, sizeof(tos_value3));
    int result;
    cv::Mat image = cv::imread("image.jpg");
    cv::resize(image, image, cv::Size(720, 540));
    if (!cv::imencode(".jpg", image, encoded_image)) {
        std::cerr << "Failed to encode frame." << std::endl;
        return;
    }

    while (true) {
        auto start = std::chrono::high_resolution_clock::now();

        myProxy->sendImage3(encoded_image, callStatus, result);
        // Do other stuff...

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;

        if (elapsed.count() < 15) {
            std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(15) - elapsed);
        }
        // auto dend = std::chrono::high_resolution_clock::now();
        // std::chrono::duration<double, std::milli> delapsed = dend - start;
        // std::printf("Function execution time: %.3f ms\n", delapsed.count());
    }
}
