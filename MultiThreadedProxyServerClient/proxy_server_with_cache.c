#include "proxy_parse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/wait.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define MAXCLIENT 100

typedef struct cache_element cache_element;

struct cache_element
{
    char *data;
    int len;
    char *url;
    time_t lru_time_track;
    cache_element *element;
};

cache_element *find(char *url);
int add_element(char *data, int size, int *url);
void remove_cache_element(cache_element *element);

int port_number = 8080;
int proxy_socketId;
pthread_t tid[MAXCLIENT];
sem_t semaphore;
pthread_mutex_t lock;

cache_element *head;
int cache_size;

int main(int argc, char *argv[])
{

    int client_socketId, clinet_len;
    struct sockaddr server_addr, client_addr;

    sem_init(&semaphore,0, MAXCLIENT);
    pthread_mutex_init(&lock, NULL);
    if(argv ==2)
    {
        port_number = atoi(argv[1]);
    }
    else{
        printf("Usage: %s <port_number>\n", argv[0]);
        exit(1);
    }
    printf("Proxy server started at port %d\n", port_number);

    proxy_socketId = socket(AF_INET, SOCK_STREAM, 0);
    if(proxy_socketId < 0)
    {
        perror("Error in creating socket");
        exit(1);
    }
    int reuse =1;
    if(setsockopt(proxy_socketId, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0)
    {
        perror("Error in setting socket options");
        exit(1);
    }
    bzero((char *) &server_addr, sizeof(server_addr));
}