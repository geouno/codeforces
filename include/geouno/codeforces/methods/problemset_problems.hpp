#pragma once

#include <iostream>
#include <optional>
#include <string>
#include <tuple>
#include <vector>
#include "geouno/codeforces/objects/Problem.hpp"
#include "geouno/codeforces/objects/ProblemStatistics.hpp"
#include "geouno/codeforces/request.hpp"
#include "geouno/third_party/json.hpp"

namespace codeforces {
	inline std::tuple<std::vector<Problem*>, std::vector<ProblemStatistics*>> problemset_problems(
		const std::optional<std::vector<std::string>>& tags = std::nullopt,
		const std::optional<std::string>& problemsetName = std::nullopt
	) {
		std::vector<std::pair<std::string, std::string>> args = {};
		if(tags.has_value()) {
			std::string handles_concat;
			for(size_t i = 0; i < tags -> size(); i++) {
				if(i)
					handles_concat += ";";
				handles_concat += tags -> at(i);
			}
			args.push_back({"tags", handles_concat});
		}
		if(problemsetName.has_value()) {
			args.push_back({"problemsetName", problemsetName.value()});
		}

		nlohmann::json result = request(
			"problemset.problems", args
		);
		std::vector<Problem*> problems;
		std::vector<ProblemStatistics*> problemStatistics;

		if(
			result.is_null()
			|| !(
				result.contains("problems") && result["problems"].is_array()
				&& result.contains("problemStatistics") && result["problemStatistics"].is_array()
			)
		) {
			std::cerr << "codeforces::problemset_problems(): Codeforces API request failed." << std::endl;
			return std::make_tuple(std::vector<Problem*>{}, std::vector<ProblemStatistics*>{});
		}

		for(const auto& problem_data : result["problems"])
			problems.push_back(new Problem(problem_data));
		for(const auto& stats_data : result["problemStatistics"])
			problemStatistics.push_back(new ProblemStatistics(stats_data));

		return std::make_tuple(problems, problemStatistics);
	}

	inline std::tuple<std::vector<Problem*>, std::vector<ProblemStatistics*>> problemset_problems(
		const nlohmann::json& optional_args = {}
	) {
		int valid_args = 0;

		std::optional<std::vector<std::string>> tags = std::nullopt;
		if(
			optional_args.contains("tags")
			&& (
				optional_args["tags"].is_string()
				|| (
					optional_args["tags"].is_array()
					&& std::all_of(
						optional_args["tags"].begin(), optional_args["tags"].end(),
						[] (const nlohmann::json& json_data) {
							return json_data.is_string();
						}
					)
				)
			)
		) {
			tags = {""};
			if(optional_args["tags"].is_string()) {
				std::string tags_string = optional_args["tags"];
				for(char c : tags_string)
					if(c != ';')
						tags.value().back().push_back(c);
					else if(!tags.value().back().empty())
						tags.value().push_back("");

			}
			else {
				tags = {};
				for(const nlohmann::json& handle_data : optional_args["tags"])
					tags.value().push_back(handle_data);
			}

			valid_args++;
		}

		std::optional<std::string> problemsetName = std::nullopt;
		if(
			optional_args.contains("problemsetName")
			&& optional_args["problemsetName"].is_string()
		) {
			problemsetName = optional_args["problemsetName"];

			valid_args++;
		}

		if(valid_args < optional_args.size()) {
			std::cerr << "codeforces::problemset_problems() failed: invalid arguments" << std::endl;
			return std::make_tuple(std::vector<Problem*>{}, std::vector<ProblemStatistics*>{});
		}

		return problemset_problems(
			tags,
			problemsetName
		);
	}
}
