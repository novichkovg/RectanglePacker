SRCDIR := src
OBJDIR := obj

SRCS := $(shell find $(SRCDIR) -name '*.cpp')
OBJS := $(patsubst %,$(OBJDIR)/%.o,$(basename $(SRCS)))
OBJS := $(subst src,,$(OBJS))

CXX := g++
CXXFLAGS := -std=c++17 -I$(SRCDIR)

$(shell mkdir -p $(dir $(OBJS)) >/dev/null)

rectangle_packer: $(OBJS)
	@$(CXX) $^ -o $@


$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	@$(RM) -rf $(OBJDIR) rectangle_packer
