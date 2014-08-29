# Copyright (c) 2014, Recep ASLANTAS <m@recp.me>
#
# Permission to use, copy, modify, and/or distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
# ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
# ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
# OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

UVS_TARGET=tcp-echo-server

CC=g++
UVS_CFLAGS=-std=c++11 -Wall
UVS_INCLUDE_PATH=-I /usr/local/include
UVS_LIB_PATH=-L /usr/local/lib
UVS_LIBS=-luv

UVS_OBJS=\
	tcp-echo-server.o\
	main.o

.PHONY: all
all: ${UVS_TARGET}

$(UVS_TARGET): $(UVS_OBJS)
	$(CC) -o $@ $^ $(UVS_CFLAGS) $(UVS_LIBS) $(UVS_INC_PATH) $(UVS_LIB_PATH)

%.o : %.cc
	$(CC) -c -o $@ $< $(UVS_CFLAGS)

.PHONY: clean
clean:
	-${RM} ${UVS_TARGET} ${UVS_OBJS}