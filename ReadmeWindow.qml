import QtQuick 2.4
import QtQuick.Controls 2.2

ApplicationWindow {
    id: help_window
    title:"Readme"
    width: 375
    minimumWidth: 375
    maximumWidth: 375
    height: 500
    minimumHeight: 500
    maximumHeight: 500
    x:main_window.x+100
    y:main_window.y+100

    // Again create background
    Image {
        id:bgimage2
        source: "data/BGImage.jpg"
        width:960
        height:540
        x:-300
        y:0
    }
    Rectangle{
        anchors.fill: bgimage2
        color: "white"
        opacity: bgrect.opacity
    }

    TxtField {
        id: txt_help_title
        txtwidth: help_window.width-40
        txtheight:20
        xPos:20
        yPos:20
        fontBold: true
        fieldText:"Further information:"
    }
    TxtField {
        id: txt_help_body1
        txtwidth: help_window.width-40
        txtheight:390
        xPos:20
        yPos:txt_help_title.txtheight+20
        fontSizePxl:13
        fieldText:"\
\nShowCPU is a small software tool that allows you to read your Linux system’s \
CPU information from /proc/cpuinfo.\n
This software was made as a 'homework assessment' for the job interview as a \
software engineer in the UI Software Development Team at Daimler AG, Sindelfingen, Germany.\n
To start reading you CPU information, simply click 'Load CPU Information' in the \
main window, you will notice that the information is displayed. \
In case you system has more than one CPU socket, you may \
as well read information for different sockets by indicating the socket ID in the provided field.\n
The background image is taken from shutterstock.com, all credits to 'Andrey VP'. \
The icons displayed for Intel or AMD CPUs are obtained from the german wikipedia \
website searching for 'intel' or 'amd', respectively.\n
Concept and programming by Florian Steinbach, 2017. \n
Developed using Qt Quick 5.9, GCC 5.3.1 and Qt Creator 4.4.0 on Ubuntu 16.04.03 LTS"
    }

    BtnStandard {
        btnheight: 40
        btnwidth: help_window.width-40
        xPos: 20
        yPos: help_window.height-20-btnheight
        btnText: "Close Window"
        onBtnRelease: help_window.close()
    }

}
