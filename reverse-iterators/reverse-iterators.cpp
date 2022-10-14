#include <algorithm>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <unordered_set>
#include <vector>

#include <gtest/gtest.h>

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
void lastOccurences(vector<string>& names)
{
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
            n = vector<string>::reverse_iterator(names.erase(next(n).base()));
        }
    }
}

TEST(LastOccurences, Basic) {
	const vector<string> names = { "Juliett", "Romeo", "Paul", "Romeo", "George", "Romeo" };
	vector<string> v = names;
	lastOccurences(v);
	EXPECT_EQ(v,  vector<string>({"Juliett", "Paul", "George", "Romeo"}));
}
