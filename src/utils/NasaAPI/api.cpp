#include "api.hpp"
#include <httplib.h>
#include <iostream>

NasaAPI::NasaAPI() {}

NasaAPI::NasaAPI(std::string key) {
  this->key = key;
}

nlohmann::json NasaAPI::GetAPI() {
  httplib::Client cli("https://api.nasa.gov");
  cli.set_follow_location(true);
  
  // Using demo dates as default for now
  std::string req = "/neo/rest/v1/feed?start_date=2015-09-07&end_date=2015-09-08&api_key=" + this->key;
  
  auto res = cli.Get(req);
  if (res && res->status == 200) {
    return nlohmann::json::parse(res->body);
  } else {
    std::cerr << "Failed to make request! Status: " << (res ? std::to_string(res->status) : "null") << '\n';
    return nlohmann::json();
  }
}

std::vector<Neo> NasaAPI::CreateNeos(nlohmann::json data) {
  std::vector<Neo> neos;
  
  if (data.contains("near_earth_objects")) {
    auto near_earth_objects = data["near_earth_objects"];
    for (auto it = near_earth_objects.begin(); it != near_earth_objects.end(); ++it) {
      for (auto& neo_json : it.value()) {
        neos.emplace_back(neo_json);
      }
    }
  }
  
  return neos;
}


