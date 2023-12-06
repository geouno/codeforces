#pragma once
// codeforces.hpp amalgamation

#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cstdint>
#include <curl/curl.h>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <optional>
#include <ostream>
#include <random>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

#include "geouno/third_party/json.hpp"

// BlogEntry.hpp


namespace codeforces {
	class BlogEntry {
	public:
		int id;
		std::string originalLocale;
		int64_t creationTimeSeconds;
		std::string authorHandle;
		std::string title;
		std::string content;
		std::string locale;
		int64_t modificationTimeSeconds;
		bool allowViewHistory;
		std::vector<std::string> tags;
		int rating;

		BlogEntry(
			int _id,
			std::string _originalLocale,
			int64_t _creationTimeSeconds,
			std::string _authorHandle,
			std::string _title,
			std::string _content,
			std::string _locale,
			int64_t _modificationTimeSeconds,
			bool _allowViewHistory,
			std::vector<std::string>& _tags,
			int _rating
		) {
			id = _id;
			originalLocale = _originalLocale;
			creationTimeSeconds = _creationTimeSeconds;
			authorHandle = _authorHandle;
			title = _title;
			content = _content;
			locale = _locale;
			modificationTimeSeconds = _modificationTimeSeconds;
			allowViewHistory = _allowViewHistory;
			tags = _tags;
			rating = _rating;
		}

		BlogEntry(const nlohmann::json& json) {
			try {
				id = json["id"];
				originalLocale = json["originalLocale"];
				creationTimeSeconds = json["creationTimeSeconds"];
				authorHandle = json["authorHandle"];
				title = json["title"];
				content = json.contains("content") ? json["content"] : "";
				locale = json["locale"];
				modificationTimeSeconds = json["modificationTimeSeconds"];
				allowViewHistory = (json["allowViewHistory"] == "true");
				tags.clear();
				for(const auto& tag : json["tags"])
					tags.push_back(tag);
				rating = json["rating"];
			}
			catch(const nlohmann::json::parse_error& e) {
				std::cerr << "JSON parse error: " << e.what() << std::endl;
			}
		}

		BlogEntry() = default;
		~BlogEntry() { };
	};
}

// Comment.hpp


namespace codeforces {
	class Comment {
	public:
		int id;
		int64_t creationTimeSeconds;
		std::string commentatorHandle;
		std::string locale;
		std::string text;
		int parentCommentId;
		int rating;

		Comment(
			int _id,
			int64_t _creationTimeSeconds,
			std::string _commentatorHandle,
			std::string _locale,
			std::string _text,
			int _parentCommentId,
			int _rating
		) {
			id = _id;
			creationTimeSeconds = _creationTimeSeconds;
			commentatorHandle = _commentatorHandle;
			locale = _locale;
			text = _text;
			parentCommentId = _parentCommentId;
			rating = _rating;
		}

		Comment(const nlohmann::json& json) {
			try {
				id = json["id"];
				creationTimeSeconds = json["creationTimeSeconds"];
				commentatorHandle = json["commentatorHandle"];
				locale = json["locale"];
				text = json["text"];
				parentCommentId = json.contains("parentCommentId") ? (int) json["parentCommentId"] : 0;
				rating = json["rating"];
			}
			catch(const nlohmann::json::parse_error& e) {
				std::cerr << "JSON parse error: " << e.what() << std::endl;
			}
		}

		Comment() = default;
		~Comment() { };
	};
}

// Contest.hpp


namespace codeforces {
	class Contest {
	public:
		enum type_t {
			CF = 									1 << 0,
			IOI = 									1 << 1,
			ICPC = 									1 << 2
		};
		enum phase_t {
			BEFORE = 								1 << 0,
			CODING = 								1 << 1,
			PENDING_SYSTEM_TEST = 					1 << 2,
			SYSTEM_TEST = 							1 << 3,
			FINISHED = 								1 << 4
		};

	private:
		const static std::unordered_map<std::string, type_t> type_map;
		const static std::unordered_map<std::string, phase_t> phase_map;

		const static std::unordered_map<type_t, std::string> type_str_map;
		const static std::unordered_map<phase_t, std::string> phase_str_map;

	public:
		int id;
		std::string name;
		type_t type;
		phase_t phase;
		bool frozen;
		int64_t durationSeconds;
		int64_t startTimeSeconds;
		int64_t relativeTimeSeconds;
		std::string preparedBy;
		std::string websiteUrl;
		std::string description;
		int difficulty;
		std::string kind;
		std::string icpcRegion;
		std::string country;
		std::string city;
		std::string season;

		Contest(
			int _id,
			const std::string& _name,
			type_t _type,
			phase_t _phase,
			bool _frozen,
			int64_t _durationSeconds,
			int64_t _startTimeSeconds,
			int64_t _relativeTimeSeconds,
			std::string _preparedBy,
			std::string _websiteUrl,
			std::string _description,
			int _difficulty,
			std::string _kind,
			std::string _icpcRegion,
			std::string _country,
			std::string _city,
			std::string _season
		) {
			id = _id;
			name = _name;
			type = _type;
			phase = _phase;
			frozen = _frozen;
			durationSeconds = _durationSeconds;
			startTimeSeconds = _startTimeSeconds;
			relativeTimeSeconds = _relativeTimeSeconds;
			preparedBy = _preparedBy;
			websiteUrl = _websiteUrl;
			description = _description;
			difficulty = _difficulty;
			kind = _kind;
			icpcRegion = _icpcRegion;
			country = _country;
			city = _city;
			season = _season;
		}

