# 使用 TCP/UDP 網路連線
- 本區功能命名空間
```cpp
using namespace GameLib::Network;
```
- 環境變數命名空間
```cpp
using namespace GameLib::Env;
```



## `TCP Connection`

- TCPServer - 
```cpp
	class TCPServer {
	public:
		TCPServer(unsigned short port);

		void start();
		void stop();
	};
```
#### `⚙️ 環境變數`
```cpp
static int SERVER_PORT;
static int MAX_CLIENTS;
```

- TCPClient -
```cpp
	class TCPClient {
	public:
		TCPClient(const std::string& host, unsigned short port);

		void connect();
		void send(const std::string& message);
		void disconnect();

	};
```
## `UDP Connection`
- UDPServer - 
```cpp

```
#### `⚙️ 環境變數`
```cpp
static int SERVER_PORT;
static int MAX_CLIENTS;
```

- UDPClient -
```cpp

```
## `連線相關類別`
- Message - 
```cpp

```

- SessionModel - 便於 `GameLib::Core` 管理的 Client 端 Model
```cpp

```



---
#### `⬅️ 上一步：` [使用基礎終端機顯示](step4.md)
