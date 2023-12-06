#pragma once

#include <iostream>
#include <optional>
#include <string>
#include <vector>
#include "geouno/codeforces/objects/User.hpp"
#include "geouno/codeforces/request.hpp"
#include "geouno/third_party/json.hpp"

namespace codeforces {
	inline std::vector<User*> user_ratedList(
		const std::optional<bool>& activeOnly = std::nullopt,
		const std::optional<bool>& includeRetired = std::nullopt,
		const std::optional<int>& contestId = std::nullopt
	) {
		std::vector<std::pair<std::string, std::string>> args = {};
		if(activeOnly.has_value()) {
			args.push_back({"activeOnly", activeOnly.value() ? "true" : "false"});
		}
		if(includeRetired.has_value()) {
			args.push_back({"includeRetired", includeRetired.value() ? "true" : "false"});
		}
		if(contestId.has_value()) {
			args.push_back({"contestId", std::to_string(contestId.value())});
		}

		nlohmann::json result = request(
			"user.ratedList", args
		);
		std::vector<User*> ret;

		if(result.is_null() || !result.is_array()) {
			std::cerr << "codeforces::user_ratedList(): Codeforces API request failed." << std::endl;
			return std::vector<User*>{};
		}

		for (const auto& user_data : result)
			ret.push_back(new User(user_data));

		return ret;
	}
}
