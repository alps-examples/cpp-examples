#include <algorithm>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

// lastOccurences - remove all copies but last from container
//
// Input:
//     List of names, containing duplicates
//
// Output:
//     List of names with duplicates removed.
//     Order of names must be preserved.
//     The last occurrence of every duplicated item should remain.
//
// Example Input:
//     Juliett
//     Romeo
//     Paul
//     Romeo
//     George
//     Romeo
//
// Example Output:
//     Juliett
//     Paul
//     George
//     Romeo
//
// In-place Run-time O(N) Memory O(N)
void lastOccurences(list<string> &names) {
  unordered_set<string> knowns;
  knowns.reserve(names.size());

  for (auto n = names.rbegin(); n != names.rend();) {
    if (knowns.insert(*n).second) {
      // *n wasn't known before, so skip to next.
      n++;
    } else {
      // *n was known, so delete *n.
      //
      // Reverse iterator R based on forward iterator F returns
      // *(F-1). Therefore , to get F corresponding to *R we need
      // *`next(F).base()`.
      //
      // By constructing reverse iterator from the return value of
      // `erase`, we automatically point to the predecessor
      // of the deleted element.
      //
      // One line of code, ten lines of comment. Long live C++.
      n = list<string>::reverse_iterator(names.erase(next(n).base()));
    }
  }
}

int main() {
  const vector<string> names = {"Juliett", "Romeo",  "Paul",
                                "Romeo",   "George", "Romeo"};
  const vector<string> expected = {"Juliett", "Paul", "George", "Romeo"};

  map<string, function<bool()>> test;

  test["Test1"] = [&]() {
    list<string> v;
    copy(names.begin(), names.end(), back_inserter(v));
    lastOccurences(v);
    return equal(v.begin(), v.end(), expected.begin(), expected.end());
  };

  for (auto &t : test) {
    cout << t.first << (t.second() ? " passed." : " failed.") << endl;
  }
}
