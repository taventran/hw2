#include "StudentList.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

bool validInfo (int id, string name, int score, char grade) {
    // Make sure user name is valid
    if (name.length() == 0) {
        return false;
    }
    for (int i = 0; i < name.length(); i++) {
        if (isalpha(name.at(i)) && islower(name.at(i))) {
            continue;
        }
        else {
            return false;
        }
    }
    if (score < 0 || score > 100) {
        return false;
    }
    if (id < 1000 || id > 9999) {
        return false;
    }

    if (grade == 'A' || grade == 'B' || grade == 'C' || grade == 'D' || grade == 'F') {
        return true; 
    }

    return false;
}

bool StudentList::checkIfExists(student* temp) {
    student* cur = head;
    while (cur != nullptr) { // Checks to see if id already exists
        if (cur->id == temp->id) {
            cur->name = temp->name;
            cur->grade = temp->grade;
            cur->score = temp->score;
            return true;
        }
        if (cur->name == temp->name) { // Checks to if username exists
            return true;
        }
        cur = cur->next;
    }
    return false;
}

bool StudentList::isEmpty() {
    if (head == nullptr) {
        return true;
    }
    return false;
}


void StudentList::addAtTail(int id, string name, int score, char grade) {
    student* temp = new student;
    bool valid = validInfo(id, name, score, grade);
    if (!valid) {
        return;
    }
    temp->id = id;
    temp->name = name;
    temp->score = score;
    temp->grade =  grade;
    temp->next = nullptr;
    std::cout << temp->name << std::endl; 
    if (isEmpty()) {
        head = temp;
        return;
    }

    if (checkIfExists(temp)) {
        return;
    }


    student* cur = head;
    while (cur->next != nullptr) {
        cur = cur->next;
    }

    cur->next = temp;
    return;
}

void StudentList::addAtIndex(int id, string name, int score, char grade, int index){
    bool valid = validInfo(id, name, score, grade);
    if (!valid) {
        return;
    }
    student* temp = new student;
    temp->id = id;
    temp->name = name;
    temp->score = score;
    temp->grade  = grade;
    temp->next = nullptr;

    if (isEmpty() && index > 0) {
        return; //out of bonds
    }

    if (isEmpty()) {
        head = temp;
        return;
    }

    if (checkIfExists(temp)) {
        return;
    }

    student* cur = head;
    


    if (index == 0) {
        temp->next = head;
        head = temp;
        print();
        return;
    } 

    cur = head;
    for(int i = 0; i < index-1; i++) {
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
    stu1->score = stu2->score;

    stu2->id = temp.id;
    stu2->name = temp.name;
    stu2->grade = temp.grade;
    stu2->score = temp.score; 
}

void StudentList::sort(string typeOfSort) {
    std::cout << "SORTING" << std::endl;
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
    if (typeOfSort == "grade") {
        while(cur != nullptr) {
            student* nextNode = cur->next;
            while (nextNode != nullptr) {
                if (cur->grade > nextNode->grade) {
                    swap(cur, nextNode);
                }
                nextNode = nextNode->next;
            }
            cur = cur->next;
        }        
    }
    if (typeOfSort == "username") {
        while(cur != nullptr) {
            student* nextNode = cur->next;
            while (nextNode != nullptr) {
                if (cur->name > nextNode->name) {
                    swap(cur, nextNode);
                }
                nextNode = nextNode->next;
            }
            cur = cur->next;
        }        
    }    
    if (typeOfSort == "score") {
        while(cur != nullptr) {
            student* nextNode = cur->next;
            while (nextNode != nullptr) {
                if (cur->score < nextNode->score) {
                    swap(cur, nextNode);
                }
                nextNode = nextNode->next;
            }
            cur = cur->next;
        }        
    }
    print();    

}

void StudentList::remove(string condition, string data) {
    if (condition == "username") {
        student* prev;
        student* cur = head;
        if (head->name == data) {
            head = head->next;
            delete cur;
        }
        while (cur != nullptr) {
            if (cur->name == data) {
                prev->next= cur->next;
                delete (cur);
            }
            prev = cur;
            cur = cur->next;
        }
    }
    if (condition == "grade") {
        student* prev;
        student* cur = head;
        char letter = data[0];
        if (head->grade == letter) {
            head = head->next;
            delete cur;
        }
        while (cur != nullptr) {
            if (cur->grade == letter) {
                prev->next= cur->next;
                delete (cur);
            }
            prev = cur;
            cur = cur->next;
        }
    }
    if (condition == "score") {
        student* prev;
        student* cur = head;
        int stuScore;
        stringstream convertToInt(data);
        convertToInt >> stuScore;
        if (head->score == stuScore) {
            head = head->next;
            delete cur;
        }
        while (cur != nullptr) {
            if (cur->score == stuScore) {
                prev->next= cur->next;
                delete (cur);
            }
            prev = cur;
            cur = cur->next;
        }
    }
    if (condition == "id") {
        student* prev;
        student* cur = head;
        int stuID;
        stringstream convertToInt(data);
        convertToInt >> stuID;
        if (head->id == stuID) {
            head = head->next;
            delete cur;
        }
        while (cur != nullptr) {
            if (cur->id == stuID) {
                prev->next= cur->next;
                delete (cur);
            }
            prev = cur;
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
    std::cout << std::endl;
    
} 

void StudentList::output(ofstream& ofs) {
    student* cur = head;
    while(cur != nullptr) {
        ofs << "[id:"<<cur->id<<";username:"<<cur->name<<";score:"<<cur->score<<";grade:"<<cur->grade<<"]"<<endl;
        cur = cur->next;
    }
}