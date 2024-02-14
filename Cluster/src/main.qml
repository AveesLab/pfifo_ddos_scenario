import QtQuick 2.7
import QtQuick.Controls 2.2
import "."
import QtMultimedia 5.5

ApplicationWindow {
    visible: true
    width: screen.width
    height: screen.height
    property alias gearImage: gearImage
    property string bState: "P"
    property bool showWeather: false
    property bool showWarn: false
    property bool showLight: false
    title: qsTr("Speedometer")

    // Background Image
    Image {
        id: backgroundImage
        anchors.fill: parent
        source: "image/back.png" // Replace with the path to your background image
    }
    // speed gage
    Image {
        id: speedImage
        width: 590
        height: 590
        anchors.verticalCenterOffset: -175
        anchors.horizontalCenterOffset: -548
        anchors.centerIn: parent
        source: "image/dial.png" // Replace with the path to your arc image
    }
    Image {
        id: rpmImage
        width: 550
        height: 550
        anchors.verticalCenterOffset: -185
        anchors.horizontalCenterOffset: 527
        anchors.centerIn: parent
        source: "image/rpm.png" // Replace with the path to your arc image
    }
    // Car Image
    Image {
        id: carImage
        y: -484
        width: 412 // Adjust the width of the car image
        height: 299
        anchors.horizontalCenterOffset: 0
        anchors.bottomMargin: 185 // Adjust the height of the car image
        source: "image/car1.png" // Replace with the path to your car image
        anchors {
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter
            margins: 20
        }
    }
    Image {
        id: weatherIcon
        width: 166
        height: 166
        anchors.verticalCenterOffset: -46
        anchors.horizontalCenterOffset: 0
        anchors.centerIn: parent
        source: weatherAPI.weatherIcon
        visible: showWeather
    }
    Image {
        id: warnIcon
        width: 864
        height: 80
        anchors.verticalCenterOffset: -506
        anchors.horizontalCenterOffset: 0
        anchors.centerIn: parent
        source: "image/warning.png"
        visible: showWarn
    }
    Timer {
        id: blinkTimer
        interval: 500 // Blink every 500ms
        running: false // Don't start running automatically
        repeat: true
        onTriggered: {
            warnIcon.visible = !warnIcon.visible // Toggle visibility
        }
    }
    Image {
        id: lightIcon
        width: 80
        height: 80
        anchors.verticalCenterOffset: -506
        anchors.horizontalCenterOffset: -548
        anchors.centerIn: parent
        source: "image/star.png"
        visible: showLight
    }

    Text {
        id: temperature
        font.pixelSize: 40
        font.bold: true
        font.italic: true
        color: 'white'
        anchors.horizontalCenter: weatherIcon.horizontalCenter
        anchors.top: weatherIcon.bottom
        anchors.topMargin: -40
        text: weatherAPI.temperature + "°C"
        anchors.horizontalCenterOffset: 1
        visible: showWeather
    }

    Canvas {
        id: speedpointer
        width: parent.width
        height: parent.height
        anchors.verticalCenterOffset: -170
        anchors.horizontalCenterOffset: -548
        rotation: 180
        anchors.centerIn: parent
        onPaint: {
            var ctx = getContext('2d');
            var centerX = width / 2;
            var centerY = height / 2;

            // Clear the canvas
            ctx.clearRect(0, 0, width, height);

            // Draw the speed bar
            var angle = (speedReceiver.speedValue - 35) * Math.PI / 180; // Convert speed to angle
            ctx.beginPath();
            ctx.moveTo(centerX, centerY);
            ctx.lineTo(centerX + 160 * Math.cos(angle), centerY + 160 * Math.sin(angle));
            ctx.lineWidth = 10;
            ctx.strokeStyle = '#ff0000';
            ctx.stroke();
        }

        Connections {
            target: speedReceiver
            onSpeedValueChanged: {
                speedpointer.requestPaint()
            }
        }
    }

    Canvas {
        id: rpmpointer
        width: parent.width
        height: parent.height
        anchors.verticalCenterOffset: -185
        anchors.horizontalCenterOffset: 527
        rotation: 180
        anchors.centerIn: parent
        onPaint: {
            var ctx = getContext('2d');
            var centerX = width / 2;
            var centerY = height / 2;

            // Clear the canvas
            ctx.clearRect(0, 0, width, height);

            // Draw the speed bar
            var angle = ((rpmReceiver.rpmValue / 30) -45) * Math.PI / 180; // Convert rpm to angle
            ctx.beginPath();
            ctx.moveTo(centerX, centerY);
            ctx.lineTo(centerX + 135 * Math.cos(angle), centerY + 135 * Math.sin(angle));
            ctx.lineWidth = 7;
            ctx.strokeStyle = '#ff0000';
            ctx.stroke();
        }

        Connections {
            target: rpmReceiver
            onRpmValueChanged: {
                rpmpointer.requestPaint()
            }
        }
    }
    Row {
        anchors.verticalCenterOffset: 486
        anchors.horizontalCenterOffset: 0
        anchors.centerIn: parent
        spacing: 10

        Text {
            id: pText
            font.pixelSize: 130
            font.italic: true
            font.bold: true
            text: "P"
            color: 'red'
        }

        Text {
            id: rText
            font.pixelSize: 130
            font.italic: true
            font.bold: true
            text: "R"
            color: 'white'
        }

        Text {
            id: nText
            font.pixelSize: 130
            font.italic: true
            font.bold: true
            text: "N"
            color: 'white'
        }

        Text {
            id: dText
            font.pixelSize: 130
            font.italic: true
            font.bold: true
            text: "D"
            color: 'white'
        }

        Connections {
            target: buttonsReceiver
            onButtonsValueChanged: {
                var buttonValue = buttonsReceiver.buttonsValue;

                if (buttonValue === "P" || buttonValue === "R" || buttonValue === "N" || buttonValue === "D") {
                    bState = buttonValue;
                    pText.color = bState === "P" ? 'red' : 'white';
                    rText.color = bState === "R" ? 'red' : 'white';
                    nText.color = bState === "N" ? 'red' : 'white';
                    dText.color = bState === "D" ? 'red' : 'white';

                    gearImage.visible = bState === "P";
                    videoOutput.visible = bState === "R";
                }
                else if(buttonValue === "Weather"){
                    showWeather = !showWeather;
                    weatherAPI.requestWeather("Seoul");
                }
                else if(buttonValue === "Warn"){
                    if (showWarn) {
                        blinkTimer.stop(); // Stop blinking
                        warnIcon.visible = false; // Ensure the icon is hidden
                    } else {
                        blinkTimer.start(); // Start blinking
                    }
                    showWarn = !showWarn;
                }
                else if(buttonValue === "Light"){
                    showLight = !showLight;
                }
            }
        }

    }

    Image {
        id: gearImage
        width: 450
        height: 450
        scale: 1
        anchors.verticalCenterOffset: -334
        anchors.horizontalCenterOffset: 1
        anchors.centerIn: parent
        source: "image/volk.png" // Replace with the path to your image
        visible: bState === "P"
    }

//    Camera {
//        id: camera
//        deviceId: "/dev/video1"
//    }

//    VideoOutput {
//        id: videoOutput
//        width: 492 // Set width of the camera output
//        height: 441
//        anchors.verticalCenterOffset: -334
//        anchors.horizontalCenterOffset: 0 // Set height of the camera output
//        anchors.horizontalCenter: parent.horizontalCenter // Center the output horizontally
//        anchors.verticalCenter: parent.verticalCenter // Center the output vertically
//        source: camera
//        visible: bState === "R"
//    }
}
