#pragma once

#include <cstdint>
#include <string>
#include <iterator>
#include <vector>

#include <boost/asio.hpp>
#include <boost/array.hpp>

#include "demo2/Message.h"
#include "demo2/ClientInputMessages.h"
#include "demo2/frame/Frame.h"

namespace demo2
{

namespace client    
{

class Client
{
public:
    Client(boost::asio::io_service& io, const std::string& server, std::uint16_t port);

    bool start();

    using InputMsg = 
        demo2::Message<
            comms::option::ReadIterator<const std::uint8_t*>,
            comms::option::Handler<Client>,
            comms::option::NameInterface
        >;

    using InMsg2 = demo2::message::Msg2<InputMsg>;
    
    void handle(InMsg2& msg);
    void handle(InputMsg&);

private:
    using Socket = boost::asio::ip::tcp::socket;

    using OutputMsg = 
        demo2::Message<
            comms::option::WriteIterator<std::back_insert_iterator<std::vector<std::uint8_t> > >,
            comms::option::LengthInfoInterface,
            comms::option::IdInfoInterface,
            comms::option::NameInterface
        >;

    using AllInputMessages = demo2::ClientInputMessages<InputMsg>;

    using Frame = demo2::frame::Frame<InputMsg, AllInputMessages>;


    void readDataFromServer();
    void readDataFromStdin();
    void sendMsg1();
    void sendMessage(const OutputMsg& msg);
    void waitForResponse();
    void processInput();

    Socket m_socket;
    boost::asio::deadline_timer m_timer;
    std::string m_server;
    std::uint16_t m_port = 0U;
    Frame m_frame;
    unsigned m_sentVersion = std::numeric_limits<unsigned>::max();
    boost::array<std::uint8_t, 32> m_readBuf;
    std::vector<std::uint8_t> m_inputBuf;
};

} // namespace client

} // namespace demo2
