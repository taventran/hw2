#pragma once
#include "ArgumentManager.h"

using namespace std;

struct student {
    int id;
    std::string name;
    int score;
    char grade;
    student* next;
};

class StudentList {
    private:
        student* head;
    public:
        StudentList() {
            head = nullptr;
        }
        void addAtTail(int id, string name, int score, char grade);
        void addAtIndex(int id, string name, int score, char grade, int index);
        void swap(student* stu1, student* stu2);
        void sort(string typeOfSort);
        bool isEmpty();
        void print();
};