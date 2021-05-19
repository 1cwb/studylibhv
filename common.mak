CUR_PATH := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

export GLOBAL_TOP_PATH := $(CUR_PATH)
export GLOBAL_INC :=-I ./

# 指定编译器
export GLOBAL_CXX := g++
export GLOBAL_CC := g++
# CFLAG包括头文件目录
export GLOBAL_CFLAGS := -g -Wall -fno-elide-constructors -std=c++11

# 静态链接库
export GLOBAL_LDFLAGS :=
export GLOBAL_LDLIBS := -l pthread -latomic

export GLOBAL_OUTPUT_OBJS_PATH := $(GLOBAL_TOP_PATH)objs
export GLOBAL_OUTPOT_OBJS_FILE :=

export GLOBAL_OBJS :=
export GLOBAL_SRC_FILE :=

# 目标
export TARGET :=

export FIRST_MAKE := $(abspath $(firstword $(MAKEFILE_LIST)))

#定义创建目录的功能块（由于类似与函数，一般叫做函数）
define CRT_DIR
	if [ ! -d $(1) ];\
	 	then\
    	mkdir -p $(1);\
	fi	
endef

define RM_DIR
	if [ -d $(1) ];\
		then\
		rm -rf $(1);\
	fi
endef