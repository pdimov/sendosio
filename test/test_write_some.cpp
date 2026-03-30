// Copyright 2026 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <sendosio/sendosio.hpp>
#include <beman/execution/execution.hpp>
#include <thread>
#include <cstdio>

namespace ex = beman::execution;

int main()
{
    sendosio::io_context ioc;
    sendosio::tcp_socket sock( ioc );

    unsigned char buffer[ 4 ] = {};

    auto sender = sendosio::write_some( sock, sendosio::const_buffer( buffer, sizeof(buffer) ) )
        | ex::then( []( boost::system::error_code ec, std::size_t n ) {

            if( ec.failed() )
            {
                std::printf( "Error: %s\n", ec.what().c_str() );
            }
            else
            {
                std::printf( "Success: %zu\n", n );
            }
        } );

    std::thread th( &sendosio::io_context::run, &ioc );

    ex::sync_wait( std::move( sender ) );

    th.join();
}
