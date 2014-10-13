#include "TcpConnection.hpp"

TcpConnection::TcpConnection(const std::string& host, const std::string& port)
    : m_host(host), m_port(port), m_socket(m_io_service), m_work(m_io_service) {}

void TcpConnection::connect()
{
    try
    {
        boost::asio::ip::tcp::resolver resolver(m_io_service);
        boost::asio::ip::tcp::resolver::query query(m_host, m_port);
        boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

        boost::asio::connect(m_socket, endpoint_iterator);

        m_connected = true;

        boost::asio::async_read_until(m_socket, m_buffer, "\r\n", 
            std::bind(&TcpConnection::read_handler, this, std::placeholders::_1, std::placeholders::_2));

        m_run_thread = std::thread([this]() { this->m_io_service.run(); });
    }
    catch (std::exception& e)
    {
        throw std::runtime_error(e.what());
    }
}

void TcpConnection::connect(const std::string& host, const std::string& port)
{
    disconnect();
    m_host = host;
    m_port = port;
    connect();
}

void TcpConnection::disconnect()
{
    m_socket.close();
    m_io_service.stop();
    m_connected = false;
    //Remove remaining packets in queue
    while(!m_recv_queue.empty())
    {
        m_recv_queue.pop();
    }
}

void TcpConnection::read_handler(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    //Need to handle errors...

    //Prepare m_buffer for output
    std::istream is(&m_buffer);
    std::string line;
    std::getline(is, line);
    line += "\n"; //Because std::getline() strips it away
    m_recv_queue.push(line);

    if(error.value() != 0)
    {
        std::cout << error.message();
        return;
    }

    //Read until next \r\n, probably could generalize this more
    boost::asio::async_read_until(m_socket, m_buffer, "\r\n", 
            std::bind(&TcpConnection::read_handler, this, std::placeholders::_1, std::placeholders::_2));
}

void TcpConnection::write_handler(const boost::system::error_code& error, std::size_t bytes_transferred) {}

void TcpConnection::send(const std::string& message)
{
    boost::asio::async_write(m_socket, boost::asio::buffer(message), std::bind(&TcpConnection::write_handler, this, std::placeholders::_1, std::placeholders::_2));
}

const std::string& TcpConnection::get_next_message()
{
    m_message = m_recv_queue.front();
    m_recv_queue.pop();
    return m_message;
}

bool TcpConnection::has_message()
{
    return !m_recv_queue.empty();
}

bool TcpConnection::is_connected()
{
    return m_connected;
}