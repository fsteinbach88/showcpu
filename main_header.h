#ifndef MAIN_HEADER_H
#define MAIN_HEADER_H

std::vector<CPUInfo> ReadFile(const char *cFileRead);
CPUInfo AssignProp(std::string sPropName, std::string sValue,CPUInfo inSocket);
int GetSocketID(const char *cFileRead, int iStartLineNumber);
bool FileExists(const char *cFile);

#endif // MAIN_HEADER_H
