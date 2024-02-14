#pragma once
#include "config.h"
#include "model.h"
#include "cuda_utils.h"
#include "logging.h"
#include "utils.h"
#include "preprocess.h"
#include "postprocess.h"
#include <chrono>
#include <fstream>


const static int kOutputSize = kMaxNumOutputBbox * sizeof(Detection) / sizeof(float) + 1;
static Logger gLogger;


// Function prototypes
void serialize_engine(unsigned int maxBatchSize, std::string& wts_name, std::string& sub_type, std::string& engine_name);
void deserialize_engine(std::string& engine_name, nvinfer1::IRuntime** runtime, nvinfer1::ICudaEngine** engine, nvinfer1::IExecutionContext** context);
void prepare_buffer(nvinfer1::ICudaEngine* engine, float** input_buffer_device, float** output_buffer_device, float** output_buffer_host);
void infer(nvinfer1::IExecutionContext& context, cudaStream_t& stream, void** buffers, float* output, int batchSize);
bool parse_args(int argc, char** argv, std::string& wts, std::string& engine, std::string& img_dir, std::string& sub_type);