		Contest(const nlohmann::json& json) {
			try {
				id = json["id"];
				name = json["name"];
				type = type_map.at(json["type"]);
				phase = phase_map.at(json["phase"]);
				frozen = (json["frozen"] == "true");
				durationSeconds = json["durationSeconds"];
				startTimeSeconds = json.contains("startTimeSeconds") ? (int) json["startTimeSeconds"] : 0;
				relativeTimeSeconds = json.contains("relativeTimeSeconds") ? (int) json["relativeTimeSeconds"] : 0;
				preparedBy = json.contains("preparedBy") ? json["preparedBy"] : "";
				websiteUrl = json.contains("websiteUrl") ? json["websiteUrl"] : "";
				description = json.contains("description") ? json["description"] : "";
				difficulty = json.contains("difficulty") ? (int) json["difficulty"] : 0;
				kind = json.contains("kind") ? json["kind"] : "";
				icpcRegion = json.contains("icpcRegion") ? json["icpcRegion"] : "";
				country = json.contains("country") ? json["country"] : "";
				city = json.contains("city") ? json["city"] : "";
				season = json.contains("season") ? json["season"] : "";
			}
			catch(const nlohmann::json::parse_error& e) {
				std::cerr << "JSON parse error: " << e.what() << std::endl;
			}
		}

		Contest() = default;
		~Contest() { };

		friend std::ostream& operator << (std::ostream& o, const type_t var) {
			return o << type_str_map.at(var);
		}
		friend std::ostream& operator << (std::ostream& o, const phase_t var) {
			return o << phase_str_map.at(var);
		}

		std::string type_str() {
			return type_str_map.at(type);
		}
		std::string phase_str() {
			return phase_str_map.at(phase);
		}

		bool should_be_finished() {
			return relativeTimeSeconds >= durationSeconds;
		}
	};

	inline const std::unordered_map<std::string, Contest::type_t> Contest::type_map = {
		{"CF", CF},
		{"IOI", IOI},
		{"ICPC", ICPC}
	};
	inline const std::unordered_map<std::string, Contest::phase_t> Contest::phase_map = {
		{"BEFORE", BEFORE},
		{"CODING", CODING},
		{"PENDING_SYSTEM_TEST", PENDING_SYSTEM_TEST},
		{"SYSTEM_TEST", SYSTEM_TEST},
		{"FINISHED", FINISHED}
	};

	inline const std::unordered_map<Contest::type_t, std::string> Contest::type_str_map = {
		{CF, "CF"},
		{IOI, "IOI"},
		{ICPC, "ICPC"}
	};
	inline const std::unordered_map<Contest::phase_t, std::string> Contest::phase_str_map = {
		{BEFORE, "BEFORE"},
		{CODING, "CODING"},
		{PENDING_SYSTEM_TEST, "PENDING_SYSTEM_TEST"},
		{SYSTEM_TEST, "SYSTEM_TEST"},
		{FINISHED, "FINISHED"}
	};
}

// Member.hpp


namespace codeforces {
	class Member {
	public:
		std::string handle;
		std::string name;

		Member(
			std::string _handle,
			std::string _name
		) {
			handle = _handle;
			name = _name;
		}
		Member(
			std::string _handle
		) {
			handle = _handle;
			name = "";
		}

		Member(const nlohmann::json& json) {
			try {
				handle = json["handle"];
				name = json.contains("name") ? json["name"] : "";
			}
			catch(const nlohmann::json::parse_error& e) {
				std::cerr << "JSON parse error: " << e.what() << std::endl;
			}
		}

		Member() = default;
		~Member() { };
	};
}

// Party.hpp


namespace codeforces {
	class Party {
	public:
		enum participantType_t {
			CONTESTANT = 							1 << 0,
			PRACTICE = 								1 << 1,
			VIRTUAL = 								1 << 2,
			MANAGER = 								1 << 3,
			OUT_OF_COMPETITION = 					1 << 4
		};

	private:
		const static std::unordered_map<std::string, participantType_t> participantType_map;

		const static std::unordered_map<participantType_t, std::string> participantType_str_map;

	public:
		int contestId;
		std::vector<Member*> members;
		participantType_t participantType;
		int teamId;
		std::string teamName;
		bool ghost;
		int room;
		int64_t startTimeSeconds;

		Party(
			int _contestId,
			std::vector<Member*> _members,
			participantType_t _participantType,
			int _teamId,
			std::string _teamName,
			bool _ghost,
			int _room,
			int64_t _startTimeSeconds
		) {	
			contestId = _contestId;
			members = _members;
			participantType = _participantType;
			teamId = _teamId;
			teamName = _teamName;
			ghost = _ghost;
			room = _room;
			startTimeSeconds = _startTimeSeconds;
		}

		Party(const nlohmann::json& json) {
			try {
				contestId = json.contains("contestId") ? (int) json["contestId"] : 0;
				members.clear();
				for(const auto& member : json["members"])
					members.push_back(new Member(member));
				participantType = participantType_map.at(json["participantType"]);
				teamId = json.contains("teamId") ? (int) json["teamId"] : 0;
				teamName = json.contains("teamName") ? json["teamName"] : "";
				ghost = (json["ghost"] == "true");
				room = json.contains("room") ? (int) json["room"] : 0;
				startTimeSeconds = json.contains("startTimeSeconds") ? (int) json["startTimeSeconds"] : 0;
			}
			catch(const nlohmann::json::parse_error& e) {
				std::cerr << "JSON parse error: " << e.what() << std::endl;
			}
		}

		Party() = default;
		~Party() { };

		friend std::ostream& operator << (std::ostream& o, const participantType_t var) {
			return o << participantType_str_map.at(var);
		}

