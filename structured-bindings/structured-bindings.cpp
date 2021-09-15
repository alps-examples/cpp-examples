#include <algorithm>
#include <map>
#include <string>

struct DevStats {
  std::string name;
  std::string team;
  size_t commits;
};

void iterateOld(std::map<std::string, DevStats>& devs) {
  for (auto &p : devs) {
    const auto &name = p.first;
    const auto &stats = p.second;

    // Do something with name and stats
  }
}

void iterateNew(std::map<std::string, DevStats>& devs) {
  for (auto &[name, stats] : devs) {
    // Do something with name and stats
  }
}

int main() {

}
