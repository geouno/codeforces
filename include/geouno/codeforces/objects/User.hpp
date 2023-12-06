#pragma once

#include <iostream>
#include <string>
#include "geouno/third_party/json.hpp"

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
