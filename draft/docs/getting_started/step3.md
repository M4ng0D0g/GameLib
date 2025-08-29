# 加入事件系統
- 本區功能命名空間
```cpp
using namespace GameLib::Core::Event;
```

## `🔔 事件系統`

- `Event` - 所有事件類型的基底
```cpp
class Event {
public:
	virtual ~Event() = default;
};
```

- `Listener<EventT>` - 監聽特定事件 `EventT` 的監聽器基底
```cpp
template <typename T>
class Listener : public std::enable_shared_from_this<Listener<T>> {
public:
	using U_Ptr = std::unique_ptr<Listener>;
	using S_Ptr = std::shared_ptr<Listener>;
	using W_Ptr = std::weak_ptr<Listener>;

	virtual ~Listener() = default;

	virtual bool onEvent(const std::shared_ptr<T>&) = 0;
	virtual void autoRegister(EventBus&) {}
};
```

- `EventBus` - 事件總線，用來集合相關的訂閱者和事件
```cpp
class EventBus {
public:
	virtual ~EventBus() = default;

	template <typename T>
	void subscribe(ListenerW_Ptr<T> listener);

	template <typename T>
	void unsubscribe(ListenerW_Ptr<T> listener);

	template <typename T>
	void publish(std::shared_ptr<T>& event);~
};
```

---
#### `⬅️ 上一步：` [加入 MVC 架構](step2.md)
#### `➡️ 下一步：` [使用基礎終端機顯示](step4.md)