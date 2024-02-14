#include "ImageReceiver.h"

ImageReceiver::ImageReceiver(QObject *parent) : QObject(parent)
{
}

void ImageReceiver::receiveImage(std::vector< uint8_t > _image1)
{
    cv::Mat decoded_image1 = cv::imdecode(_image1, cv::IMREAD_COLOR);
    if (decoded_image1.empty()) {
        std::cerr << "Failed to decode image." << std::endl;
        return;
    };
    cv::imshow("Decoded Image1", decoded_image1);
    cv::waitKey(1);
}
