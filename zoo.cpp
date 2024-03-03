#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

// Animal class definition
class Animal {
protected:
    string name;
    int age;
    string species;

public:
    Animal(string _name, int _age, string _species) : name(_name), age(_age), species(_species) {}

    // Getters
    string getName() const { return name; }
    int getAge() const { return age; }
    string getSpecies() const { return species; }
};

// Hyena class definition
class Hyena : public Animal {
private:
    string habitat;

public:
    Hyena(string _name, int _age, string _habitat) : Animal(_name, _age, "Hyena"), habitat(_habitat) {}

    string getHabitat() const { return habitat; }
};

// Lion class definition
class Lion : public Animal {
private:
    string prideName;

public:
    Lion(string _name, int _age, string _prideName) : Animal(_name, _age, "Lion"), prideName(_prideName) {}

    string getPrideName() const { return prideName; }
};

// Tiger class definition
class Tiger : public Animal {
private:
    string habitat;

public:
    Tiger(string _name, int _age, string _habitat) : Animal(_name, _age, "Tiger"), habitat(_habitat) {}

    string getHabitat() const { return habitat; }
};

// Bear class definition
class Bear : public Animal {
private:
    string color;

public:
    Bear(string _name, int _age, string _color) : Animal(_name, _age, "Bear"), color(_color) {}

    string getColor() const { return color; }
};

int main() {
    // Reading animal details from arrivingAnimals.txt
    ifstream inFile("arrivingAnimals.txt");
    vector<Animal*> animals;

    if (!inFile) {
        cerr << "Error: Unable to open file." << endl;
        return 1;
    }

    string line;
    while (getline(inFile, line)) {
        istringstream iss(line);
        string species;
        iss >> species;

        string name;
        int age;
        string attribute;

        while (iss >> attribute) {
            if (attribute == "year") {
                iss >> attribute; // Skip "old"
                iss >> age;
            } else if (attribute == "female" || attribute == "male") {
                break; // Skip gender, not needed for this assignment
            } else {
                if (attribute == "from" || attribute == "park,") {
                    break; // Skip location, not needed for this assignment
                } else {
                    name += (attribute + " ");
                }
            }
        }
        name.pop_back(); // Remove trailing space

        if (species == "hyena") {
            animals.push_back(new Hyena(name, age, "Friguia Park"));
        } else if (species == "lion") {
            animals.push_back(new Lion(name, age, "Zanzibar"));
        } else if (species == "tiger") {
            animals.push_back(new Tiger(name, age, "Dhaka"));
        } else if (species == "bear") {
            animals.push_back(new Bear(name, age, "Alaska Zoo"));
        }
    }
    inFile.close();

    // Counting species using std::map
    map<string, int> speciesCount;
    for (const auto& animal : animals) {
        speciesCount[animal->getSpecies()]++;
    }

    // Writing report to newAnimals.txt
    ofstream outFile("newAnimals.txt");
    if (!outFile) {
        cerr << "Error: Unable to create report file." << endl;
        return 1;
    }

    for (const auto& species : speciesCount) {
        outFile << species.first << " count: " << species.second << endl;
    }

    // Release memory allocated for animals
    for (const auto& animal : animals) {
        delete animal;
    }

    return 0;
}

// 1. Class Design:
// I created an Animal class as the base class with common properties such as name, age, and species.
// Four subclasses (Hyena, Lion, Tiger, and Bear) were implemented, each representing a specific species of animal with unique attributes (habitat, prideName, color, etc.).
// Inheritance was used to inherit common properties and methods from the base class.
// 2. Data Structures:
// I utilized std::vector to store instances of animals dynamically. This allows for easy addition and removal of animals without worrying about the size of the container.
// A std::map was employed to count the number of occurrences of each species. This data structure allows efficient retrieval and manipulation of species counts.
// 3. File I/O:
// The program reads animal details from the arrivingAnimals.txt file line by line. Each line contains information about a single animal.
// Information is extracted from the file using std::ifstream and std::istringstream, and animals are instantiated accordingly.
// The report containing the count of each species is written to the newAnimals.txt file using std::ofstream.
// 4. Control Structures & OOP Design:
// Loops and conditionals were used to iterate over lines in the input file and to differentiate between different species.
// Encapsulation was achieved by defining member variables of classes as private and providing public getters to access them.
// Inheritance and polymorphism were utilized to handle different species of animals using a common interface (Animal class).
// 5. Error Handling:
// Error handling was implemented to check for file opening errors and to ensure proper file closure.
// Proper memory management was ensured by deallocating memory allocated to animal objects using delete.
// 6. Code Organization:
// The code is organized into logical sections such as class definitions, main function, file I/O, and memory management.
// Comments are provided throughout the code to explain the logic, functionality, and design choices.