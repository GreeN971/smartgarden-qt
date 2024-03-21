import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

Item{
    Rectangle
    {
        id: mainRectangle
        anchors.fill: parent
        Column
        {
            spacing: 2
            Rectangle
            {
               id: topRectangle
               //anchors.centerIn: mainRectangle
               height: mainRectangle.height / 2
               width: mainRectangle.width
               color: "blue"
                Rectangle{
                    width: topRectangle.width - 10
                    height: topRectangle.height - 10
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    Grid{
                        columns: 2
                        spacing: 2
                        //aligns items inside grid to center of a grid
                        horizontalItemAlignment: Grid.AlignHCenter
                        verticalItemAlignment: Grid.AlignHCenter
                        //aligns grid into center
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        Rectangle {
                            height: 60
                            width: 60
                            Image {
                               height: 60
                               width: 60
                               source: "qrc:/SmartGardenV2/UI/Assets/thermometer.png"
                            }
                        }

                        Rectangle {
                            height: 60
                            width: 60
                            color: "orange"
                            Text {
                               id: temperatureText
                               text: envData.data.temperature
                               font.pixelSize: 30
                               anchors.centerIn: parent
                            }
                        }

                        Rectangle {
                            height: 60
                            width: 60
                            Image {
                               height: 60
                               width: 60
                               source: "qrc:/SmartGardenV2/UI/Assets/humidity.png"
                            }
                        }

                        Rectangle {
                            height: 60
                            width: 60
                            Text {
                               id:humidityText
                               text: envData.data.airHumidity
                               font.pixelSize: 30
                               anchors.centerIn: parent
                            }
                        }
                    }
                }
            }
            Rectangle
            {
                id:bottomRectangle
                height: mainRectangle.height / 2
                width: mainRectangle.width

                color: "green"
                ColumnLayout{
                    id: gridL
                    spacing: 0
                    Rectangle
                    {
                        width: bottomRectangle.width
                        height: 50
                        color: "orange"
                        RowLayout
                        {
                            anchors.fill: parent
                            Text {
                                id: killSwitchText
                                text: qsTr("Kill Switch")
                                color: "red"
                                font.pixelSize: 30
                            }
                            Switch {
                                Layout.alignment: Qt.AlignRight
                                id: switchOne
                                //anchors.centerIn: switchRecOne
                                checked: true
                                icon.height: 30
                                width: 30
                            }
                        }
                    }
                    Rectangle
                    {
                        width: bottomRectangle.width
                        height: 50
                        color: "blue"
                        RowLayout
                        {
                            anchors.fill: parent
                            Text {
                                id: wateringSwitchText
                                text: qsTr("Time based watering")
                                color: "red"
                                font.pixelSize: 30
                            }
                            Switch {
                                id: wateringSwich
                                Layout.alignment: Qt.AlignRight
                                //anchors.centerIn: switchRecOne
                                checked: true
                                icon.height: 30
                                width: 30
                            }
                        }
                    }
                    Rectangle
                    {
                        width: bottomRectangle.width
                        height: bottomRectangle.height - 100
                        color: "yellow"
                        RowLayout {
                            x: -50
                            anchors.centerIn: parent
                            //Layout.alignment: Qt.AlignHCenter
                            SpinBox {
                                id: hourSpinBox
                                from: 0
                                to: 23
                                //prefix: "Hour: "
                                value: 12 // Default value for demonstration
                                transform: Rotation {
                                    origin.x: 50
                                    origin.y: 50
                                    angle: -90
                                }
                                background: Rectangle
                                {
                                    color: "transparent"
                                }
                                contentItem: Text
                                {
                                    text: hourSpinBox.value
                                    font.pixelSize: 30
                                    rotation: 90
                                    horizontalAlignment: Text.AlignHCenter
                                    verticalAlignment: Text.AlignVCenter
                                    transformOrigin: Item.Center
                                }
                            }
                            Image {
                                source: "qrc:/SmartGardenV2/UI/Assets/colon.png"
                                height: 20
                                width:5
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                transformOrigin: Item.Center
                            }

                            SpinBox {
                                id: minuteSpinBox
                                //Layout.fillHeight: true
                                from: 0
                                to: 59
                                //prefix: "Minute: "
                                value: 30 // Default value for demonstration
                                transform: Rotation {
                                    origin.x: 50
                                    origin.y: 50
                                    angle: -90
                                }
                                background: Rectangle
                                {
                                    transformOrigin: Item.Center
                                    color: "transparent"
                                }
                                contentItem: Text
                                {
                                    text: minuteSpinBox.value
                                    font.pixelSize: 30
                                    rotation: 90
                                    horizontalAlignment: Text.AlignHCenter
                                    verticalAlignment: Text.AlignVCenter
                                    transformOrigin: Item.Center
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
