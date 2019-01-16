CC := gcc
CFLAGS := -Wall -O3
Libs := -lsqlite3 -lpthread
Target := client
Source := $(wildcard src/*.c)
Objs := $(patsubst %.c,%.o,$(Source))
Modules += main reg login my_connect interface_login pthread_read interface_chat list set_disp_mode
AllObjs := $(addsuffix /src/*.o,$(Modules))

