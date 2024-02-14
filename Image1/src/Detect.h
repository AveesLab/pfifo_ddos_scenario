#ifndef DETECT_H
#define DETECT_H

#include <QObject>
#include <iostream>
#include <string>
#include <unistd.h>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/ClusterProxy.hpp>
#include <opencv2/opencv.hpp>
#include <cstdint>


using namespace v1_0::commonapi;

class Detect : public QObject
{
    Q_OBJECT

public:
    explicit Detect(QObject *parent = nullptr);
    std::shared_ptr < CommonAPI::Runtime > runtime;
    std::shared_ptr<ClusterProxy<>> myProxy;
    cv::VideoCapture cap;

public slots:
    void startCamera();
};


#endif // DETECT_H