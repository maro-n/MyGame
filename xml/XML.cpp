
#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

int main()
{
  {
    boost::property_tree::ptree pt;
    read_xml("Sample.xml", pt);

    // root内のstrを取得し表示
    if (boost::optional<std::string> str = pt.get_optional<std::string>("root.str")) {
      std::cout << str.get() << std::endl;
    }
    else {
      std::cout << "root.str is nothing" << std::endl;
    }

    // root内のvaluesを取得し、その中身をループで全て表示
    BOOST_FOREACH(const boost::property_tree::ptree::value_type& child, pt.get_child("root.values")) {
      const int value = boost::lexical_cast<int>(child.second.data());
      std::cout << value << std::endl;
    }
  }

  std::cout << std::endl;

  {
    int i = 0;

    enum Status{
      ATK,
      DEF,
      INT,
      DEX,
      SPD,
    };

    std::string status[5];
    status[ATK] = "ATK";
    status[DEF] = "DEF";
    status[INT] = "INT";
    status[DEX] = "DEX";
    status[SPD] = "SPD";

    boost::property_tree::ptree pt;
    read_xml("Player.xml", pt);

    // root内のstrを取得し表示
    if (boost::optional<std::string> str = pt.get_optional<std::string>("Players.status")) {
      std::cout << str.get() << std::endl;
    }
    else {
      std::cout << "Players.Player.Status.ATK is nothing" << std::endl;
    }

    // root内のvaluesを取得し、その中身をループで全て表示
    BOOST_FOREACH(const boost::property_tree::ptree::value_type& child, pt.get_child("Players.Player.Status")) {
      const int value = boost::lexical_cast<int>(child.second.data());
      std::cout << status[i] << value << std::endl;
      ++i;
    }

  }
}
