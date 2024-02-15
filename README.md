# DDoS scenario with pfifo_fast<br>

## Step 0: Build Kernel Image ~~~.

Kernel image with a special DDoS attack prevention method called Band-S in the following link:

- [Kernel image for Band-S](https://github.com/AveesLab/linux-tegra-5.10_s/blob/oe4t-patches-l4t-r35.1/README.md)<br><br>

## Step 1: Make sure you have installed git and cmake
```bash
sudo apt update
sudo apt install git
sudo apt install cmake
```

<br/>

## Step 2: Install OpenJDK Java 8
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

## Step 3: Install the Boost.Asio library
Boost.Asio is a C++ network library.
```bash
sudo apt install libboost-all-dev
```

<br/>

## Step 4: Build the CommonAPI core runtime

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

## Step 5: Build the vsomeip library

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

## Step 6: Build the CommonAPI SOME/IP runtime library

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



## Step 7: Install Open-TEE

Install optee-os-nvidia rel 35.
```bash
sudo apt install ???
sudo apt install ???
sudo apt install ???
```

Install optee-client 4.0.0 library.
```bash
sudo apt install ???
sudo apt install ???
sudo apt install ???
```


<br/>

## Step 8: Execute Cluster and Image Detecetion with DDoS Scenario

```bash
./do_cluster.sh
./do_detect.sh
./ddos_attacker.py
```
