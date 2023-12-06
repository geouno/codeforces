#pragma once

#include <iostream>
#include <string>
#include "geouno/third_party/json.hpp"

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
