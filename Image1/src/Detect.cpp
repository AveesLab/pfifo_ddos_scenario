#include <fstream>
#include "Detect.h"
#include <opencv2/dnn.hpp>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <sys/types.h>
#include "hello_world_ta.h"
#include <err.h>
#include <stdio.h>
#include <string.h>
#include <tee_client_api.h>

Detect::Detect(QObject *parent) : QObject(parent)
{
    runtime = CommonAPI::Runtime::get();
    myProxy = runtime->buildProxy<ClusterProxy>("local", "cluster_service");

    while (!myProxy->isAvailable())
        usleep(10);

}

void Detect::startCamera() {
    cv::VideoCapture cap(0);  // Open the default camera
    if (!cap.isOpened()) {
        std::cerr << "Could not open camera." << std::endl;
        return;
    }

    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    cap.set(cv::CAP_PROP_FPS, 30);
    CommonAPI::CallStatus callStatus;
    CommonAPI::CallStatus checkStatus;
    int result;
    int error;
    uint8_t emergency = 0x20;
    uint8_t normal = 0x00; 
    bool setSockOptNeeded = true;
    int number;
    myProxy->getErrorBroadcastEvent().subscribe([&](const int32_t &result) {
        if(result == 1 && setSockOptNeeded) {
	    TEEC_Result res;
	    TEEC_Context ctx;
	    TEEC_Session sess;
	    TEEC_Operation op;
	    TEEC_UUID uuid = TA_HELLO_WORLD_UUID;
	    uint32_t err_origin;
	    res = TEEC_InitializeContext(NULL, &ctx);
	    if (res != TEEC_SUCCESS)
	        errx(1, "TEEC_InitializeContext failed with code 0x%x", res);
	    res = TEEC_OpenSession(&ctx, &sess, &uuid,
	            TEEC_LOGIN_PUBLIC, NULL, NULL, &err_origin);
	    if (res != TEEC_SUCCESS)
	    errx(1, "TEEC_Opensession failed with code 0x%x origin 0x%x",
	        res, err_origin);
	
	    // 암호화된 데이터 파일 읽기
	    std::ifstream file("signature.bin", std::ios::binary);
	    if (!file) {
	        std::cerr << "Error: File not found." << std::endl;
	        return 1; // or other error handling
	    }
	    std::vector<char> encrypted_data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	    if (file.fail()) {
	        std::cerr << "Error reading the file." << std::endl;
	        return 1; // or other error handling
	    }
	    file.close();        
	
	    // 공개키 데이터 로드
	    std::ifstream key_file("public_key.pem", std::ios::binary);
	    std::vector<char> public_key((std::istreambuf_iterator<char>(key_file)), std::istreambuf_iterator<char>());
	    key_file.close();   
	
	    // TEEC_Operation 설정
	    memset(&op, 0, sizeof(op));
	    op.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INOUT, TEEC_MEMREF_TEMP_INPUT, TEEC_MEMREF_TEMP_INPUT, TEEC_NONE);
	    op.params[0].value.a = 15; // 예를 들어 socket fd 값
	    op.params[1].tmpref.buffer = encrypted_data.data();
	    op.params[1].tmpref.size = encrypted_data.size();
	    op.params[2].tmpref.buffer = public_key.data();
	    op.params[2].tmpref.size = public_key.size();
	    //TA_HELLO_WORLD_CMD_DEC_VALUE
	    // TA에 커맨드 전송
	    res = TEEC_InvokeCommand(&sess, TA_HELLO_WORLD_CMD_INC_VALUE, &op, &err_origin);
	    if (res != TEEC_SUCCESS) errx(1, "TEEC_InvokeCommand failed with code 0x%x origin 0x%x", res, err_origin);
	    printf("Set Emergency\n");
	    TEEC_CloseSession(&sess);
	
	    TEEC_FinalizeContext(&ctx);
            setSockOptNeeded = false;
        }
    });
    while (true) {
        cv::Mat frame;
        cap >> frame;  // Get a new frame from the camera
        if (frame.empty()) {
            std::cerr << "Failed to capture an image." << std::endl;
            return;
        }
        std::vector<uchar> encoded_frame;
        if (!cv::imencode(".jpg", frame, encoded_frame)) {
            std::cerr << "Failed to encode frame." << std::endl;
            return;
        }
            // auto start = std::chrono::high_resolution_clock::now();
        myProxy->sendImage1(encoded_frame, callStatus);
            // auto end = std::chrono::high_resolution_clock::now();
            // auto tt = std::chrono::duration<double>(end - start).count();
            // std::cout << "time :" << tt << std::endl;

        // if(number > 2 && send_future.wait_for(std::chrono::milliseconds(100)) != std::future_status::ready) {
        //     setsockopt(15, IPPROTO_IP, IP_TOS, &emergency, sizeof(emergency));
        //     FILE *fp = fopen(EMERGENCY_FLAG_PATH, "w");
        //     if (fp) {
        //         fprintf(fp, "1");
        //         fclose(fp);
        //     } else {
        //         perror("Failed to set emergency_flag");
        //     }
        //     // setSockOptNeeded = true;
        //     myProxy->sendImage1(encoded_frame, callStatus, result);
        //     std::cout << "EMERGENCY1" << std::endl;
        //     setSockOptNeeded = false;
        // }
    }
}
