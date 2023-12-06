#pragma once

#include <iostream>
#include "geouno/codeforces/objects/BlogEntry.hpp"
#include "geouno/codeforces/request.hpp"
#include "geouno/third_party/json.hpp"

namespace codeforces {
	inline BlogEntry* blogEntry_view(const int& blogEntryId) {
		nlohmann::json result = request(
			"blogEntry.view", {
				{"blogEntryId", std::to_string(blogEntryId)}
			}
		);

		if(result.is_null()) {
			std::cerr << "codeforces::blogEntry_view(): Codeforces API request failed." << std::endl;
			return nullptr;
		}

		return new BlogEntry(result);
	}
}
