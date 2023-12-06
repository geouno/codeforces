#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include "geouno/third_party/json.hpp"

namespace codeforces {
	class ProblemResult {
	public:
		enum type_t {
			PRELIMINARY,
			FINAL
		};

	private:
		const static std::unordered_map<std::string, type_t> type_map;

		const static std::unordered_map<type_t, std::string> type_str_map;

	public:
		double points;
		int penalty;
		int rejectedAttemptCount;
		type_t type;
		int64_t bestSubmissionTimeSeconds;

		ProblemResult(
			double _points,
			int _penalty,
			int _rejectedAttemptCount,
			type_t _type,
			int64_t _bestSubmissionTimeSeconds
		) {
			points = _points;
			penalty = _penalty;
			rejectedAttemptCount = _rejectedAttemptCount;
			type = _type;
			bestSubmissionTimeSeconds = _bestSubmissionTimeSeconds;
		}

		ProblemResult(const nlohmann::json& json) {
			try {
				points = json["points"];
				penalty = json.contains("penalty") ? (int) json["penalty"] : 0;
				rejectedAttemptCount = json["rejectedAttemptCount"];
				type = type_map.at(json["type"]);
				bestSubmissionTimeSeconds = json.contains("bestSubmissionTimeSeconds") ? (int) json["bestSubmissionTimeSeconds"] : 0;
			}
			catch(const nlohmann::json::parse_error& e) {
				std::cerr << "JSON parse error: " << e.what() << std::endl;
			}
		}

		ProblemResult() = default;
		~ProblemResult() { };

		friend std::ostream& operator << (std::ostream& o, const type_t var) {
			return o << type_str_map.at(var);
		}

		std::string type_str() {
			return type_str_map.at(type);
		}
	};

	inline const std::unordered_map<std::string, ProblemResult::type_t> ProblemResult::type_map = {
		{"PRELIMINARY", PRELIMINARY},
		{"FINAL", FINAL}
	};

	inline const std::unordered_map<ProblemResult::type_t, std::string> ProblemResult::type_str_map = {
		{PRELIMINARY, "PRELIMINARY"},
		{FINAL, "FINAL"}
	};
}
