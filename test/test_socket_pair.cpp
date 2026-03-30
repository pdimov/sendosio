// Copyright 2026 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <sendosio/sendosio.hpp>
#include <beman/execution/execution.hpp>
#include <thread>

namespace ex = beman::execution;

int main()
{
    sendosio::io_context ioc;

    auto sp = sendosio::test::make_socket_pair( ioc );

    int x1 = 7;
    auto wsnd = sendosio::write( sp.second, sendosio::const_buffer( &x1, sizeof(x1) ) );

    int x2 = 0;
    auto rsnd = sendosio::read( sp.first, sendosio::mutable_buffer( &x2, sizeof(x2) ) );

    std::thread th( &sendosio::io_context::run, &ioc );

    ex::sync_wait( ex::when_all( std::move(rsnd), std::move(wsnd) ) );

    th.join();

    return x2 == 7? 0: 1;
}
