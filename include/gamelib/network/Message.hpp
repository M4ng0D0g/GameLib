#pragma once

#include <memory>
#include <cstdint>
#include <vector>

// class Message : public yojimbo::Message {

// };

namespace GameLib::Network {

	class Message {
	public:
		using S_Ptr = std::shared_ptr<Message>;

		// 訊息類型ID，可以用 enum class
		enum class Type : uint16_t {
			LOGIN_REQUEST = 1,
			LOGIN_RESPONSE,
			CHAT_MESSAGE,
			//...其他訊息類型
		};


		virtual ~Message() = default;

		virtual Type getType() const = 0;

		// 序列化成 byte buffer (可用 std::vector<uint8_t> 或自訂)
		virtual std::vector<uint8_t> serialize() const = 0;

		// 反序列化(靜態工廠函式)
		static S_Ptr deserialize(const std::vector<uint8_t>& buffer);
	};
	
}