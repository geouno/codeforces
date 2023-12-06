#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "geouno/codeforces/objects/User.hpp"
#include "geouno/codeforces/request.hpp"
#include "geouno/third_party/json.hpp"

namespace codeforces {
	inline std::vector<User*> user_info(const std::vector<std::string>& handles) {
		std::string handles_string;
		for(size_t i = 0; i < handles.size(); i++) {
			if(i > 0)
				handles_string += ";";
			handles_string += handles[i];
		}

		nlohmann::json result = request(
			"user.info", {
				{"handles", handles_string}
			}
		);
		std::vector<User*> ret;

		if(result.is_null() || !result.is_array()) {
			std::cerr << "codeforces::user_info(): Codeforces API request failed." << std::endl;
			return std::vector<User*>{};
		}

		for (const auto& user_data : result)
			ret.push_back(new User(user_data));

		return ret;
	}
}
