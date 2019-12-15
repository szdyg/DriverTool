#include "driverconnect.h"
using std::wstring;
using std::string;
using std::vector;

namespace driverconnect
{


BOOL IsServiceExist(IN LPCTSTR lpName)
{
    SC_HANDLE   schService = NULL;
    SC_HANDLE   schManager = NULL;
    BOOL        bRet = FALSE;

    do
    {
        schManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
        if (NULL == schManager)
        {
            break;
        }
        schService = OpenService(schManager, lpName, SERVICE_ALL_ACCESS);
        if (schService != NULL)
        {
            bRet = TRUE;
        }

    } while (FALSE);

    if (schService != NULL)
    {
        CloseServiceHandle(schService);
    }
    if (schManager != NULL)
    {
        CloseServiceHandle(schManager);
    }

    return bRet;

}


BOOL InstallDriver(IN LPCTSTR lpServiceName,
                   IN LPCTSTR lpDisplayName,
                   IN LPCTSTR lpFilePath,
                   IN DWORD dwServiceType,
                   IN DWORD dwStartType,
                   IN LPCTSTR lpNameOfGroup)
{
    BOOL bRet = FALSE;
    SC_HANDLE   schService = NULL;
    SC_HANDLE   schManager = NULL;

    do
    {
        schManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
        if (NULL == schManager)
        {
            break;
        }
        schService = CreateService(schManager,
            lpServiceName,
            lpDisplayName,
            SERVICE_ALL_ACCESS,
            dwServiceType,
            dwStartType,
            SERVICE_ERROR_NORMAL,
            lpFilePath,
            lpNameOfGroup,
            NULL,
            NULL,
            NULL,
            NULL);

        if (schService == NULL)
        {
            DWORD  dwErr = GetLastError();
            if (dwErr == ERROR_SERVICE_EXISTS)

            {
                bRet = TRUE;
            }
        }
        else
        {
            bRet = TRUE;
        }

    } while (FALSE);

    // Close the service object.
    if (schService != NULL)
    {
        CloseServiceHandle(schService);
        schService = NULL;
    }
    if (schManager != NULL)
    {
        CloseServiceHandle(schManager);
        schManager = NULL;
    }

    return bRet;

}




BOOL UnInstallDriver(IN LPCTSTR lpServiceName)
{
    SC_HANDLE   schService = NULL;
    SC_HANDLE   schManager = NULL;
    BOOL        bRet = FALSE;

    do
    {
        schManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
        if (NULL == schManager)
        {
            break;
        }
        schService = OpenService(schManager, lpServiceName, SERVICE_ALL_ACCESS);
        if (schService == NULL)
        {
            break;
        }
        if (!DeleteService(schService))
        {
            break;
        }
        bRet = TRUE;

    } while (FALSE);

    // Close the service object.
    if (schService != NULL)
    {
        CloseServiceHandle(schService);
    }
    if (schManager != NULL)
    {
        CloseServiceHandle(schManager);
    }
    return bRet;
}

BOOL StartDriver(IN LPCTSTR lpServiceName)
{
    SC_HANDLE   schService = NULL;
    SC_HANDLE   schManager = NULL;
    BOOL        bRet = FALSE;

    do
    {
        schManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
        if (NULL == schManager)
        {
            break;
        }
        schService = OpenService(schManager, lpServiceName, SERVICE_ALL_ACCESS);
        if (schService == NULL)
        {
            break;
        }
        if (!StartService(schService, 0, NULL))
        {
            if (GetLastError() != ERROR_SERVICE_ALREADY_RUNNING)
            {
                break;
            }
        }
        bRet = TRUE;
    } while (FALSE);

    // Close the service object.
    if (schService != NULL)
    {
        CloseServiceHandle(schService);
    }
    if (schManager != NULL)
    {
        CloseServiceHandle(schManager);
    }
    return bRet;

}

BOOL StopDriver(IN LPCTSTR lpServiceName)
{
    SC_HANDLE   schService = NULL;
    SC_HANDLE   schManager = NULL;
    BOOL        bRet = FALSE;
    SERVICE_STATUS  serviceStatus;

    do
    {
        schManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
        if (NULL == schManager)
        {
            break;
        }
        schService = OpenService(schManager, lpServiceName, SERVICE_ALL_ACCESS);
        if (schService == NULL)
        {
            break;
        }
        if (!ControlService(schService, SERVICE_CONTROL_STOP, &serviceStatus))
        {
            break;
        }

        //等待停止,最多20次
        ULONG utime = 20;
        DWORD dwret = 0;
        while (utime > 0)
        {
            Sleep(500);
            SERVICE_STATUS_PROCESS ServicesStatusProcess = { 0 };
            QueryServiceStatusEx(schService, SC_STATUS_PROCESS_INFO, (LPBYTE)&ServicesStatusProcess, sizeof(ServicesStatusProcess), &dwret);
            if (ServicesStatusProcess.dwCurrentState == SERVICE_STOPPED)
            {
                break;
            }
            utime--;
        }

        if (utime > 0)
        {
            bRet = TRUE;
        }

    } while (FALSE);

    // Close the service object.
    if (schService != NULL)
    {
        CloseServiceHandle(schService);
    }
    if (schManager != NULL)
    {
        CloseServiceHandle(schManager);
    }
    return bRet;

}

}