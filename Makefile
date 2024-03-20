EXECUTABLE = build/tests
INCLUDES = Stack.h
CXX = g++
OBJDIR = build
BRED    = \033[1;31m
BGREEN  = \033[1;32m
BYELLOW = \033[1;33m
GREEN   = \033[1;35m
BCYAN   = \033[1;36m
RESET   = \033[0m

$(OBJDIR)/%: %.cpp
	@printf "$(BYELLOW)Building object file $(BCYAN)$@$(RESET)\n"
	@mkdir -p build
	$(CXX) -c $< $(CXXFLAGS) -o $@.o
	@printf "$(BYELLOW)Linking executable $(BCYAN)$@$(RESET)\n"
	$(CXX) $(LDFLAGS) $@.o -o $@

default: $(EXECUTABLE)

$(OBJDIR)/%.o: %.cpp $(INCLUDES) Makefile
	@printf "$(BYELLOW)Building object file $(BCYAN)$@$(RESET)\n"
	@mkdir -p build
	$(CXX) -c $< $(CXXFLAGS) -o $@

run: $(EXECUTABLE)
	./$(EXECUTABLE)