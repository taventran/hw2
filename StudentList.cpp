#include "StudentList.h"

bool StudentList::isEmpty() {
    if (head == nullptr) {
        return true;
    }
    return false;
}


void StudentList::addAtTail(int id, string name, int score, char grade) {
    student* temp = new student;
    temp->id = id;
    temp->name = name;
    temp->score = score;
    temp->grade  = grade;
    temp->next = nullptr;

    if (isEmpty()) {
        head = temp;
        return;
    }

    student* cur = head;

    while (cur->next != nullptr) {
        std::cout << cur->id << " " << id << std::endl;
        if (cur->id == temp->id) {
            std::cout << "Update" << endl;
            cur->name = name;
            cur->grade = grade;
            cur->score = score;
            return;
        }
        std::cout << "Went through" << std::endl;
        if (cur->name == name) {
            std::cout << "SAME NAME" << endl;
            return;
        }
        cur = cur->next;
    }
    std::cout << "ran" << endl;
    cur->next = temp;
    return;
}

void StudentList::addAtIndex(int id, string name, int score, char grade, int index){
    student* temp = new student;
    temp->id = id;
    temp->name = name;
    temp->score = score;
    temp->grade  = grade;
    temp->next = nullptr;

    if (isEmpty()) {
        head = temp;
        return;
    }

    student* cur = head;
    while (cur->next != nullptr) { // Checks to see if id already exists
        if (cur->id == temp->id) {
            std::cout << "Update" << std::endl;
            cur->name = name;
            cur->grade = grade;
            cur->score = score;
            return;
        }
        if (cur->name == temp->name) { // Checks to if username exists
            return;
        }
        cur = cur->next;
    }


    if (index == 0) {
        temp->next = head;
        head = temp;
        return;
    } 

    cur = head;
    for(int i = 1; i < index-1; i++) {
        cur = cur->next;
        if (cur == nullptr) {
            std::cout << "Out of bounds man" << std::endl;
            return; // Out of bounds
        }
    }
    temp->next = cur->next;
    cur->next = temp;
    return;
}

void StudentList::swap(student* stu1, student* stu2) {
    student temp;
    temp.id = stu1->id;
    temp.name = stu1->name;
    temp.grade = stu1->grade;
    temp.score = stu1->score;

    stu1->id = stu2->id;
    stu1->name = stu2->name;
    stu1->grade = stu2->grade;
    stu1->score = stu1->score;

    stu2->id = temp.id;
    stu2->name = temp.name;
    stu2->grade = temp.grade;
    stu2->score = temp.score; 
}

void StudentList::sort(string typeOfSort) {
    if (isEmpty()) {
        return;
    }
    
    student* cur = head;
    if (typeOfSort == "id") {
        while(cur != nullptr) {
            student* nextNode = cur->next;
            while (nextNode != nullptr) {
                if (cur->id > nextNode->id) {
                    swap(cur, nextNode);
                }
                nextNode = nextNode->next;
            }
            cur = cur->next;
        }

    }

}

void StudentList::print() {
    student* cur = head;
    while (cur != nullptr) {
        std::cout << "id:" << cur->id << " name:" << cur->name << " score:" << cur->score << " grade:" 
        << cur->grade << std::endl; 
        cur = cur->next;
    }
} 