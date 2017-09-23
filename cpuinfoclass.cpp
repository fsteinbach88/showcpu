#include "cpuinfoclass_header.h"

using namespace std;

// Constructor and destructor definitions appear a bit useless here, but:
// maybe they will be useful at a later stage of development
CPUInfo::CPUInfo(){}
CPUInfo::~CPUInfo(){}


// Define the "get" functions to read general data for one socket:
string CPUInfo::getVendorID()
{
    if (vsVendorID.size()>0)
    {
        return vsVendorID[0]; // assuming the same for all cores in one socket
    }
    return ""; // if not, return something to avoid crashing
}

int CPUInfo::getCPUFamily()
{
    if (viCPUFamily.size()>0)
    {
        return viCPUFamily[0]; // assuming the same for all cores in one socket
    }
    return 0; // if not, return something to avoid crashing
}

int CPUInfo::getCPUModel()
{
    if (viModel.size()>0)
    {
        return viModel[0]; // assuming the same for all cores in one socket
    }
    return 0; // if not, return something to avoid crashing
}

string CPUInfo::getModelName()
{
    if (vsModelName.size()>0)
    {
        return vsModelName[0]; // assuming the same for all cores in one socket
    }
    return ""; // if not, return something to avoid crashing
}

double CPUInfo::getCPUMaxFrequMhz()
{
    // Find max. frequency
    double dMaxF=0.0;

    for (int i=0;i<(int)vdCPUMHz.size();i++)
    {
        if (vdCPUMHz[i]>dMaxF)
        {
            dMaxF=vdCPUMHz[i];
        }
    }

    return dMaxF;
}

double CPUInfo::getCPUMaxCacheKB()
{
    // Find max. cache size
    double dMaxC=0.0;

    for (int i=0;i<(int)vdCacheSize.size();i++)
    {
        if (vdCacheSize[i]>dMaxC)
        {
            dMaxC=vdCacheSize[i];
        }
    }

    return dMaxC;
}

bool CPUInfo::getHyperThrPossible()
{
    if (vbHyperthreadYesNo.size()>0)
    {
        return vbHyperthreadYesNo[0]; // assuming the same for all cores in one socket
    }
    return true; // if not, return something to avoid crashing
}

int CPUInfo::getNumbLogCores()
{
    if (viNumbLogCores.size()>0)
    {
        return viNumbLogCores[0]; // assuming the same for all cores in one socket
    }
    return 0; // if not, return something to avoid crashing
}

int CPUInfo::getNumbPhyCores()
{
    if (viNumbPhysCores.size()>0)
    {
        return viNumbPhysCores[0]; // assuming the same for all cores in one socket
    }
    return 0; // if not, return something to avoid crashing
}
