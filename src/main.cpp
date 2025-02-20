#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

class bill {
private:
  std::string Item;
  int Rate, Quantity;

public:
  bill() : Item(""), Rate(0), Quantity(0) {}
  void setItem(std::string item) { Item = item; }
  void setRate(int rate) { Rate = rate; }
  void setQuant(int quant) { Quantity = quant; }

  std::string getItem() { return Item; }
  int getRate() { return Rate; }
  int getQuant() { return Quantity; }
};

void clearscreen() {
  // /033[2j -> clears the entire screen
  // /033[H -> moves cursor to top left corner
  std::cout << "\033[2J\033[H";
}

void add(bill b) {
  bool status = false;
  while (!status) {
    int choice;
    std::cout << "\t1. add item\n";
    std::cout << "\t2. close the window\n";
    std::cout << "\tenter the choice: \n";
    std::cin >> choice;

    if (choice == 1) {
      clearscreen();
      std::string item;
      int rate, qty;

      std::cout << "enter the item name: \n";
      std::cin.ignore(); // ignores any leftover new line character
      std::getline(std::cin, item);
      b.setItem(item);
      std::cout << "enter the item rate: \n";
      std::cin >> rate;
      b.setRate(rate);
      std::cout << "enter the quantity of item: \n";
      std::cin >> qty;
      b.setQuant(qty);

      std::string path = std::string(std::getenv("HOME")) +
                         "/Projects/billing-sys/src/extars/items.txt";
      std::ofstream items(path, std::ios::app);

      if (!items) {
        std::cout << "\terror: file not found\n";
      } else {
        items << "\t" << b.getItem() << " : " << b.getRate() << " : "
              << b.getQuant() << "\n\n";
      }

      items.close();
      std::cout << "item is added successfully\n";
      // check 23:30
    } else if (choice == 2) {
      clearscreen();
      std::cout << "\tback to main menu\n";
      status = true;
    }
  }
}

int main() {
  bill b;

  while (true) {
    clearscreen();
    std::string input;
    std::cout << "\tBilling Syatem\n";
    std::cout << "\t——————————————\n";
    std::cout << "\t\t1. adding items\n";
    std::cout << "\t\t2. print the bill\n";
    std::cout << "\t\t3. exit program\n\n";
    std::cout << "\t\tenter the choice: ";
    std::cin >> input;

    if (input == "add") {
      clearscreen();
      add(b);
    }
  }
}