		std::string participantType_str() {
			return participantType_str_map.at(participantType);
		}
	};

	inline const std::unordered_map<std::string, Party::participantType_t> Party::participantType_map = {
		{"CONTESTANT", CONTESTANT},
		{"PRACTICE", PRACTICE},
		{"VIRTUAL", VIRTUAL},
		{"MANAGER", MANAGER},
		{"OUT_OF_COMPETITION", OUT_OF_COMPETITION}
	};

	inline const std::unordered_map<Party::participantType_t, std::string> Party::participantType_str_map = {
		{CONTESTANT, "CONTESTANT"},
		{PRACTICE, "PRACTICE"},
		{VIRTUAL, "VIRTUAL"},
		{MANAGER, "MANAGER"},
		{OUT_OF_COMPETITION, "OUT_OF_COMPETITION"}
	};
}

// Problem.hpp


namespace codeforces {
	class Problem {
	public:
		enum type_t {
			PROGRAMMING = 							1 << 0,
			QUESTION = 								1 << 0
		};

	private:
		const static std::unordered_map<std::string, type_t> type_map;

		const static std::unordered_map<type_t, std::string> type_str_map;

	public:
		int contestId;
		std::string problemsetName;
		std::string index;
		std::string name;
		type_t type;
		double points;
		int rating;
		std::vector<std::string> tags;

		Problem(
			int _contestId,
			const std::string& _problemsetName,
			const std::string& _index,
			const std::string& _name,
			type_t _type,
			double _points,
			int _rating,
			const std::vector<std::string>& _tags
		) {
			contestId = _contestId;
			problemsetName = _problemsetName;
			index = _index;
			name = _name;
			type = _type;
			points = _points;
			rating = _rating;
			tags = _tags;
		}

		Problem(const nlohmann::json& json) {
			try {
				contestId = json.contains("contestId") ? (int) json["contestId"] : -1;
				problemsetName = json.contains("problemsetName") ? json["problemsetName"] : "";
				index = json["index"];
				name = json["name"];
				type = type_map.at(json["type"]);
				points = json.contains("points") ? (int) json["points"] : -1;
				rating = json.contains("rating") ? (int) json["rating"] : -1;
				tags.clear();
				for(const auto& tag : json["tags"])
					tags.push_back(tag);
			}
			catch(const nlohmann::json::parse_error& e) {
				std::cerr << "JSON parse error: " << e.what() << std::endl;
			}
		}

		Problem() = default;
		~Problem() { };

		friend std::ostream& operator << (std::ostream& o, const type_t var) {
			return o << type_str_map.at(var);
		}

		std::string type_str() {
			return type_str_map.at(type);
		}

		friend std::ostream& operator << (std::ostream& o, const Problem& p) {
			o << "[";
			o << p.contestId << ", ";
			o << p.problemsetName << ", ";
			o << p.index << ", ";
			o << p.name << ", ";
			o << type_str_map.at(p.type) << ", ";
			o << p.points << ", ";
			o << p.rating << ", ";

			o << "{";
			for(auto& t : p.tags)
				o << t << ", ";
			return o << "} ]";
		}
	};

	inline const std::unordered_map<std::string, Problem::type_t> Problem::type_map = {
		{"PROGRAMMING", PROGRAMMING},
		{"QUESTION", QUESTION}
	};

	inline const std::unordered_map<Problem::type_t, std::string> Problem::type_str_map = {
		{PROGRAMMING, "PROGRAMMING"},
		{QUESTION, "QUESTION"}
	};
}

// Hack.hpp


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

// ProblemResult.hpp


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

// ProblemStatistics.hpp


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

// RanklistRow.hpp


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

// RatingChange.hpp


namespace codeforces {
	class RatingChange {
	public:
		int contestId;
		std::string contestName;
		std::string handle;
		int rank;
		int64_t ratingUpdateTimeSeconds;
		int oldRating;
		int newRating;

		RatingChange(
			int _contestId,
			std::string _contestName,
			std::string _handle,
			int _rank,
			int64_t _ratingUpdateTimeSeconds,
			int _oldRating,
			int _newRating
		) {
			contestId = _contestId;
			contestName = _contestName;
			handle = _handle;
			rank = _rank;
			ratingUpdateTimeSeconds = _ratingUpdateTimeSeconds;
			oldRating = _oldRating;
			newRating = _newRating;
		}

		RatingChange(const nlohmann::json& json) {
			try {
				contestId = json["contestId"];
				contestName = json["contestName"];
				handle = json["handle"];
				rank = json["rank"];
				ratingUpdateTimeSeconds = json["ratingUpdateTimeSeconds"];
				oldRating = json["oldRating"];
				newRating = json["newRating"];
			}
			catch(const nlohmann::json::parse_error& e) {
				std::cerr << "JSON parse error: " << e.what() << std::endl;
			}
		}

		RatingChange() = default;
		~RatingChange() { };
	};
}

// RecentAction.hpp


namespace codeforces {
	class RecentAction {
	public:
		int64_t timeSeconds;
		BlogEntry* blogEntry;
		Comment* comment;

		RecentAction(
			int64_t _timeSeconds,
			BlogEntry* _blogEntry,
			Comment* _comment
		) {
			timeSeconds = _timeSeconds;
			blogEntry = _blogEntry;
			comment = _comment;
		}

		RecentAction(const nlohmann::json& json) {
			try {
				timeSeconds = json["timeSeconds"];
				blogEntry = json.contains("blogEntry") ? new BlogEntry(json["blogEntry"]) : nullptr;
				comment = json.contains("comment") ? new Comment(json["comment"]) : nullptr;
			}
			catch(const nlohmann::json::parse_error& e) {
				std::cerr << "JSON parse error: " << e.what() << std::endl;
			}
		}

