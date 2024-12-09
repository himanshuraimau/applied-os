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
