#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

class DataElement {
public:
    virtual void printData() = 0;
    virtual ~DataElement() {} // Virtual destructor is important for polymorphic deletion
    virtual std::string toString() = 0; // Add a toString method for saving to file
};

class IntegerElement : public DataElement {
    private:
        int data;
    public:
        IntegerElement(int data) : data(data) {}
        void printData() override { 
            std::cout << "Integer: " << data << std::endl; 
        }
        std::string toString() override { 
            return "Integer:" + std::to_string(data); 
        }
};

class StringElement : public DataElement {
    private:
        std::string data;
    public:
        StringElement(std::string data) : data(data) {}
        void printData() override { std::cout << "String: " << data << std::endl; }
        std::string toString() override { return "String:" + data; }
};

class FloatElement : public DataElement {
    private:
        float data;
    public:
        FloatElement(float data) : data(data) {}
        void printData() override { std::cout << "Float: " << data << std::endl; }
        std::string toString() override { return "Float:" + std::to_string(data); }
};

class DataList {
    private:
        std::vector<DataElement*> elements;
    public:
        void addElement(DataElement* element) {
            elements.push_back(element);
        }

        void removeElement(DataElement * element) {
            auto it = std::remove(elements.begin(), elements.end(), element);
            if (it != elements.end()) {
                delete *it; // Free the memory
                elements.erase(it, elements.end());
            }
        }

        void printAllElements() {
            for (auto& element : elements) {
                element->printData();
            }
        }

        void sort() {
            std::sort(elements.begin(), elements.end(), [](DataElement* a, DataElement* b) {
                return a->toString() < b->toString();
            });
        }

        void saveToFile(const std::string& filename) {
            std::ofstream file(filename);
            if (file.is_open()) {
                for (auto& element : elements) {
                    file << element->toString() << std::endl;
                }
                file.close();
            } else {
                std::cerr << "Unable to open file for writing." << std::endl;
            }
        }

        void loadFromFile(const std::string& filename) {
            std::ifstream file(filename);
            if (file.is_open()) {
                std::string line;
                while (std::getline(file, line)) {
                    if (line.find("Integer:") == 0) {
                        int value = std::stoi(line.substr(8));
                        addElement(new IntegerElement(value));
                    } else if (line.find("String:") == 0) {
                        std::string value = line.substr(7);
                        addElement(new StringElement(value));
                    } else if (line.find("Float:") == 0) {
                        float value = std::stof(line.substr(6));
                        addElement(new FloatElement(value));
                    }
                }
                file.close();
            } else {
                std::cerr << "Unable to open file for reading." << std::endl;
            }
        }

        // Destructor to clean up dynamically allocated memory
        ~DataList() {
            for (auto& element : elements) {
                delete element; // Free the memory
            }
        }
};     

int main() {
    DataList myList;
    myList.addElement(new IntegerElement(10));
    myList.addElement(new StringElement("Hello"));
    myList.addElement(new FloatElement(3.14f));

    myList.printAllElements();

    myList.saveToFile("data.txt");

    DataList newList;
    newList.loadFromFile("data.txt");
    std::cout << "Loaded from file:" << std::endl;
    newList.printAllElements();

    newList.sort();
    std::cout << "Sorted list:" << std::endl;
    newList.printAllElements();

    return 0;
}