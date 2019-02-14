GXX = g++ -std=c++11
APPDIR = $(PWD)
APPINCH = $(shell find $(APPDIR) -name "*.hpp")
SRC = $(shell find $(APPDIR) -name "*.cpp")

SUB_DIR = $(shell ls -F $(APPDIR) | grep /)
INCLUDE += $(foreach tmp, $(SUB_DIR), -I./$(tmp))
APP = $(patsubst %.cpp, %.o, $(SRC))

LDFLAGS = -laio -lleveldb -lrados -lrbd -ldl -lboost_system-mt -lfuse

main : $(APP)
	$(GXX) -g -D_FILE_OFFSET_BITS=64 -o main $(INCLUDE) $(APP) $(LDFLAGS)

$(APP):%.o:%.cpp
	$(GXX) -g -D_FILE_OFFSET_BITS=64 -c $(INCLUDE) $(LD_DIR) $(LDFLAGS) $< -o $@ 

clean:
	rm -f $(APP)
	rm -f main
