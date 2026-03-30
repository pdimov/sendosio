# Copyright 2026 Peter Dimov
# Distributed under the Boost Software License, Version 1.0.
# https://www.boost.org/LICENSE_1_0.txt

function(add_sendosio_test name)

	set(target sendosio-${name})

	add_executable(${target})

	target_sources(${target} PRIVATE ${name}.cpp)

	target_link_libraries(${target} PRIVATE sendosio::sendosio)

	add_test(NAME ${target} COMMAND ${target})

endfunction()

add_sendosio_test(test_read_some)
add_sendosio_test(test_socket_pair)
