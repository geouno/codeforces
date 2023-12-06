#pragma once

#include <iostream>
#include <string>
#include "geouno/third_party/json.hpp"

namespace codeforces {
	class RatingChange {
	public:
		int contestId;
		std::string contestName;
		std::string handle;
		int rank;
		int64_t ratingUpdateTimeSeconds;
		int oldRating;
		int newRating;

		RatingChange(
			int _contestId,
			std::string _contestName,
			std::string _handle,
			int _rank,
			int64_t _ratingUpdateTimeSeconds,
			int _oldRating,
			int _newRating
		) {
			contestId = _contestId;
			contestName = _contestName;
			handle = _handle;
			rank = _rank;
			ratingUpdateTimeSeconds = _ratingUpdateTimeSeconds;
			oldRating = _oldRating;
			newRating = _newRating;
		}

		RatingChange(const nlohmann::json& json) {
			try {
				contestId = json["contestId"];
				contestName = json["contestName"];
				handle = json["handle"];
				rank = json["rank"];
				ratingUpdateTimeSeconds = json["ratingUpdateTimeSeconds"];
				oldRating = json["oldRating"];
				newRating = json["newRating"];
			}
			catch(const nlohmann::json::parse_error& e) {
				std::cerr << "JSON parse error: " << e.what() << std::endl;
			}
		}

		RatingChange() = default;
		~RatingChange() { };
	};
}
