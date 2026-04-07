#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Student {
    string id;
    string name;
    int score;
    int insert_idx;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<Student> students;
    students.reserve(10000);
    unordered_map<string, int> id_to_idx;
    unordered_map<string, int> name_to_idx;

    bool id_sorted_valid = false;
    vector<const Student*> id_sorted;

    bool score_sorted_valid = false;
    vector<const Student*> score_sorted;

    int cmd;
    while (cin >> cmd) {
        if (cmd == 1) {
            string id, name;
            int score;
            cin >> id >> name >> score;
            if (id_to_idx.find(id) != id_to_idx.end()) {
                cout << "FAILED\n";
            } else {
                int idx = students.size();
                students.push_back({id, name, score, idx});
                id_to_idx[id] = idx;
                name_to_idx[name] = idx;
                id_sorted_valid = false;
                score_sorted_valid = false;
                cout << "SUCCESS\n";
            }
        } else if (cmd == 2) {
            for (const auto& s : students) {
                cout << s.id << " " << s.name << " " << s.score << "\n";
            }
        } else if (cmd == 3) {
            string id;
            cin >> id;
            if (id_to_idx.find(id) != id_to_idx.end()) {
                const auto& s = students[id_to_idx[id]];
                cout << s.id << " " << s.name << " " << s.score << "\n";
            }
        } else if (cmd == 4) {
            string name;
            cin >> name;
            if (name_to_idx.find(name) != name_to_idx.end()) {
                const auto& s = students[name_to_idx[name]];
                cout << s.id << " " << s.name << " " << s.score << "\n";
            }
        } else if (cmd == 5) {
            if (!id_sorted_valid) {
                id_sorted.clear();
                id_sorted.reserve(students.size());
                for (const auto& s : students) {
                    id_sorted.push_back(&s);
                }
                sort(id_sorted.begin(), id_sorted.end(), [](const Student* a, const Student* b) {
                    return a->id < b->id;
                });
                id_sorted_valid = true;
            }
            for (const auto* s : id_sorted) {
                cout << s->id << " " << s->name << " " << s->score << "\n";
            }
        } else if (cmd == 6) {
            if (!score_sorted_valid) {
                score_sorted.clear();
                score_sorted.reserve(students.size());
                for (const auto& s : students) {
                    score_sorted.push_back(&s);
                }
                sort(score_sorted.begin(), score_sorted.end(), [](const Student* a, const Student* b) {
                    if (a->score != b->score) {
                        return a->score > b->score;
                    }
                    return a->insert_idx < b->insert_idx;
                });
                score_sorted_valid = true;
            }
            for (const auto* s : score_sorted) {
                cout << s->id << " " << s->name << " " << s->score << "\n";
            }
        } else if (cmd == 7) {
            cout << "END\n";
            break;
        }
    }

    return 0;
}