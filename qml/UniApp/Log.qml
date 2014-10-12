import QtQuick 2.1
import QtQuick.Controls 1.1

Rectangle {

    TextArea {
        text: log.Log;
        anchors.fill: parent;
        readOnly: true;
    }
}
