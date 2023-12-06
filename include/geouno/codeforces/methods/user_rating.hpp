#pragma once

#include <iostream>
#include <vector>
#include "geouno/codeforces/objects/RatingChange.hpp"
#include "geouno/codeforces/request.hpp"
#include "geouno/third_party/json.hpp"

namespace codeforces {
	inline std::vector<RatingChange*> user_rating(const std::string& handle) {
		nlohmann::json result = request(
			"user.rating", {
				{"handle", handle}
			}
		);
		std::vector<RatingChange*> ret;
		
		if(result.is_null() || !result.is_array()) {
			std::cerr << "codeforces::user_rating(): Codeforces API request failed." << std::endl;
			return std::vector<RatingChange*>{};
		}

		for (const auto& change_data : result)
			ret.push_back(new RatingChange(change_data));

		return ret;
	}
}
