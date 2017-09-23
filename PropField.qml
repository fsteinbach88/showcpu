import QtQuick 2.4

Item {    // This textfield is only for showing either CPU properties or their values:
    id:propField
    property int pwidth : main_window.width-250
    property int pheight : 20
    property int xPos: 210
    property int yPos: 60
    property double bgOpacity: 0.2
    property string bgColor: "#181a1c"
    property string txtColor: "black"
    property string propName : ""
    property string propVal : ""
    property int fontSizePxl: 15

    visible: false

    Rectangle {
            id: propRect
            width: propField.pwidth
            height: propField.pheight
            x: propField.xPos
            y: propField.yPos
            color: propField.bgColor
            opacity: propField.bgOpacity
        }
    Text {
        id:propNameText
        x:propField.xPos+10
        y:propField.yPos
        height:propRect.height
        color:propField.txtColor
        text:propField.propName
        font.pixelSize: propField.fontSizePxl
        font.bold: true
        horizontalAlignment: Text.AlignLeft
        verticalAlignment:Text.AlignVCenter
        wrapMode: Text.Wrap
    }
    Text {
        id:propValueText
        x:propNameText.x+220
        y:propNameText.y
        height:propRect.height
        color:propField.txtColor
        text:propField.propVal
        font.pixelSize: propField.fontSizePxl
        font.bold: false
        horizontalAlignment: Text.AlignLeft
        verticalAlignment:Text.AlignVCenter
        wrapMode: Text.Wrap
    }

}
