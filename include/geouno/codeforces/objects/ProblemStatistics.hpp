#pragma once

#include <iostream>
#include <string>
#include "geouno/third_party/json.hpp"

namespace codeforces {
	class ProblemStatistics {
	public:
		int contestId;
		std::string index;
		int solvedCount;

		ProblemStatistics(
			int _contestId,
			std::string _index,
			int _solvedCount
		) {
			contestId = _contestId;
			index = _index;
			solvedCount = _solvedCount;
		}

		ProblemStatistics(const nlohmann::json& json) {
			try {
				contestId = json.contains("contestId") ? (int) json["contestId"] : 0;
				index = json["index"];
				solvedCount = json["solvedCount"];
			}
			catch(const nlohmann::json::parse_error& e) {
				std::cerr << "JSON parse error: " << e.what() << std::endl;
			}
		}

		ProblemStatistics() = default;
		~ProblemStatistics() { };
	};
}
