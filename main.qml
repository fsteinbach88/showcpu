import QtQuick 2.4
import QtQuick.Window 2.2
import showcpu.guibackend 1.0

Window {
    id: main_window
    visible: true
    width: 200
    minimumWidth: 200
    maximumWidth: 860 //which is the image height
    height: 300
    minimumHeight: 300
    maximumHeight: 520
    title: "ShowCPU"
    property string inputstring: ""

    // Create instance of GUIBackEnd called "backend"
    GUIBackEnd {
        id: backend
    }

    // Create a background:
    Image {
        id:bgimage
        source: "data/BGImage.jpg"
        width:960
        height:540
        x:-100
        y:0
    }
    Rectangle{
        id: bgrect
        anchors.fill: bgimage
        color: "white"
        opacity: 0.6
    }

    // Create first three buttons based on the "BtnStandard" template
    BtnStandard { // Loading the data and expanding the window
        id: startbtn
        xPos: 20
        yPos: 20
        btnwidth: 160
        btnheight: 160
        fontSizePxl: 20
        fontBold: true
        btnText: "Load CPU<br>Information"
        doAnimation: true
        onBtnRelease: {
        }
        onAnimationFinished: {
            main_info_field.startFieldAnimation()
            backend.readCPUInformation("/proc/cpuinfo");
            // the rest is happending when animation in main_info_field is done
        }
    }
    BtnStandard{
        id: helpbtn
        xPos: 20
        yPos: 190
        btnwidth: 160
        btnheight: 40
        btnText: "Readme"
        onBtnRelease: {
            var component = Qt.createComponent("ReadmeWindow.qml")
            var window    = component.createObject(main_window)
            window.show()
        }
    }
    BtnStandard{
        id: closebtn
        xPos: 20
        yPos: 240
        btnwidth: 160
        btnheight: 40
        btnText: "Close"
        onBtnRelease: {
            Qt.quit()
        }
    }

    // Textfields:
    TxtField { // main field containing basic information on CPU
        id: main_info_field
        fieldTextCentered: ""
        fontSizePxl: 24
        fontBold: true
        bgOpacity:0.4
        xPos: startbtn.xPos+10+startbtn.btnwidth
        yPos:20
        txtwidth: 0
        txtheight: 0
        doAnimation: true // will be set to false once animation is over
        onFieldAnimFinished: {
            if (backend.dataLoaded())
            {
                startbtn.btnText="Data Loaded"
                startbtn.txtColor="green"
                if (backend.getNSockets()=="1") fieldTextCentered= "CPU Information"
                else fieldTextCentered= "CPU Information (Socket 1)"

                // Below: make all fields showing properties visible

                // NOTE:
                // Note that this is only working for socket 1
                // Hence, we type "0,0" in the "get"-methods to indicate that we wish to load
                // information from the 1st socket and "0,0" for 1st socket and 1st logical core
                // For the information displayed, this is okay: They should be equal for all
                // logical cores

                socket_info.visible=true
                socket_info.fieldText="Number of sockets: "+backend.getNSockets();
                image_manufacturer.visible=true
                if (backend.getVendorID(0)=="GenuineIntel"){
                    image_manufacturer.visible=true
                    image_manufacturer.source="data/intel_logo_wiki.png"
                }
                else {
                    if (backend.getVendorID(0)=="AuthenticAMD"){
                        image_manufacturer.visible=true
                        image_manufacturer.source="data/amd_logo_wiki.png"
                    }
                    else
                    {
                        // other manufacturer, no icon image so far
                    }
                }
                // Make fields showing properties visible and lead CPOU properties
                p1.visible= true; p1.propVal=backend.getModelName(0);
                p2.visible= true; p2.propVal=backend.getVendorID(0);
                p3.visible= true; p3.propVal=backend.getMaxFreqMHz(0);
                p4.visible= true; p4.propVal=backend.getMaxCacheKB(0);
                p5.visible= true; p5.propVal=backend.getNPhysCores(0);
                p6.visible= true; p6.propVal=backend.getNLogCores(0);
                p7.visible= true; p7.propVal=backend.getCPUFam(0);
                p8.visible= true; p8.propVal=backend.getCPUModel(0);
                p9.visible= true; p9.propVal=backend.getStepping(0,0);
                p10.visible= true; p10.propVal=backend.getFPU(0,0);
                p11.visible= true; p11.propVal=backend.getFPUExc(0,0);
                p12.visible= true; p12.propVal=backend.getWP(0,0);
                p13.visible= true; p13.propVal=backend.getCPUIDLev(0,0);
                p14.visible= true; p14.propVal=backend.getBogoMIPS(0,0);
                p15.visible= true; p15.propVal=backend.getCLFlush(0,0);
                p16.visible= true; p16.propVal=backend.getCacheAlg(0,0);
                p17.visible= true; p17.propVal=backend.getAdrSz(0,0);
                //p18.visible= true; p18.propVal=backend.getFlags(0,0); // not used at the moment
            }
            else
            {
                startbtn.btnText="Error:\nData not loaded"
                startbtn.txtColor="red"
            }
        }
    }

    PropField {
        id: p1
        propName: "Model Name:"
        propVal: ""
    }
    PropField {
        id: p2
        yPos: p1.yPos+p1.pheight+5
        propName: "Vendor ID:"
        propVal: ""
    }
    PropField {
        id: p3
        yPos: p2.yPos+p2.pheight+5
        propName: "Max. Actual Frequency (MHz):"
    }
    PropField {
        id: p4
        yPos: p3.yPos+p3.pheight+5
        propName: "Max. Cache Size (KB):"
    }
    PropField {
        id: p5
        yPos: p4.yPos+p4.pheight+5
        propName: "Physical Cores:"
    }
    PropField {
        id: p6
        yPos: p5.yPos+p5.pheight+5
        propName: "Logical Cores:"
    }
    PropField {
        id: p7
        yPos: p6.yPos+p6.pheight+5
        propName: "CPU Family:"
    }
    PropField {
        id: p8
        yPos: p7.yPos+p7.pheight+5
        propName: "CPU Model:"
    }
    PropField {
        id: p9
        yPos: p8.yPos+p8.pheight+5
        propName: "Stepping:"
    }
    PropField {
        id: p10
        yPos: p9.yPos+p9.pheight+5
        propName: "Floating-Point Unit:"
    }
    PropField {
        id: p11
        yPos: p10.yPos+p10.pheight+5
        propName: "FPU Exception:"
    }
    PropField {
        id: p12
        yPos: p11.yPos+p11.pheight+5
        propName: "Write Project:"
        propVal: ""
    }
    PropField {
        id: p13
        yPos: p12.yPos+p12.pheight+5
        propName: "CPUID Level:"
        propVal: ""
    }
    PropField {
        id: p14
        yPos: p13.yPos+p13.pheight+5
        propName: "BogoMIPS:"
    }
    PropField {
        id: p15
        yPos: p14.yPos+p14.pheight+5
        propName: "Cache-Line Flush Size (bytes):"
    }
    PropField {
        id: p16
        yPos: p15.yPos+p15.pheight+5
        propName: "Cache Alignment (bytes):"
    }
    PropField {
        id: p17
        yPos: p16.yPos+p16.pheight+5
        propName: "Address Sizes:"
    }
    // Flags field is commented for now: We need to enlarge the window or change textbox size
    // to show that
//    PropField {
//        id: p18
//        yPos: p17.yPos+p17.pheight+5
//        propName: "Flags:"
//        propVal: ""
//    }

    // Add an area below the main buttons that shows the icon of the
    // producer (works for AMD and Intel) and tells the user how many sockets are present
    // --> For the moment, this program only displays results from socket 1, changing to show
    // a different socket's data is possible during future development
    TxtField {
        id: socket_info
        xPos: 20
        yPos: 290
        txtwidth: startbtn.btnwidth
        txtheight: 27
        visible:false
    }

    Image {
        id:image_manufacturer
        visible: false
        x:20
        y:350
        width: 160
        fillMode: Image.PreserveAspectFit
    }
}
