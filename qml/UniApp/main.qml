import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    id: applicationWindow1
    title: qsTr("Hello World")
    width: 720
    height: 1230

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: show_menu.x==0? qsTr("open Menu") : qsTr("close Menu")
                onTriggered: triggerMenu();
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    Rectangle
    {
        id: menu_view
        anchors.fill:parent
        color:"black"

        ListView
        {
            anchors.fill: parent

            Component
            {
                id: menu_delegate
                Item
                {
                    height:150
                    width:parent.width
                    Rectangle
                    {
                        height:80
                        width:applicationWindow1.width/2
                        radius:15
                        color: ListView.isCurrentItem ? "gray" : "red"
                        Text
                        {
                            anchors.verticalCenter: parent
                            text:name
                            color:"white"
                        }
                    }
                }
            }
            focus:true
            delegate: menu_delegate
            model: menu_items
        }

        ListModel
        {
            id: menu_items
            ListElement
            {
                name: "main"
            }
            ListElement
            {
                name: "Stundenplan"
            }
            ListElement
            {
                name: "Mensa"
            }
        }
    }

    Rectangle
    {
        id:main_view
        anchors.fill:parent

        Button {
            text: "Log goes "
            anchors.centerIn: parent
            onClicked:
            {
                log.text=applicationWindow1.height+"x"+applicationWindow1.width;
            }
        }

        TextField {
            id: log
            height: 133
            readOnly: true
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            placeholderText: qsTr("Text Field")
        }


        // show menu animation
        transform: Translate
        {
            id:show_menu
            x:0
            Behavior on x { NumberAnimation { duration: 400; easing.type: Easing.OutQuad}}
        }
    }

    function triggerMenu()
    {
        show_menu.x=show_menu.x==0? applicationWindow1.width/2 : 0;
    }

}
