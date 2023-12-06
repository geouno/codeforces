#pragma once

#include <algorithm>
#include <iostream>
#include <map>
#include <optional>
#include <ostream>
#include <string>
#include <tuple>
#include <vector>
#include "geouno/codeforces/objects/Contest.hpp"
#include "geouno/codeforces/objects/Problem.hpp"
#include "geouno/codeforces/objects/RanklistRow.hpp"
#include "geouno/codeforces/request.hpp"
#include "geouno/third_party/json.hpp"

namespace codeforces {
	inline std::tuple<Contest*, std::vector<Problem*>, std::vector<RanklistRow*>> contest_standings(
		const int& contestId,
		const std::optional<bool>& asManager = std::nullopt,
		const std::optional<int>& from = std::nullopt,
		const std::optional<int>& count = std::nullopt,
		const std::optional<std::vector<std::string>>& handles = std::nullopt,
		const std::optional<int>& room = std::nullopt,
		const std::optional<bool>& showUnofficial = std::nullopt
	) {
		std::vector<std::pair<std::string, std::string>> args = {
			{"contestId", std::to_string(contestId)}
		};
		if(asManager.has_value()) {
			args.push_back({"asManager", asManager.value() ? "true" : "false"});
		}
		if(from.has_value()) {
			args.push_back({"from", std::to_string(from.value())});
		}
		if(count.has_value()) {
			args.push_back({"count", std::to_string(count.value())});
		}
		if(handles.has_value()) {
			std::string handles_concat;
			for(size_t i = 0; i < handles -> size(); i++) {
				if(i)
					handles_concat += ";";
				handles_concat += handles -> at(i);
			}
			args.push_back({"handles", handles_concat});
		}
		if(room.has_value()) {
			args.push_back({"room", std::to_string(room.value())});
		}
		if(showUnofficial.has_value()) {
			args.push_back({"showUnofficial", showUnofficial.value() ? "true" : "false"});
		}

		nlohmann::json result = request(
			"contest.standings", args
		);
		Contest* contest;
		std::vector<Problem*> problems;
		std::vector<RanklistRow*> rows;

		if(
			result.is_null()
			|| !(
				result.contains("contest")
				&& result.contains("problems") && result["problems"].is_array()
				&& result.contains("rows") && result["rows"].is_array()
			)
		) {
			std::cerr << "codeforces::contest_standings(): Codeforces API request failed." << std::endl;
			return std::make_tuple(nullptr, std::vector<Problem*>{}, std::vector<RanklistRow*>{});
		}

		contest = new Contest(result["contest"]);
		for(const auto& problem_data : result["problems"])
			problems.push_back(new Problem(problem_data));
		for(const auto& row_data : result["rows"])
			rows.push_back(new RanklistRow(row_data));

		return std::make_tuple(contest, problems, rows);
	}

	inline std::tuple<Contest*, std::vector<Problem*>, std::vector<RanklistRow*>> contest_standings(
		const int& contestId,
		const nlohmann::json& optional_args
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

		std::optional<std::vector<std::string>> handles = std::nullopt;
		if(
			optional_args.contains("handles")
			&& (
				optional_args["handles"].is_string()
				|| (
					optional_args["handles"].is_array()
					&& std::all_of(
						optional_args["handles"].begin(), optional_args["handles"].end(),
						[] (const nlohmann::json& json_data) {
							return json_data.is_string();
						}
					)
				)
			)
		) {
			if(optional_args["handles"].is_string()) {
				handles = std::vector<std::string>{""};
				std::string handles_string = optional_args["handles"];
				for(char c : handles_string)
					if(c != ';')
						handles -> back() += c;
					else if(!handles -> back().empty())
						handles -> push_back("");

				if(handles -> back().empty())
					handles -> pop_back();
			}
			else {
				handles = std::vector<std::string>{};
				for(const nlohmann::json& handle_data : optional_args["handles"])
					handles -> push_back(handle_data);
			}

			valid_args++;
		}

		std::optional<int> room = std::nullopt;
		if(
			optional_args.contains("room")
			&& optional_args["room"].is_number_integer()
		) {
			room = optional_args["room"];

			valid_args++;
		}

		std::optional<bool> showUnofficial = std::nullopt;
		if(
			optional_args.contains("showUnofficial")
			&& optional_args["showUnofficial"].is_boolean()
		) {
			showUnofficial = optional_args["showUnofficial"];

			valid_args++;
		}

		if(valid_args < optional_args.size()) {
			std::cerr << "codeforces::contest_standings() failed: invalid arguments" << std::endl;
			return std::make_tuple(nullptr, std::vector<Problem*>{}, std::vector<RanklistRow*>{});
		}

		return contest_standings(
			contestId,
			asManager,
			from,
			count,
			handles,
			room,
			showUnofficial
		);
	}
}
