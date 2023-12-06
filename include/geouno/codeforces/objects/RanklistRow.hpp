#pragma once

#include <iostream>
#include <vector>
#include "geouno/codeforces/objects/Party.hpp"
#include "geouno/codeforces/objects/ProblemResult.hpp"
#include "geouno/third_party/json.hpp"

namespace codeforces {
	class RanklistRow {
	public:
		Party* party;
		int rank;
		double points;
		int penalty;
		int successfulHackCount;
		int unsuccessfulHackCount;
		std::vector<ProblemResult> problemResults;
		int64_t lastSubmissionTimeSeconds;

		RanklistRow(
			Party* _party,
			int _rank,
			double _points,
			int _penalty,
			int _successfulHackCount,
			int _unsuccessfulHackCount,
			std::vector<ProblemResult>& _problemResults,
			int64_t _lastSubmissionTimeSeconds = 0
		) {
			party = _party,
			rank = _rank;
			points = _points;
			penalty = _penalty;
			successfulHackCount = _successfulHackCount;
			unsuccessfulHackCount = _unsuccessfulHackCount;
			problemResults = _problemResults;
			lastSubmissionTimeSeconds = _lastSubmissionTimeSeconds;
		}

		RanklistRow(const nlohmann::json& json) {
			try {
				party = new Party(json["party"]);
				rank = json["rank"];
				points = json["points"];
				penalty = json["penalty"];
				successfulHackCount = json["successfulHackCount"];
				unsuccessfulHackCount = json["unsuccessfulHackCount"];
				problemResults.clear();
				for(const auto& problemResult : json["problemResults"])
					problemResults.push_back(ProblemResult(problemResult));
				lastSubmissionTimeSeconds = json.contains("lastSubmissionTimeSeconds") ? (int) json["lastSubmissionTimeSeconds"] : 0;
			}
			catch(const nlohmann::json::parse_error& e) {
				std::cerr << "JSON parse error: " << e.what() << std::endl;
			}
		}

		RanklistRow() = default;
		~RanklistRow() { };
	};
}
