import QtQuick 2.15
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls 2.15
import SmartGarden 1.0

Window {
    id: mainWindow
    width: 840
    height: 480
    minimumHeight: 480
    minimumWidth: 840
    visible: true
    title: qsTr("Smart Garden")
    RowLayout {
        anchors.fill: parent
        spacing: 2
        Loader{
            id: leftLoader
            anchors.fill: mainWindow
            width: mainWindow.width / 2
            height: mainWindow.height
            source: "./UI/HomeScreen/LeftSide/LeftSide.qml"

        }

        Loader{
            id: rightLoader
            anchors.fill: mainWindow
            width: mainWindow.width / 2
            height: mainWindow.height
            source: "./UI/HomeScreen/RightSide/RightSide.qml"
        }
    }
}
