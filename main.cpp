#include <iostream>
#include <sstream>
#include <fstream>
#include "Graph.hpp"

void usage(std::string name)
{
    std::cout << "Usage: "<< name <<" <city filename>\n";
}


struct city 
{
    std::string name;
    std::vector<int> connections;
};

std::vector<std::string> getCityList(std::string line) 
{
    std::stringstream ss(line);
    std::string city_name;
    std::vector<std::string> city_list;

    while(getline(ss, city_name, ','))
    {
        if (city_name != "cities")
        city_list.push_back(city_name);
    }
    return city_list;
}

void fillCityConnections(Graph * g, std::string line, std::vector<std::string> city_list)
{
    std::stringstream ss(line);
    std::string curr_city;

    std::string distance_s;
    int distance;

    int count = -1;
    while(getline(ss,distance_s, ','))
    {
        if (count == -1)
        {
            curr_city = distance_s; count++; continue;
        }
        distance = stoi(distance_s);

    if(distance > 0)
    {
        std::cout << " ... Reading in " << curr_city << " -- " << city_list[count] ;
        std::cout << " -- " << distance << "\n";
        g->addEdge(curr_city, city_list[count], distance);
    }
    count++;
  }
}

void fillGraph(Graph * g, const char * filename)
{
    std::ifstream inFile(filename, std::ios::in);
    if (inFile.is_open())
    {
        std::string line;
        std::vector<std::string> city_list;

        int line_num = -1;
        while (std::getline(inFile, line))
        {
            if (line_num == -1) {
                city_list = getCityList(line);
                for (auto & city: city_list) g->addVertex(city);
            }
            else
            {
              fillCityConnections(g, line, city_list);
            }
            line_num++;
        }
        inFile.close();
    }
    else
    {
        std::cerr << "Unable to open file\n";
    }
}


int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        usage(argv[0]);
        return -1;
    }

    const char* filename = argv[1];
    Graph mainGr;

    fillGraph(&mainGr, filename);

    mainGr.assignDistricts();
    mainGr.displayEdges();
    return 0;
}