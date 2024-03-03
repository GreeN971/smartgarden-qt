import QtQuick 2.15
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls 2.15
import SmartGarden 1.0

Item {
    Rectangle{
        //Jeste pak upravit height vsech prvku aby to nebylo hardcoded
        id: mainRectangle
        anchors.fill: parent
        width: parent.width
        height: parent.height
        color: "grey"
        Column{
            Rectangle
            {

                Image {
                    id: soilMeterImg
                    source: "qrc:/SmartGardenV2/UI/Assets/meter.png"
                }
                height: soilMeterImg.height
                width: mainRectangle.width


            }



            ListView
            {
                anchors.fill: parent
                id : soilIdsView
                model: envData.data.soilIDListModel
                delegate:
                    Row
                    {

                        spacing: 2
                        Rectangle{

                            height:80 //mainRectangle.height / 2
                            width: mainRectangle.width / 2

                            Text{
                                font.pixelSize: 30
                                text: soilID
                            }
                        }

                        Rectangle{
                            height:80
                            width: mainRectangle.width / 2
                            Text{
                                font.pixelSize: 30
                                text: soilValue
                            }
                        }
                    }
            }


            Rectangle
            {
                Image {
                    id: valveStatus
                    source: "qrc:/SmartGardenV2/UI/Assets/water-control.png"
                }
                height: soilMeterImg.height
                width: mainRectangle.width
            }

            Grid{
                columns: 2
                spacing: 2
                Rectangle{
                    height:80 //mainRectangle.height / 2
                    width: mainRectangle.width / 2
                    Text{
                        font.pixelSize: 30
                        text: qsTr("Valve 1 status")
                    }
                }

                Rectangle{
                    height:80
                    width: mainRectangle.width / 2
                    Text{
                        font.pixelSize: 30
                        text: qsTr("On")
                    }
                }

                Rectangle{
                    height:80 //mainRectangle.height / 2
                    width: mainRectangle.width / 2

                    Text{
                        font.pixelSize: 30
                        text: qsTr("Valve 2 status")
                    }
                }

                Rectangle{
                    height:80
                    width: mainRectangle.width / 2
                    Text{
                        font.pixelSize: 30
                        text: qsTr("Off")
                    }
                }
            }
        }
    }
}
