#include <windows.h>

HANDLE hNamedPipe;

const char * pStr = "A";
const char * pPipeName = "\\\\.\\pipe\\test";

void CreateNamedPipeInServer() {
    HANDLE hEvent;
    OVERLAPPED ovlpd;

    hNamedPipe = CreateNamedPipe(pPipeName,
            PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,
            0, 1, 1024, 1024, 0, NULL);

    if(INVALID_HANDLE_VALUE == hNamedPipe) {
        hNamedPipe = NULL;
        printf("[E]: Creat pip failed!\n");
        return;
    }

    hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if(!hEvent) {
        printf("[E]: Creat event failed!\n");
    }

    memset(&ovlpd, 0, sizeof(OVERLAPPED));

    ovlpd.hEvent = hEvent;
    
    if(!ConnectNamedPipe(hNamedPipe, &ovlpd)) {
        if(ERROR_IO_PENDING != GetLastError()) {
            CloseHandle(hNamedPipe);
            CloseHandle(hEvent);
            return;
        }
    }

    if(WAIT_FAILED == WaitForSingleObject(hEvent, INFINITE)) {
        CloseHandle(hNamedPipe);
        CloseHandle(hEvent);
        return;
    }
    CloseHandle(hEvent);
}

void NamedPipeReadInServer() {
    char * pReadBuf;
    DWORD dwRead;

    pReadBuf = (char *)malloc(sizeof(strlen(pStr) + 1));
    memset(pReadBuf, 0, strlen(pStr) + 1);

    if(!ReadFile(hNamedPipe, pReadBuf, strlen(pStr), &dwRead, NULL)) {
        free(pReadBuf);
        return;
    }
    printf("%s\n", pReadBuf);
}

void NamedPipeWriteInServer() {
    DWORD dwWrite;
    if(!WriteFile(hNamedPipe, pStr, strlen(pStr), &dwWrite, NULL)) {
        return;
    }
    printf("%s\n", pStr);
}

int main() {
    CreateNamedPipeInServer();
    NamedPipeWriteInServer();
    NamedPipeReadInServer();
    return 0;
};
