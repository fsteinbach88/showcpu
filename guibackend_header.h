#ifndef GUIBACKEND_HEADER_H
#define GUIBACKEND_HEADER_H

#include <QObject>
#include <QString>

#include "cpuinfoclass_header.h"
#include "main_header.h"

/* This class and its application was created with the help of
 * the Qt Documentation:
 * doc.qt.io/qt-5/qtqml-cppintegration-topic.html
 */

class GUIBackEnd : public QObject
{
    Q_OBJECT
public:
    explicit GUIBackEnd(QObject *parent = nullptr);

signals:

public slots:
    void readCPUInformation(QString filename);
    bool dataLoaded(); // tells if data was loaded successfully (bool will be true)

    QString getNSockets(); // return the number of CPU sockets
    QString getVendorID(int iSocket);
    QString getModelName(int iSocket);
    QString getMaxFreqMHz(int iSocket);
    QString getMaxCacheKB(int iSocket);
    QString getNPhysCores(int iSocket);
    QString getNLogCores(int iSocket);
    QString getCPUFam(int iSocket);
    QString getCPUModel(int iSocket);
    QString getStepping(int iSocket,int iLogCore);
    QString getFPU(int iSocket,int iLogCore);
    QString getFPUExc(int iSocket,int iLogCore);
    QString getWP(int iSocket,int iLogCore);
    QString getCPUIDLev(int iSocket,int iLogCore);
    QString getBogoMIPS(int iSocket,int iLogCore);
    QString getCLFlush(int iSocket,int iLogCore);
    QString getCacheAlg(int iSocket,int iLogCore);
    QString getAdrSz(int iSocket,int iLogCore);
//    QString getFlags(int iSocket,int iLogCore); // not used at the moment

private:
    bool m_bDataLoaded=false;
    std::vector<CPUInfo> m_ALLCPUINFO;
};

#endif // GUIBACKEND_HEADER_H
