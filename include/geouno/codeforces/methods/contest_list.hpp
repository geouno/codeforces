#pragma once

#include <iostream>
#include <vector>
#include "geouno/codeforces/objects/Contest.hpp"
#include "geouno/codeforces/request.hpp"
#include "geouno/third_party/json.hpp"

namespace codeforces {
	inline std::vector<Contest*> contest_list(const bool gym = false) {
		nlohmann::json result = request(
			"contest.list", {
				{"gym", gym ? "true" : "false"}
			}
		);
		std::vector<Contest*> ret;

		if(result.is_null() || !result.is_array()) {
			std::cerr << "codeforces::contest_list(): Codeforces API request failed." << std::endl;
			return std::vector<Contest*>{};
		}

		for(const auto& contest_data : result)
			ret.push_back(new Contest(contest_data));

		return ret;
	}
}