		RecentAction() = default;
		~RecentAction() { };
	};
}

// Submission.hpp


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

// User.hpp


namespace codeforces {
	class User {
	public:
		std::string handle;
		std::string email;
		std::string vkId;
		std::string openId;
		std::string firstName;
		std::string lastName;
		std::string country;
		std::string city;
		std::string organization;
		int contribution;
		std::string rank;
		int rating;
		std::string maxRank;
		int maxRating;
		int64_t lastOnlineTimeSeconds;
		int64_t registrationTimeSeconds;
		int friendOfCount;
		std::string avatar;
		std::string titlePhoto;

		User(
			std::string _handle,
			std::string _email,
			std::string _vkId,
			std::string _openId,
			std::string _firstName,
			std::string _lastName,
			std::string _country,
			std::string _city,
			std::string _organization,
			int _contribution,
			std::string _rank,
			int _rating,
			std::string _maxRank,
			int _maxRating,
			int64_t _lastOnlineTimeSeconds,
			int64_t _registrationTimeSeconds,
			int _friendOfCount,
			std::string _avatar,
			std::string _titlePhoto
		) {
			handle = _handle;
			email = _email;
			vkId = _vkId;
			openId = _openId;
			firstName = _firstName;
			lastName = _lastName;
			country = _country;
			city = _city;
			organization = _organization;
			contribution = _contribution;
			rank = _rank;
			rating = _rating;
			maxRank = _maxRank;
			maxRating = _maxRating;
			lastOnlineTimeSeconds = _lastOnlineTimeSeconds;
			registrationTimeSeconds = _registrationTimeSeconds;
			friendOfCount = _friendOfCount;
			avatar = _avatar;
			titlePhoto = _titlePhoto;
		}

		User(const nlohmann::json& json) {
			try {
				handle = json["handle"];
				email = json.contains("email") ? json["email"] : "";
				vkId = json.contains("vkId") ? json["vkId"] : "";
				openId = json.contains("openId") ? json["openId"] : "";
				firstName = json.contains("firstName") ? json["firstName"] : "";
				lastName = json.contains("lastName") ? json["lastName"] : "";
				country = json.contains("country") ? json["country"] : "";
				city = json.contains("city") ? json["city"] : "";
				organization = json.contains("organization") ? json["organization"] : "";
				contribution = json["contribution"];
				rank = json["rank"];
				rating = json["rating"];
				maxRank = json["maxRank"];
				maxRating = json["maxRating"];
				lastOnlineTimeSeconds = json["lastOnlineTimeSeconds"];
				registrationTimeSeconds = json["registrationTimeSeconds"];
				friendOfCount = json["friendOfCount"];
				avatar = json["avatar"];
				titlePhoto = json["titlePhoto"];
			}
			catch(const nlohmann::json::parse_error& e) {
				std::cerr << "JSON parse error: " << e.what() << std::endl;
			}
		}

		User() = default;
		~User() { };
	};
}

// sha384_and_sha512.hpp
// INSPIRATION TAKEN FROM https://github.com/autobotoptimusprime/cc_hashlib/blob/main/sha384_and_sha512.hpp

