#pragma once

#include <chrono>

// ***************************************************************************/

namespace GameLib::Utils {

	using time = uint64_t;

	// 時間來源： 系統時間（wall-clock time）。
	// 可讀性： 可以對應到實際的日期與時間（例如 2025-05-08 13:00）。
	// 可調性： 可能會被手動或透過 NTP 校正（例如使用者修改系統時間）。
	// 用途： 儲存事件發生的絕對時間點（如日誌紀錄、排程）。
	inline time systemNowMs() noexcept {
		return static_cast<time>(
			std::chrono::duration_cast<std::chrono::milliseconds>(
				std::chrono::system_clock::now().time_since_epoch()).count()
			);
	}

	// 時間來源： 穩定、單調遞增的時間來源。
	// 可讀性： 無法對應到實際的日期時間，僅是時間間隔。
	// 穩定性： 不會 被系統時間變更影響，適合計時。
	// 用途： 計算經過時間（如延遲、超時、執行時間測量）。
	inline time steadyNowMs() noexcept {
		return static_cast<time>(
			std::chrono::duration_cast<std::chrono::milliseconds>(
				std::chrono::steady_clock::now().time_since_epoch()).count()
			);
	}
}