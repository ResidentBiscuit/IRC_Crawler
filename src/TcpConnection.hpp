#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <queue>
#include <string>
#include <thread>
#include <functional>
#include <stdexcept>

class TcpConnection
{
public:
    TcpConnection(const std::string& host, const std::string& port);
    void connect();
    void disconnect();
    void read_handler(const boost::system::error_code& error, std::size_t bytes_transferred);
    void write_handler(const boost::system::error_code& error, std::size_t bytes_transferred);
    void send(const std::string& message);
    const std::string& get_next_message();
    bool has_message();
    bool is_connected();
 
private:
    std::string m_host;
    std::string m_port;
    std::queue<std::string> m_recv_queue;
    std::thread run_thread;
    std::string message;
    bool connected;
 
    boost::asio::streambuf m_buffer;
    boost::asio::io_service m_io_service;
    boost::asio::io_service::work m_work;
    boost::asio::ip::tcp::socket m_socket;
};

#endif