namespace ccat {

using std::uint16_t;
using std::uint32_t;
using std::uint64_t;
using std::size_t;

auto inline is_little_endian() -> bool {
  uint16_t __i = 0x0100; // 256
  return *reinterpret_cast<unsigned char *>(&__i) == 0;
}

namespace hashlib {

class base_of_sha384_and_sha512 {
public:
	using byte = unsigned char;
	base_of_sha384_and_sha512() = default;
	// added constructor
	explicit base_of_sha384_and_sha512(const std::string& s) : __seq(s.begin(), s.end()) {}
	base_of_sha384_and_sha512(const base_of_sha384_and_sha512&) = delete;
	base_of_sha384_and_sha512(base_of_sha384_and_sha512&& other) noexcept : __seq(std::move(other.__seq)) {}
	auto operator= (const base_of_sha384_and_sha512&) ->base_of_sha384_and_sha512& = delete;
	auto operator= (base_of_sha384_and_sha512&& other) noexcept ->base_of_sha384_and_sha512& {
		if (std::addressof(other) != this) {
			__seq = std::move(other.__seq);
		}
		return *this;
	}
	virtual ~base_of_sha384_and_sha512(){};
//to be implemented:
	virtual auto get_init_magic_nums() -> std::array<uint64_t, 8> = 0;
	virtual auto get_result_size() ->size_t = 0;
//
	auto hexdigest() ->std::string {
		std::stringstream _ss;
		_ss << std::hex;
		auto result = digest();
		std::for_each(result.begin(), std::next(result.begin(), get_result_size() / 8), [&_ss](uint64_t i) -> void {
			for (size_t _{}; _ < 8; ++_) {
				uint16_t tmp = reinterpret_cast<byte*>(&i)[is_little_endian() ? 7 - _ : _];
				// avoid insertion of null characters
				if(tmp < 0x10)
					_ss << '0';
				_ss << tmp;
			}
		});
		return _ss.str();
	}
	auto digest() -> std::array<uint64_t, 8> {
		__extend_to_big_endian_N1024bits();
		std::array<uint64_t, 8> magic_nums = get_init_magic_nums(), _H{};
		static std::array<uint64_t, 80> K{
				0x428a2f98d728ae22u, 0x7137449123ef65cdu, 0xb5c0fbcfec4d3b2fu, 0xe9b5dba58189dbbcu,
				0x3956c25bf348b538u, 0x59f111f1b605d019u, 0x923f82a4af194f9bu, 0xab1c5ed5da6d8118u,
				0xd807aa98a3030242u, 0x12835b0145706fbeu, 0x243185be4ee4b28cu, 0x550c7dc3d5ffb4e2u,
				0x72be5d74f27b896fu, 0x80deb1fe3b1696b1u, 0x9bdc06a725c71235u, 0xc19bf174cf692694u,
				0xe49b69c19ef14ad2u, 0xefbe4786384f25e3u, 0x0fc19dc68b8cd5b5u, 0x240ca1cc77ac9c65u,
				0x2de92c6f592b0275u, 0x4a7484aa6ea6e483u, 0x5cb0a9dcbd41fbd4u, 0x76f988da831153b5u,
				0x983e5152ee66dfabu, 0xa831c66d2db43210u, 0xb00327c898fb213fu, 0xbf597fc7beef0ee4u,
				0xc6e00bf33da88fc2u, 0xd5a79147930aa725u, 0x06ca6351e003826fu, 0x142929670a0e6e70u,
				0x27b70a8546d22ffcu, 0x2e1b21385c26c926u, 0x4d2c6dfc5ac42aedu, 0x53380d139d95b3dfu,
				0x650a73548baf63deu, 0x766a0abb3c77b2a8u, 0x81c2c92e47edaee6u, 0x92722c851482353bu,
				0xa2bfe8a14cf10364u, 0xa81a664bbc423001u, 0xc24b8b70d0f89791u, 0xc76c51a30654be30u,
				0xd192e819d6ef5218u, 0xd69906245565a910u, 0xf40e35855771202au, 0x106aa07032bbd1b8u,
				0x19a4c116b8d2d0c8u, 0x1e376c085141ab53u, 0x2748774cdf8eeb99u, 0x34b0bcb5e19b48a8u,
				0x391c0cb3c5c95a63u, 0x4ed8aa4ae3418acbu, 0x5b9cca4f7763e373u, 0x682e6ff3d6b2b8a3u,
				0x748f82ee5defb2fcu, 0x78a5636f43172f60u, 0x84c87814a1f0ab72u, 0x8cc702081a6439ecu,
				0x90befffa23631e28u, 0xa4506cebde82bde9u, 0xbef9a3f7b2c67915u, 0xc67178f2e372532bu,
				0xca273eceea26619cu, 0xd186b8c721c0c207u, 0xeada7dd6cde0eb1eu, 0xf57d4f7fee6ed178u,
				0x06f067aa72176fbau, 0x0a637dc5a2c898a6u, 0x113f9804bef90daeu, 0x1b710b35131c471bu,
				0x28db77f523047d84u, 0x32caab7b40c72493u, 0x3c9ebe0a15c9bebcu, 0x431d67c49c100d4cu,
				0x4cc5d4becb3e42b6u, 0x597f299cfc657e2au, 0x5fcb6fab3ad6faecu, 0x6c44198c4a475817u
		};
		for (size_t _{}; _ < __seq.size() / 128; ++_) {
			auto offset = _ * 128;
			auto _extent_seq_chunk = __extend_128bytes_to_640bytes(offset);
			_H = magic_nums;
#if defined(__cplusplus) && __cplusplus >= 201703L || defined(_MSVC_LANG) && _MSVC_LANG >= 201703L
			auto& [a, b, c, d, e, f, g, h] = _H;
#else
			auto &a = _H[0], &b = _H[1], &c = _H[2], &d = _H[3], &e = _H[4], &f = _H[5], &g = _H[6], &h = _H[7];
#endif
			for (size_t i{}; i < 80; ++i) {
				auto _S1 = __rrotate(e, 14) ^ __rrotate(e, 18) ^ __rrotate(e, 41);
				auto _ch = (e & f) ^ ((~e) & g);
				auto _w = __cvt_byte8_to_uint64_t(&_extent_seq_chunk[i * 8]);
				auto _S0 = __rrotate(a, 28) ^ __rrotate(a, 34) ^ __rrotate(a, 39);
				auto _maj = (a & b) ^ (a & c) ^ (b & c);
				auto _Forml = h + _S1 + _ch + K[i] + _w;
				d += _Forml;
				h = _Forml + _S0 + _maj;
				auto tmp = _H[7];
				for (size_t j = 7; j > 0; --j) _H[j] = _H[j - 1];
				_H[0] = tmp;
			}
			for (size_t j{}; j < 8; ++j) magic_nums[j] += _H[j];
		}
		return magic_nums;
	}
	// auto update(const std::string& str) ->base_of_sha384_and_sha512& {
	// 	std::copy(str.begin(), str.end(), std::back_inserter(__seq));
	// 	return *this;
	// }
	// xd
	void update(const std::string& str) {
		__seq = std::vector<byte>(str.begin(), str.end());
	}
	auto operator>>(std::string& str) -> void {
		str = hexdigest();
		clear();
	}
	auto operator<<(const std::string& str) ->base_of_sha384_and_sha512& {
		update(str);
		return *this;
	}
	auto clear() -> void {
		__seq.clear();
	}
	auto empty() -> bool {
		return __seq.empty();
	}
protected:
	auto __extend_128bytes_to_640bytes(size_t _offset) -> std::array<byte, 640> {
		std::array<byte, 640> result{};
		size_t i{};
		for (; i < 128; ++i) result[i] = __seq[i + _offset];
		while (i < 640) {
			auto _s0 = __cvt_byte8_to_uint64_t(&result[i - 15 * 8]);
			auto _s1 = __cvt_byte8_to_uint64_t(&result[i - 2 * 8]);
			auto _s2 = __cvt_byte8_to_uint64_t(&result[i - 16 * 8]);
			auto _s3 = __cvt_byte8_to_uint64_t(&result[i - 7 * 8]);
			_s0 = __rrotate(_s0, 1) ^ __rrotate(_s0, 8) ^ (_s0 >> 7);
			_s1 = __rrotate(_s1, 19) ^ __rrotate(_s1, 61) ^ (_s1 >> 6);
			auto __cvt_bytes = __cvt_uint64_t_to_big_endian_byte8(_s0 + _s1 + _s2 + _s3);
			for (size_t j{}; j < 8; ++j)
				result[i++] = __cvt_bytes[j];
		}
		return result;
	}
	auto __extend_to_big_endian_N1024bits() -> void {
		uint64_t src_size_unit_bits = __seq.size() * 8;
		__seq.emplace_back('\x80');
		size_t insert_0_index = __seq.size();
		auto src_size_ = reinterpret_cast<byte*>(&src_size_unit_bits);
		for (size_t i{}; i < 16; ++i) {
			__seq.emplace_back(i < 8 ? '\0' : src_size_[is_little_endian() ? 7 - i + 8 : i - 8]);
		}
		while (__seq.size() % 128) {
			__seq.emplace(std::next(__seq.begin(), insert_0_index), '\0');
		}
	}
	auto __cvt_byte8_to_uint64_t(byte* b) -> uint64_t {
		uint64_t result{0};
		for (size_t i{}; i < 8; ++i) {
			result += uint64_t(b[7 - i]) << i * 8;
		}
		return result;
	}
	auto __cvt_uint64_t_to_big_endian_byte8(uint64_t _ui64) -> std::array<byte, 8> {
		std::array<byte, 8> result{};
		for (size_t i{}; i < 8; ++i) {
			result[i] = reinterpret_cast<byte*>(&_ui64)[is_little_endian() ? 7 - i : i];
		}
		return result;
	}
	constexpr auto __rrotate(uint64_t _ui64, size_t n) -> uint64_t {
		return (_ui64 >> n) | (_ui64 << (64 - n));
	}
	std::vector<byte> __seq;
};



class sha512 : public base_of_sha384_and_sha512 {
public:
	using base_of_sha384_and_sha512::base_of_sha384_and_sha512;
	constexpr static size_t result_length = 64;//unit: bytes
	auto get_init_magic_nums() -> std::array<uint64_t, 8> override {
		return {
			0x6a09e667f3bcc908u, 0xbb67ae8584caa73bu, 
			0x3c6ef372fe94f82bu, 0xa54ff53a5f1d36f1u,
			0x510e527fade682d1u, 0x9b05688c2b3e6c1fu,
			0x1f83d9abfb41bd6bu, 0x5be0cd19137e2179u
		};
	}
	auto get_result_size() ->size_t override {
		return result_length;
	}
};


class sha384 : public base_of_sha384_and_sha512 {
public:
	using base_of_sha384_and_sha512::base_of_sha384_and_sha512;
	constexpr static size_t result_length = 48;//unit: bytes
	auto get_init_magic_nums() -> std::array<uint64_t, 8> override {
		return {
			0xcbbb9d5dc1059ed8u, 0x629a292a367cd507u, 
			0x9159015a3070dd17u, 0x152fecd8f70e5939u, 
			0x67332667ffc00b31u, 0x8eb44a8768581511u,
			0xdb0c2e0d64f98fa7u, 0x47b5481dbefa4fa4u
		};
	}
	auto get_result_size() ->size_t override {
		return result_length;
	}
};
}
}

