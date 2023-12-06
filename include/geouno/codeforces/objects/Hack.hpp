#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include "geouno/codeforces/objects/Party.hpp"
#include "geouno/codeforces/objects/Problem.hpp"
#include "geouno/third_party/json.hpp"

namespace codeforces {
	class Hack {
	public:
		enum verdict_t {
			NULL_VERDICT = 							0,
			HACK_SUCCESSFUL = 						1 << 1,
			HACK_UNSUCCESSFUL = 					1 << 2,
			INVALID_INPUT = 						1 << 3,
			GENERATOR_INCOMPILABLE = 				1 << 4,
			GENERATOR_CRASHED = 					1 << 5,
			IGNORED = 								1 << 6,
			TESTING = 								1 << 7,
			OTHER = 								1 << 8
		};

	private:
		const static std::unordered_map<std::string, verdict_t> verdict_map;

		const static std::unordered_map<verdict_t, std::string> verdict_str_map;

	public:
		int id;
		int64_t creationTimeSeconds;
		Party* hacker;
		Party* defender;
		verdict_t verdict;
		Problem* problem;
		std::string test;

		Hack(
			int _id,
			std::string _index,
			int64_t _creationTimeSeconds,
			Party* _hacker,
			Party* _defender,
			verdict_t _verdict,
			Problem* _problem,
			std::string _test
		) {
			id = _id;
			creationTimeSeconds = _creationTimeSeconds;
			hacker = _hacker;
			defender = _defender;
			verdict = _verdict;
			problem = _problem;
			test = _test;
		}

		Hack(const nlohmann::json& json) {
			try {
				id = json["id"];
				creationTimeSeconds = json["creationTimeSeconds"];
				hacker = new Party(json["hacker"]);
				defender = new Party(json["defender"]);
				verdict = json.contains("verdict") ? verdict_map.at(json["verdict"]) : Hack::NULL_VERDICT;
				problem = new Problem(json["problem"]);
				test = json.contains("test") ? json["test"] : "";
			}
			catch(const nlohmann::json::parse_error& e) {
				std::cerr << "JSON parse error: " << e.what() << std::endl;
			}
		}

		Hack() = default;
		~Hack() { };

		friend std::ostream& operator << (std::ostream& o, const verdict_t var) {
			return o << verdict_str_map.at(var);
		}

		std::string verdict_str() {
			return verdict_str_map.at(verdict);
		}
	};

	inline const std::unordered_map<std::string, Hack::verdict_t> Hack::verdict_map = {
		{"NULL_VERDICT", NULL_VERDICT},
		{"HACK_SUCCESSFUL", HACK_SUCCESSFUL},
		{"HACK_UNSUCCESSFUL", HACK_UNSUCCESSFUL},
		{"INVALID_INPUT", INVALID_INPUT},
		{"GENERATOR_INCOMPILABLE", GENERATOR_INCOMPILABLE},
		{"GENERATOR_CRASHED", GENERATOR_CRASHED},
		{"IGNORED", IGNORED},
		{"TESTING", TESTING},
		{"OTHER", OTHER}
	};

	inline const std::unordered_map<Hack::verdict_t, std::string> Hack::verdict_str_map = {
		{NULL_VERDICT, "NULL_VERDICT"},
		{HACK_SUCCESSFUL, "HACK_SUCCESSFUL"},
		{HACK_UNSUCCESSFUL, "HACK_UNSUCCESSFUL"},
		{INVALID_INPUT, "INVALID_INPUT"},
		{GENERATOR_INCOMPILABLE, "GENERATOR_INCOMPILABLE"},
		{GENERATOR_CRASHED, "GENERATOR_CRASHED"},
		{IGNORED, "IGNORED"},
		{TESTING, "TESTING"},
		{OTHER, "OTHER"}
	};
}
