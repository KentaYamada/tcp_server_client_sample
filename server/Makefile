CXX := clang
CFLAGS := -W -O2
APPNAME := tcp_server_app
SRCS := $(wildcard *.c)
INCLUDES := $(wildcard *.h)
OBJS := $(SRCS:%.c=%.o)

all: clean $(APPNAME)
$(APPNAME): $(OBJS)
	$(CXX) $(CFLAGS) -o $@ $^ -I $(INCLUDES)
%.o: %.c
	$(CXX) -o $@ -c $<
clean:
	rm -f $(OBJS) $(APPNAME)
