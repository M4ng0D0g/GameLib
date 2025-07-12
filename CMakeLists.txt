cmake_minimum_required(VERSION 3.14)
project(GameLib LANGUAGES CXX)

# ----------------------------
# 基本編譯設定
# ----------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ----------------------------
# Include 路徑
# ----------------------------
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# ASIO Standalone
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/asio/asio/include)

# nlohmann/json (單檔版)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/nlohmann)

# 如果有啟用 yojimbo，再打開這段：
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/yojimbo/yojimbo)

# ----------------------------
# 收集來源檔案
# ----------------------------
file(GLOB_RECURSE GAMELIB_SRC CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

# ⚠️ 如果要加入 yojimbo 檔案，可用以下方式
# file(GLOB YOJIMBO_SRC CONFIGURE_DEPENDS
#     ${CMAKE_CURRENT_SOURCE_DIR}/external/yojimbo/yojimbo/*.cpp
# )

# ----------------------------
# 建立靜態連結庫
# ----------------------------
add_library(GameLib STATIC
    ${GAMELIB_SRC}
    # ${YOJIMBO_SRC}  ← 如有需要可解除註解
)

# ----------------------------
# 給使用者暴露的 public include 路徑
# ----------------------------
target_include_directories(GameLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external/nlohmann
    ${CMAKE_CURRENT_SOURCE_DIR}/external/asio/asio/include
)

# ----------------------------
# 定義平台相關宏（給 raylib 用）
# ----------------------------
target_compile_definitions(GameLib PRIVATE
    PLATFORM_DESKTOP
    ASIO_STANDALONE       # 使用 Asio standalone 時必加
)
