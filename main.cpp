/*
 * QUICK SUMMARY:
 * This program reads the information from /proc/cpuinfo on Linux systems.
 * The information is processed to be displayed in a graphical user interface (GUI).
 * The CPU information is stored in a specific class "CPUInfo". Each instance of this class represents a socket.
 * To communicate with the GUI, the class "GUIBackEnd" is used.
 *
 * by Florian Steinbach, 2017
 */

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <math.h>
#include <vector>

#include "guibackend_header.h"

using namespace std;

int main(int argc, char *argv[])
{

    //Declare necessary variables:
    char cFilename[]="/proc/cpuinfo"; // filename, we wish to read information from /proc/cpuinfo

    // Check if file exists, if not: tell user and terminate program
    if (!FileExists(cFilename))
    {
        printf("File %s does not exist, terminating program\n",cFilename);
        return 0;
    }

    QGuiApplication app(argc, argv);

    qmlRegisterType<GUIBackEnd>("showcpu.guibackend",1,0,"GUIBackEnd");

    QQmlApplicationEngine engine;

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

vector<CPUInfo> ReadFile(const char *cFileRead)
{
    /*
     * This function provides the framework to read /proc/cpuinfo in Linux systems.
     * The file "cpuinfo" contains the names of properties of the CPU and their corresponding values.
     * The actual assignment of properties in class "CPUInfo" is done in a seperate function (AssignProp)
     */

    // DECLARATIONS
    vector<CPUInfo> vAllSockets; // IMPORTANT, WILL BE RETURNED: Storing all CPU information for all sockets
    ifstream fCPUInfoFile(cFileRead); // input file
    string sLine; // full line of the file
    string sProp; // only the property name
    string sPropValue; // only the value of this property (for now, as string)
    size_t iPosDelim; // will store the position of the ":" symbol delimiting the property name and the value
    int iCountLineNumber=0; // track lines that have already been read, we start counting at 0
    int iStartAtLineNumber=0; // start reading to search for new socket ID in this line, initially start at 0
    int iSocketID=0; // the number of sockets-1
    CPUInfo dummySocket;

    // First of all, check if the file exists:
    if (!FileExists(cFileRead)) return vAllSockets; //if not, return an empty dataset

    // PREPARATIONS
    iSocketID = GetSocketID(cFileRead,iStartAtLineNumber); // find socket ID for 1st logical processor
    // if socket ID for 1st logical processor is not 0, we need to pre-allocate vector elements for each socket until this one:
    if (iSocketID>0)
        for (int i=0;i<=iSocketID;i++) vAllSockets.push_back(dummySocket);
    vAllSockets.push_back(dummySocket); // if iSocketID == 0
    // pre-allocate 1st socket
    CPUInfo thisSocket;

    //START READING:
    // We do not need to check if the file exists: We did this before
    while (getline( fCPUInfoFile, sLine)) // go through each line reading the data
    {
        // READ PROPERTY NAME AND VALUE FROM THIS LINE:
        iPosDelim = sLine.find(":"); // Find where the actual value is delimited from property name by character ":"
        if (iPosDelim != string::npos) // returns false if there is no ":" character or position is after end of this line
        {
            sProp = sLine.substr(0,iPosDelim+1); // property name, including the ":" symbol, which does not matter too much
            sPropValue = sLine.substr(iPosDelim+1); // value, starts one character after the acquired position until the end of the line
            sPropValue.erase(0,1); // necessary since 1st character is space

            /* If you wish to display the result in terminal:
            if ( sPropValue.size()>0) cout << "Line " << iCountLineNumber << " " << sProp <<" " << sPropValue << endl;
            else cout << "Line " << iCountLineNumber << " " << sProp << " empty" << endl;
            */

            // ASSIGN DATA TO INSTANCE OF CPUInfo CLASS
            // if we found a new highest socket ID, pre-allocate all necessary elements until this one:
            if (iSocketID>(int)vAllSockets.size()-1)
                for (int i=(int)vAllSockets.size();i<=iSocketID;i++)
                    vAllSockets.push_back(dummySocket);

            vAllSockets[iSocketID] = AssignProp(sProp,sPropValue,vAllSockets[iSocketID]);

            iCountLineNumber++; // means go to next line number
            sLine.clear(); // clear string from this line to be able to read next line
        }
        else // No ":" character found: Assume a new block for a new processor starts here: Search for correct socket ID again
        {
            // finally check with the read data, if hyperthreading is possible and assign prop:
            if (vAllSockets[iSocketID].getNumbLogCores() > vAllSockets[iSocketID].getNumbPhyCores())
                vAllSockets[iSocketID].vbHyperthreadYesNo.push_back(true);
            else
                vAllSockets[iSocketID].vbHyperthreadYesNo.push_back(false);

            iStartAtLineNumber=iCountLineNumber+2;
            iSocketID = GetSocketID(cFileRead,iStartAtLineNumber);
        }
    }
    fCPUInfoFile.close(); // after reaching the last line

    return vAllSockets;
}

CPUInfo AssignProp(string sPropName, string sValue,CPUInfo inSocket)
{
    // This function assigns the property name and its value to the correct variable in the CPUInfo class
    CPUInfo outSocket=inSocket;

    // go through all keywords from cpuinfo and assign value to correct variable in CPUInfo instance:
    if (sPropName.find("processor") != string::npos) {
        outSocket.viLogCoreID.push_back(stoi(sValue));
        return outSocket;
    }
    if (sPropName.find("vendor_id") != string::npos) {
        outSocket.vsVendorID.push_back(sValue);
        return outSocket;
    }
    if (sPropName.find("cpu family") != string::npos) {
        outSocket.viCPUFamily.push_back(stoi(sValue));
        return outSocket;
    }
    if (sPropName.find("model name") != string::npos) {
        outSocket.vsModelName.push_back(sValue);
        return outSocket;
    }
    if (sPropName.find("model") != string::npos) {
        outSocket.viModel.push_back(stoi(sValue));
        return outSocket;
    }
    if (sPropName.find("stepping") != string::npos) {
        outSocket.viStepping.push_back(stoi(sValue));
        return outSocket;
    }
    if (sPropName.find("microcode") != string::npos) {
        outSocket.vsMicrocode.push_back(sValue);
        return outSocket;
    }
    if (sPropName.find("cpu MHz") != string::npos) {
        outSocket.vdCPUMHz.push_back(stod(sValue));
        return outSocket;
    }
    if (sPropName.find("cache size") != string::npos) {
        outSocket.vdCacheSize.push_back(stod(sValue));
        return outSocket;
    }
    if (sPropName.find("siblings") != string::npos) {
        outSocket.viNumbLogCores.push_back(stoi(sValue));
        return outSocket;
    }
    if (sPropName.find("core id") != string::npos) {
        outSocket.viCoreID.push_back(stoi(sValue));
        return outSocket;
    }
    if (sPropName.find("cpu cores") != string::npos) {
        outSocket.viNumbPhysCores.push_back(stoi(sValue));
        return outSocket;
    }
    if (sPropName.find("apicid") != string::npos) {
        outSocket.viAPICID.push_back(stoi(sValue));
        return outSocket;
    }
    if (sPropName.find("initial apicid") != string::npos) {
        outSocket.viInitialAPICID.push_back(stoi(sValue));
        return outSocket;
    }
    if (sPropName.find("fpu_exception") != string::npos) {
        if (sValue=="yes") outSocket.vbFPUException.push_back(true);
        else outSocket.vbFPUException.push_back(false);
        return outSocket;
    }
    if (sPropName.find("fpu") != string::npos) {
        if (sValue=="yes") outSocket.vbFPU.push_back(true);
        else outSocket.vbFPU.push_back(false);
        return outSocket;
    }
    if (sPropName.find("cpuid level") != string::npos) {
        outSocket.viCPUIDLevel.push_back(stoi(sValue));
        return outSocket;
    }
    if (sPropName.find("wp") != string::npos) {
        if (sValue=="yes") outSocket.vbWP.push_back(true);
        else outSocket.vbWP.push_back(false);
        return outSocket;
    }
    if (sPropName.find("flags") != string::npos) {
        outSocket.vsFlags.push_back(sValue);
        return outSocket;
    }
    if (sPropName.find("bogomips") != string::npos) {
        outSocket.vdBogoMIPS.push_back(stod(sValue));
        return outSocket;
    }
    if (sPropName.find("clflush size") != string::npos) {
        outSocket.viClFlushSize.push_back(stoi(sValue));
        return outSocket;
    }
    if (sPropName.find("cache_alignment") != string::npos) {
        outSocket.viCacheAlignment.push_back(stoi(sValue));
        return outSocket;
    }
    if (sPropName.find("address sizes") != string::npos) {
        outSocket.vsAddressSizs.push_back(sValue);
        return outSocket;
    }
    if (sPropName.find("power management") != string::npos) {
        outSocket.vsPowerManagement.push_back(sValue);
        return outSocket;
    }

    // if we have come to this line, no keyword was found, return the "old" information:
    return outSocket;
}

int GetSocketID(const char *cFileRead, int iStartLineNumber)
{
    //READING A BLOCK OF cpuinfo ONLY TO FIND SOCKET ID:
    // --> Reading works similar to the main reading function (ReadFile)

    // Declarations
    ifstream fFile(cFileRead); // input file
    string sThisLine;
    string sSocketID;
    int iCountLine=0;

    while (getline(fFile,sThisLine)) // go through each line reading the data
    {
        if (iCountLine>=iStartLineNumber)
        {
            if (sThisLine.find("physical id")!=string::npos)
            {
                // found the line where physical id of the socket is stored:
                if (sThisLine.find(":") != string::npos) sSocketID=sThisLine.substr(sThisLine.find(":")+1);
                sSocketID.erase(0,1); // necessary as 1st character is space

                // Now, the socket ID has been found, we can close this function:
                fFile.close(); // after reaching the last line
                return stoi(sSocketID);
            }
            sThisLine.clear(); // clear string from this line to be able to read next line
        }
        iCountLine++;
    }
    return 0; // just in case
}

bool FileExists(const char *cFile)
{
    // This short function returns true if a file exists or false, respectively.
    ifstream infile(cFile);
    return infile.good();
}
