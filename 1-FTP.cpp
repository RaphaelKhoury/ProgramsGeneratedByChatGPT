#include <boost/asio.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session> {
public:
    Session(tcp::socket socket) : socket_(std::move(socket)) {}

    void Start() { DoRead(); }

private:
    void DoRead() {
        auto self(shared_from_this());
        socket_.async_read_some(
            boost::asio::buffer(buffer_),
            [this, self](boost::system::error_code ec, std::size_t length) {
                if (!ec) {
                    std::string filename(buffer_.data(), length);
                    if (filename.back() == '\n') {
                        filename.pop_back();  // Remove newline character
                    }
                    SendFile(filename);
                }
            });
    }

    void SendFile(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (file) {
            file.seekg(0, std::ios::end);
            std::size_t file_size = file.tellg();
            file.seekg(0, std::ios::beg);

            boost::asio::streambuf response;
            std::ostream response_stream(&response);
            response_stream << "HTTP/1.1 200 OK\r\n";
            response_stream << "Content-Type: application/octet-stream\r\n";
            response_stream << "Content-Disposition: attachment; filename=\"" << filename << "\"\r\n";
            response_stream << "Content-Length: " << file_size << "\r\n";
            response_stream << "Connection: close\r\n\r\n";

            socket_.async_send(response.data(),
                [this, self, &file, file_size](boost::system::error_code ec, std::size_t) {
                    if (!ec) {
                        char* buffer = new char[file_size];
                        file.read(buffer, file_size);
                        socket_.async_send(
                            boost::asio::buffer(buffer, file_size),
                            [this, self, buffer](boost::system::error_code ec, std::size_t) {
                                delete[] buffer;
                            });
                    }
                });
        }
        else {
            boost::asio::streambuf response;
            std::ostream response_stream(&response);
            response_stream << "HTTP/1.1 404 Not Found\r\n";
            response_stream << "Connection: close\r\n\r\n";
            socket_.async_send(response.data(),
                [this, self](boost::system::error_code ec, std::size_t) {});
        }
    }

    tcp::socket socket_;
    boost::asio::streambuf buffer_;
};

class Server {
public:
    Server(boost::asio::io_context& io_context, std::uint16_t port)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {  
        DoAccept();
    }

private:
    void DoAccept() {
        acceptor_.async_accept([this](boost::system::error_code ec, tcp::socket socket) {
            if (!ec) {
                std::make_shared<Session>(std::move(socket))->Start();
            }
            DoAccept();
            });
    }

    tcp::acceptor acceptor_;
};

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: file_server <port> <file_directory>\n";
        return 1;
    }
 }
   

