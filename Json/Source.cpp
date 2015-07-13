
#include "picojson.h"
#include <fstream>
#include <memory>

void main(){
  picojson::value root;
  {
    std::ifstream stream("example.json");
    if (!stream.is_open()) return;
    stream >> root;
  }
  picojson::object image = root.get<picojson::object>()["Image"].get<picojson::object>();
  std::cout << "width = " << image["width"].get<double>() << std::endl;
  picojson::array ids = image["IDs"].get<picojson::array>();

  for (auto item : ids){
    std::cout << item.get<double>() << std::endl;
  }
}
