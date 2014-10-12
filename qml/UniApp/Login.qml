import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

Rectangle {
    id: settingsWindow;
    color:"red";

    Column {
        width: implicitWidth;
        height: implicitHeight;
        anchors {verticalCenter: parent.verticalCenter; horizontalCenter: parent.horizontalCenter;}
        spacing: 20;

        TextField {
            id:username;
            placeholderText: qsTr("Benutzername");
            text: DataLayer.getUsername();
            width: settingsWindow.width/2;
        }

        TextField {
            id:password;
            placeholderText: qsTr("Passwort");
            width: settingsWindow.width/2;
            echoMode: TextInput.Password;
        }

        CheckBox {
            id: saveUserAndPassword;
            text: qsTr("save");
        }

        Row {
            spacing: 50;
            Button {
                id:loadButton;
                height: implicitHeight;
                width: implicitWidth;
                text: qsTr("Load");
                onClicked: {
                    if (username.text != "" && password.text != "")
                    {
                        DataLayer.setUserAndPassword(username.text, password.text, saveUserAndPassword.checked);
                    }
                }
            }
            Button {
                id:cancelButton;
                height: implicitHeight;
                width: implicitWidth;
                text: qsTr("Cancel");
                onClicked: {
                    DataLayer.abortLogin();
                }
            }

        }
    }
}
