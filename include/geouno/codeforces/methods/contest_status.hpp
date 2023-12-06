#pragma once

#include <iostream>
#include <optional>
#include <string>
#include <vector>
#include "geouno/codeforces/objects/Submission.hpp"
#include "geouno/codeforces/request.hpp"
#include "geouno/third_party/json.hpp"

namespace codeforces {
	inline std::vector<Submission*> contest_status(
		const int& contestId,
		const std::optional<bool>& asManager = std::nullopt,
		const std::optional<std::string>& handle = std::nullopt,
		const std::optional<int>& from = std::nullopt,
		const std::optional<int>& count = std::nullopt
	) {
		std::vector<std::pair<std::string, std::string>> args = {
			{"contestId", std::to_string(contestId)}
		};
		if(asManager.has_value()) {
			args.push_back({"asManager", asManager.value() ? "true" : "false"});
		}
		if(handle.has_value()) {
			args.push_back({"handle", handle.value()});
		}
		if(from.has_value()) {
			args.push_back({"from", std::to_string(from.value())});
		}
		if(count.has_value()) {
			args.push_back({"count", std::to_string(count.value())});
		}

		nlohmann::json result = request(
			"contest.status", args
		);
		std::vector<Submission*> ret;

		if(result.is_null() || !result.is_array()) {
			std::cerr << "codeforces::contest_status(): Codeforces API request failed." << std::endl;
			return std::vector<Submission*>{};
		}

		for(const auto& submission_data : result)
			ret.push_back(new Submission(submission_data));

		return ret;
	}

	inline std::vector<Submission*> contest_status(
		const int& contestId,
		const nlohmann::json& optional_args = {}
	) {
		int valid_args = 0;

		std::optional<bool> asManager = std::nullopt;
		if(
			optional_args.contains("asManager")
			&& optional_args["asManager"].is_boolean()
		) {
			asManager = optional_args["asManager"];

			valid_args++;
		}

		std::optional<std::string> handle = std::nullopt;
		if(
			optional_args.contains("handle")
			&& optional_args["handle"].is_string()
		) {
			handle = optional_args["handle"];

			valid_args++;
		}

		std::optional<int> from = std::nullopt;
		if(
			optional_args.contains("from")
			&& optional_args["from"].is_number_integer()
		) {
			from = optional_args["from"];

			valid_args++;
		}

		std::optional<int> count = std::nullopt;
		if(
			optional_args.contains("count")
			&& optional_args["count"].is_number_integer()
		) {
			count = optional_args["count"];

			valid_args++;
		}

		if(valid_args < optional_args.size()) {
			std::cerr << "codeforces::contest_status() failed: invalid arguments" << std::endl;
			return std::vector<Submission*>{};
		}

		return contest_status(
			contestId,
			asManager,
			handle,
			from,
			count
		);
	}
}
