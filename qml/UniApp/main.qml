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

    //side menu
    Rectangle
    {
        id: menu_view
        anchors.fill:parent
        color: "#303030";
        ListView
        {
            id:menu_listView
            anchors.topMargin:50
            anchors.left:parent.left
            anchors.right:parent.right
            anchors.bottom:parent.bottom
            anchors.top:parent.top

            focus:show_menu.x==0? false:true
            highlightFollowsCurrentItem: false
            model: menu_items
            delegate: Item
            {
                height:120
                width:applicationWindow1.width/2
                id: menu_delegate
                property variant myData: model
                Text
                {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left:parent.left
                    anchors.leftMargin:20
                    text:name
                    font.bold: true
                    color:parent.ListView.isCurrentItem ? "red" : "white"
                }
                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        if(parent.ListView.view.currentIndex !== index)
                        {
                            parent.ListView.view.currentIndex = index;
                            pageLoader.setSource(fileName);
                        }
                    }
                }
                Rectangle { height: 2; width: parent.width * 0.9; color: "gray"; anchors { horizontalCenter: parent.horizontalCenter; bottom: parent.bottom } }
            }
        }

        ListModel
        {
            id: menu_items
            ListElement
            {
                name: "Termine"
                fileName: "StartWindow.qml"
            }
            ListElement
            {
                name: "Stundenplan"
                fileName: "Timetable.qml"
            }
            ListElement
            {
                name: "Mensa"
                fileName: "StartWindow.qml"
            }
            ListElement
            {
                name: "Einstellungen"
                fileName: "Settings.qml"
            }
        }
    }
    //main window
    Rectangle
    {
        id:main_view
        anchors.fill:parent
        //toolbar with button to open menu
        Rectangle
        {
            id:toolbar
            anchors.top:parent.top;
            anchors.left: parent.left;
            anchors.right:parent.right;
            height:75
            color:"black";
            Image
            {
                anchors.top:parent.top;
                anchors.left:parent.left;
                anchors.bottom: parent.bottom;
                source: "to_menu.png"
                MouseArea
                {
                    anchors.fill:parent
                    onClicked:
                    {
                        triggerMenu();
                    }
                }
            }
            Label
            {
                id:toolbarLabel
                anchors.horizontalCenter: parent.horizontalCenter;
                anchors.verticalCenter: parent.verticalCenter;
                text:menu_listView.currentItem.myData.name;
                color:"white"
            }
        }

        //load the selected window
        Loader
        {   anchors.top:toolbar.bottom;
            anchors.left: parent.left;
            anchors.right:parent.right;
            anchors.bottom: parent.bottom;
            id: pageLoader
            source: "StartWindow.qml"
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
