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

#ifndef __libuv_samples__tcp_echo_server__
#define __libuv_samples__tcp_echo_server__

#include <uv.h>

class EchoServer {
private:
  uv_loop_t * m_loop;
  uv_tcp_t m_server;
  struct sockaddr_in m_bind_addr;
  
  void on_new_connection(uv_stream_t *server, int status);
  void on_alloc_buffer(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf);
  void on_read(uv_stream_t* stream, ssize_t nread, const uv_buf_t* buf);
  void on_write(uv_write_t* req, int status);
public:
  EchoServer(int port, const char* ip = "0.0.0.0");
  ~EchoServer();
  
  uv_loop_t * loop();
  int listen();
  void disconnect();
};

#endif /* defined(__libuv_samples__tcp_echo_server__) */
