#include "client.hpp"

#include <curl/curl.h>
#include <curl/easy.h>

std::string NeoClient::request(const std::string &url) {
  std::string response;

  curl_easy_setopt(this->curl_, CURLOPT_URL, url.c_str());
  curl_easy_setopt(this->curl_, CURLOPT_WRITEFUNCTION,
                   NeoClient::writeCallback);
  curl_easy_setopt(this->curl_, CURLOPT_WRITEDATA, &response);
  curl_easy_setopt(this->curl_, CURLOPT_FOLLOWLOCATION, 1L);

  CURLcode res = curl_easy_perform(this->curl_);
  if (res != CURLE_OK) {
    return "";
  }

  return response;
}

size_t NeoClient::writeCallback(void *contents, size_t size, size_t nmemb,
                                std::string *buffer) {
  return 0;
}
