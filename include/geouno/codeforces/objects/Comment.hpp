#pragma once

#include <iostream>
#include <string>
#include "geouno/third_party/json.hpp"

namespace codeforces {
	class Comment {
	public:
		int id;
		int64_t creationTimeSeconds;
		std::string commentatorHandle;
		std::string locale;
		std::string text;
		int parentCommentId;
		int rating;

		Comment(
			int _id,
			int64_t _creationTimeSeconds,
			std::string _commentatorHandle,
			std::string _locale,
			std::string _text,
			int _parentCommentId,
			int _rating
		) {
			id = _id;
			creationTimeSeconds = _creationTimeSeconds;
			commentatorHandle = _commentatorHandle;
			locale = _locale;
			text = _text;
			parentCommentId = _parentCommentId;
			rating = _rating;
		}

		Comment(const nlohmann::json& json) {
			try {
				id = json["id"];
				creationTimeSeconds = json["creationTimeSeconds"];
				commentatorHandle = json["commentatorHandle"];
				locale = json["locale"];
				text = json["text"];
				parentCommentId = json.contains("parentCommentId") ? (int) json["parentCommentId"] : 0;
				rating = json["rating"];
			}
			catch(const nlohmann::json::parse_error& e) {
				std::cerr << "JSON parse error: " << e.what() << std::endl;
			}
		}

		Comment() = default;
		~Comment() { };
	};
}
