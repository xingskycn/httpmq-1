VPATH = src:include:lib
CPPFLAGS = -I include


httpmq :httpmq.o  error.o tcb.o http.o
	gcc -o httpmq httpmq.o error.o tcb.o http.o  -ltokyocabinet -levent
httpmq.o : httpmq.c head.h
tcb.o : tcb.c head.h
error.o : error.c head.h
http.o : http.c head.h

#防止存在clean文件而不执行命令
.PHONY : clean
clean:
	rm *.o


