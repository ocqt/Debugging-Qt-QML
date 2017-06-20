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
            position: 0.0; color: "blue"
        }
        GradientStop {
            position: 1.0; color: "grey"
        }
    }

    Text {
        text: qsTr("MAIN SCREEN: " + ViewManager.currentScreenName)
        font.pixelSize: 16
        color: "white"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 50
    }

    Column {
        anchors.left: parent.left
        anchors.leftMargin: 40
        anchors.top: parent.top
        anchors.topMargin: 140
        spacing: 20
        Text {
            id: txtNavigation
            text: qsTr("Navigation: " )
            font.pixelSize: 26
            color: "white"

        }

        CustomButton {
            id: btnGoToRed
            text: "Go to Red Screen"
            onButtonClicked: {
                ViewManager.setCurrentScreen("UI_RED_SCREEN")
            }
        }

        CustomButton {
            id: btnGoToGreen
            text: "Go to Green Screen"
            onButtonClicked: {
                ViewManager.setCurrentScreen("UI_GREEN_SCREEN")
            }
        }
    }

    Column {
        anchors.right: parent.right
        anchors.rightMargin: 40
        anchors.top: parent.top
        anchors.topMargin: 140
        spacing: 20
        Text {
            id: txtDebugTests
            text: qsTr("Debug Tests: " )
            font.pixelSize: 16
            color: "white"

        }

        CustomButton {
            id: btnDivideByZero
            text: "Divide by Zero"
            onButtonClicked: {
                DebugTests.badMath()
            }
        }

        CustomButton {
            id: btnBreakInLoop
            text: "Break in Loop"
            property int someInt: 22
            onButtonClicked: {
                DebugTests.breakInLoop()
            }
        }

        CustomButton {
            id: btnBadPointerToQml
            text: "Bad Pointer To QML"
            onButtonClicked: {
               DebugTests.badPointerToQml()
            }
        }

        CustomButton {
            id: btnBadPointer
            text: "Bad Pointer C++"
            onButtonClicked: {
               DebugTests.badPointer()
            }
        }

        CustomButton {
            id: btnStackOverflow
            text: "Stack Overflow"
            onButtonClicked: {
               DebugTests.stackOverflow(0)
            }
        }
    }


}



