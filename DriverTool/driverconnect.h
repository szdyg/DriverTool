#pragma once
#include "Windows.h"
#include <vector>
#include <string>
namespace driverconnect
{
    BOOL IsServiceExist(IN LPCTSTR lpName);

    BOOL InstallDriver(IN LPCTSTR lpServiceName,
        IN LPCTSTR lpDisplayName,
        IN LPCTSTR lpFilePath,
        IN DWORD dwServiceType,
        IN DWORD dwStartType,
        IN LPCTSTR lpNameOfGroup);

    BOOL StartDriver(IN LPCTSTR lpServiceName);


    BOOL StopDriver(IN LPCTSTR lpServiceName);

    BOOL UnInstallDriver(IN LPCTSTR lpServiceName);
}
