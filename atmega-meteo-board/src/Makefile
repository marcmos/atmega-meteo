MAIN = atmega-meteo

SRCS = $(wildcard *.cpp) $(wildcard */*.cpp) $(wildcard */*/*.cpp)
OBJS = $(SRCS:.cpp=.o)

all: $(MAIN)

$(MAIN): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) $(LIBS) -o $(MAIN)
	$(OBJCOPY) -O ihex $(MAIN) $(MAIN).hex

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean
clean:
	rm -f *.o */*.o */*/*.o $(MAIN) $(MAIN).hex
