#include <benchmark/benchmark.h>

#include "CXXGraph/CXXGraph.hpp"
#include "Utilities.hpp"

static void Dijkstra_X(benchmark::State &state) {
  CXXGraph::Graph<int> g;
  auto range_start = edges.begin();
  auto range_end = edges.find(state.range(0));
  std::unordered_map<unsigned long, CXXGraph::Edge<int> *> edgesX;
  edgesX.insert(range_start, range_end);
  for (auto e : edgesX) {
    g.addEdge(&(*e.second));
  }
  for (auto _ : state) {
    auto &result = g.dijkstra(*(range_start->second->getNodePair().first),
                              *(range_end->second->getNodePair().second));
  }
  state.SetComplexityN(2);
}
BENCHMARK(Dijkstra_X)
    ->RangeMultiplier(16)
    ->Range((unsigned long)1, (unsigned long)1 << 16)
    ->Complexity();

static void Dijkstra_FromReadedCitHep(benchmark::State &state) {
  auto edgeSet = cit_graph_ptr->getEdgeSet();
  for (auto _ : state) {
    auto &result = cit_graph_ptr->dijkstra(
        *((*(edgeSet.begin()))->getNodePair().first),
        *((*(++edgeSet.begin()))->getNodePair().second));
  }
  state.SetComplexityN(2);
}

// BENCHMARK(Dijkstra_FromReadedCitHep)->Complexity();
