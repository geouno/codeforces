#pragma once

#include <iostream>
#include <vector>
#include "geouno/codeforces/objects/Comment.hpp"
#include "geouno/codeforces/request.hpp"
#include "geouno/third_party/json.hpp"

namespace codeforces {
	inline std::vector<Comment*> blogEntry_comments(const int& blogEntryId) {
		nlohmann::json result = request(
			"blogEntry.comments", {
				{"blogEntryId", std::to_string(blogEntryId)}
			}
		);
		std::vector<Comment*> ret;

		if(result.is_null() || !result.is_array()) {
			std::cerr << "codeforces::blogEntry_comments(): Codeforces API request failed." << std::endl;
			return std::vector<Comment*>{};
		}

		for(const auto& comment_data : result)
			ret.push_back(new Comment(comment_data));

		return ret;
	}
}