// curl_get.hpp


static size_t curl_WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
	size_t total_size = size * nmemb;
	output -> append(static_cast<char*>(contents), total_size);
	return total_size;
}

inline std::string curl_get(const std::string& url) {
	static std::unique_ptr<CURL, void(*)(CURL*)> curl_handle(nullptr, [] (CURL* handle) {
		if(handle)
			curl_easy_cleanup(handle);
	});

	if(!curl_handle) {
		curl_handle.reset(curl_easy_init());
		curl_easy_setopt(curl_handle.get(), CURLOPT_WRITEFUNCTION, curl_WriteCallback);

		if(!curl_handle) {
			std::cerr << "Failed to reser cURL handle.\n";
			return "";
		}
	}

	std::string response;
	curl_easy_setopt(curl_handle.get(), CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl_handle.get(), CURLOPT_WRITEDATA, &response);

	CURLcode curl_exit_code = curl_easy_perform(curl_handle.get());
	if(curl_exit_code != CURLE_OK) {
		std::cerr << "Failed to perform the request: " << curl_easy_strerror(curl_exit_code) << std::endl;
		response = "";
	}

	return std::move(response);
}

// request.hpp


namespace codeforces {
	[[maybe_unused]] static void set_credentials(std::string, std::string);
	[[maybe_unused]] static void unset_credentials();

	[[maybe_unused]] static nlohmann::json request(std::string, std::vector<std::pair<std::string, std::string>>);
	[[maybe_unused]] static nlohmann::json authorized_request(std::string, std::vector<std::pair<std::string, std::string>>);
	[[maybe_unused]] static nlohmann::json unauthorized_request(std::string, std::vector<std::pair<std::string, std::string>>);


	static bool credentials_set = false;
	static std::string API_key, API_key_secret;

	static void set_credentials(std::string _API_key, std::string _API_key_secret) {
		API_key = _API_key, API_key_secret = _API_key_secret;
		credentials_set = true;
	}

	static void unset_credentials() {
		credentials_set = false;
	}


