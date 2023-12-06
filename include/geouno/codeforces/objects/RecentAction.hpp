#pragma once

#include <iostream>
#include "geouno/codeforces/objects/BlogEntry.hpp"
#include "geouno/codeforces/objects/Comment.hpp"
#include "geouno/third_party/json.hpp"

namespace codeforces {
	class RecentAction {
	public:
		int64_t timeSeconds;
		BlogEntry* blogEntry;
		Comment* comment;

		RecentAction(
			int64_t _timeSeconds,
			BlogEntry* _blogEntry,
			Comment* _comment
		) {
			timeSeconds = _timeSeconds;
			blogEntry = _blogEntry;
			comment = _comment;
		}

		RecentAction(const nlohmann::json& json) {
			try {
				timeSeconds = json["timeSeconds"];
				blogEntry = json.contains("blogEntry") ? new BlogEntry(json["blogEntry"]) : nullptr;
				comment = json.contains("comment") ? new Comment(json["comment"]) : nullptr;
			}
			catch(const nlohmann::json::parse_error& e) {
				std::cerr << "JSON parse error: " << e.what() << std::endl;
			}
		}

		RecentAction() = default;
		~RecentAction() { };
	};
}
