#pragma once

#include <iostream>
#include <optional>
#include <vector>
#include "geouno/codeforces/methods/contest_standings.hpp"
#include "geouno/codeforces/objects/Contest.hpp"
#include "geouno/codeforces/objects/Problem.hpp"
#include "geouno/codeforces/request.hpp"
#include "geouno/third_party/json.hpp"

namespace codeforces {
	inline std::vector<Problem*> contest_problems(const int& contestId) {
		auto [contest, ret, rows] = contest_standings(contestId);

		return ret;
	}

	inline std::vector<Problem*> contest_problems(Contest* contest) {
		if(!contest -> id) {
			std::cerr << "codeforces::contest_problems(Contest& contest) failed: contest does not have an id." << std::endl;
			return {};
		}

		return contest_problems(contest -> id);
	}
}
