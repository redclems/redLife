CXX = g++
CXXFLAGS = -Wall -Wextra -Iinclude -std=c++14

SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin

SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJ = $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
DEP = $(OBJ:.o=.d)
BIN = $(BINDIR)/app

.PHONY: all clean

all: $(BIN)

$(BIN): $(OBJ)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

-include $(DEP)

clean:
	rm -rf $(OBJDIR) $(BINDIR)
clear:
	clear
