import QtQuick 2.4
import QtQuick.Controls 2.2

Item {
    // Define properties of a textfield:
    id:txtItem
    property int txtwidth : 0
    property int txtheight : 0
    property int txtrectMargin: 5 // margin between text and rectangle
    property int xPos: 0
    property int yPos: 0
    property double bgOpacity: 0.5
    property string bgColor: "#181a1c"
    property string txtColor: "black"
    property string fieldText : ""
    property string fieldTextCentered : ""
    property int fontSizePxl: 15
    property bool rectvisibility:true // to switch off the background rectangle
    property bool fontBold: false
    property bool doAnimation: false // only for animations (i.e. the main field)
    property int animationDuration: 500 //ms

    signal fieldAnimFinished()
    signal startFieldAnimation()

    Rectangle {
        id: txtRect
        width: txtItem.txtwidth
        height: txtItem.txtheight
        x: txtItem.xPos
        y: txtItem.yPos
        color: txtItem.bgColor
        opacity: txtItem.bgOpacity
        visible: txtItem.rectvisibility
    }
    Text {
        id:txtTextbody
        width: txtItem.txtwidth-2*txtItem.txtrectMargin
        height: txtItem.txtheight-2*txtItem.txtrectMargin
        x: txtItem.xPos+txtItem.txtrectMargin
        y: txtItem.yPos+txtItem.txtrectMargin
        color:txtItem.txtColor
        text:txtItem.fieldText
        font.pixelSize: txtItem.fontSizePxl
        font.bold: txtItem.fontBold
        horizontalAlignment: Text.AlignJustify
        verticalAlignment:Text.AlignTop
        wrapMode: Text.Wrap
    }

    Text {
        id:txtTextCentered
        width: txtItem.txtwidth-2*txtItem.txtrectMargin
        height: txtItem.txtheight-2*txtItem.txtrectMargin
        x: txtItem.xPos+txtItem.txtrectMargin
        y: txtItem.yPos+txtItem.txtrectMargin
        color:txtItem.txtColor
        text:txtItem.fieldTextCentered
        font.pixelSize: txtItem.fontSizePxl
        font.bold: txtItem.fontBold
        font.capitalization: Font.SmallCaps
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment:Text.AlignTop
        wrapMode: Text.Wrap
    }
    onStartFieldAnimation: {
        if (txtItem.doAnimation){
            expandfieldWidth.start()
            expandfieldHeight.start()
        }
    }

    PropertyAnimation { // expand main text field in width (after expanding main window)
        //main_window.isFinished=true
        id: expandfieldWidth
        target: main_info_field
        property:"txtwidth"
        from: main_info_field.txtwidth
        to: main_window.maximumWidth-210
        duration:animationDuration
        easing: easing.type=Easing.InOutExpo
        onStopped: {
            txtItem.doAnimation=false
            txtItem.fieldAnimFinished()
        }
    }
    PropertyAnimation { // expand main text field in width (after expanding main window)
        id: expandfieldHeight
        target: main_info_field
        property:"txtheight"
        from: main_info_field.txtheight
        to: main_window.maximumHeight-40
        duration:animationDuration
        easing: easing.type=Easing.InOutExpo
    }


}