	static std::mt19937 rng((uint32_t) std::chrono::steady_clock::now().time_since_epoch().count());

	static nlohmann::json request(std::string method, std::vector<std::pair<std::string, std::string>> parameters) {
		if(credentials_set)
			return authorized_request(method, parameters);
		else
			return unauthorized_request(method, parameters);
	}

	static nlohmann::json authorized_request(std::string method, std::vector<std::pair<std::string, std::string>> parameters) {
		assert(credentials_set == true);

		parameters.push_back({"apiKey", API_key});
		auto TSE = std::chrono::system_clock::now().time_since_epoch();
		parameters.push_back({"time", std::to_string(std::chrono::duration_cast<std::chrono::seconds>(TSE).count())});
		int param_count = parameters.size();

		std::string six_digit_rand(6, 0);
		for(int i = 0; i < 6; i++)
			six_digit_rand[i] = '0' + (rng() % 10);

		std::string to_be_hashed = six_digit_rand + "/" + method + "?";
		sort(parameters.begin(), parameters.end());
		for(int i = 0; i < param_count; i++) {
			if(i > 0)
				to_be_hashed += "&";
			to_be_hashed += parameters[i].first + "=" + parameters[i].second;
		}
		to_be_hashed += "#" + API_key_secret;

		static ccat::hashlib::sha512 sha512_handle;
		sha512_handle.update(to_be_hashed);
		std::string apiSig = sha512_handle.hexdigest();

		std::string url = "https://codeforces.com/api/" + method + "?";
		for(int i = 0; i < param_count; i++) {
			if(i > 0)
				url += "&";
			url += parameters[i].first + "=" + parameters[i].second;
		}
		url += "&apiSig=" + six_digit_rand + apiSig;

		std::cout << "authorized_request url: " << url << std::endl;

		std::string api_response = curl_get(url);

		nlohmann::json ret{};
		try {
			ret = nlohmann::json::parse(api_response);

			if(!ret.contains("status")) {
				std::cerr << "Error in CF API request" << std::endl;
				return {};
			}

			if(ret["status"] == "FAILED") {
				std::cerr << "Request failed with comment: " << ret["comment"] << std::endl;
				return {};
			}

			return ret["result"];
		}
		catch(const nlohmann::json::parse_error& e) {
			std::cerr << "JSON parse error: " << e.what() << std::endl;
			return {};
		}
	}

	static nlohmann::json unauthorized_request(std::string method, std::vector<std::pair<std::string, std::string>> parameters) {
		int param_count = parameters.size();

		std::string url = "https://codeforces.com/api/" + method + "?";
		for(int i = 0; i < param_count; i++) {
			if(i > 0)
				url += "&";
			url += parameters[i].first + "=" + parameters[i].second;
		}

		std::string api_response = curl_get(url);

		nlohmann::json ret{};
		try {
			ret = nlohmann::json::parse(api_response);

			if(!ret.contains("status")) {
				std::cerr << "Error in CF API request" << std::endl;
				return {};
			}

			if(ret["status"] == "FAILED")  {
				std::cerr << "Request failed with comment: " << ret["comment"] << std::endl;
				return {};
			}

			return ret["result"];
		}
		catch(const nlohmann::json::parse_error& e) {
			std::cerr << "JSON parse error: " << e.what() << std::endl;
			return {};
		}
	}
}

// blogEntry_comments.hpp


namespace codeforces {
	inline std::vector<Comment*> blogEntry_comments(const int& blogEntryId) {
		nlohmann::json result = request(
			"blogEntry.comments", {
				{"blogEntryId", std::to_string(blogEntryId)}
			}
		);
		std::vector<Comment*> ret;

		if(result.is_null() || !result.is_array()) {
			std::cerr << "codeforces::blogEntry_comments(): Codeforces API request failed." << std::endl;
			return std::vector<Comment*>{};
		}

		for(const auto& comment_data : result)
			ret.push_back(new Comment(comment_data));

		return ret;
	}
}

// blogEntry_view.hpp


namespace codeforces {
	inline BlogEntry* blogEntry_view(const int& blogEntryId) {
		nlohmann::json result = request(
			"blogEntry.view", {
				{"blogEntryId", std::to_string(blogEntryId)}
			}
		);

		if(result.is_null()) {
			std::cerr << "codeforces::blogEntry_view(): Codeforces API request failed." << std::endl;
			return nullptr;
		}

		return new BlogEntry(result);
	}
}

// contest_hacks.hpp


namespace codeforces {
	inline std::vector<Hack*> contest_hacks(const int& contestId, const std::optional<bool>& asManager = std::nullopt) {
		nlohmann::json result = request(
			"contest.hacks", {
				{"contestId", std::to_string(contestId)},
				{"asManager", (asManager.has_value() && asManager.value()) ? "true" : "false"}
			}
		);
		std::vector<Hack*> ret;

		if(result.is_null() || !result.is_array()) {
			std::cerr << "codeforces::contest_hacks(): Codeforces API request failed." << std::endl;
			return std::vector<Hack*>{};
		}

		for(const auto& hack_data : result)
			ret.push_back(new Hack(hack_data));

		return ret;
	}
}

// contest_list.hpp


namespace codeforces {
	inline std::vector<Contest*> contest_list(const bool gym = false) {
		nlohmann::json result = request(
			"contest.list", {
				{"gym", gym ? "true" : "false"}
			}
		);
		std::vector<Contest*> ret;

		if(result.is_null() || !result.is_array()) {
			std::cerr << "codeforces::contest_list(): Codeforces API request failed." << std::endl;
			return std::vector<Contest*>{};
		}

		for(const auto& contest_data : result)
			ret.push_back(new Contest(contest_data));

		return ret;
	}
}

