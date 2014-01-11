import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.1

Rectangle {
    id: settingsWindow;
    color:"red";

    Column {
        id: someId;
        width: implicitWidth;
        height: implicitHeight;
        anchors.top: parent.top;
        anchors.horizontalCenter: parent.horizontalCenter;
        spacing: 50;

        TextField {
            id:username;
            placeholderText: qsTr("Benutzername");
            width: settingsWindow.width/2;
        }

        TextField {
            id:password;
            placeholderText: qsTr("Passwort");
            width: settingsWindow.width/2;
            echoMode: TextInput.PasswordEchoOnEdit;
        }

        Button {
            text: qsTr("hole Daten");
            onClicked: Client.getSession(username.text,password.text);
        }
    }

    TextArea {
        text: Client.Log;
        anchors {left: settingsWindow.left; right: settingsWindow.right; bottom: settingsWindow.bottom; top: someId.bottom; topMargin: 50;}
    }
}
