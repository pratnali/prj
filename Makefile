LLVM_CONFIG?=llvm-config
ifndef VERBOSE
	QUITE:=@
endif

#CXX=/Users/pratnali/Work/LLVM/build/Release+Profile+Asserts/bin/clang
SRC_DIR?=$(PWD)
LDFLAGS+=$(shell $(LLVM_CONFIG) --system-libs --ldflags) -v
COMMON_FLAGS=-Wall -Wextra -std=c++11
CXXFLAGS += $(COMMON_FLAGS) $(shell $(LLVM_CONFIG) --cxxflags)
CPPFLAGS += $(shell $(LLVM_CONFIG) --cppflags) -I $(SRC_DIR) -I /Users/pratnali/Work/LLVM/llvm/include -I$(LLVM_HOME)/include -D__STDC_CONSTANT_MACROS -D__STDC_LIMIT_MACROS
LLVM_CONFIG=llvm-config

HELLO = helloworld 
HELLO_OBJECTS = hello.o 
default: $(HELLO) 

%.o:	$(SRC_DIR)/%.cpp 	
	@echo Compiling $*.cpp 
	$(QUIET) $(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $< 
	
$(HELLO) : $(HELLO_OBJECTS) 
	@echo Linking $@ 
	$(QUIET) $(CXX) -o $@ $(CXXFLAGS) $(LDFLAGS) $^ `$(LLVM_CONFIG) --libs bitreader core support `

clean::
	$(QUITE) rm -f $(HELLO) $(HELLO_OBJECTS) 
