# Cluster Settings
You can run two executables [simultaneously on one device](#process-to-process-vsomeip-communication).<br>
The json file is only required when applying communication between devices.<br>
The two devices must be connected to the same Wi-Fi for Vsomeip communication.<br>
Please follow the [Device to Device Vsomeip communication](#device-to-device-vsomeip-communication) instructions below to communicate between devices.<br>
<br>

## Process to Process Vsomeip communication
<a name="process-to-process-vsomeip-communication"></a>

### Git clone
```bash
cd ~
git clone https://github.com/AveesLab/sea-me-hackathon-2023.git
cd sea-me-hackathon-2023/Cluster/src
```

### Make Cluster
```bash
qmake .
make -jX
```

### Execute Cluster
```bash
./cluster
```
<img src="https://github.com/AveesLab/sea-me-hackathon-2023/assets/125881959/6e168588-6af5-44fa-8721-9e3c23f5092f" width="70%" height="50%" title="px(픽셀) 크기 설정" alt="Screenshot from 2023-07-11 13-09-46"></img><br><br><br>

## Device to Device Vsomeip communication
<a name="device-to-device-vsomeip-communication"></a>
The two devices must be connected to the same Wi-Fi for Vsomeip communication.<br>


### Check your device IP adress
```bash
ifconfig -a
```
<img src="https://github.com/AveesLab/sea-me-hackathon-2023/assets/125881959/fc6d9446-9ab7-4ce7-8a25-e5214dcd63fe" width="70%" height="50%" title="px(픽셀) 크기 설정" alt="ifconfig"></img>
<br>

### Network ping check
You can check if communication is possible by ping test between devices.

### Ping to TX2
<img src="https://github.com/AveesLab/hackathon-someip/assets/125881959/06ef3f9e-3e89-468e-aa5b-1985d7b73dae" width="70%" height="50%" title="px(픽셀) 크기 설정" alt="ping_to_tx2"></img><br><br>


### Ping to laptop
<img src="https://github.com/AveesLab/hackathon-someip/assets/125881959/349ef132-b782-4f6d-bb54-e722a2ff6308" width="70%" height="50%" title="px(픽셀) 크기 설정" alt="ping to laptop"></img><br><br>

### Set route table
Below image is before add route table<br>
you have to set route table to use vsomeip communication
```bash
route -n // check your route table
```
<img src="https://github.com/AveesLab/sea-me-hackathon-2023/assets/125881959/ba938278-007d-415b-a233-e94027b63fd1" width="70%" height="50%" title="px(픽셀) 크기 설정" alt="Screenshot from 2023-07-10 18-44-12"></img>


Add route table
```bash
sudo route add -nv 224.244.224.24X [your ethernet ID] // example: sudo route add -nv 224.244.224.243 wlan0
route -n
```
<img src="https://github.com/AveesLab/sea-me-hackathon-2023/assets/125881959/901b3af8-f49c-4488-9286-cbb9bf7c21ff" width="70%" height="50%" title="px(픽셀) 크기 설정" alt="Screenshot from 2023-07-10 18-44-36"></img>

# Set vsomeip_cluster.json
```bash
cd sea-me-hackathon-2023/Cluster/json
vim vsomeip_server.json
```
<img src="https://github.com/AveesLab/sea-me-hackathon-2023/assets/125881959/72ac5fa2-af54-4e44-93b3-21bc2fc21e80" width="70%" height="50%" title="px(픽셀) 크기 설정" alt="json"></img>

Change the unicast number to your IP address.

Change the multicast number to the multicast number assigned to you.

### Execute cluster
```bash
cd ~
cd sea-me-hackathon-2023/Cluster/src
qmake .
make -jX
chmod +x do_cluster.sh // Commands with 'do_~.sh' are intended to be executed by applying the json file.
./do_cluster.sh
```



### Cluster display
<img src="https://github.com/AveesLab/sea-me-hackathon-2023/assets/125881959/6e168588-6af5-44fa-8721-9e3c23f5092f" width="70%" height="50%" title="px(픽셀) 크기 설정" alt="Screenshot from 2023-07-11 13-09-46"></img>

