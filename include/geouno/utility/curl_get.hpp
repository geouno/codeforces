#pragma once

#include <curl/curl.h>
#include <iostream>
#include <memory>
#include <string>

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
