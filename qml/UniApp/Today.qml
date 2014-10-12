import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1

Rectangle
{
    id:terminWindow
    color:"#ce8440"
    height:800;
    width:500;

    Rectangle
    {
        id:selectDay;
        anchors{left:parent.left; right:parent.right; bottom:parent.bottom;}
        height:50;

        Button
        {
            anchors.left: parent.left;
            anchors.bottom: parent.bottom;
            text:"prev";
            onClicked: DataLayer.loadDataFromClient(-1);
        }

        Button
        {
            anchors.right: parent.right;
            anchors.bottom: parent.bottom;
            text:"next";
            onClicked: DataLayer.loadDataFromClient(1);
        }
    }

    ListView
    {
        //        anchors.fill:parent;
        anchors{left:parent.left; right:parent.right; top:parent.top; bottom:selectDay.top;}
        model: DataLayer.dataModel;
        delegate: Item {
            id: terminEntry;
            width: parent.width
            height:200

            Rectangle
            {
                id :innerItem
                anchors {top: terminEntry.top; bottom:terminEntry.bottom;bottomMargin: 20}
                color: "#d4d4d4"
                width: parent.width;
                radius:15

                Text
                {
                    id: timeDescr
                    anchors {top: parent.top; topMargin: 4; horizontalCenter: parent.horizontalCenter; }
                    height:implicitHeight+5
                    font.bold: true;
                    text: model.modelData.Time;
                }

                Rectangle { height: 2; width: parent.width-parent.radius; color: "black"; anchors { horizontalCenter: parent.horizontalCenter; top: timeDescr.bottom } }

                Text
                {
                    anchors {top:timeDescr.bottom; topMargin: 10; left:parent.left; leftMargin: 5;}
                    font.bold: true;
                    text:model.modelData.Description+"\n"+model.modelData.Place;
                }

            }
        }
    }

    Login
    {
        id: login;
        anchors.fill: parent;
        visible: DataLayer.authRequired;
    }

}
