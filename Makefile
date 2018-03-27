TARGET=EDCB-SendSuspend
SRCS=EDCB_SendSuspend.cpp EDCBCtrlCmd/SendCtrlCmd.cpp EDCBCtrlCmd/CtrlCmdUtil.cpp EDCBCtrlCmd/CtrlCmdUtil2.cpp EDCBCtrlCmd/StringUtil.cpp EDCBCtrlCmd/Util.cpp
CXX = g++
CXXFLAGS += -Wall -std=c++0x -O3
BUILD_DIR = obj

.SUFFIXES: .o .cpp

.PHONY: all
all: depend $(TARGET)

$(TARGET): $(addprefix $(BUILD_DIR)/,$(SRCS:%.cpp=%.o))
	$(CXX) -o $(TARGET) $^

$(BUILD_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	$(RM) $(TARGET) depend.inc
	$(RM) -r $(BUILD_DIR)

.PHONY: depend
depend: $(SRCS)
	$(RM) depend.inc
	for i in $^; do\
		$(CXX) $(CXXFLAGS) -MM -MP -MT $(BUILD_DIR)/$${i%.cpp}.o $$i >> depend.inc;\
	done

-include depend.inc
