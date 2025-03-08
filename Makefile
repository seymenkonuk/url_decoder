# GEREKLİ DEĞİŞKENLER
# C Compiler
CC = gcc
CC_FLAGS = -Wall -Werror -Wextra 
# AR
AR = ar
AR_FLAGS = rcs
# Dizinler
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
# Çıktı
NAME = url_decoder
TARGET = $(BIN_DIR)/lib$(NAME).a
# Dosyalar
SRCS = $(wildcard $(SRC_DIR)/*.c)		 					# src dizinindeki tüm c dosyaları
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))	# obj dizinindeki oluşması gereken tüm o dosyaları

# LIB OLUŞTURMA
# All
all: $(TARGET)
# Lib Dosyasının Üretilmesi
$(TARGET): $(OBJS)
	@$(AR) $(AR_FLAGS) $(TARGET) $^
# Obje Dosyalarının Üretilmesi
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
# Obje ve Bin Dosyalarını Sil
clean:
	@rm -f $(OBJ_DIR)/* $(BIN_DIR)/*
# Tekrar Derle
re: clean all
# Debug build
debug: CFLAGS += -g
debug: clean all
# Release build
release: CFLAGS += -O3
release: clean all

# TEST
# Gerekli Parametreler
URL1 = "https://localhost/search?q=\%24test+test\%2Fpath\%2Fvalue&category=\%2Ffiles\%2Fdocs"
URL2 = "https://localhost/dashboard?section=%64%61%74%61&action=%70%72%6F%63%65%73%73"
# Build
test-build: $(TARGET)
	@$(CC) test/test.c -L$(BIN_DIR) -l$(NAME) -o ./$(BIN_DIR)/test.exe
# Run
test-run:
	@echo -------------------------------------------------------------------------------------------
	@echo Calistirilan Komut: ./$(BIN_DIR)/test.exe
	@echo -------------------------------------------------------------------------------------------
	@./$(BIN_DIR)/test.exe
	@echo -------------------------------------------------------------------------------------------
	@echo Calistirilan Komut: ./$(BIN_DIR)/test.exe '${URL1}'
	@echo -------------------------------------------------------------------------------------------
	@./$(BIN_DIR)/test.exe '${URL1}'
	@echo -------------------------------------------------------------------------------------------
	@echo Calistirilan Komut: ./$(BIN_DIR)/test.exe '${URL2}'
	@echo -------------------------------------------------------------------------------------------
	@./$(BIN_DIR)/test.exe '${URL2}'
	@echo -------------------------------------------------------------------------------------------
# Build & Run
test: test-build test-run
# Re Test
re-test: re test

# DOCKER
# Build
docker-build:
	@docker build -t $(NAME) .
# Run
docker-run:
	@docker run --rm --name $(NAME) $(NAME)
# Clean
docker-clean:
	@docker rmi $(NAME)
# Build & Run
docker: docker-build docker-run

# PHONY
.PHONY: all clean re debug release
.PHONY: test-build test-run test re-test 
.PHONY: docker-build docker-run docker-clean docker
