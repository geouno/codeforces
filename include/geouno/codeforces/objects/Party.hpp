#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "geouno/codeforces/objects/Member.hpp"
#include "geouno/third_party/json.hpp"

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
