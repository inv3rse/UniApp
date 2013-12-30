import QtQuick 2.0

Rectangle
{
    id:startWindow
    color:"blue"
    ListView
    {
        anchors.fill:parent;
        model:15;
        anchors.margins: 20
        delegate: Item
        {
            width: parent.width
            height:150
            Rectangle
            {
                width: parent.width
                height:130
                radius:15;
                color: "white"
                Rectangle
                {
                    id:timeDescr
                    width:parent.width;
                    height:50

                    color:"lightgray"
                    Text
                    {

                        font.bold: true;
                        text:"von xxx bis yyy:"
                    }
                }

                Text
                {
                    anchors.top:timeDescr.bottom;
                    font.bold: true;
                    text:"Terminbeschreibung";
                }
            }
        }
    }
}
