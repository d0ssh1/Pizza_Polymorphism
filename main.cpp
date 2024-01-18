#include <iostream>
#include <string>
#include "vector"
#include "limits"

using namespace std;

class PrintSmth {
public:
    virtual string Print() = 0;
};

class Ingredient : public PrintSmth {
public:
    string name;
    int price;

    string Print() override {
        return name;
    }
};

class Tomato : public Ingredient {
private:
    string name = "Pomidorka";
    int price_factor = 5;
public:
    int getPriceFactor() const {
        return price_factor;
    }
};

class Pepperoni : public Ingredient {
private:
    string name = "Kolbaska";
    int price_factor = 7;
public:
    int getPriceFactor() const {
        return price_factor;
    }
};

class Olives : public Ingredient {
private:
    string name = "Olivochki";
    int price_factor = 6;
public:
    int getPriceFactor() const {
        return price_factor;
    }
};

class Mushrooms : public Ingredient {
private:
    string name = "Gribochki";
    int price_factor = 8;
public:
    int getPriceFactor() const {
        return price_factor;
    }
};

class Pizza : public PrintSmth {
public:
    Pizza(const string &n, int s, const string &description, int ingredientCount) : name(n),
                                                                                    description(
                                                                                            description),
                                                                                    size(s),
                                                                                    ingredientCount(
                                                                                            ingredientCount) {}

    string name;
    string description;
    int salt = 1;
    int cheese = 1;
    int ingredientCount = 0;
    short int size = 1; // 1 = 25 = 1, 2 = 30 = 1.25, 3 = 35 = 1.5, 4 = 40 = 1.75. Коэффициенты для ингредиентов
    int price = 0;

    void setSalt(int salt) {
        Pizza::salt = salt;
    }

    int getSalt() const {
        return salt;
    }

    void setCheese(int cheese) {
        Pizza::cheese = cheese;
    }

    int getCheese() const {
        return cheese;
    }

    int getPrice() const {
        return price;
    }

    void setPrice() {
        Tomato tomato;
        Olives olives;
        Mushrooms mushrooms;
        Pepperoni pepperoni;

        float sizeFactor;
        switch (size) {
            case 25:
                sizeFactor = 1;
                break;
            case 30:
                sizeFactor = 1.25;
                break;
            case 35:
                sizeFactor = 1.5;
                break;
            case 40:
                sizeFactor = 1.75;
                break;
        }

        const int mushroomPrice = mushrooms.getPriceFactor();
        const int olivePrice = olives.getPriceFactor();
        const int tomatoPrice = tomato.getPriceFactor();
        const int pepperoniPrice = pepperoni.getPriceFactor();

        Pizza::price =
                250 +
                (sizeFactor * (ingredientCount * (mushroomPrice + olivePrice + tomatoPrice + pepperoniPrice) + cheese +
                               salt));
    }

    void moreSalt() {
        int saltNow = Pizza::getSalt();
        Pizza::setSalt(++saltNow);
    }

    void moreCheese() {
        int cheeseNow = Pizza::getCheese();
        Pizza::setCheese(++cheeseNow);
    }

    string Print() override {
        return name;
    }
};

void Menu() {
    vector<Pizza> pizzaOrderVector;
    while (true) {
        int variant;
        bool nameExist;
        cout << "----------------\n";
        cout << "What you would like to do?\n";
        cout << "1. Create new pizza!\n";
        cout << "2. Delete pizza :(\n";
        cout << "3. Make more salt! (1 portion)\n";
        cout << "4. Make more cheese! (1 portion)\n";
        cout << "5. Print your order\n";
        cout << "6. Finish my work (plz)\n";
        cout << "----------------\n";

        cin >> variant;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистка буфера

        switch (variant) {
            case 1: {
                string name, descr;
                int ingr_count, size;

                do {
                    cout << "Name your pizza to not be confused\n";
                    getline(cin, name);

                    nameExist = false;
                    for (auto &pizza: pizzaOrderVector) {
                        if (pizza.name == name) {
                            cout << "Pizza with this name is already exist! Try again.\n";
                            nameExist = true;
                            break;
                        }
                    }
                } while (nameExist);
                cout << "How much ingredients do you want? (Tomatos, mushrooms, pepperoni, olives)\n";
                cin >> ingr_count;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "How you can describe your pizza?\n";
                getline(cin, descr);
                cout << "What about size? 25, 30, 35 or 40 cm\n";
                cin >> size;
                if (!(size == 25 || size == 30 || size == 35 || size == 40)) {
                    cout << "That's wrong size! Try again or I will delete all your order! >:(\n";
                    cin >> size;
                    if (!(size == 25 || size == 30 || size == 35 || size == 40)) { break; }
                }
                Pizza pizza(name, size, descr, ingr_count);
                cout << "Great! Your pizza in the order!\n";
                pizza.setPrice();
                pizzaOrderVector.push_back(pizza);
                break;
            }
            case 2: {
                string name_delete;
                cout << "Which one pizza do you want to delete? Enter name please\n";
                getline(cin, name_delete);
                for (auto it = pizzaOrderVector.begin(); it != pizzaOrderVector.end();) {
                    if (it->name == name_delete) {
                        it = pizzaOrderVector.erase(it);
                    } else {
                        ++it;
                    }
                }
                break;
            }
            case 3: {
                string moresaltpizzaname;
                cout << "Please enter which pizza you want to make saltier\n";
                getline(cin, moresaltpizzaname);
                for (auto &pizza: pizzaOrderVector) {
                    if (pizza.name == moresaltpizzaname) {
                        pizza.setSalt(pizza.getSalt() + 1);
                    } else {
                        cout << "Name error\n";
                    }
                }
                cout << "Salt was added succesfully!\n";
                break;
            }
            case 4: {
                string morecheesepizzaname;
                cout << "Please enter which pizza you want to make cheesier\n";
                getline(cin, morecheesepizzaname);
                for (auto &pizza: pizzaOrderVector) {
                    if (pizza.name == morecheesepizzaname) {
                        pizza.setCheese(pizza.getCheese() + 1);
                    } else {
                        cout << "Name error\n";
                    }
                }
                cout << "Cheese was added succesfully!\n";
                break;
            }
            case 5: {
                cout << "Your order is:\n";
                for (Pizza pizza: pizzaOrderVector) {
                    cout << "----------------\n";
                    cout << "Name: " << pizza.Print() << endl; // Полиморфизм в деле!
                    cout << "Description: " << pizza.description << endl;
                    cout << "Salt: " << pizza.getSalt() << endl;
                    cout << "Cheese: " << pizza.getCheese() << endl;
                    cout << "Size: " << pizza.size << endl;
                    cout << "Price: " << pizza.getPrice() << endl;
                }
                int totalPrice = 0;
                for (auto &pizza: pizzaOrderVector) {
                    totalPrice += pizza.price;
                }
                cout << endl;
                cout << "Total price: " << totalPrice << endl;
                break;
            }
            case 6: {
                return; // Выход
            }
            default: {
                cout << "Invalid option, please try again.\n";
                break;
            }
        }
    }
}

int main() {
    Menu();
    return 0;
}
