#include <fstream>
#include <iomanip>
#include <iostream>
#include <set>
#include <string>
#include <vector>

// Model
class Student
{
private:
    std::string name;
    int age;
    std::string course;

public:
    Student(const std::string &name, int age, const std::string &course) : name(name), age(age), course(course)
    {
    }

    // Assignment operator to allow updates
    Student &operator=(const Student &other)
    {
        if (this != &other)
        {
            name = other.name;
            age = other.age;
            course = other.course;
        }
        return *this;
    }

    const std::string &getName() const
    {
        return name;
    }

    int getAge() const
    {
        return age;
    }

    const std::string &getCourse() const
    {
        return course;
    }

    void updateStudent(const std::string &newName, int newAge, const std::string &newCourse)
    {
        name = newName;
        age = newAge;
        course = newCourse;
    }
};

// Observer
class Observer
{
public:
    virtual void update() = 0;
};

class StudentModel
{
private:
    std::vector<Student> students;
    std::set<class Observer *> observers;

public:
    void addObserver(Observer *observer)
    {
        observers.insert(observer);
    }

    void removeObserver(Observer *observer)
    {
        observers.erase(observer);
    }

    void notifyObservers()
    {
        for (Observer *observer : observers)
        {
            observer->update();
        }
    }

    void addStudent(const Student &student)
    {
        students.push_back(student);
        notifyObservers();
    }

    std::vector<Student> &getAllStudents()
    {
        return students;
    }

    bool removeStudent(int index)
    {
        bool result = false;
        if (!students.empty())
        {
            if (index >= 0 && index <= students.size())
            {
                students.erase(students.begin() + index);
                notifyObservers();
                std::cout << "Student removed successfully." << std::endl;
                result = true;
            }
            else
            {
                std::cout << "Invalid index. No student removed." << std::endl;
            }
        }
        else
        {
            std::cout << "No students to removed." << std::endl;
        }

        return result;
    }

    void saveStudentsToFile(const std::string &filename)
    {
        std::ofstream file(filename);
        if (file.is_open())
        {
            file << "No.,Name,Age,Course" << std::endl; // Header

            for (size_t i = 0; i < students.size(); ++i)
            {
                const Student &student = students[i];
                file << i + 1 << "," << student.getName() << "," << student.getAge() << "," << student.getCourse()
                     << std::endl;
            }

            file.close();
            std::cout << "Student data saved to " << filename << std::endl;
        }
        else
        {
            std::cerr << "Unable to open the file: " << filename << std::endl;
        }
    }
};

// View
class StudentView : public Observer
{
private:
    StudentModel *model; // Add a pointer to the model
public:
    StudentView(StudentModel *model) : model(model)
    {
        model->addObserver(this);
    }

    void update() override
    {
        viewAllStudents();
        std::cout << "Student data updated!" << std::endl;
    }

    void showStudent(const Student &student)
    {
        std::cout << "Name: " << student.getName() << std::endl;
        std::cout << "Age: " << student.getAge() << std::endl;
        std::cout << "Course: " << student.getCourse() << std::endl;
    }

    Student getStudentInput()
    {
        std::string name, course;
        int age;

        std::cout << "Enter student name: ";
        std::cin.ignore();
        std::getline(std::cin, name);

        std::cout << "Enter student age: ";
        std::cin >> age;

        std::cin.ignore();
        std::cout << "Enter student course: ";
        std::getline(std::cin, course);

        return Student(name, age, course);
    }

    Student updateStudentInput(const Student &oldStudent)
    {
        std::string newName, newCourse;
        int newAge;

        std::cout << "Enter new student name (" << oldStudent.getName() << "): ";
        std::cin.ignore();
        std::getline(std::cin, newName);

        std::cout << "Enter new student age (" << oldStudent.getAge() << "): ";
        std::cin >> newAge;

        std::cin.ignore();
        std::cout << "Enter new student course (" << oldStudent.getCourse() << "): ";
        std::getline(std::cin, newCourse);

        return Student(newName.empty() ? oldStudent.getName() : newName,
                       newAge <= 0 ? oldStudent.getAge() : newAge,
                       newCourse.empty() ? oldStudent.getCourse() : newCourse);
    }

    void showStudentTable(const std::vector<Student> &students)
    {
        std::cout << std::left << std::setw(4) << "No." << std::setw(20) << "Name" << std::setw(10) << "Age"
                  << std::setw(20) << "Course" << std::endl;

        for (size_t i = 0; i < students.size(); ++i)
        {
            const Student &student = students[i];
            std::cout << std::setw(4) << i + 1 << std::setw(20) << student.getName() << std::setw(10)
                      << student.getAge() << std::setw(20) << student.getCourse() << std::endl;
        }
    }

    int getStudentIndexToUpdate()
    {
        std::cout << "Enter the index of the student to update: ";
        int index;
        std::cin >> index;
        return index;
    }

    int getStudentIndexToRemove()
    {
        std::cout << "Enter the index of the student to remove: ";
        int index;
        std::cin >> index;
        return index;
    }

    std::string getFileName()
    {
        std::string input;
        std::cout << "Enter the filename to save student data: ";
        std::cin.ignore();
        std::getline(std::cin, input);
        return input;
    }

    void log(std::string msg)
    {
        std::cout << msg << std::endl;
    }

    void viewAllStudents()
    {
        const std::vector<Student> &students = model->getAllStudents();
        if (students.empty())
        {
            log("No students to display.");
        }
        else
        {
            showStudentTable(students);
        }
    }
};

// Controller
class StudentController
{
private:
    StudentModel *model;
    StudentView *view;

public:
    StudentController(StudentModel *model, StudentView *view) : model(model), view(view)
    {
    }

    void run()
    {
        while (true)
        {
            std::cout << "Options: add, update, remove, save, exit" << std::endl;
            std::cout << "Enter an option: ";
            std::string option;
            std::cin >> option;

            if (option == "exit")
            {
                break;
            }
            else if (option == "add")
            {
                Student student = view->getStudentInput();
                model->addStudent(student);
            }
            else if (option == "update")
            {
                updateStudent();
            }
            else if (option == "remove")
            {
                removeStudent();
            }
            else if (option == "save")
            {
                saveStudentsToFile();
            }
        }
    }

    void removeStudent()
    {
        int index = view->getStudentIndexToRemove() - 1;
        model->removeStudent(index);
    }

    void updateStudent()
    {
        if (model->getAllStudents().empty())
        {
            view->log("No students to update.");
            return;
        }

        int index = view->getStudentIndexToUpdate() - 1;

        if (index >= 0 && index < model->getAllStudents().size())
        {
            Student oldStudent = model->getAllStudents()[index];
            Student newStudent = view->updateStudentInput(oldStudent);
            model->getAllStudents()[index] = newStudent;
            model->notifyObservers();
            view->log("Student updated successfully.");
        }
        else
        {
            view->log("Invalid index.");
        }
    }

    void saveStudentsToFile()
    {
        std::string filename = view->getFileName();
        model->saveStudentsToFile(filename);
    }
};

int main()
{
    StudentModel model;
    StudentView view(&model);
    StudentController controller(&model, &view);
    //controller.run();

    return 0;
}
