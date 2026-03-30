#ifndef SENDOSIO_IMPL_SENDOSIO_HPP_INCLUDED
#define SENDOSIO_IMPL_SENDOSIO_HPP_INCLUDED

// Copyright 2026 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <sendosio/detail/use_sender.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/read.hpp>
#include <boost/asio/write.hpp>

namespace sendosio
{

class io_context: public boost::asio::io_context
{
public:

    using boost::asio::io_context::io_context;
};

class tcp_socket: public boost::asio::ip::tcp::socket
{
public:

    using boost::asio::ip::tcp::socket::socket;
};

class const_buffer: public boost::asio::const_buffer
{
public:

    using boost::asio::const_buffer::const_buffer;
};

class mutable_buffer: public boost::asio::mutable_buffer
{
public:

    using boost::asio::mutable_buffer::mutable_buffer;
};

template<class BufSeq> auto read_some( tcp_socket& sock, BufSeq&& seq )
{
    return sock.async_read_some( std::forward<BufSeq>( seq ), sendosio::detail::use_sender );
}

template<class BufSeq> auto read( tcp_socket& sock, BufSeq&& seq )
{
    return boost::asio::async_read( sock, std::forward<BufSeq>( seq ), sendosio::detail::use_sender );
}

template<class BufSeq> auto write_some( tcp_socket& sock, BufSeq&& seq )
{
    return sock.async_write_some( sock, std::forward<BufSeq>( seq ), sendosio::detail::use_sender );
}

template<class BufSeq> auto write( tcp_socket& sock, BufSeq&& seq )
{
    return boost::asio::async_write( sock, std::forward<BufSeq>( seq ), sendosio::detail::use_sender );
}

} // namespace sendosio

#endif // #ifndef SENDOSIO_IMPL_SENDOSIO_HPP_INCLUDED
