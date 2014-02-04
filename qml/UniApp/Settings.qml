import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.1

Rectangle {
    id: settingsWindow;
    color:"red";

    Column {
        width: implicitWidth;
        height: implicitHeight;
        anchors {verticalCenter: parent.verticalCenter; horizontalCenter: parent.horizontalCenter;}
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
            height: implicitHeight;
            width: implicitWidth;
            text: qsTr("Save");
            onClicked: {
                DataLayer.setUsername(username.text);
                DataLayer.setPassword(password.text);
                DataLayer.loadDataFromClient();
            }
        }
    }
}
