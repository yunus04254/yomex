CXX = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS =

INCLUDE_DIR = include
SRC_DIR = src

OBJS = $(SRC_DIR)/Order.o $(SRC_DIR)/OrderBook.o $(SRC_DIR)/main.o
TARGET = yomex

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(TARGET) $(OBJS)

$(SRC_DIR)/Order.o: $(INCLUDE_DIR)/Order.h $(SRC_DIR)/Order.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -o $@ -c $(SRC_DIR)/Order.cpp

$(SRC_DIR)/OrderBook.o: $(INCLUDE_DIR)/Order.h $(INCLUDE_DIR)/OrderBook.h $(SRC_DIR)/OrderBook.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -o $@ -c $(SRC_DIR)/OrderBook.cpp

$(SRC_DIR)/main.o: $(INCLUDE_DIR)/Order.h $(INCLUDE_DIR)/OrderBook.h $(SRC_DIR)/main.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -o $@ -c $(SRC_DIR)/main.cpp

clean:
	rm -f $(OBJS) $(TARGET)
