#include"head.h"
#include <tcutil.h>
#include <tcbdb.h>
TCBDB *db = NULL;
BDBCUR *cur;

void tcb_open(void) {
	if (db == NULL) {
		db = tcbdbnew();
		if (!tcbdbopen(db, TCBDBPATH, BDBOWRITER | BDBOCREAT)) {	
			tcb_err();
		}
	}
	atexit(tcb_close);
}

/* 向数据库插入数据 */
bool tcb_put(const char *key,const char *value)
{
	if (!tcbdbput2(db, key, value)) {
		tcb_err();
	}
	return true;
}
/* 获取对应键值 */
char *tcb_get(const char *key)
{
	static char *value;
	value = tcbdbget2(db, key);
	printf("v:%s\n", value);
	if (!value)
		tcb_err();
	return value;
}
/* 删除对应健纪录 */
bool tcb_out(const char *key)
{
	if (!tcbdbout2(db, key)) {
		tcb_err();
	}
	return true;
}

void tcb_close(void)
{
	int ecode;
	printf("tcb close\n");
	tcbdbsync(db);
	if(!tcbdbclose(db)){
	    ecode = tcbdbecode(db);
	    fprintf(stderr, "close error: %s\n", tcbdberrmsg(ecode));
	}
	tcbdbdel(db);
}

void tcb_err(void)
{
	 int ecode;
     ecode = tcbdbecode(db);	
	 fprintf(stderr, "open error:%s\n", tcbdberrmsg(ecode));
	 exit(-1);
}

