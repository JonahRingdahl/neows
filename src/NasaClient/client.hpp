#pragma once

#include <cstddef>
#include <curl/curl.h>
#include <string>

class NeoClient {
public:
  NeoClient(const std::string &apiKey);
  ~NeoClient();

  std::string getFeed(const std::string &startDate, const std::string &endDate);
  std::string getNeo(const std::string &asteroidId);

private:
  std::string apiKey_;
  CURL *curl_;

  std::string request(const std::string &url);
  static size_t writeCallback(void *contents, size_t size, size_t nmemb,
                              std::string *buffer);
};
