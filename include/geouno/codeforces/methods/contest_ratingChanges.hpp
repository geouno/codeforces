#pragma once

#include <iostream>
#include <vector>
#include "geouno/codeforces/objects/RatingChange.hpp"
#include "geouno/codeforces/request.hpp"
#include "geouno/third_party/json.hpp"

namespace codeforces {
	inline std::vector<RatingChange*> contest_ratingChanges(const int& contestId) {
		nlohmann::json result = request(
			"blogEntry.comments", {
				{"contestId", std::to_string(contestId)}
			}
		);
		std::vector<RatingChange*> ret;

		if(result.is_null() || !result.is_array()) {
			std::cerr << "codeforces::contest_ratingChanges(): Codeforces API request failed." << std::endl;
			return std::vector<RatingChange*>{};
		}

		for(const auto& comment_data : result)
			ret.push_back(new RatingChange(comment_data));

		return ret;
	}
}
