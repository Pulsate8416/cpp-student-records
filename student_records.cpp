#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

// Define an enumeration for grade levels
enum GradeLevel {
    FRESHMAN = 1,
    SOPHOMORE,
    JUNIOR,
    SENIOR
};

// Using alias for student record
using StudentRecord = struct {
    std::string name;
    GradeLevel level;
    double gpa;
};

// Namespace for student utilities
namespace StudentUtils {
    // Convert a string to uppercase
    void formatName(std::string &name) {
        std::transform(name.begin(), name.end(), name.begin(),
                      [](unsigned char c) { return std::toupper(c); });
    }

    // Convert GradeLevel enum to string
    std::string gradeLevelToString(GradeLevel level) {
        switch (level) {
            case FRESHMAN: return "Freshman";
            case SOPHOMORE: return "Sophomore";
            case JUNIOR: return "Junior";
            case SENIOR: return "Senior";
            default: return "Unknown";
        }
    }

    // Display student information in a formatted way
    void displayStudentInfo(const StudentRecord& student) {
        std::cout << "\nStudent Record:" << std::endl;
        std::cout << "Name: " << student.name << std::endl;
        std::cout << "Grade Level: " << gradeLevelToString(student.level) << std::endl;
        std::cout << "GPA: " << std::fixed << std::setprecision(2) << student.gpa << std::endl;
    }
}

int main() {
    std::cout << "=== Student Records Manager ===" << std::endl;

    // Basic implementation (required by assignment)
    StudentRecord student;
    std::string name;
    int levelChoice;
    double gpa;

    // Get student name
    std::cout << "Enter student name: ";
    std::getline(std::cin, name);

    // Get grade level
    std::cout << "Enter grade level (1=Freshman, 2=Sophomore, 3=Junior, 4=Senior): ";
    std::cin >> levelChoice;
    
    // Simple validation
    if (levelChoice >= FRESHMAN && levelChoice <= SENIOR) {
        student.level = static_cast<GradeLevel>(levelChoice);
    } else {
        std::cout << "Invalid grade level. Defaulting to Freshman." << std::endl;
        student.level = FRESHMAN;
    }

    // Get GPA
    std::cout << "Enter GPA: ";
    std::cin >> gpa;
    student.gpa = gpa;

    // Format the name (string operation)
    student.name = name;
    StudentUtils::formatName(student.name);

    // Display the student record
    StudentUtils::displayStudentInfo(student);

    // *** BONUS FEATURES START HERE ***
    
    std::cout << "\n=== BONUS FEATURES ===" << std::endl;
    
    // BONUS 1: Multiple student records
    std::vector<StudentRecord> students;
    students.push_back(student); // Add the first student we already processed
    
    // BONUS 2: GPA validation function
    auto validateGPA = [](double gpa) {
        return (gpa >= 0.0 && gpa <= 4.0);
    };
    
    // Ask if user wants to add more students
    char addMore;
    std::cout << "\nDo you want to add more students? (y/n): ";
    std::cin >> addMore;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    while (tolower(addMore) == 'y') {
        StudentRecord newStudent;
        
        // Get student name
        std::cout << "Enter student name: ";
        std::getline(std::cin, name);
        
        // Get grade level
        std::cout << "Enter grade level (1=Freshman, 2=Sophomore, 3=Junior, 4=Senior): ";
        std::cin >> levelChoice;
        
        // Validate grade level input
        while (levelChoice < FRESHMAN || levelChoice > SENIOR) {
            std::cout << "Invalid grade level. Please enter a number 1-4: ";
            std::cin >> levelChoice;
        }
        
        // Get GPA with validation
        std::cout << "Enter GPA: ";
        std::cin >> gpa;
        
        // BONUS 3: GPA validation
        while (!validateGPA(gpa)) {
            std::cout << "Invalid GPA. Please enter a value between 0.00 and 4.00: ";
            std::cin >> gpa;
        }
        
        // Clean input buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        // Set student record values
        newStudent.name = name;
        StudentUtils::formatName(newStudent.name);
        newStudent.level = static_cast<GradeLevel>(levelChoice);
        newStudent.gpa = gpa;
        
        // Add to vector
        students.push_back(newStudent);
        
        // Ask for another student
        std::cout << "\nDo you want to add another student? (y/n): ";
        std::cin >> addMore;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    // BONUS 3: Sort students alphabetically
    std::sort(students.begin(), students.end(),
              [](const StudentRecord& a, const StudentRecord& b) {
                  return a.name < b.name;
              });
    
    // Display all student records
    std::cout << "\n=== All Student Records (Alphabetical Order) ===" << std::endl;
    for (const auto& s : students) {
        StudentUtils::displayStudentInfo(s);
    }
    
    return 0;
}
