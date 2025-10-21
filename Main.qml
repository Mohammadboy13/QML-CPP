import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    width: 1000
    height: 600
    visible: true
    title: "QML Creator - Rectangles"

    Rectangle {
        anchors.fill: parent
        color: "#f0f0f0"

        Text {
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 10
            text: "QML Creator - " + QMLCreator.members.length + " rectangles"
            font.pixelSize: 16
            font.bold: true
        }

        // Repeater to create rectangles from C++ data
        Repeater {
            model: QMLCreator.members

            delegate: Rectangle {
                id: memberRect

                // Standard size
                width: 100
                height: 100

                // Position from C++ data
                x: modelData.X
                y: modelData.Y

                // Color from C++ data
                color: modelData.color_Hex

                border {
                    width: 2
                    color: "black"
                }
                radius: 8

                // Display information
                Column {
                    anchors.centerIn: parent
                    spacing: 3

                    Text {
                        text: modelData.Id_qml
                        font.pixelSize: 12
                        font.bold: true
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                    }

                    Text {
                        text: "CPP: " + modelData.Id_cpp
                        font.pixelSize: 10
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                    }

                    Text {
                        text: modelData.Msec + " ms"
                        font.pixelSize: 10
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                    }

                    Text {
                        text: modelData.Min + " - " + modelData.Max
                        font.pixelSize: 10
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                    }
                }

                // Drag functionality
                Drag.active: dragArea.drag.active
                Drag.hotSpot.x: width / 2
                Drag.hotSpot.y: height / 2

                MouseArea {
                    id: dragArea
                    anchors.fill: parent
                    drag.target: parent

                    onReleased: {
                        // Update position in C++ when user moves rectangle
                        qmlCreator.updatePosition(modelData.Id_qml, parent.x, parent.y)
                        console.log("Moved", modelData.Id_qml, "to position:", parent.x, parent.y)
                    }

                    onClicked: {
                        console.log("Clicked:", modelData.Id_qml,
                                   "Color:", modelData.color_Hex,
                                   "CPP Data:", modelData.Id_cpp)
                    }
                }
            }
        }
    }
}
