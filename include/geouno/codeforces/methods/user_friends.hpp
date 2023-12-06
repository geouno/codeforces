#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "geouno/codeforces/request.hpp"
#include "geouno/third_party/json.hpp"

namespace codeforces {
	inline std::vector<std::string> user_friends(
		const bool onlyOnline = false
	) {
		nlohmann::json result = authorized_request(
			"user.friends", {
				{"onlyOnline", onlyOnline ? "true" : "false"}
			}
		);
		std::vector<std::string> ret;

		if(result.is_null() || !result.is_array()) {
			std::cerr << "codeforces::user_friends(): Codeforces API request failed." << std::endl;
			return std::vector<std::string>{};
		}

		for (const auto& friend_data : result)
			ret.push_back(friend_data);

		return ret;
	}
}
