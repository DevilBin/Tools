#include <windows.h>

HANDLE hNamedPipe;

const char * pStr = "B";
const char * pPipeName = "\\\\.\\pipe\\test";

void OpenNamedPipeInClient() {
    if(!WaitNamedPipe(pPipeName, NMPWAIT_WAIT_FOREVER)) {
        printf("[E]: Pipe name not found!\n");
        return;
    }

    hNamedPipe = CreateFile(pPipeName, GENERIC_READ | GENERIC_WRITE,
            0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if(INVALID_HANDLE_VALUE == hNamedPipe) {
        printf("[E]: Open pipe failed!\n");
        return;
    }
}

void NamedPipeReadInClient() {
    char * pReadBuf;
    DWORD dwRead;

    pReadBuf = (char *)malloc(sizeof(strlen(pStr) + 1));
    memset(pReadBuf, 0, strlen(pStr) + 1);

    if(!ReadFile(hNamedPipe, pReadBuf, strlen(pStr), &dwRead, NULL)) {
        free(pReadBuf);
        printf("[E]: Read pipe failed!\n");
        return;
    }
    printf("%s\n", pReadBuf);
}

void NamedPipeWriteInClient() {
    DWORD dwWrite;
    if(!WriteFile(hNamedPipe, pStr, strlen(pStr), &dwWrite, NULL)) {
        printf("[E]: Write byte failed!\n");
        return;
    }
    printf("%s", pStr);
}

int main() {
    OpenNamedPipeInClient();
    NamedPipeReadInClient();
    NamedPipeWriteInClient();
    return 0;
}
