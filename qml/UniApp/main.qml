import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    id: applicationWindow1
    title: qsTr("Hello World")
    width: 720
    height: 1230
    visible:true

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

//---------toolbar with button to open menu----------------
    Rectangle
    {
        id:toolbar
        anchors {top:parent.top; left: parent.left; right:parent.right;}
        height:75
        color:"black";

        Image
        {
            id: menuImg;
            anchors {top:parent.top; left:parent.left; bottom: parent.bottom; topMargin: 5; bottomMargin: 5;}
            source: "to_menu.png"
        }
        Label
        {
            id:toolbarLabel;
            anchors {left: menuImg.right; leftMargin: 5; verticalCenter: parent.verticalCenter;}
            text:menu_listView.currentItem.myData.name;
            color:"white"
        }

        MouseArea
        {
            anchors {left:toolbar.left; top:toolbar.top; bottom:toolbar.bottom; right:toolbarLabel.right;}
            onClicked:triggerMenu();
        }
    }

//-----------------------begin side menu-----------------------
    Rectangle
    {
        id: menu_view
        anchors {left:parent.left; bottom:parent.bottom; right:parent.right; top: toolbar.bottom;}
        color: "#303030";
        ListView
        {
            id:menu_listView
            anchors {topMargin:50; left:parent.left; right:parent.right; bottom:parent.bottom; top:parent.top;}
            focus:show_menu.x==0? false:true
            highlightFollowsCurrentItem: false
            model: menu_items
            delegate: Item
            {
                property variant myData: model

                height:120
                width:applicationWindow1.width/2
                Text
                {
                    anchors {verticalCenter: parent.verticalCenter; left:parent.left; leftMargin:20;}
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
                            menu_listView.currentIndex = index;
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
//-----------------------end side menu-----------------------

    //main window
    Rectangle
    {
        id:main_view
        anchors {left:parent.left; bottom:parent.bottom; right:parent.right; top: toolbar.bottom;}

        //load the selected window
        Loader
        {
            id: pageLoader
            anchors {top:parent.top; left: parent.left; right:parent.right; bottom: parent.bottom;}
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
