// Copyright 2026 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <sendosio/sendosio.hpp>
#include <beman/execution/execution.hpp>

namespace ex = beman::execution;

int main()
{
    sendosio::io_context ioc;
    sendosio::tcp_socket sock( ioc );

    unsigned char buffer[ 4 ];
    auto sender = sendosio::read_some( sock, sendosio::mutable_buffer( buffer, sizeof(buffer) ) );

    // temporary
    constexpr auto x = ex::get_completion_signatures<decltype(sender), ex::detail::sync_wait_env>();

    ex::sync_wait( std::move( sender ) );
}
