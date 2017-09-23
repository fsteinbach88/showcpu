# showcpu
ShowCPU is an application programmed in the course of a “homework assessment” and accompanies the interview as a software engineer in the UI Software Development Team at Daimler AG, Sindelfingen, Germany. The major task of ShowCPU is to provide information on the CPU within a Linux system by reading /proc/cpuinfo and subsequently displaying the data in a graphical user interface (GUI). ShowCPU is capable of reading the information for each CPU socket and logical core. At this stage of development, only the 1st socket’s information is displayed in the GUI, which is sufficient for most systems. However, ShowCPU is programmed to allow further development towards displaying information for each specific CPU socket on machines with multiple CPUs such as high-performance clusters or servers. The ShowCPU application was developed on Ubuntu 16.04.03 LTS using the open-source version of Qt Creator 4.4.0, Qt Quick 5.9, GCC 5.3.1 and C++11. 
To install and run ShowCPU (tested on Ubuntu 16.04.03), please follow the instructions below:
1)	Install Qt from terminal: 
wget http://download.qt.io/official_releases/qt/5.9/5.9.1/qt-opensource-linux-x64-5.9.1.run
chmod +x qt-opensource-linux-x64-5.9.1.run
./qt-opensource-linux-x64-5.9.1.run
More information on installing Qt is provided on https://wiki.qt.io/Install_Qt_5_on_Ubuntu.
2)	Download the ShowCPU source code from GitHub:
ADD LINK
3)	Build and run ShowCPU on your system:
Open the “ShowCPU.proc” project file in Qt Creator. Click Build and Run or hit Ctrl+r, the application will start. Click on “Load CPU Information” to read /proc/cpuinfo and display the data. Moreover, an executable is created in the source-code directory. You can paste or move it locally to run the application again. 
