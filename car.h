#ifndef CAR_H
#define CAR_H
#include <string>
#include <random>
#include <chrono>
using namespace std::literals::string_literals; // For the 's' suffix
extern int id_generator;
extern std::mt19937 mt;

enum CarColor{
Red, Blue, Yellow, Green, Black, Grey, Pink, Gold, White, NUM_COLORS // Pink, Gold, White are only available for customizing.
};
std::string ColorToString(CarColor c);

enum CarType{
Electric, Hybrid, Gasoline, NUM_TYPES
};
std::string TypeToString(CarType t);

class Car{
    protected:
    int id{0};
    int price{0};
    std::string brand{"None"s};
    CarColor color;
    CarType type;

    public:
    Car();
    void virtual Customize(const CarColor& customizeColor);
    void GetInfo() const;
    void WriteInfo(std::string filename) const;
    int GetPrice() const;
    int GetId() const;
    CarColor GetColor() const;
    CarType GetType() const;
    std::string GetBrand() const;
    bool virtual GetIsDiscount();
    void virtual SetDiscount();
    friend bool operator ==(const Car& m, const Car& n);
    friend bool operator !=(const Car& m, const Car& n);
    friend bool operator <(const Car& m, const Car& n);
    virtual ~Car() = default;
};

class BWM : public Car{
    public:
    BWM();
    void Customize(const CarColor& customizeColor) override;
};

class Marcedes : public Car{
    public:
    Marcedes();
    void Customize(const CarColor& customizeColor) override;
};

class TELAS : public Car{
    bool isDiscount{false};

    public:
    TELAS();
    bool GetIsDiscount() override;
    void SetDiscount() override;
    void Customize(const CarColor& customizeColor) override;
};

#endif
