import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

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
                Grid{
                    anchors.centerIn: parent
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    rows:2
                    columns: 2
                    //width: bottomRectangle.width - 100
                    //height: bottomRectangle.height - 100

                    Rectangle
                    {
                        id: switchRecOne
                        width: bottomRectangle.width / 6
                        height: bottomRectangle.height / 2
                        Switch{
                            anchors.centerIn: switchRecOne
                            icon.color: "red"
                            icon.height: 60
                            width: 60
                        }
                    }
                    Rectangle{
                        id: textRecOne
                        width: bottomRectangle.width / 2
                        height: bottomRectangle.height / 2
                        Text {
                            anchors.centerIn:textRecOne
                            id: killSwitchText
                            text: qsTr("Kill Switch")
                            color: "red"
                            font.pixelSize: 30
                        }
                    }
                    Rectangle
                    {
                        id: switchRecTwo
                        width: bottomRectangle.width / 6
                        height: bottomRectangle.height / 2
                        Switch{
                            id: wateringOverride

                            signal woStatusChanged()

                            anchors.centerIn:switchRecTwo
                            icon.color: "red"
                            icon.height: 60
                            width: 60
                            onClicked:
                            function()
                            {
                                manualWateringText.color.r = Math.random()
                                manualWateringText.color.g = Math.random()
                                manualWateringText.color.b = Math.random()
                                console.log("Status has changed to" + (wateringOverride.checked? "On" : "Off"))
                            }
                        }
                    }
                    Rectangle{
                        id:textRecTwo
                        width: bottomRectangle.width / 2
                        height: bottomRectangle.height / 2
                        Text {
                            anchors.centerIn:textRecTwo
                            id: manualWateringText
                            text: qsTr("Manual watering")
                            color: "red"
                            font.pixelSize: 30
                        }
                    }
                }
            }
        }
    }
}
