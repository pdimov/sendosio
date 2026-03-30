# Copyright 2026 Peter Dimov
# Distributed under the Boost Software License, Version 1.0.
# https://www.boost.org/LICENSE_1_0.txt

add_executable(sendosio_test_socket_pair)

target_sources(sendosio_test_socket_pair PRIVATE test_socket_pair.cpp)

target_link_libraries(sendosio_test_socket_pair PRIVATE sendosio::sendosio)

add_test(sendosio_test_socket_pair sendosio_test_socket_pair)
