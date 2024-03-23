import QtQuick 2.15
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls 2.15
import SmartGarden 1.0


ColumnLayout
{
    //in order for centering to work in scaling maybe contrainer
    //rectangle is needed
    anchors.fill: parent
    id: parentLayout
        Rectangle {
            Layout.alignment: Qt.AlignTop
            Image{
                id: meter
                source: "qrc:/qml/UI/Assets/meter.png"
            }
            Layout.fillWidth: true
            color: "lightblue"
            height: meter.height
        }
        GridLayout {
                    Layout.row: 1
                    Layout.columnSpan: 2
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    columns: 2
                    Rectangle {
                        id: soilListRectangle
                        color: "lightyellow"
                        Layout.fillWidth: true
                        Layout.preferredHeight: 100
                        Layout.row: 0
                        Layout.column: 0
                        ListView
                        {
                            anchors.fill: parent
                            id : soilIdsView
                            model: envData.data.soilIDListModel
                            clip: true
                            //interactive: false
                            delegate:
                                Grid {
                                    rowSpacing: 10
                                    columnSpacing: 20
                                    Rectangle{
                                        Text {
                                            anchors.centerIn: parent
                                            id: soilIDText
                                            text: soilID
                                            font.pixelSize: 30
                                        }
                                        id: soilRecDefWidth
                                        height: soilIdsView.height / 2
                                        width: soilListRectangle.width / 1.5
                                    }
                                    Rectangle{
                                        Text {
                                            anchors.centerIn: parent
                                            id: soilValueText
                                            text: soilValue
                                            font.pixelSize: 30
                                        }
                                        height: soilIdsView.height / 2
                                        width: soilRecDefWidth.width / 3
                                    }
                            }
                        }
                    }
                }
            Rectangle {
                Layout.alignment: Qt.AlignTop
                Image{
                    id: valve
                    source: "qrc:/qml/UI/Assets/water-control.png"
                }
                Layout.fillWidth: true
                color: "lightblue"
                height: meter.height + 10
            }

        GridLayout{
            Layout.row: 1
            Layout.columnSpan: 2
            Layout.fillWidth: true
            Layout.fillHeight: true
            columns: 2
                    Rectangle {
                        id: valveListRectangle
                        color: "lightgrey"
                        Layout.fillWidth: true
                        Layout.preferredHeight: 100
                        Layout.row: 1
                        Layout.column: 0
                        ListView
                        {
                            anchors.fill: parent
                            id : valveIDView
                            model: envData.valveIDListModel
                            clip: true
                            interactive: false
                            delegate:
                                Grid {
                                    rowSpacing: 10
                                    columnSpacing: 20
                                    Rectangle {
                                        Text {
                                            anchors.centerIn: parent
                                            id:valveIDText
                                            text: valveID
                                            font.pixelSize: 30
                                        }
                                        id: recDefWidth
                                        height: valveIDView.height / 2
                                        width: valveListRectangle.width / 2
                                    }
                                    Rectangle {
                                        Text {
                                            anchors.centerIn: parent
                                            id:valveValueText
                                            text: valveValue
                                            font.pixelSize: 30
                                        }
                                        height: valveIDView.height / 2
                                        width: recDefWidth.width
                                    }
                            }
                        }
                    }
                }

}

