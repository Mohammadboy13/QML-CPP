import QtQuick
import QtQuick.Controls 2.0
import QtQuick.Window 2.0
import QtQuick.Layouts 1.0
import QtQuick.Dialogs
Window {

    id : parent
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    color: "lightblue"


    Rectangle{

        id:rect
        height: 10
        width: 10
        x: 10
        y: 10
        color: "red"
        opacity: 0.4
        visible: true
        rotation: 10
        scale: 1.5
    }
    // Button {
    //     id: myButton
    //     text: "Click me"

    //     // پاسخ به سیگنال clicked
    //     onClicked: {
    //         console.log("Button clicked!")
    //         text = "Clicked!"
    //     }
    // }
    Rectangle {
        id: animatedRect
        width: 100; height: 100
        color: "red"

        // انیمیشن‌ها
        Behavior on x {
            NumberAnimation { duration: 500 }
        }

        Behavior on color {
            ColorAnimation { duration: 300 }
        }

        // حالت‌ها
        states: [
            State {
                name: "active"
                PropertyChanges {
                    target: animatedRect
                    color: "green"
                    scale: 1.5
                }
            }
        ]

        // ترانزیشن بین حالت‌ها
        transitions: [
            Transition {
                from: "*"; to: "active"
                NumberAnimation { properties: "scale"; duration: 200 }
            }
        ]
    }


    /*
    Rectangle{
        color: "lightgreen"
        width: parent.width/2
        height: parent.height
        RowLayout {
           TextField {
               id: passwordInput
                width: parent.width - revealButton.width
                placeholderText: "Password"
                echoMode: passwordVisible ? TextInput.Password : TextInput.Normal
            }
        SpinBox{
            anchors.centerIn: parent

        }
        }

    }
    Rectangle {
        id: master
        x: 10
        y: 10
        width: 50
        height: 50
        color: "#00ff00"

        Behavior on x {
            NumberAnimation {
                duration: 2000
            }
        }
    }

    Text{
        id: "hellobox";
        text:"Hello WORLD"
    }
    Column {
        width: 200; height: 200

        TextInput { id: myTextInput; text: "Hello World" }

        Text { text: myTextInput.text }
    }Rectangle {
        property color red
        property color nextColor
        onNextColorChanged: console.log("The next color will be: " + nextColor.toString())
    }*/
}
