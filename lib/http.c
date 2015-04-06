#include"head.h"
int http_init(void (*handler) (struct evhttp_request *req, void *arg)) 
{
	struct event_base * base = event_base_new(); 
	struct evhttp * http_server = evhttp_new(base);
	if (!http_server) {
		printf("evhttp_new error\n");
		return -1;
	}
    int ret = evhttp_bind_socket(http_server, HTTP_HOST, HTTP_PORT);
    if (ret != 0) {
		printf("bind socket error\n");
	     return -1;
	}
	evhttp_set_gencb(http_server, http_request_handler, NULL);
	printf("http server listen: \n");
	event_base_dispatch(base);
	evhttp_free(http_server);
}

