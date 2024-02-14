import QtQuick 2.7
import QtQuick.Controls 2.2
import com.seame.Detect 1.0

ApplicationWindow {
    visible: true
    width: 320
    height: 240
    title: qsTr("image2")

    Detect {
        id: detect
    }

    Button {
        id: buttonCamera
        property bool isToggled: false
        x: 95
        y: 60 // Add this line

        onClicked: {
            isToggled = !isToggled;
            if (isToggled) {
                detect.startCamera();
            }
        }
        width: 131
        height: 120

        contentItem: Image {
            id: cameraImage
            width: 100
            height: 100
            source: buttonCamera.isToggled ? "image/camon.png" : "image/camoff.png" // Use the state here
        }

        background: Rectangle {
            color: "transparent"
        }
    }

}
