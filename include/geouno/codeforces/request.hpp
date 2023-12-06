#pragma once

#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include <cassert>
#include "geouno/third_party/json.hpp"
#include "geouno/third_party/sha384_and_sha512.hpp"
#include "geouno/utility/curl_get.hpp"

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
