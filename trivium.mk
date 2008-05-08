# Makefile for Trivium
ALGO_NAME := TRIVIUM

# comment out the following line for removement of Trivium from the build process
STREAM_CIPHERS += $(ALGO_NAME)

$(ALGO_NAME)_OBJ      := trivium.o
$(ALGO_NAME)_TEST_BIN := main-trivium-test.o debug.o uart.o serial-tools.o \
                         nessie_stream_test.o nessie_common.o trivium.o cli.o \
			 performance_test.o
$(ALGO_NAME)_NESSIE_TEST      := "nessie"
$(ALGO_NAME)_PEROFRMANCE_TEST := "performance"
