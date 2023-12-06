#pragma once

#include <iostream>
#include <optional>
#include <string>
#include <vector>
#include "geouno/codeforces/objects/Submission.hpp"
#include "geouno/codeforces/request.hpp"
#include "geouno/third_party/json.hpp"

namespace codeforces {
	inline std::vector<Submission*> problemset_recentStatus(
		const int& count,
		const std::optional<std::string>& problemsetName = std::nullopt
	) {
		std::vector<std::pair<std::string, std::string>> args = {
			{"count", std::to_string(count)}
		};
		if(problemsetName.has_value()) {
			args.push_back({"problemsetName", problemsetName.value()});
		}

		nlohmann::json result = request(
			"problemset.recentStatus", args
		);
		std::vector<Submission*> ret;

		if(result.is_null() || !result.is_array()) {
			std::cerr << "codeforces::problemset_recentStatus(): Codeforces API request failed." << std::endl;
			return std::vector<Submission*>{};
		}

		for(const auto& submission_data : result)
			ret.push_back(new Submission(submission_data));

		return ret;
	}

	inline std::vector<Submission*> problemset_recentStatus(
		const int& count,
		const nlohmann::json& optional_args = {}
	) {
		int valid_args = 0;

		std::optional<std::string> problemsetName = std::nullopt;
		if(
			optional_args.contains("problemsetName")
			&& optional_args["problemsetName"].is_string()
		) {
			problemsetName = optional_args["problemsetName"];

			valid_args++;
		}

		if(valid_args < optional_args.size()) {
			std::cerr << "codeforces::problemset_recentStatus() failed: invalid arguments" << std::endl;
			return std::vector<Submission*>{};
		}

		return problemset_recentStatus(
			count,
			problemsetName
		);
	}
}
