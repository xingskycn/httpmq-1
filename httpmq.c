#include "head.h"

//出队列操作
void queue_get(char *qname, struct evbuffer *out) 
{
	char value = tcb_get(qname);
	tcb_out(qname);
	evbuffer_add_printf(out, "HTTPSQS_GET_OK\n");
}

//入队列操作
void queue_post(char *qname, char *data,  struct evbuffer *out)
{
	tcb_put(qname, data);
	evbuffer_add_printf(out, "HTTPSQS_POST_OK\n");
}

void http_request_handler(struct evhttp_request *req, void *arg)
{
	char *line;
	int bsize;
	const char *cmd, *query;
	const char *qname;
	const char *uri = evhttp_request_get_uri(req);
	const struct evhttp_uri* euri;
	struct evbuffer *out = evbuffer_new();
	struct evkeyvalq *headers = evhttp_request_get_input_headers(req);
	struct evkeyvalq params;
	if (!(euri = evhttp_uri_parse(uri))) {
		printf("uri error");
		return;
	}
	if ((query = evhttp_uri_get_query(euri)) == NULL) {
		printf("not query");
		return;
	}
	if (evhttp_parse_query_str(uri, &params) == -1 ) {
		printf("evhttp_parse_query_str error");
		return;
	}
	if ((qname = evhttp_find_header(&params, "name")) == NULL) {
		err_quit("queue name is required\n");
		return;
	}
	printf("out\n");
	evhttp_add_header(headers, "Content-Type", "text/plain");
	evhttp_add_header(headers, "Connection", "keep-alive");
	evhttp_add_header(headers, "Cache-Control", "no-cache");
	switch (evhttp_request_get_command(req)) {
		case EVHTTP_REQ_GET: 
			queue_get(qname, out);
			break;
		case EVHTTP_REQ_POST:
			//queue_post(qname, out);
			break;
		default:
			break;
	}
	evhttp_send_reply(req, HTTP_OK, "OK", out);
	evbuffer_free(out);
}
int main (int argc, char **argv)
{
	tcb_open(); 
	http_init(http_request_handler);
}
