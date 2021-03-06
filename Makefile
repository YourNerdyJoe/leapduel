
SOURCES := client common client/lib
BUILD := client/build
CPP_FILES := $(foreach dir, $(SOURCES), $(notdir $(wildcard $(dir)/*.cpp)))
O_FILES := $(addprefix $(BUILD)/, $(CPP_FILES:.cpp=.o))
DEPENDS := $(O_FILES:.o=.d)

CC := g++
CC_FLAGS := -g -Wall -O2 -std=c++11 -I /usr/include/SDL2/ -I /opt/LeapSDK/include/
LD_FLAGS := -lSDL2 -lSDL2_image -lSDL2_net -lLeap

TARGET := leapduel

all: $(TARGET) $(BUILD)

$(TARGET) : $(O_FILES)
	$(CC) $(LD_FLAGS) -o $@ $^

$(BUILD)/%.o : client/%.cpp $(BUILD)
	$(CC) $(CC_FLAGS) -c -o $@ $<

$(BUILD)/%.o : common/%.cpp $(BUILD)
	$(CC) $(CC_FLAGS) -c -o $@ $<

$(BUILD):
	mkdir -p $(BUILD)

clean: 
	rm $(BUILD)/*.o $(BUILD)/*.d $(TARGET)

CC_FLAGS += -MMD
-include $(DEPENDS)

