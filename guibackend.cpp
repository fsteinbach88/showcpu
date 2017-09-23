#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <math.h>
#include <vector>

#include "guibackend_header.h"

using namespace std;

// constructor
GUIBackEnd::GUIBackEnd(QObject *parent) : QObject(parent) {}

void GUIBackEnd::readCPUInformation(QString filename)
{
    QByteArray tmpByteArr = filename.toLatin1();
    const char *cFileName = tmpByteArr.data();
    m_ALLCPUINFO = ReadFile(cFileName);

    if (m_ALLCPUINFO.size()>0) m_bDataLoaded=true;
    else m_bDataLoaded=false;
}

bool GUIBackEnd::dataLoaded() {return m_bDataLoaded;}

QString GUIBackEnd::getNSockets()
{
    return QString::number(m_ALLCPUINFO.size());
}

QString GUIBackEnd::getVendorID(int iSocket)
{
    string sVendor= m_ALLCPUINFO[iSocket].getVendorID();
    QString newStr=QString::fromStdString(sVendor);
    return newStr;
}
QString GUIBackEnd::getModelName(int iSocket)
{
    string sModelName= m_ALLCPUINFO[iSocket].getModelName();
    QString newStr=QString::fromStdString(sModelName);
    return newStr;
}
QString GUIBackEnd::getMaxFreqMHz(int iSocket)
{
    double dFreq= m_ALLCPUINFO[iSocket].getCPUMaxFrequMhz();
    dFreq = round(dFreq);
    QString newStr=QString::number(dFreq);
    return newStr;
}
QString GUIBackEnd::getMaxCacheKB(int iSocket)
{
    double dCache= m_ALLCPUINFO[iSocket].getCPUMaxCacheKB();
    dCache = round(dCache);
    QString newStr=QString::number(dCache);
    return newStr;
}
QString GUIBackEnd::getNPhysCores(int iSocket)
{
    int iNPCores= m_ALLCPUINFO[iSocket].getNumbPhyCores();
    QString newStr=QString::number(iNPCores);
    return newStr;
}
QString GUIBackEnd::getNLogCores(int iSocket)
{
    int iLPCores= m_ALLCPUINFO[iSocket].getNumbLogCores();
    QString newStr=QString::number(iLPCores);
    return newStr;
}
QString GUIBackEnd::getCPUFam(int iSocket)
{
    int iCPUFam= m_ALLCPUINFO[iSocket].getCPUFamily();
    QString newStr=QString::number(iCPUFam);
    return newStr;
}
QString GUIBackEnd::getCPUModel(int iSocket)
{
    int iCPUMod= m_ALLCPUINFO[iSocket].getCPUModel();
    QString newStr=QString::number(iCPUMod);
    return newStr;
}
QString GUIBackEnd::getStepping(int iSocket,int iLogCore)
{
    vector<int> vTmp = m_ALLCPUINFO[iSocket].viStepping;
    QString newStr=QString::number(vTmp[iLogCore]);
    return newStr;
}
QString GUIBackEnd::getFPU(int iSocket,int iLogCore)
{
    vector<bool> vTmp = m_ALLCPUINFO[iSocket].vbFPU;
    bool bThisFPU = vTmp[iLogCore];
    QString newStr;
    if (bThisFPU) newStr="yes, capable of floating-point number operations";
    else newStr="no, incapable of floating-point number operations";
    return newStr;
}
QString GUIBackEnd::getFPUExc(int iSocket,int iLogCore)
{
    vector<bool> vTmp = m_ALLCPUINFO[iSocket].vbFPUException;
    bool bThisFPUe = vTmp[iLogCore];
    QString newStr;
    if (bThisFPUe) newStr="yes, exceptions possible";
    else newStr="no, exceptions not possible";
    return newStr;
}
QString GUIBackEnd::getWP(int iSocket,int iLogCore)
{
    vector<bool> vTmp = m_ALLCPUINFO[iSocket].vbWP;
    bool bWP = vTmp[iLogCore];
    QString newStr;
    if (bWP) newStr="yes, enforcing read-only pages for the kernel";
    else newStr="no, not enforcing read-only pages for the kernel";
    return newStr;
}
QString GUIBackEnd::getCPUIDLev(int iSocket,int iLogCore)
{
    vector<int> vTmp = m_ALLCPUINFO[iSocket].viCPUIDLevel;
    QString newStr=QString::number(vTmp[iLogCore]);
    return newStr;
}
QString GUIBackEnd::getBogoMIPS(int iSocket,int iLogCore)
{
    vector<double> vTmp = m_ALLCPUINFO[iSocket].vdBogoMIPS;
    QString newStr=QString::number(vTmp[iLogCore]);
    return newStr;
}
QString GUIBackEnd::getCLFlush(int iSocket,int iLogCore)
{
    vector<int> vTmp = m_ALLCPUINFO[iSocket].viClFlushSize;
    QString newStr=QString::number(vTmp[iLogCore]);
    return newStr;
}
QString GUIBackEnd::getCacheAlg(int iSocket,int iLogCore)
{
    vector<int> vTmp = m_ALLCPUINFO[iSocket].viCacheAlignment;
    QString newStr=QString::number(vTmp[iLogCore]);
    return newStr;
}
QString GUIBackEnd::getAdrSz(int iSocket,int iLogCore)
{
    vector<string> vTmp = m_ALLCPUINFO[iSocket].vsAddressSizs;
    QString newStr=QString::fromStdString(vTmp[iLogCore]);
    return newStr;
}

// Flags is not used at the moment: We need to enlarge the window or textbox to show them
/*
QString GUIBackEnd::getFlags(int iSocket,int iLogCore)
{
    vector<string> vTmp=m_ALLCPUINFO[iSocket].vsFlags;
    string sFlag= vTmp[iLogCore];
    QString newStr=QString::fromStdString(sFlag);
    return newStr;
}*/

