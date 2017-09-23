import QtQuick 2.4

Item {
    // Define properties of the "standard" button:
    id:btnItem
    property int btnwidth : 0
    property int btnheight : 0
    property int xPos: 0
    property int yPos: 0
    property double btnOpacity: 0.8
    property string colorNormal: "#181a1c"
    property string colorHighl: "#939697"
    property string txtColor: "white"
    property string btnText : "empty"
    property int fontSizePxl: 15
    property bool fontBold: false
    property bool doAnimation: false // only for buttons starting animations (i.e. the start button)
    property int animationDuration: 750 //ms

    signal btnRelease()
    signal animationFinished()

    Rectangle {
        id: btnRect
        width: btnItem.btnwidth
        height: btnItem.btnheight
        x: btnItem.xPos
        y: btnItem.yPos
        color: btnItem.colorNormal
        opacity: btnItem.btnOpacity

        MouseArea {
            anchors.fill: btnRect
            onEntered: {
                btnRect.color = btnItem.colorHighl
            }
            onReleased: {
                btnRect.color = btnItem.colorNormal
                if (doAnimation) {
                    expandwindowWidth.start()
                    expandwindowHeight.start()
                }
                btnItem.btnRelease()
            }
        }
    }

    Text {
        id:btnText
        anchors.fill: btnRect
        color:btnItem.txtColor
        text:btnItem.btnText
        horizontalAlignment:Text.AlignHCenter
        verticalAlignment:Text.AlignVCenter
        font.pixelSize: btnItem.fontSizePxl
        font.bold: btnItem.fontBold
    }

    // Some Animations:
    PropertyAnimation { // expand whole window in width (after clicking main button)
        id: expandwindowWidth
        target: main_window
        property:"width"
        from: main_window.width
        to: main_window.maximumWidth
        duration:animationDuration
        easing: easing.type=Easing.InOutExpo
        onStopped:   {
            btnItem.doAnimation=false
            btnItem.animationFinished()
        }
    }
    PropertyAnimation { // expand whole window in height (after clicking main button)
        id: expandwindowHeight
        target: main_window
        property:"height"
        from: main_window.height
        to: main_window.maximumHeight
        duration:animationDuration
        easing: easing.type=Easing.InOutExpo
    }
}

