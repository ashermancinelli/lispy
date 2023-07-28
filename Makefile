OBJS := \
	opc.o \
	dbg.o \
	vm.o

STACK_MAX ?= 1024
HEAP_MAX ?= 1024
CXXFLAGS += \
						-DSTACK_MAX=$(STACK_MAX) \
						-DHEAP_MAX=$(HEAP_MAX) \
						-std=c++20 -g

lc: $(OBJS) lc.o
	$(CXX) $(CXXFLAGS) $(OBJS) lc.o -o lc

bcc: $(OBJS) bcc.o
	$(CXX) $(CXXFLAGS) $(OBJS) bcc.o -o bcc

all: bcc lc

clean:
	@rm *.o bcc lc
