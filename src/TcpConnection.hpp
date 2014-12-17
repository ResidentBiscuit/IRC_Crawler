#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

/**
 * TcpConnection.
 * Provides a basic interace for opening up, reading, and writing to a TCP socket with another host.
 *
 * @author Jared Ready
 */

#include <boost/asio.hpp>
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
    ~TcpConnection();
    /**
     * Open a connection to host:port
     */
    void connect();
    /**
     * Closes current connection and opens a new connection to host:port
     */
    void connect(const std::string& host, const std::string& port);
    /**
     * Close connection
     */
    void disconnect();
    /**
     * Pushes a message onto the send queue to be sent
     * @param message message to send
     */
    void send(const std::string& message);
    /**
     * Messages are pushed onto a queue asynchronously. This method pops a message off the queue.
     * @return the message.
     */
    const std::string& get_next_message();
    /**
     * @return true if there is a message waiting in receive queue
     */
    bool has_message();
    /**
     * @return true if connection is alive
     */
    bool is_connected();
 
private:
    void read_handler(const boost::system::error_code& error, std::size_t bytes_transferred);
    void write_handler(const boost::system::error_code& error, std::size_t bytes_transferred);

	void write();
	void write_impl(const std::string& message);

    std::string m_host;
    std::string m_port;
    std::queue<std::string> m_recv_queue;
	std::queue<std::string> m_send_queue;
    std::thread m_run_thread;
    std::string m_message;
    bool m_connected;
 
    boost::asio::streambuf m_buffer;
    boost::asio::io_service m_io_service;
	boost::asio::io_service::strand m_strand;
    boost::asio::io_service::work m_work;
    boost::asio::ip::tcp::socket m_socket;
};

#endif