// copyright 2010 t. schneider tes@mit.edu
//
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This software is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this software.  If not, see <http://www.gnu.org/licenses/>.


#ifndef TCPServer20100719H
#define TCPServer20100719H

#include <iostream>
#include <string>
#include <set>
#include <deque>

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/foreach.hpp>
#include "asio.hpp"

#include "interface.h"
#include "connection.h"

namespace goby
{
    namespace util
    {
        class TCPConnection;
        class TCPServer : public LineBasedInterface
        {
          public:    
            static TCPServer* get_instance(unsigned& clientkey,
                                           unsigned port,
                                           const std::string& delimiter = "\r\n");
    
          private:
          TCPServer(const std::string& port,
                    const std::string& delimiter = "\r\n")
              : acceptor_(io_service_, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 9000)),
                delimiter_(delimiter)
                {  }
    
    
            void do_start()
            { start_accept(); }
        
            void do_write(const std::string& line);
            void do_close(const asio::error_code& error);
            
          private:
            void start_accept();
            void handle_accept(boost::shared_ptr<TCPConnection> new_connection,
                               const asio::error_code& error);
            
          private:
            static std::map<std::string, TCPServer*> inst_;
            std::string server_;
            std::string port_;
            asio::ip::tcp::acceptor acceptor_;
            boost::shared_ptr<TCPConnection> new_connection_;
            std::set< boost::shared_ptr<TCPConnection> > connections_;
            std::string delimiter_;
    
        };


        class TCPConnection : public boost::enable_shared_from_this<TCPConnection>,
            public LineBasedConnection<asio::ip::tcp::socket>
            {
              public:
                static boost::shared_ptr<TCPConnection> create(asio::io_service& io_service,
                                                               std::vector< std::deque<std::string> >& in,
                                                               boost::mutex& in_mutex,
                                                               const std::string& delimiter);
                
                asio::ip::tcp::socket& socket()
                { return socket_; }
    
                void start()
                { socket_.get_io_service().post(boost::bind(&TCPConnection::read_start, this)); }

                void write(const std::string& msg)
                { socket_.get_io_service().post(boost::bind(&TCPConnection::socket_write, this, msg)); }    

                void close(const asio::error_code& error)
                { socket_.get_io_service().post(boost::bind(&TCPConnection::socket_close, this, error)); }
        
              private:
                void socket_write(const std::string& line);
                void socket_close(const asio::error_code& error);
    
              TCPConnection(asio::io_service& io_service,
                            std::vector< std::deque<std::string> >& in,
                            boost::mutex& in_mutex,
                            const std::string& delimiter)
                  : LineBasedConnection<asio::ip::tcp::socket>(socket_, out_, in, in_mutex, delimiter),
                    socket_(io_service)
                    { }
    

              private:
                asio::ip::tcp::socket socket_;
                std::deque<std::string> out_; // buffered write data
    
            };
    }

}

#endif