// contest_standings.hpp


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

// contest_problems.hpp


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

// contest_ratingChanges.hpp


namespace codeforces {
	inline std::vector<RatingChange*> contest_ratingChanges(const int& contestId) {
		nlohmann::json result = request(
			"blogEntry.comments", {
				{"contestId", std::to_string(contestId)}
			}
		);
		std::vector<RatingChange*> ret;

		if(result.is_null() || !result.is_array()) {
			std::cerr << "codeforces::contest_ratingChanges(): Codeforces API request failed." << std::endl;
			return std::vector<RatingChange*>{};
		}

		for(const auto& comment_data : result)
			ret.push_back(new RatingChange(comment_data));

		return ret;
	}
}

// contest_status.hpp


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

// problemset_problems.hpp


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

// problemset_recentStatus.hpp


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

// recentActions.hpp


namespace codeforces {
	inline std::vector<RecentAction*> contest_recentActions(const int& maxCount) {
		nlohmann::json result = request(
			"recentActions", {
				{"maxCount", std::to_string(maxCount)}
			}
		);
		std::vector<RecentAction*> ret;

		if(result.is_null() || !result.is_array()) {
			std::cerr << "codeforces::contest_recentActions(): Codeforces API request failed." << std::endl;
			return std::vector<RecentAction*>{};
		}

		for (const auto& action_data : result)
			ret.push_back(new RecentAction(action_data));

		return ret;
	}
}

// user_blogEntries.hpp


namespace codeforces {
	inline std::vector<BlogEntry*> user_blogEntries(const std::string& handle) {
		nlohmann::json result = request(
			"user.blogEntries", {
				{"handle", handle}
			}
		);
		std::vector<BlogEntry*> ret;

		if(result.is_null() || !result.is_array()) {
			std::cerr << "codeforces::user_blogEntries(): Codeforces API request failed." << std::endl;
			return std::vector<BlogEntry*>{};
		}

		for (const auto& entry_data : result)
			ret.push_back(new BlogEntry(entry_data));

		return ret;
	}
}

// user_friends.hpp


namespace codeforces {
	inline std::vector<std::string> user_friends(
		const bool onlyOnline = false
	) {
		nlohmann::json result = authorized_request(
			"user.friends", {
				{"onlyOnline", onlyOnline ? "true" : "false"}
			}
		);
		std::vector<std::string> ret;

		if(result.is_null() || !result.is_array()) {
			std::cerr << "codeforces::user_friends(): Codeforces API request failed." << std::endl;
			return std::vector<std::string>{};
		}

		for (const auto& friend_data : result)
			ret.push_back(friend_data);

		return ret;
	}
}

// user_info.hpp


namespace codeforces {
	inline std::vector<User*> user_info(const std::vector<std::string>& handles) {
		std::string handles_string;
		for(size_t i = 0; i < handles.size(); i++) {
			if(i > 0)
				handles_string += ";";
			handles_string += handles[i];
		}

		nlohmann::json result = request(
			"user.info", {
				{"handles", handles_string}
			}
		);
		std::vector<User*> ret;

		if(result.is_null() || !result.is_array()) {
			std::cerr << "codeforces::user_info(): Codeforces API request failed." << std::endl;
			return std::vector<User*>{};
		}

		for (const auto& user_data : result)
			ret.push_back(new User(user_data));

		return ret;
	}
}

// user_ratedList.hpp


namespace codeforces {
	inline std::vector<User*> user_ratedList(
		const std::optional<bool>& activeOnly = std::nullopt,
		const std::optional<bool>& includeRetired = std::nullopt,
		const std::optional<int>& contestId = std::nullopt
	) {
		std::vector<std::pair<std::string, std::string>> args = {};
		if(activeOnly.has_value()) {
			args.push_back({"activeOnly", activeOnly.value() ? "true" : "false"});
		}
		if(includeRetired.has_value()) {
			args.push_back({"includeRetired", includeRetired.value() ? "true" : "false"});
		}
		if(contestId.has_value()) {
			args.push_back({"contestId", std::to_string(contestId.value())});
		}

		nlohmann::json result = request(
			"user.ratedList", args
		);
		std::vector<User*> ret;

		if(result.is_null() || !result.is_array()) {
			std::cerr << "codeforces::user_ratedList(): Codeforces API request failed." << std::endl;
			return std::vector<User*>{};
		}

		for (const auto& user_data : result)
			ret.push_back(new User(user_data));

		return ret;
	}
}

// user_rating.hpp


namespace codeforces {
	inline std::vector<RatingChange*> user_rating(const std::string& handle) {
		nlohmann::json result = request(
			"user.rating", {
				{"handle", handle}
			}
		);
		std::vector<RatingChange*> ret;
		
		if(result.is_null() || !result.is_array()) {
			std::cerr << "codeforces::user_rating(): Codeforces API request failed." << std::endl;
			return std::vector<RatingChange*>{};
		}

		for (const auto& change_data : result)
			ret.push_back(new RatingChange(change_data));

		return ret;
	}
}

// user_status.hpp


namespace codeforces {
	inline std::vector<Submission*> user_status(const std::string& handle) {
		nlohmann::json result = request(
			"user.status", {
				{"handle", handle}
			}
		);
		std::vector<Submission*> ret;

		if(result.is_null() || !result.is_array()) {
			std::cerr << "codeforces::user_status(): Codeforces API request failed." << std::endl;
			return std::vector<Submission*>{};
		}

		for (const auto& submission : result)
			ret.push_back(new Submission(submission));

		return ret;
	}
}

// codeforces.hpp

