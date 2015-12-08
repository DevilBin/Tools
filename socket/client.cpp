/*************************************************************************
	> File Name: client.cpp
	> Author: DevilBin 
	> Mail: whu.evil.binary@gmail.com 
	> Created Time: Fri 30 Oct 2015 08:09:50 PM CST
 ************************************************************************/

#include <iostream> 
#include <fstream> 
#include <cstdlib> 
#include <string> 
#include <vector> 
#include <deque> 
#include <list> 
#include <map> 
#include <algorithm>
#include <memory.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <ctime>

#define PORT 8888
#define THREAD_NUM 8
#define IP "127.0.0.1"
#define LSIZE 1024
#define FILESIZE 1024 * 1024 * 1024

using namespace std;
unsigned char *file_buff;
struct thread_args {
    int index;
    int seek;
    int size;
    int socket_fd;
};
struct data {
    int index;
    char buff[LSIZE];
};
void* tcp_recv_thread(void* arg);

class CMutex{
public:
    CMutex(){ pthread_mutex_init(&m_mutex, NULL); }
    ~CMutex(){ pthread_mutex_destroy(&m_mutex); }
    void Lock() const { pthread_mutex_lock(&m_mutex); }
    void Unlock() const { pthread_mutex_unlock(&m_mutex); }
private:
    mutable pthread_mutex_t m_mutex;
};

class client {
public:
    int init_client(int port);
    void request_file_name(int client_fd);
    void tcp_file_get(int port);
};

int client::init_client(int port) {
    struct sockaddr_in server_addr;
    int len = sizeof(server_addr);
    int client_fd = socket(PF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(IP);
    server_addr.sin_port = htons(port);
    if(connect(client_fd, (struct sockaddr *)&server_addr, (socklen_t)len) < 0) {
        perror("connect error!\n");
    }
    return client_fd;
}

void client::request_file_name(int client_fd) {
    char file_size[20];
    send(client_fd, "hello.txt", sizeof("hello.txt"), 0);
    recv(client_fd, file_size, 20, 0);
    cout << "file size is " << file_size << '\n';
}

void client::tcp_file_get(int port) {
    FILE *file_fd = fopen("hi.txt", "w+");
    fclose(file_fd);
    pthread_t tid[10];
    for(int i = 0; i < THREAD_NUM; ++i) {
        struct thread_args *args;
        args = (struct thread_args *)malloc(sizeof(struct thread_args));
        int new_client_fd = init_client(port);
        args->socket_fd = new_client_fd;
        pthread_create(&(tid[i]), NULL, tcp_recv_thread, (void *)args);
	}
	for(int i = 0; i < THREAD_NUM; ++i) {
		pthread_join(tid[i], NULL);
	}
}

void* tcp_recv_thread(void* arg) {
    struct thread_args *args = (struct thread_args *)arg;
    struct data recvData;
    int seek; int size = FILESIZE / (LSIZE * THREAD_NUM);
    FILE *file_fd = fopen("hi.txt", "r+");
    recv(args->socket_fd, (char *)&seek, 4, 0);
    fseek(file_fd, seek * LSIZE, SEEK_SET);
    for(;;) {
        recv(args->socket_fd, (char *)&(recvData), sizeof(recvData), 0);
        if(recvData.index < 0) {
            close(args->socket_fd);
            break;
        }
        else {
            fputs(recvData.buff, file_fd);
        }
    }
    //fclose(file_fd);
}

int main(int argc, char **argv) {
    clock_t start, end;
    int port = PORT;
    if(argc > 1) {
        port = atoi(argv[1]);
    }
    client c;
    int client_fd = c.init_client(port);
    start = clock();
    c.request_file_name(client_fd);   
    c.tcp_file_get(port);
    end = clock();
    cout << "The time was: " << ((double)(end - start) / CLOCKS_PER_SEC) << " second.\n";
    return 0;
}
 

