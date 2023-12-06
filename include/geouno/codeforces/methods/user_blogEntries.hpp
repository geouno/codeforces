#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "geouno/codeforces/objects/BlogEntry.hpp"
#include "geouno/codeforces/request.hpp"
#include "geouno/third_party/json.hpp"

namespace codeforces {
	inline std::vector<BlogEntry*> user_blogEntries(const std::string& handle) {
		nlohmann::json result = request(
			"user.blogEntries", {
				{"handle", handle}
			}
		);
		std::vector<BlogEntry*> ret;

		if(result.is_null() || !result.is_array()) {
			std::cerr << "codeforces::user_blogEntries(): Codeforces API request failed." << std::endl;
			return std::vector<BlogEntry*>{};
		}

		for (const auto& entry_data : result)
			ret.push_back(new BlogEntry(entry_data));

		return ret;
	}
}
