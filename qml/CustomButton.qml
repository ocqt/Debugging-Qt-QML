import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Button {
    signal buttonClicked

    onClicked: {
        buttonClicked()
    }

    style: ButtonStyle {
        background: Rectangle {
            implicitWidth: 200
            implicitHeight: 36
            border.width: control.activeFocus ? 2 : 1
            border.color: "#888"
            radius: 4
            gradient: Gradient {
                GradientStop { position: 0 ; color: control.pressed ? "#ccc" : "#eee" }
                GradientStop { position: 1 ; color: control.pressed ? "#aaa" : "#ccc" }
            }
        }
        label: Text {
            id: label
            anchors.centerIn: parent
            text: control.text
            color: "navy"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 18
        }
    }
}
