#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "geouno/third_party/json.hpp"

namespace codeforces {
	class BlogEntry {
	public:
		int id;
		std::string originalLocale;
		int64_t creationTimeSeconds;
		std::string authorHandle;
		std::string title;
		std::string content;
		std::string locale;
		int64_t modificationTimeSeconds;
		bool allowViewHistory;
		std::vector<std::string> tags;
		int rating;

		BlogEntry(
			int _id,
			std::string _originalLocale,
			int64_t _creationTimeSeconds,
			std::string _authorHandle,
			std::string _title,
			std::string _content,
			std::string _locale,
			int64_t _modificationTimeSeconds,
			bool _allowViewHistory,
			std::vector<std::string>& _tags,
			int _rating
		) {
			id = _id;
			originalLocale = _originalLocale;
			creationTimeSeconds = _creationTimeSeconds;
			authorHandle = _authorHandle;
			title = _title;
			content = _content;
			locale = _locale;
			modificationTimeSeconds = _modificationTimeSeconds;
			allowViewHistory = _allowViewHistory;
			tags = _tags;
			rating = _rating;
		}

		BlogEntry(const nlohmann::json& json) {
			try {
				id = json["id"];
				originalLocale = json["originalLocale"];
				creationTimeSeconds = json["creationTimeSeconds"];
				authorHandle = json["authorHandle"];
				title = json["title"];
				content = json.contains("content") ? json["content"] : "";
				locale = json["locale"];
				modificationTimeSeconds = json["modificationTimeSeconds"];
				allowViewHistory = (json["allowViewHistory"] == "true");
				tags.clear();
				for(const auto& tag : json["tags"])
					tags.push_back(tag);
				rating = json["rating"];
			}
			catch(const nlohmann::json::parse_error& e) {
				std::cerr << "JSON parse error: " << e.what() << std::endl;
			}
		}

		BlogEntry() = default;
		~BlogEntry() { };
	};
}
