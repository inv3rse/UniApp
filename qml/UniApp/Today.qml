import QtQuick 2.0

Rectangle
{
    id:startWindow
    color:"red"
    ListView
    {
        anchors.fill:parent;
        model:dataModel;
        anchors.margins: 20
        delegate: Item
        {
            width: parent.width
            height:200
            Rectangle
            {
                width: parent.width
                height:180
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
                        text:model.modelData.Time;
                    }
                }

                Text
                {
                    anchors.top:timeDescr.bottom;
                    font.bold: true;
                    text:model.modelData.Description+"\n"+model.modelData.Place;
                }
            }
        }
    }
}
