#include <iostream>
#include <vector>
using namespace std;

class Student{

public:
    string name;
    int id;
    float grade;

    void display() {
        cout << "name:" << name << "id:" << id << "grade:" << grade << endl;
    }

};

int main() {
    vector<Student> students;
    int choice;

    while (true) {
        cout << "1. 학생 추가\n2. 학생 조회\n. 종료\n선택: ";
        cin >> choice;

        if (choice == 1) {
            Student s;
            cout << "이름: "; cin >> s.name;
            cout << "학번: "; cin >> s.id;
            cout << "성적: "; cin >> s.grade;
            students.push_back(s);
        } else if (choice == 2) {
            for (auto& s : students) s.display();
        } else {
            break;
        }
    }
    return 0;
}

