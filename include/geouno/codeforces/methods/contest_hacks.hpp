#pragma once

#include <iostream>
#include <optional>
#include <vector>
#include "geouno/codeforces/objects/Hack.hpp"
#include "geouno/codeforces/request.hpp"
#include "geouno/third_party/json.hpp"

namespace codeforces {
	inline std::vector<Hack*> contest_hacks(const int& contestId, const std::optional<bool>& asManager = std::nullopt) {
		nlohmann::json result = request(
			"contest.hacks", {
				{"contestId", std::to_string(contestId)},
				{"asManager", (asManager.has_value() && asManager.value()) ? "true" : "false"}
			}
		);
		std::vector<Hack*> ret;

		if(result.is_null() || !result.is_array()) {
			std::cerr << "codeforces::contest_hacks(): Codeforces API request failed." << std::endl;
			return std::vector<Hack*>{};
		}

		for(const auto& hack_data : result)
			ret.push_back(new Hack(hack_data));

		return ret;
	}
}
