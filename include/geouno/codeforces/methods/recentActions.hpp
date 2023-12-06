#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "geouno/codeforces/objects/RecentAction.hpp"
#include "geouno/codeforces/request.hpp"
#include "geouno/third_party/json.hpp"

namespace codeforces {
	inline std::vector<RecentAction*> contest_recentActions(const int& maxCount) {
		nlohmann::json result = request(
			"recentActions", {
				{"maxCount", std::to_string(maxCount)}
			}
		);
		std::vector<RecentAction*> ret;

		if(result.is_null() || !result.is_array()) {
			std::cerr << "codeforces::contest_recentActions(): Codeforces API request failed." << std::endl;
			return std::vector<RecentAction*>{};
		}

		for (const auto& action_data : result)
			ret.push_back(new RecentAction(action_data));

		return ret;
	}
}
