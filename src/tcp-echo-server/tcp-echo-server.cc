/* Copyright (c) 2014, Recep ASLANTAS <m@recp.me>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "tcp-echo-server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std::placeholders;

EchoServer::EchoServer(int port, const char* ip)
                              : m_loop(uv_default_loop()), m_server({0}), m_bind_addr({0}) {
  uv_tcp_init(m_loop, &m_server);
  uv_ip4_addr(ip, port, &m_bind_addr);
  uv_tcp_bind(&m_server, (struct sockaddr *)&m_bind_addr, 0);
}

EchoServer::~EchoServer()  {
  this->disconnect();
}

uv_loop_t * EchoServer::loop() {
  return m_loop;
}

void EchoServer::on_alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
  *buf = uv_buf_init((char*) malloc(suggested_size), (int)suggested_size);
}

void EchoServer::on_write(uv_write_t *req, int status) {
  if (status == -1) {
    // Write error
  }
  char *base = (char*) req->data;
  free(base);
  free(req);
}

void EchoServer::on_read(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf) {
  if (nread == -1) {
    uv_close((uv_handle_t*) client, NULL);
    return;
  }

  uv_write_t *req = (uv_write_t *) malloc(sizeof(uv_write_t));
  req->data = (void*) buf->base;
  uv_write(req, client, buf, 1, std::bind(&EchoServer::on_write, this, _1, _2));
}

void EchoServer::on_new_connection(uv_stream_t *server, int status) {
  if (status == -1) {
    return;
  }
  
  uv_tcp_t *client = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
  uv_tcp_init(m_loop, client);
  if (uv_accept(server, (uv_stream_t*) client) == 0) {
    uv_read_start(
                  (uv_stream_t*) client,
                  std::bind(&EchoServer::on_alloc_buffer, this, _1, _2, _3),
                  std::bind(&EchoServer::on_read, this, _1, _2, _3));
  } else {
    uv_close((uv_handle_t*) client, NULL);
  }
}

int EchoServer::listen() {
  return uv_listen((uv_stream_t*) &m_server, 128,
                   std::bind(&EchoServer::on_new_connection, this, _1, _2));
}

void EchoServer::disconnect() {
  if (uv_is_active((uv_handle_t *)&m_server)) {
    uv_close((uv_handle_t *)&m_server, NULL);
  }
}
