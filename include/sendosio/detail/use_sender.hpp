#ifndef SENDOSIO_DETAIL_USE_SENDER_HPP_INCLUDED
#define SENDOSIO_DETAIL_USE_SENDER_HPP_INCLUDED

// Copyright 2026 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/asio/async_result.hpp>
#include <beman/execution/execution.hpp>
#include <tuple>
#include <type_traits>

namespace sendosio
{
namespace detail
{

namespace ex = beman::execution;

struct use_sender_t {};
inline constexpr use_sender_t use_sender;

template<class Receiver, class... Args>
struct completion_handler
{
    Receiver& recv_;

    void operator()( Args... args ) const
    {
        ex::set_value( std::move(recv_), std::move(args)... );
    }
};

template<class Sig, class Init, class... InitArgs> class sender;

template<class... Args, class Init, class... InitArgs> class sender<void(Args...), Init, InitArgs...>
{
private:

    struct tag_type {};
    using init_type = std::decay_t<Init>;
    using args_type = std::tuple< std::decay_t<InitArgs>... >;

public: // was private, but beman::execution wants to destructure it in tag_of_t

    tag_type tag_;
    init_type init_;
    args_type args_;

private:

    template<class Receiver> struct operation_state
    {
        init_type init_;
        args_type args_;
        std::decay_t<Receiver> recv_;

        using operation_state_concept = ex::operation_state_t;

        void start() & noexcept
        {
            std::apply( [&]( auto&&... args ) {

                std::move(init_)( completion_handler<std::decay_t<Receiver>, Args...>{ recv_ }, std::move(args)... );

            }, std::move(args_) );
        }
    };

public:

    using sender_concept = ex::sender_t;

    using completion_signatures = ex::completion_signatures<
        ex::set_value_t( Args... ),
        ex::set_error_t( std::exception_ptr )
    >;

    template<class Self, class... Env>
    static consteval completion_signatures get_completion_signatures() noexcept
    {
        return {};
    }

/*
    explicit sender( Init&& init, InitArgs&&... init_args ): init_( std::forward<Init>(init) ), args_( std::forward<InitArgs>(init_args)... )
    {
    }
*/

    template<class Receiver> operation_state<Receiver> connect( Receiver&& r ) &&
    {
        return { std::move(init_), std::move(args_), std::forward<Receiver>( r ) };
    }

    template<class Receiver> operation_state<Receiver> connect( Receiver&& r ) const&
    {
        return { init_, args_, std::forward<Receiver>( r ) };
    }
};

} // namespace detail
} // namespace sendosio

namespace boost
{
namespace asio
{

template<class Sig>
struct async_result<sendosio::detail::use_sender_t, Sig>
{
    template<class Init, class Token, class... InitArgs>
    static sendosio::detail::sender<Sig, Init, InitArgs...> initiate( Init&& init, Token&& /*token*/, InitArgs&&... init_args)
    {
        return sendosio::detail::sender<Sig, Init, InitArgs...>{ {}, std::forward<Init>(init), { std::forward<InitArgs>(init_args)... } };
    }
};

} // namespace asio
} // namespace boost

#endif // #ifndef SENDOSIO_DETAIL_USE_SENDER_HPP_INCLUDED
