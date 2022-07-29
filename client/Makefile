CXX := clang
CFLAGS := -W -O2
APPNAME := tcp_client_app
SRCS := $(wildcard *.c)
INCLUDES := $(wildcard *.h)
BINS := ../bin
OBJS := $(SRCS:%.c=%.o)

all: clean $(APPNAME)
$(APPNAME): $(OBJS)
	$(CXX) $(CFLAGS) -o $@ $^ -I $(INCLUDES)
%.o: %.c
	$(CXX) -o $@ -c $<
clean:
	$(RM) $(OBJS) $(APPNAME)
