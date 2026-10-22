#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

// Returns true if a person can attend every event.
bool can_attend_all(vector<pair<int, int>> events) {
    sort(events.begin(), events.end());

    for (int i = 1; i < (int)events.size(); i++) {
        // Equal end and start times are allowed.
        if (events[i].first < events[i - 1].second) {
            return false;
        }
    }

    return true;
}

// Returns the minimum number of meeting rooms required.
int min_rooms_required(vector<pair<int, int>> events) {
    if (events.empty()) {
        return 0;
    }

    sort(events.begin(), events.end());

    // Min-heap containing the end times of active meetings.
    priority_queue<int, vector<int>, greater<int>> minHeap;

    int maxRooms = 0;

    for (const auto& event : events) {
        int start = event.first;
        int end = event.second;

        // Free rooms whose meetings have already ended.
        while (!minHeap.empty() && minHeap.top() <= start) {
            minHeap.pop();
        }

        // Allocate a room for the current meeting.
        minHeap.push(end);

        maxRooms = max(maxRooms, (int)minHeap.size());
    }

    return maxRooms;
}

int main() {
    vector<pair<int, int>> events = {
        {9, 10},
        {10, 11},
        {9, 12},
        {11, 12}
    };

    cout << boolalpha;
    cout << "Can attend all: "
         << can_attend_all(events) << '\n';

    cout << "Minimum rooms required: "
         << min_rooms_required(events) << '\n';

    return 0;
}