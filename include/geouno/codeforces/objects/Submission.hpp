#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include "geouno/codeforces/objects/Party.hpp"
#include "geouno/codeforces/objects/Problem.hpp"
#include "geouno/third_party/json.hpp"

namespace codeforces {
	class Submission {
	public:
		enum verdict_t {
			NULL_VERDICT = 							0,
			FAILED = 								1 << 0,
			OK = 									1 << 1,
			PARTIAL = 								1 << 2,
			COMPILATION_ERROR = 					1 << 3,
			RUNTIME_ERROR = 						1 << 4,
			WRONG_ANSWER = 							1 << 5,
			PRESENTATION_ERROR = 					1 << 6,
			TIME_LIMIT_EXCEEDED = 					1 << 7,
			MEMORY_LIMIT_EXCEEDED = 				1 << 8,
			IDLENESS_LIMIT_EXCEEDED = 				1 << 9,
			SECURITY_VIOLATED = 					1 << 10,
			CRASHED = 								1 << 11,
			INPUT_PREPARATION_CRASHED = 			1 << 12,
			CHALLENGED = 							1 << 13,
			SKIPPED = 								1 << 14,
			TESTING = 								1 << 15,
			REJECTED = 								1 << 16
		};

	private:
		const static std::unordered_map<std::string, verdict_t> verdict_map;

		const static std::unordered_map<verdict_t, std::string> verdict_str_map;

	public:
		int id;
		int contestId;
		int64_t creationTimeSeconds;
		int64_t relativeTimeSeconds;
		Problem* problem;
		Party* author;
		std::string programmingLanguage;
		verdict_t verdict;
		std::string testset;
		int passedTestCount;
		int timeConsumedMillis;
		int memoryConsumedBytes;
		double points;

		Submission(
			int _id,
			int _contestId,
			int64_t _creationTimeSeconds,
			int64_t _relativeTimeSeconds,
			Problem* _problem,
			Party* _author,
			std::string _programmingLanguage,
			verdict_t _verdict,
			std::string _testset,
			int _passedTestCount,
			int _timeConsumedMillis,
			int _memoryConsumedBytes,
			double _points
		) {
			id = _id;
			contestId = _contestId;
			creationTimeSeconds = _creationTimeSeconds;
			relativeTimeSeconds = _relativeTimeSeconds;
			problem = _problem;
			author = _author;
			programmingLanguage = _programmingLanguage;
			verdict = _verdict;
			testset = _testset;
			passedTestCount = _passedTestCount;
			timeConsumedMillis = _timeConsumedMillis;
			memoryConsumedBytes = _memoryConsumedBytes;
			points = _points;
		}

		Submission(const nlohmann::json& json) {
			try {
				id = json["id"];
				contestId = json.contains("contestId") ? (int) json["contestId"] : 0;
				creationTimeSeconds = json["creationTimeSeconds"];
				relativeTimeSeconds = json["relativeTimeSeconds"];
				problem = new Problem(json["problem"]);
				author = new Party(json["author"]);
				programmingLanguage = json["programmingLanguage"];
				verdict = json.contains("verdict") ? verdict_map.at(json["verdict"]) : NULL_VERDICT;
				testset = json["testset"];
				passedTestCount = json["passedTestCount"];
				timeConsumedMillis = json["timeConsumedMillis"];
				memoryConsumedBytes = json["memoryConsumedBytes"];
				points = json.contains("points") ? (int) json["points"] : -1;
			}
			catch(const nlohmann::json::parse_error& e) {
				std::cerr << "JSON parse error: " << e.what() << std::endl;
			}
		}

		Submission() = default;
		~Submission() { };

		friend std::ostream& operator << (std::ostream& o, const verdict_t var) {
			return o << verdict_str_map.at(var);
		}

		std::string verdict_str() {
			return verdict_str_map.at(verdict);
		}
	};

	inline const std::unordered_map<std::string, Submission::verdict_t> Submission::verdict_map = {
		{"NULL_VERDICT", NULL_VERDICT},
		{"FAILED", FAILED},
		{"OK", OK},
		{"PARTIAL", PARTIAL},
		{"COMPILATION_ERROR", COMPILATION_ERROR},
		{"RUNTIME_ERROR", RUNTIME_ERROR},
		{"WRONG_ANSWER", WRONG_ANSWER},
		{"PRESENTATION_ERROR", PRESENTATION_ERROR},
		{"TIME_LIMIT_EXCEEDED", TIME_LIMIT_EXCEEDED},
		{"MEMORY_LIMIT_EXCEEDED", MEMORY_LIMIT_EXCEEDED},
		{"IDLENESS_LIMIT_EXCEEDED", IDLENESS_LIMIT_EXCEEDED},
		{"SECURITY_VIOLATED", SECURITY_VIOLATED},
		{"CRASHED", CRASHED},
		{"INPUT_PREPARATION_CRASHED", INPUT_PREPARATION_CRASHED},
		{"CHALLENGED", CHALLENGED},
		{"SKIPPED", SKIPPED},
		{"TESTING", TESTING},
		{"REJECTED", REJECTED}
	};

	inline const std::unordered_map<Submission::verdict_t, std::string> Submission::verdict_str_map = {
		{NULL_VERDICT, "NULL_VERDICT"},
		{FAILED, "FAILED"},
		{OK, "OK"},
		{PARTIAL, "PARTIAL"},
		{COMPILATION_ERROR, "COMPILATION_ERROR"},
		{RUNTIME_ERROR, "RUNTIME_ERROR"},
		{WRONG_ANSWER, "WRONG_ANSWER"},
		{PRESENTATION_ERROR, "PRESENTATION_ERROR"},
		{TIME_LIMIT_EXCEEDED, "TIME_LIMIT_EXCEEDED"},
		{MEMORY_LIMIT_EXCEEDED, "MEMORY_LIMIT_EXCEEDED"},
		{IDLENESS_LIMIT_EXCEEDED, "IDLENESS_LIMIT_EXCEEDED"},
		{SECURITY_VIOLATED, "SECURITY_VIOLATED"},
		{CRASHED, "CRASHED"},
		{INPUT_PREPARATION_CRASHED, "INPUT_PREPARATION_CRASHED"},
		{CHALLENGED, "CHALLENGED"},
		{SKIPPED, "SKIPPED"},
		{TESTING, "TESTING"},
		{REJECTED, "REJECTED"}
	};
}
