

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
struct Course {
    string CourseID;
    string CourseName;
    vector<string> prereqs;
    Course() {}
};
struct Node {
    Course course;
    Node* left;
    Node* right;
    Node() {
        left = nullptr;
        right = nullptr;
    }
    Node(Course aCourse) : Node() {
        this->course = aCourse;
    }
};
class BinarySearchTree {

private:
    Node* root;
    void addNode(Node* node, Course course);
    void printsample(Node* node);
    void printcourseinfo(Node* node, string coursenum);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void Insert(Course course);
    int prerequisit(Course course);
    void printsample();
    void printcourseinfo(string coursenum);

};


BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}
BinarySearchTree::~BinarySearchTree() {
    while (root != nullptr) {
        delete(root);
    }
}

void BinarySearchTree::printsample()
{
    this->printsample(root);
}
void BinarySearchTree::printcourseinfo(string coursenum) {
    this->printcourseinfo(root, coursenum);
}
int BinarySearchTree::prerequisit(Course course) {
    int total = 0;
    for (int i = 0; i < course.prereqs.size(); ++i){
        if (course.prereqs[i].length() > 0) {
            total++;
        }
        else if(course.prereqs[i].length() == NULL) {
            total = 0;
        }
    }
    return total;
}
void BinarySearchTree::addNode(Node* node, Course course) {
    if (node->course.CourseID.compare(course.CourseID) > 0) {
        if (node->left == nullptr) {
            node->left = new Node(course);
        }
        else {
            this->addNode(node->left, course);
        }
    }
    else if(node->course.CourseID.compare(course.CourseID) < 0) {
        if (node->right == nullptr) {
            node->right = new Node(course);
        }
        else {
            this->addNode(node->right, course);
        }
    }
}
void BinarySearchTree::Insert(Course course) {
    if (root == nullptr) {
        root = new Node(course);
    }
    else {
        this->addNode(root, course);
    }
}
void BinarySearchTree::printsample(Node* node) {//prints all nodes in binary tree
    if (node != nullptr) {
        printsample(node->left);//prints left node
        cout << node->course.CourseID << ", " << node->course.CourseName << endl;//prints course id and name
        printsample(node->right); //print right node
   }
}
void BinarySearchTree::printcourseinfo(Node* cur, string coursenum) {
    int count = 0;//count for if the for loop is true
    while (cur != nullptr) {//loop until current node is nullptr or found
        if (cur->course.CourseID.compare(coursenum) == 0) { //if current node is equal to searched for node
            cout << cur->course.CourseID << ", " << cur->course.CourseName << endl;
            int size = prerequisit(cur->course);
            cout << "Prerequisites: ";
            for (int i = 0; i < size; ++i) {
                cout << cur->course.prereqs[i];
                if (i != size-1) {
                    cout << ", ";
                    count++;
                }
                if (i == 0)
                {
                    count++;
                }
            }
            if (count == 0 && count < 1) {
                cout << "None" << count;

            }
            cout << endl;
            return;
        }
        else if (coursenum.compare(cur->course.CourseID) < 0)
        {
            cur = cur->left;
        }
        else {
            cur = cur->right;
        }
    }
}
void loadcourses(string csvpath, BinarySearchTree* bst) {
    ifstream file(csvpath);
    if (file.is_open()) {
        while (!file.eof()) {
            vector<string> coursedata;
            string data;
            getline(file, data);
            while (data.length() > 0)
            {
                unsigned int spacer = data.find(',');
                if (spacer < 100)
                {
                    coursedata.push_back(data.substr(0, spacer));
                    data.erase(0, spacer + 1);
                }
                else {
                    coursedata.push_back(data.substr(0, data.length()));
                    data = "";
                }
            }
            Course course;
            course.CourseID = coursedata[0];
            course.CourseName = coursedata[1];
            for (int i = 2; i < coursedata.size(); ++i) {
                course.prereqs.push_back(coursedata[i]);
            }
            bst->Insert(course);
        }
        
        file.close();
        

    }
}
int main()
{
    string coursenum;
    string csvpath = "CourseList.txt";
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Course course;
    int choice = 0;
    while (choice != 9) {
        cout << endl << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl << endl;
        cout << "What would you like to do? ";
        cin >> choice;
        switch (choice) {
        case 1:
            loadcourses(csvpath, bst);
            break;
        case 2:
            //print sample
            cout << "Here is a sample schedule: " << endl << endl;
            bst->printsample();
            break;
        case 3:
            //print course info
            cout << "Enter couse id: ";
            cin >> coursenum;
            bst->printcourseinfo(coursenum);
            break;
        case 9:
            break;
        default:
            cout << choice << " is not a valid option." << endl;
            cin.clear();
            main();
            break;
        }
    }
    cout << "Thank you for using the Course Planner!" << endl;
}