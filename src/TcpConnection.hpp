#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

/**
 * TcpConnection.
 * Provides a basic interace for opening up, reading, and writing to a TCP socket with another host.
 *
 * @author Jared Ready
 */

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
    /**
     * Constructor
     * @param host URL or IPv4 or v6 address of target host
     * @param port port number
     */
    TcpConnection(const std::string& host, const std::string& port);
    /**
     * Open a connection to host:port
     */
    void connect();
    /**
     * Close connection
     */
    void disconnect();
    /**
     * Send a message though the connection
     * @param message message to send
     */
    void send(const std::string& message);
    /**
     * Messages are pushed onto a queue asynchronously. This method pops a message off the queue.
     * @return the message.
     */
    const std::string& get_next_message();
    bool has_message();
    bool is_connected();
 
private:
    void read_handler(const boost::system::error_code& error, std::size_t bytes_transferred);
    void write_handler(const boost::system::error_code& error, std::size_t bytes_transferred);

    std::string m_host;
    std::string m_port;
    std::queue<std::string> m_recv_queue;
    std::thread m_run_thread;
    std::string m_message;
    bool m_connected;
 
    boost::asio::streambuf m_buffer;
    boost::asio::io_service m_io_service;
    boost::asio::io_service::work m_work;
    boost::asio::ip::tcp::socket m_socket;
};

#endif