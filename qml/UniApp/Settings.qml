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
        anchors {top: parent.top; topMargin: 20; horizontalCenter: parent.horizontalCenter;}
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
            echoMode: TextInput.Password;
        }

        Button {
            id:saveUser;
            text: qsTr("Save");
            onClicked: {
                DataLayer.setUsername(username.text);
                DataLayer.setPassword(password.text);
                DataLayer.loadDataFromClient();
            }
        }
    }

    TextArea {
        text: log.Log;
        anchors {left: settingsWindow.left; right: settingsWindow.right; bottom: settingsWindow.bottom; top: saveUser.bottom; topMargin: 50;}
        readOnly: true;
    }
}
