

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
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
    else if(node->course.CourseID.compare(course.CourseID) < 0) { //if node course id is < implemented course id position in right position other wise move right and repeat.
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
        this->addNode(root, course);//calls addnode to insert a new node since there is a root already
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
                cout << cur->course.prereqs[i];//print current couse prerequisits loop
                if (i != size-1) { // if two prerequisits are found print a comma between them
                    cout << ", ";
                    count++; //increment count so system knows theres a class
                }
                if (i == 0) //if i does equal zero due to there being one class increment
                {
                    count++;
                }
            }
            if (count == 0 && count < 1) { //if count is less than 1 and equal to zero print none
                cout << "None";

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
    ifstream file(csvpath); //opens file using the csvpath
    if (file.is_open()) { //checks if file is open
        while (!file.eof()) { //until end of file
            vector<string> coursedata; //new vector called coursedata
            string data; //string called data
            getline(file, data); //getline in file, and use string data
            while (data.length() > 0) //while data string length is > 0
            {
                unsigned int spacer = data.find(','); //find a comma and set as integer location
                if (spacer < 100) //if comma is less than 100 positions
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
            course.CourseID = coursedata[0]; //sets course id to poistion 0
            course.CourseName = coursedata[1]; //sets course name to position 1
            for (int i = 2; i < coursedata.size(); ++i) { //loop for prerequisits
                course.prereqs.push_back(coursedata[i]);
            }
            bst->Insert(course);//call insert class to keep vectors from file loaded
        }
        
        file.close(); //close file
        

    }
}
int main()
{
    bool isRunning = true;
    string coursenum;
    string csvpath = "CourseList.txt"; //reference to file name
    BinarySearchTree* bst; //creates binary tree label
    bst = new BinarySearchTree(); // creates new binary tree
    Course course; //calls struct
    int choice = 0; 
    while (isRunning) {
        loadcourses(csvpath, bst); //automatically loads the Data Structure
        cout << "=================================" << endl;
        cout << "=  Welcome to SNHU Course List  =" << endl;
        cout << "=================================" << endl;
        //cout << "1. Load Data Structure." << endl; // old selction for selecting to load the Data Structure
        cout << "1. Print Course List." << endl;
        cout << "2. Print Course." << endl;
        cout << "3. Exit" << endl << endl;
        cout << "What would you like to do? ";
        cin >> choice;
        switch (choice) {
        /*case 1:
            loadcourses(csvpath, bst);
            break; */ //old method of loading course selection list manually
        case 1:
            system("cls"); // clear screen making it more orgainized
            //print sample
            cout << "Here is a sample schedule: " << endl << endl;
            bst->printsample();
            cout << endl;
            system("pause"); //pause so that the user can read
            system("cls"); // clear screen to allow the user to have a better experience
            break;
        case 2:
            system("cls");
            cout << "Select from these courses: " << endl; //let the user know why the courses are being displayed for them
            //print course info
            bst->printsample();
            cout << endl << "Enter couse id: "; //has user input selected course
            cin >> coursenum;
            transform(coursenum.begin(), coursenum.end(), coursenum.begin(),
                [](unsigned char c) { return static_cast<unsigned char>(toupper(c)); }); //user can input upper or lower case letters they will be adjusted for the BST
            cout << endl;
            bst->printcourseinfo(coursenum);
            cout << endl;
            system("pause");
            cin.clear();
            system("cls");
            break;
        case 3:
            isRunning = false; //confirms weather the window will keep running or not
            break;
        default:
            cout << endl <<"  " << choice << " is not a valid option" << endl;
            system("pause");
            cin.clear();
            system("cls");
            
            break;
        }
    }
    cout << "Thank you for using the Course Planner!" << endl;
    return(0);
}