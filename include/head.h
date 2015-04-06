#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<pwd.h>
#include<errno.h>
#include<fcntl.h>
#include<stdint.h>
#include<stdbool.h>
#include<netinet/in.h>
#include<poll.h>
#include<pthread.h>
#include<signal.h>
#include<syslog.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<sys/ipc.h>
#include<sys/socket.h>
#include<sys/msg.h>
#include<sys/un.h>
#include<event.h>
#include<event2/event.h>
#include<event2/http.h>

#define MAXLINE 1000
#define TCBDBPATH "/root/project/data/queue.tcb"
#define HTTP_HOST "0.0.0.0"
#define HTTP_PORT 1219

/* 错误处理函数 */
void err_quit(char *fmt, ...);

/*tcb数据库处理 */
void tcb_open(void);
void tcb_close(void);
char *tcb_get(const char *key);
void tcb_err(void);

/* http服务器管理 */
int http_init(void (*)(struct evhttp_request*, void *)) ;
void http_request_handler(struct evhttp_request *req, void *arg);
