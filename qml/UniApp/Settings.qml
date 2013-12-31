import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.1

Rectangle {
    id: settingsWindow
    color:"red"

    Column {
        width: implicitWidth
        height: implicitHeight
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        spacing: 50

        TextField {
            placeholderText: qsTr("Benutzername")
            width: settingsWindow.width/2
        }

        TextField {
            placeholderText: qsTr("Passwort")
            width: settingsWindow.width/2
            echoMode: TextInput.PasswordEchoOnEdit
        }

        Button {
            text: qsTr("hole Daten")
        }
    }
}
