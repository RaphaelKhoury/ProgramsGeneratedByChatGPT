#include <boost/asio.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session> {
public:
    Session(tcp::socket socket, const std::string& file_directory)
        : socket_(std::move(socket)), file_directory_(file_directory) {}

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
        // Validate user input to prevent directory traversal attacks
        std::string full_path = file_directory_ + "/" + filename;
        if (full_path.find(file_directory_) != 0) {
            // Requested file is not within the specified directory
            SendErrorResponse(403, "Forbidden");
            return;
        }

        std::ifstream file(full_path, std::ios::binary);
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
            // Return a generic error message to prevent giving out information that could be used by an attacker
            SendErrorResponse(404, "File Not Found");
        }
    }

    void SendErrorResponse(int status_code, const std::string& message) {
        boost::asio::streambuf response;
        std::ostream response_stream(&response);
        response_stream << "HTTP/1.1 " << status_code << " " << message << "\r\n";
        response_stream << "Content-Type: text/plain\r\n";
        response_stream << "Content-Length: " << message.length() << "\r\n";
        response_stream << "Connection: close\r\n\r\n";
        response_stream << message;

        socket_.async_send(response.data(),
            [this, self](boost::system::error_code ec, std::size_t) {});
    }

    tcp::socket socket_;
    boost::asio::streambuf buffer_;
    std::string file_directory_;
};

class Server {
public:
    Server(boost::asio::io_context
