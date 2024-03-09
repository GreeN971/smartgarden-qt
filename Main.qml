import QtQuick 2.15
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls 2.15
import SmartGarden 1.0
import QtQuick.Controls.Material

Window {
    id: mainWindow
    Material.theme: Material.Light
    Material.accent: Material.Blue
    width: 840
    height: 480
    minimumHeight: 480
    minimumWidth: 840
    visible: true
    title: qsTr("Smart Garden")
    RowLayout {
        anchors.fill: parent
        Loader{
            id: leftLoader
            Layout.fillHeight: true
            Layout.preferredWidth: mainWindow.width / 2
            source: "./UI/HomeScreen/LeftSide/LeftSide.qml"
        }
        Loader{
            id: rightLoader
            Layout.fillHeight: true
            Layout.preferredWidth: mainWindow.width / 2
            source: "./UI/HomeScreen/RightSide/RightSide.qml"
        }
    }
}
