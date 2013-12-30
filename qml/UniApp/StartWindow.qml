import QtQuick 2.0

Rectangle
{
    id:startWindow
    color:"blue"
    ListView
    {
        anchors.fill:parent;
        model:5;
        anchors.margins: 20
        delegate: Item
        {
            width: parent.width
            height:150
            Rectangle
            {
                width: parent.width
                height:130
                color: "white"
                Text
                {
                    id:timeDescr
                    font.bold: true;
                    text:"von xxx bis yyy:"
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
