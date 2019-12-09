#include <string>
#include <vector>
#include <hamilton.h>
#include <dijkstra.h>
#include <dfs.h>
#include "common/logger.h"
#include "common/data_struct.h"

using namespace std;

const string field = R"(
OOOOOOOOOOOOOOOOOOOOOOOOOOO
OHHHHHOHOOOOOOHOOOHHHHHHHOO
OOOHOOOHOOOOOOHOOOHOOOOOOOO
OOOHOOOHOOOOOOHOOOHHHHHHHOO
OOOHOOOHOOOOOOHOOOOOOOOOHOO
OHHHHHOHHHHHHHHOOOHHHHHHHOO
OOOOOOOOOOOOOOOOOOOOOOOOOOO
)";

int main() {
    vector<char> buffer;
    auto width = 0;
    auto height = 0;
    for (const auto &item : field) {
        if (item != '\n') {
            if (height == 0) {
                ++width;
            }
            buffer.push_back(item);
            continue;
        } else if (width != 0) {
            ++height;
        }
    }
    LOG("width: %u, height: %u", width, height);

    using namespace data::detail;
    Graph graph(buffer, width, height);
    graph.PrintGraph();
    Vertex start_pos = graph.GetCoord(2, 4);
    Vertex end_pos = graph.GetCoord(19, 2);

    Hamilton hamilton(graph);
    Dijkstra dijkstra(graph);
    Dfs dfs(graph);

    dfs.SearchLongest(start_pos);
    list<VertexList> all_path;
    dfs.SearchAllPath(start_pos, 12, all_path);

    return 0;
}