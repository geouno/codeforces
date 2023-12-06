#pragma once

#include <iostream>
#include <vector>
#include "geouno/codeforces/objects/Submission.hpp"
#include "geouno/codeforces/request.hpp"
#include "geouno/third_party/json.hpp"

namespace codeforces {
	inline std::vector<Submission*> user_status(const std::string& handle) {
		nlohmann::json result = request(
			"user.status", {
				{"handle", handle}
			}
		);
		std::vector<Submission*> ret;

		if(result.is_null() || !result.is_array()) {
			std::cerr << "codeforces::user_status(): Codeforces API request failed." << std::endl;
			return std::vector<Submission*>{};
		}

		for (const auto& submission : result)
			ret.push_back(new Submission(submission));

		return ret;
	}
}
