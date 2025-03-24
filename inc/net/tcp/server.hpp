#ifndef NET_TCP_SERVER_H
#define NET_TCP_SERVER_H

#include <netinet/in.h>
#include <sys/socket.h>

#include <cstddef>
#include <cstdint>

namespace net::tcp {

struct ServerOptions {
  std::uint16_t port;
  std::size_t max_conn = 32;
};

class Server {
public:
  class Client {
  public:
    friend class Server;
    Client() = delete;
    Client(const Client &) = delete;
    Client(Client &&) = default;

    Client &operator=(const Client &) = delete;
    Client &operator=(Client &&) = delete;

  private:
    explicit Client(const Server &m_server);

    const Server &m_server;
    sockaddr_in m_addr;
    socklen_t m_addrLength = sizeof(m_addr);
    const int m_fd = ::accept(
        m_server.m_fd, reinterpret_cast<sockaddr *>(&m_addr), &m_addrLength);
  };

  Server() = delete;
  Server(const Server &) = delete;
  Server(Server &&) = default;
  explicit Server(ServerOptions &&opts);
  ~Server();

  Server &operator=(const Server &) = delete;
  Server &operator=(Server &&) = delete;

private:
  const ServerOptions m_opts;
  const int m_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
};

} // namespace net::tcp

#endif // !NET_TCP_SERVER_H
