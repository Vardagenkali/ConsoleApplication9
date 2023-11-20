#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Reservoir {
private:
    std::string name;
    double width;
    double length;
    double maxDepth;

public:
    Reservoir() : name(""), width(0.0), length(0.0), maxDepth(0.0) {}

    explicit Reservoir(const std::string& _name, double _width, double _length, double _maxDepth)
        : name(_name), width(_width), length(_length), maxDepth(_maxDepth) {}

    ~Reservoir() {}

    Reservoir(const Reservoir& other)
        : name(other.name), width(other.width), length(other.length), maxDepth(other.maxDepth) {}

    double calculateVolume() const {
        return width * length * maxDepth;
    }

    double calculateSurfaceArea() const {
        return width * length;
    }

    bool areSameType(const Reservoir& other) const {
        return true; 
    }

    bool compareSurfaceArea(const Reservoir& other) const {
        if (areSameType(other)) {
            return calculateSurfaceArea() < other.calculateSurfaceArea();
        }
        return false;
    }


    void setName(const std::string& _name) {name = _name;}

    void setWidth(double _width) {width = _width;}

    void setLength(double _length) {length = _length;}

    void setMaxDepth(double _maxDepth) {maxDepth = _maxDepth;}

    const std::string& getName() const {return name;}

    double getWidth() const {return width;}

    double getLength() const {return length;}

    double getMaxDepth() const {return maxDepth;}

    void displayInfo() const {
        std::cout << "Reservoir: " << name << "\n";
        std::cout << "Width: " << width << " meters\n";
        std::cout << "Length: " << length << " meters\n";
        std::cout << "Max Depth: " << maxDepth << " meters\n";
        std::cout << "Volume: " << calculateVolume() << " cubic meters\n";
        std::cout << "Surface Area: " << calculateSurfaceArea() << " square meters\n";
    }
};

class ReservoirManager {
private:
    std::vector<Reservoir> reservoirs;

public:
    void addReservoir(const Reservoir& reservoir) {
        reservoirs.push_back(reservoir);
    }

    const std::vector<Reservoir>& getReservoirs() const {return reservoirs;}

    void removeReservoir(const std::string& name) {
        auto it = std::remove_if(reservoirs.begin(), reservoirs.end(),
            [&name](const Reservoir& reservoir) {
                return reservoir.getName() == name;
            });
        reservoirs.erase(it, reservoirs.end());
    }

    void saveToTextFile(const std::string& filename) const {
        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            for (const Reservoir& reservoir : reservoirs) {
                outFile << "Reservoir: " << reservoir.getName() << "\n";
                outFile << "Width: " << reservoir.getWidth() << " meters\n";
                outFile << "Length: " << reservoir.getLength() << " meters\n";
                outFile << "Max Depth: " << reservoir.getMaxDepth() << " meters\n";
                outFile << "Volume: " << reservoir.calculateVolume() << " cubic meters\n";
                outFile << "Surface Area: " << reservoir.calculateSurfaceArea() << " square meters\n";
                outFile << "\n";
            }
            outFile.close();
        }
        else {
            std::cerr << "Unable to open file: " << filename << std::endl;
        }
    }

    void saveToBinaryFile(const std::string& filename) const {
        std::ofstream outFile(filename, std::ios::binary);
        if (outFile.is_open()) {
            for (const Reservoir& reservoir : reservoirs) {
                outFile.write(reinterpret_cast<const char*>(&reservoir), sizeof(Reservoir));
            }
            outFile.close();
        }
        else {
            std::cerr << "Unable to open file: " << filename << std::endl;
        }
    }
};

int main() {
    ReservoirManager manager;

    Reservoir sea("Ocean", 1000.0, 2000.0, 50.0);
    Reservoir pool("Swimming Pool", 20.0, 30.0, 2.0);
    Reservoir pond("Fish Pond", 10.0, 15.0, 1.0);

    manager.addReservoir(sea);
    manager.addReservoir(pool);
    manager.addReservoir(pond);

    for (const Reservoir& reservoir : manager.getReservoirs()) {
        reservoir.displayInfo();
        std::cout << "-----------------------------\n";
    }

    manager.saveToTextFile("reservoirs.txt");

    manager.saveToBinaryFile("reservoirs.bin");

    return 0;
}
