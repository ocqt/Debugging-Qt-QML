import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4


Item {
    id: root
    visible: true
    width: 800
    height: 600

    property bool loadingCompleted: false
    property bool ignoreComboBoxEvent: true;

    Component.onCompleted: {

        cboLanguage.currentIndex = Translator.languageIndex
        loadingCompleted = true
        createVariable()
    }

    function createVariable() {
        var i = 56
        console.log("i = " + i)

        var a = 6
        console.log("a = " + a)
    }

    Loader
    {
        id: loaderUI
        anchors.fill: parent
        clip: true

        // The ViewManager will set the initial screen
        //source: "blueScreen.qml"
        asynchronous: false

    }

    Text {
        id: lblTranslatedText
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: txtHello1.top
        anchors.bottomMargin: 10
        color: "white"
        //text: "The text below is localized:"
        text: qsTr("The current locale: " + Translator.localeName)
    }

    Text {
        id: txtHello1
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: cboLanguage.top
        anchors.bottomMargin: 10
        font.bold: true
        color: "white"
        text: qsTr("Hello World")

    }

    ComboBox {
        id: cboLanguage
        anchors.bottom:  parent.bottom
        anchors.bottomMargin: 30
        anchors.horizontalCenter: parent.horizontalCenter
        model: Translator.languageList
        width: 100

        onCurrentIndexChanged: {
            if (loadingCompleted === false) return

            if (Translator.languageIndex !== currentIndex) {

                Translator.languageIndex = currentIndex
            }
        }
    }



    Connections {
        target: ViewManager
        onCurrentScreenChanged: setNextScreen()
    }

    function setNextScreen(  )
    {
        console.log ("setNextScreen " + ViewManager.currentScreenFilename)

        loaderUI.source = ""
        loaderUI.source = ViewManager.currentScreenFilename


    }

}

