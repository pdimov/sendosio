#ifndef SENDOSIO_SENDOSIO_HPP_INCLUDED
#define SENDOSIO_SENDOSIO_HPP_INCLUDED

// Copyright 2026 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <utility>

namespace sendosio
{

class io_context;

class tcp_socket;

namespace test
{

std::pair<tcp_socket, tcp_socket> make_socket_pair( io_context& ioc );

} // namespace test

class const_buffer;
class mutable_buffer;

// sender_of<error_code, size_t>
template<class BufSeq> auto read_some( tcp_socket& sock, BufSeq&& seq );

// sender_of<error_code, size_t>
template<class BufSeq> auto read( tcp_socket& sock, BufSeq&& seq );

// sender_of<error_code, size_t>
template<class BufSeq> auto write_some( tcp_socket& sock, BufSeq&& seq );

// sender_of<error_code, size_t>
template<class BufSeq> auto write( tcp_socket& sock, BufSeq&& seq );

} // namespace sendosio

#include <sendosio/impl/sendosio.hpp>

#endif // #ifndef SENDOSIO_SENDOSIO_HPP_INCLUDED
