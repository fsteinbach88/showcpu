#ifndef CPUINFOCLASS_H
#define CPUINFOCLASS_H
#include <vector>
#include <string>
/*
 * A class called "CPUInfo" stores the information from the cpuinfo file.
 * A system may have more than one socket (CPU) and each socket may have more than one physical core.
 * The file "cpuinfo" contains specific information for each physical and logical core of each socket, which we will keep here.
 * The properties are stored as vector<type>. The number of elements in each vector corresponds to the number of logical cores ("processors" in cpuinfo).
 *
 * Some general properties typically hold for the whole socket (vendor ID, etc), these can be returned as a single string or number.
 * Note that it only makes sense to load these general properties until every logical core's properties have been read.
 *
 * For now all variables are declared as "public", this may change during further development.
 *
 * A new object of the class needs to be created for a new socket. To summarise all sockets, another vector (vector<CPUInfo>) can be used.
 *
 * To improve this program in the future and e.g. compare different systems, one could add a system ID to the variables.
 */
class CPUInfo
{
public:
    // Constructor, destructor declaration:
    CPUInfo();
    ~CPUInfo();
    // Declaration of functions returning properties for the whole socket (obviously, those are the properties that interest most users):
    std::string getVendorID();
    int getCPUFamily();
    int getCPUModel();
    std::string getModelName();
    double getCPUMaxFrequMhz();
    double getCPUMaxCacheKB();
    bool getHyperThrPossible(); // true: yes, it is possible
    int getNumbLogCores();
    int getNumbPhyCores();


    // Declaration of vectors:
    std::vector<int>            viLogCoreID; // this is "processor" in cpuinfo
    std::vector<std::string>    vsVendorID;
    std::vector<int>            viCPUFamily;
    std::vector<int>            viModel;
    std::vector<std::string>    vsModelName;
    std::vector<int>            viStepping;
    std::vector<std::string>    vsMicrocode;
    std::vector<double>         vdCPUMHz;
    std::vector<double>         vdCacheSize;
    std::vector<bool>           vbHyperthreadYesNo; // if in cpuinfo cpu cores<siblings, this is true
    std::vector<int>            viNumbLogCores; // siblings in cpunifo
    std::vector<int>            viCoreID;
    std::vector<int>            viNumbPhysCores; // cpu cores in cpuinfo
    std::vector<int>            viAPICID;
    std::vector<int>            viInitialAPICID;
    std::vector<bool>           vbFPU;
    std::vector<bool>           vbFPUException;
    std::vector<int>            viCPUIDLevel;
    std::vector<bool>           vbWP;
    std::vector<std::string>    vsFlags; // not further sorted here, a potential future improvement is to read flags to get more information
    std::vector<double>         vdBogoMIPS;
    std::vector<int>            viClFlushSize;
    std::vector<int>            viCacheAlignment;
    std::vector<std::string>    vsAddressSizs; //
    std::vector<std::string>    vsPowerManagement; // keep as string, further evualuation is part of future developments
};

#endif // CPUINFOCLASS_H
