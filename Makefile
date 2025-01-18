NAME = matt-daemon

BUILD_DIR = .build

BUILD_TYPE ?= debug

SRC_DIR = src
INC_DIR = inc
OBJ_DIR = $(BUILD_DIR)/obj
DEP_DIR = $(BUILD_DIR)/dep

SRC = $(shell find $(SRC_DIR) -type f -name '*.cpp')
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEP = $(OBJ:$(OBJ_DIR)/%.o=$(DEP_DIR)/%.d)

CXX = clang++

CXXFLAGS_REQUIRED = -Wall -Werror -Wextra -pedantic -std=c++23 -stdlib=libc++ -I$(INC_DIR)
CXXFLAGS_DEBUG = $(CXXFLAGS_REQUIRED) -g3 -fsanitize=address -DDEVELOPMENT
CXXFLAGS_PRODUCTION = $(CXXFLAGS_REQUIRED) -O3 -DNDEBUG

ifeq ($(BUILD_TYPE), debug)
	CXXFLAGS = $(CXXFLAGS_DEBUG)
else ifeq ($(BUILD_TYPE), production)
	CXXFLAGS = $(CXXFLAGS_PRODUCTION)
else
	$(error Unknown BUILD_TYPE: $(BUILD_TYPE))
endif

LDFLAGS =

all: $(NAME)

-include $(DEP)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

compile_flags:
	echo $(CXXFLAGS_REQUIRED) | tr ' ' '\n' > compile_flags.txt

.PHONY: all clean fclean compile_flags re
