import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4


Rectangle {
    id: root
    visible: true
    width: 800
    height: 600

    property bool loadingCompleted: false
    property bool ignoreComboBoxEvent: true;

    gradient: Gradient {
        GradientStop {
            position: 0.0; color: "red"
        }
        GradientStop {
            position: 1.0; color: "grey"
        }
    }

    Text {
        id: txtTitle
        text: qsTr("Hello I am the " + ViewManager.currentScreenName)
        font.pixelSize: 16
        color: "white"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 50
    }

    Button {
        anchors.top: txtTitle.bottom
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        text: "<< Back"
        onClicked: {
             ViewManager.setCurrentScreen("UI_BLUE_SCREEN")
        }
    }

}




