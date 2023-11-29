#ifndef CAR_H
#define CAR_H
#include <string>
#include <ctime>
using namespace std;

enum CarColor{
RED, BLUE, YELLOW, GREEN, BLACK, GREY, NUM_COLORS
};

enum CarType{
ELECTRIC, HYBRID, GASOLINE, NUM_TYPES
};

class Car{
public:
int ID;
int salePrice;
std::string manu;
CarColor color;
CarType type;
bool isSold;
std::time_t soldTime;
Car();
Car(int id, int price, std::string input_manu, CarColor input_color, CarType input_type);
void SellCar(int &TotalSale);
void UpdatePrice(int newPrice);
};

class BMW : public Car{
    public:
    BMW();
    BMW(int id, int salePrice, std::string manu, CarColor color, CarType type);
};

class BENZ : public Car{
    public:
    BENZ();
    BENZ(int id, int salePrice, std::string manu, CarColor color, CarType type);
};

class TESLA : public Car{    
    public:
    bool isDiscount;
    TESLA();
    TESLA(int id, int salePrice, std::string manu, CarColor color, CarType type);
};
#endif
