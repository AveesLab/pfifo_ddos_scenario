# SEA:ME@Korea 2023 Summer Hackathon<br>

During this hackathon, your mission is to develop a new digital instrument cluster system based on our baseline implementation in this repository. We'll provide you an Nvidia Jetson TX 2 embedded board that is the final target system. However, the instrument cluster can run on Intel/AMD CPU-based Ubuntu Linux distributions. If you use a Windows laptop, you have to install VMware and Ubuntu Linux as a guest operating system. We provide a preconfigured VMware image that includes all the libraries, tools, and source codes ready for the hackathon in the following link:

- [VMware Ubuntu image](https://github.com/AveesLab/sea-me-hackathon-2023/blob/master/VMware%20Ubuntu%20image/README.md)<br>

Otherwise, if you want to use a native Linux environment, you have to install (i) vsomeip, (ii) CommonAPI, and (iii) QT5. Please follow the instructions below to prepare your development environment:
<!---
## Contents
- [Step 1: Install OpenJDK Java 8](#step-1-install-openjdk-java-8)
- [Step 2: Install Boost.Asio library](#step-2-install-boostasio-library)
- [Step 3: Build the CommonAPI Runtime Library](#step-3-build-the-commonapi-runtime-library)
- [Step 4: Build the vsomeip Library](#step-4-build-the-vsomeip-library)
- [Step 5: Build the CommonAPI SOME/IP Runtime Library](#step-5-build-the-commonapi-someip-runtime-library)
- [Step 6: Install Qt](#step-6-install-qt)
- [Step 7: Execute Cluster & Controller](#step-7-execute-cluster-and-controller)
---
<br>


# CommonAPI vSomeIP QT Setup
-->

## Step 0: Make sure you have installed git and cmake
```bash
sudo apt update
sudo apt install git
sudo apt install cmake
```

<br/>

## Step 1: Install OpenJDK Java 8
```bash
sudo apt install openjdk-8-jdk
```

You can check installation

```bash
java -version
```

If you already have openJDK 11 in your system, your default JDK version will be 11.
![스크린샷, 2023-07-07 21-58-18](https://github.com/AveesLab/sea-me-hackathon-2023/assets/96398568/49d28f85-6f4f-4ca6-a971-abfa95dd7f68)

Then you can change the JDK version using the following command:

```bash
sudo update-alternatives --config java
```

Please select java-8 as in the following: 
![스크린샷, 2023-07-07 21-58-41](https://github.com/AveesLab/sea-me-hackathon-2023/assets/96398568/130277ce-b1bd-4c0c-8375-8a877ab1c869)
```bash
java -version
```
![스크린샷, 2023-07-07 21-59-08](https://github.com/AveesLab/sea-me-hackathon-2023/assets/96398568/f3c6b169-3de6-4bba-83ba-087a9e92da07)


<br/>

## Step 2: Install the Boost.Asio library
Boost.Asio is a C++ network library.
```bash
sudo apt install libboost-all-dev
```

<br/>

## Step 3: Build the CommonAPI core runtime

Create a build directory, which is `build-commonapi` in my case.

```bash
cd ~
mkdir build-commonapi && cd build-commonapi
```

Download, build, and install the CommonAPI runtime.

```bash
git clone https://github.com/GENIVI/capicxx-core-runtime.git
cd capicxx-core-runtime/
git checkout 3.2.0
mkdir build
cd build
cmake ..
make -j6
sudo make install
```

Result:

```bash
[100%] Linking C shared library libCommonAPI.so
[100%] Built target CommonAPI
```

<br/>

## Step 4: Build the vsomeip library

Install dependent packages.
```bash
sudo apt install asciidoc source-highlight doxygen graphviz libgtest-dev
```
Download and build the vsomeip library.

```bash
cd ~
cd build-commonapi
git clone https://github.com/COVESA/vsomeip.git
cd vsomeip
git checkout 3.1.20.3
mkdir build
cd build
cmake -DENABLE_SIGNAL_HANDLING=1 -DDIAGNOSIS_ADDRESS=0x10 ..
make -j6
sudo make install
```


Result:

```bash
[100%] Linking CXX executable vsomeipd
[100%] Built target vsomeipd
```

<br/>

## Step 5: Build the CommonAPI SOME/IP runtime library

Download and build the CommonAPI SOME/IP runtime library.

```bash
cd ~
cd build-commonapi
git clone https://github.com/GENIVI/capicxx-someip-runtime.git
cd capicxx-someip-runtime/
git checkout 3.2.0
mkdir build
cd build
cmake -DUSE_INSTALLED_COMMONAPI=OFF ..
make -j6
sudo make install

```

Result:

```bash
[100%] Linking CXX shared library libCommonAPI-SomeIP.so
[100%] Built target CommonAPI-SomeIP
```

#### Add library path
```bash
cd ~
sudo vi .bashrc
```
Add the following line at the end of the .bash file:
```bash
export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
```

Source the .bashrc.

```bash
source .bashrc
```
<br/>



## Step 6: Install Qt

Install the QT5 packages.
```bash
sudo apt install qt5-default
sudo apt install qtcreator
sudo apt install qtdeclarative5-dev
```

You must install the QT Multimdeia module.
```bash
sudo apt install qtmultimedia5-dev
sudo apt install qml-module-qtquick-controls2
sudo apt install libqt5multimediawidgets5 libqt5multimedia5
sudo apt install libqt5multimedia5-plugins qml-module-qtmultimedia
```


<br/>

## Step 7: Execute Cluster and Controller
The environment setup is completed.<br>
You can run the Controller and Cluster by following each README in the links below:
- [Cluster](https://github.com/AveesLab/sea-me-hackathon-2023/tree/master/Cluster)
- [Controller](https://github.com/AveesLab/sea-me-hackathon-2023/tree/master/Controller)
