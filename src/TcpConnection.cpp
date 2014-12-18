#include "TcpConnection.hpp"

TcpConnection::TcpConnection(const std::string& host, const std::string& port)
    : m_host(host), m_port(port), m_strand(m_io_service), m_socket(m_io_service), m_work(m_io_service) {}

TcpConnection::~TcpConnection()
{
    if(is_connected())
    {
        disconnect();
    }
    std::cout << "Socket destroyed." << std::endl;
}

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
    if(!is_connected())
    {
        return;
    }
    boost::system::error_code error;
    m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, error);
    //Remove remaining packets in queues
    while(!m_recv_queue.empty())
    {
        m_recv_queue.pop();
    }
    while (!m_send_queue.empty())
    {
        m_send_queue.pop();
    }
    m_run_thread.detach();
    m_socket.close();
    m_io_service.stop();
    m_connected = false;
}

void TcpConnection::send(const std::string& message)
{
	m_strand.post(std::bind(&TcpConnection::write_impl, this, message));
}

std::string TcpConnection::get_next_message()
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

void TcpConnection::read_handler(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    //Need to add handle for errors...

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

void TcpConnection::write_handler(const boost::system::error_code& error, std::size_t bytes_transferred)
{
	m_send_queue.pop();

	if(error.value() != 0)
	{
		std::cerr << "Failed to write: " << error.message() << std::endl;
	}

	if(!m_send_queue.empty())
	{
		//More messages to send
		write();
	}
}

void TcpConnection::write()
{
	const std::string& message = m_send_queue.front();
	boost::asio::async_write(m_socket, boost::asio::buffer(message), std::bind(&TcpConnection::write_handler, this, std::placeholders::_1, std::placeholders::_2));
}

void TcpConnection::write_impl(const std::string& message)
{
	m_send_queue.push(message);
	if (m_send_queue.size() > 1)
	{
		//Waiting to send another message still
		return;
	}

	write();
}