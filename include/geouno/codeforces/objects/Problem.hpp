#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "geouno/third_party/json.hpp"

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
