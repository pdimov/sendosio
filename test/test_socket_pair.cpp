// Copyright 2026 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <sendosio/sendosio.hpp>

int main()
{
    sendosio::io_context ioc;
    auto r = sendosio::test::make_socket_pair( ioc );
}
