CC := gcc
CFLAGS := -Wall -O3
Libs := -lsqlite3 -lpthread
Target := server
Source := $(wildcard src/*.c)
Objs := $(patsubst %.c,%.o,$(Source))
Modules += main reg login init my_accept pthread_read online list chat stoall offline changepwd changename insertmsg viewmsg insertmsgall insertoffmsg viewoffmsg out ban rmban
AllObjs := $(addsuffix /src/*.o,$(Modules))

