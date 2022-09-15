#include "StudentList.h"
#include "ArgumentManager.h"
#include <algorithm> // Needed for erase and remove to work


student cleanInputData(std::string line) {
    student addStudent;

    if (line.find("id") == string::npos || line.find("grade") == string::npos 
    || line.find("username") == string::npos || line.find("score") == string::npos) {
        return addStudent; // Checking to see if it's missing a data point
    }

    int idIndex = line.find("id") + 3;
    int usernameIndex = line.find("username") + 9;
    int scoreIndex = line.find("score") + 6;
    int gradeIndex = line.find("grade") + 6;

    if (idIndex > gradeIndex || idIndex > usernameIndex || idIndex > scoreIndex) {
        std::cout << "ID NOT RIGHT POSITION" << endl;
        addStudent.valid = false;
        return addStudent;
    }
    if(usernameIndex > scoreIndex || usernameIndex > gradeIndex) {
        std::cout << "Username not right position" << endl;
        addStudent.valid = false;
        return addStudent;
    }
    if (scoreIndex > gradeIndex) {
        std::cout << "score not in right position" << endl;
        addStudent.valid = false;
        return addStudent;
    }

    stringstream idStr(line.substr(idIndex, 4));
    int id;
    idStr >> id;
    addStudent.id = id;

    string name;
    int index = usernameIndex;
    while(line.at(index) != ';') {
        name += line.at(index);
        index++;
    }
    
    addStudent.name = name;
    string holdScore;
    index = scoreIndex;
    while(line.at(index) != ';') {
        holdScore += line.at(index);
        index++;
    }
    stringstream scoreStr(holdScore);
    int score;
    scoreStr >> score;
    addStudent.score = score;
    char grade = line.at(gradeIndex);
    addStudent.grade = grade;


    return addStudent;
}

int main (int argc, char* argv[]) {
    ArgumentManager am(argc, argv);
    std::string infile = am.get("input");
    std::string comfile = am.get("command");
    std::string outfile = am.get("output");

    std::cout << "Input: " << infile << " Output: " << outfile << std::endl;  
    std::ifstream ifs(infile);
    std::ifstream cfs(comfile);
    std::ofstream ofs(outfile);

    std::string line;

    StudentList students;
    
    while(getline(ifs, line)) {
        line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
        student addStudent = cleanInputData(line);
        if (addStudent.valid == false) {
            continue;
        }
        if (line.empty()) {
            continue;
        }
        students.addAtTail(addStudent.id, addStudent.name, addStudent.score, addStudent.grade);
    }
    
    
    students.print();
    while(getline(cfs, line)) {
        line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
        if (line.find("Add") != string::npos) {
            if (line.find("id") == string::npos || line.find("grade") == string::npos 
            || line.find("username") == string::npos || line.find("score") == string::npos) {
                 continue; // Checking to see if it's missing a data point
                }
            int beginIndex = line.find('(');
            int index = beginIndex;
            while (line.at(index) != ')') {
                index++;
            }
            int howFar = line.find(')') - beginIndex - 1; // Make sure to get it if it's multiple digits
            student newStudent = cleanInputData(line);
            int addAtThisIndex;
            stringstream convertToInt(line.substr(beginIndex+1, howFar));
            convertToInt >> addAtThisIndex;
            //cout << addAtThisIndex << endl;
            students.addAtIndex(newStudent.id, newStudent.name, newStudent.score, newStudent.grade, addAtThisIndex);
        }
        if (line.find("Sort") != string::npos) {
            int beginIndex = line.find('(') + 1;
            int howFar = line.find(')') - beginIndex; 
            string sortCond = line.substr(beginIndex, howFar);
            std::cout << sortCond << endl;
            students.sort(sortCond);
            continue;          
        
        }
        if (line.find("Remove") != string::npos) {
            int beginIndex = line.find('(') + 1;
            int index = beginIndex;
            int howFar = line.find(':') - beginIndex;
            string removeCond = line.substr(beginIndex, howFar);
            std:cout << removeCond << std::endl;
            beginIndex = line.find(':') + 1;
            howFar = line.find(')') - beginIndex;
            string data = line.substr(beginIndex, howFar);
            cout << data << endl;
            students.remove(removeCond, data);
            continue;
        }
        
        
    }
    

    students.output(ofs);

    

}