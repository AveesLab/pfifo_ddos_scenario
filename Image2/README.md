# Controller Settings
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
cd sea-me-hackathon-2023/Controller/src
```

### Make Controller
```bash
qmake .
make -jX
```

### Execute Controller
```bash
./controller
```
<img src="https://github.com/AveesLab/sea-me-hackathon-2023/assets/125881959/31fb5ead-1796-49ba-a4fa-fa7fb004110e" width="70%" height="50%" title="px(픽셀) 크기 설정" alt="displaycontroller"></img><br><br><br>

## Device to Device Vsomeip communication
<a name="device-to-device-vsomeip-communication"></a>
The two devices must be connected to the same Wi-Fi for Vsomeip communication.<br>


### Check your device IP adress
```bash
ifconfig -a
```
<img src="https://github.com/AveesLab/sea-me-hackathon-2023/assets/125881959/4f3a10b1-789a-44a2-9de4-06c5c214b0b5" width="70%" height="50%" title="px(픽셀) 크기 설정" alt="ifconfig"></img><br><br>

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
<img src="https://github.com/AveesLab/sea-me-hackathon-2023/assets/125881959/146701fc-1170-4bf9-a48d-955b5fac4a66" width="70%" height="50%" title="px(픽셀) 크기 설정" alt="Screenshot from 2023-07-10 18-09-36"></img>


### Add route table
```bash
sudo route add -nv 224.244.224.24X [your ethernet ID] // example: sudo route add -nv 224.244.224.243 wlo1
route -n
```
<img src="https://github.com/AveesLab/sea-me-hackathon-2023/assets/125881959/b1346758-c9a8-4575-97dd-5102d353b8a8" width="70%" height="50%" title="px(픽셀) 크기 설정" alt="Screenshot from 2023-07-10 18-10-28"></img>

### Set vsomeip_client.json
```bash
cd sea-me-hackathon-2023/Controller/json
vim vsomeip_client.json
```
<img src="https://github.com/AveesLab/sea-me-hackathon-2023/assets/125881959/f85c7bb1-18b0-400e-8be7-0dfc4df93961" width="70%" height="50%" title="px(픽셀) 크기 설정" alt="json"></img>

Change the unicast number to your IP address.

Change the multicast number to the multicast number assigned to you.

### Execute controller
```bash
cd ~
cd sea-me-hackathon-2023/Controller/src
qmake .
make -jX
chmod +x do_controller.sh // Commands with 'do_~.sh' are intended to be executed by applying the json file.
./do_controller.sh
```



### Controller display
<img src="https://github.com/AveesLab/sea-me-hackathon-2023/assets/125881959/31fb5ead-1796-49ba-a4fa-fa7fb004110e" width="70%" height="50%" title="px(픽셀) 크기 설정" alt="displaycontroller"></img>

