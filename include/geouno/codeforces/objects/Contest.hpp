#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include "geouno/third_party/json.hpp"

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
