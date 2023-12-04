##### flag setting ######
debug = 1
##########################

CC = g++
CFLAGS = -O2
TARGET = main.out
OBJS = main.o wordgame.o

ifeq ($(debug), 1)
	CFLAGS += -g
endif

# curl 관련 옵션 및 라이브러리 추가
CFLAGS += $(shell curl-config --cflags)
LIBS += $(shell curl-config --libs)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f *.o main.out

