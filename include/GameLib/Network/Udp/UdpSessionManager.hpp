// // Network/Udp/UdpSessionManager.hpp
// #pragma once
// #include "Network/Base/SessionManagerBase.hpp"
// #include "Network/Udp/UdpSession.hpp"

// namespace GL::Net::Udp {

// class UdpSessionManager : public Base::SessionManagerBase<UdpSession> {
// public:
//     /* 依需求，可用 remoteEndpoint 作 index */
//     UdpSession::Ptr findOrCreate(const boost::asio::ip::udp::endpoint& ep) {
//         auto key = ep.address().to_string() + ":" + std::to_string(ep.port());
//         auto s   = this->find(key);
//         if (!s) {
//             s = std::make_shared<UdpSession>(ep);
//             this->add(s);
//         }
//         return s;
//     }

//     void tick(std::chrono::steady_clock::time_point now) override {
//         const auto ttl = std::chrono::seconds(30);   // UDP 一般較短
//         for (auto it = sessions_.begin(); it != sessions_.end(); ) {
//             if (now - it->second->lastActive() > ttl) {
//                 it = sessions_.erase(it);
//             } else ++it;
//         }
//     }
// };

// } // namespace
