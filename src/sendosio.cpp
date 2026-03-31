// Copyright 2026 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <sendosio/sendosio.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>

using sendosio::tcp_socket;

static boost::asio::awaitable<void> make_socket_pair_impl( boost::asio::io_context& ioc, tcp_socket::base_type& client, tcp_socket::base_type& server )
{
    using boost::asio::ip::tcp;

    boost::asio::basic_socket_acceptor<tcp, boost::asio::io_context::executor_type> acceptor( ioc, tcp::endpoint( tcp::v4(), 0 ) );
    unsigned short port = acceptor.local_endpoint().port();

    co_await client.async_connect( tcp::endpoint( boost::asio::ip::address_v4::loopback(), port ), boost::asio::use_awaitable );
    server = co_await acceptor.async_accept( boost::asio::use_awaitable );
}

std::pair<tcp_socket, tcp_socket> sendosio::test::make_socket_pair( io_context& ioc )
{
    std::pair<tcp_socket, tcp_socket> r{ tcp_socket( ioc ), tcp_socket( ioc ) };

    boost::asio::co_spawn( ioc, make_socket_pair_impl( ioc, r.first, r.second ), boost::asio::detached );

    ioc.run();
    ioc.restart();

    return r;
}
