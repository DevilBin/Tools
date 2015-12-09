/*************************************************************************
	> File Name: server.cpp
	> Author: DevilBin 
	> Mail: whu.evil.binary@gmail.com 
	> Created Time: Fri 30 Oct 2015 08:10:13 PM CST
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
#include <sstream>

#define SERVERPORT 8888
#define THREAD_NUM 8
#define LSIZE 1024
#define FILESIZE 1024 * 1024 * 1024

using namespace std;
char file_name[20];
unsigned char *file_buff;
struct thread_args {
    char *filename;
    int seek;
    int size;
    int socket_fd;
};
struct data {
    int index;
    char buff[LSIZE];
};
void* tcp_send_thread(void* arg);

class CMutex{
public:
    CMutex(){ pthread_mutex_init(&m_mutex, NULL); }
    ~CMutex(){ pthread_mutex_destroy(&m_mutex); }
    void Lock() const { pthread_mutex_lock(&m_mutex); }
    void Unlock() const { pthread_mutex_unlock(&m_mutex); }
private:
    mutable pthread_mutex_t m_mutex;
};

class server {
public:
    server() {
        len = sizeof(client_addr);
    }
    int init_server(int port); 
    int wait_file_name(int server_fd);
    void tweak_client(int server_fd, char* file_name);
private:
    unsigned int len;
    int client_fd;
    struct sockaddr_in client_addr;
    struct sockaddr_in server_addr;
};

int server::init_server(int port) {
    int server_fd = socket(PF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(server_fd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr_in)) < 0) {
        perror("Serverfd bind failed!\n");
        exit(1);
    }
    return server_fd;
}

int server::wait_file_name(int server_fd) {
    listen(server_fd, 10);
    client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &len);
    recv(client_fd, file_name, 20, 0); 
    send(client_fd, "1024 * 1024 * 1024", sizeof("1024 * 1024 * 1024"), 0);
    return client_fd;
}

void server::tweak_client(int server_fd, char* file_name) {
    struct sockaddr_in new_client_addr;
    unsigned int len = sizeof(new_client_addr);
    int size = FILESIZE / (LSIZE * THREAD_NUM);
    pthread_t tid[10];
    for(int i = 0; i < THREAD_NUM; ++i) {
        struct thread_args *args;
        args = (struct thread_args *)malloc(sizeof(struct thread_args));
        listen(server_fd, 10);
        int new_client_fd = accept(server_fd, (struct sockaddr*)&new_client_addr, &len);
        args->filename = file_name;
        args->seek = i * size;
        args->size = size;
        args->socket_fd = new_client_fd;
        pthread_create(&(tid[i]), NULL, tcp_send_thread, (void *)args);
    }
    for(int i = 0; i < THREAD_NUM; ++i) {
		pthread_join(tid[i], NULL);
	}
}
void* tcp_send_thread(void* arg) {
    struct thread_args *args = (struct thread_args *)arg;
    struct data sendData;
    int index = 0;
    FILE *file_fd = fopen("hello.txt", "r+");
    fseek(file_fd, (args->seek) * LSIZE, SEEK_SET);
    send(args->socket_fd, (char *)&(args->seek), 4, 0);//index
    while(index < args->size)  {
        if(fgets(sendData.buff, LSIZE + 1, file_fd) > 0) {
            sendData.index = index;
            send(args->socket_fd, (char *)&sendData, sizeof(sendData), 0);
            index++;
        }
        else {
            break;
        }
    }
    sendData.index = -1;
    send(args->socket_fd, (char *)&sendData, sizeof(sendData), 0);
    fclose(file_fd);
    close(args->socket_fd);
}

int main(int argc, char** argv) {
    int port = SERVERPORT;
    if(argc > 1) {
        port = atoi(argv[1]);
    }
    server s;
    int server_fd = s.init_server(port);
    int control_client_fd = s.wait_file_name(server_fd);
    cout << "recv file name " << file_name << '\n';
    s.tweak_client(server_fd, file_name);
    return 0;
}
    
