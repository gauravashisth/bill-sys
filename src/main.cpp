#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unistd.h>

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
  std::cout << "\033[2J\033[H";
  // /033[2j -> clears the entire screen
  // /033[H -> moves cursor to top left corner
}

void add(bill b) {
  while (true) {
    int choice;
    std::cout<< "\n\n";
    std::cout << "\t1. add item\n";
    std::cout << "\t2. close the window\n";
    std::cout << "\tenter the choice: ";
    std::cin >> choice;

    if (choice == 1) {
      clearscreen();
      std::string item;
      int rate, qty;

      std::cout<< "\n\n";
      std::cout << "\tenter the item name: ";
      std::cin.ignore(); // ignores any leftover new line character
      std::getline(std::cin, item);
      b.setItem(item);
      std::cout << "\tenter the item rate: ";
      std::cin >> rate;
      b.setRate(rate);
      std::cout << "\tenter the quantity of item: ";
      std::cin >> qty;
      b.setQuant(qty);

      // defines the path of file, where all the item details are stored
      std::string path = std::string(std::getenv("HOME")) +
                         "/Projects/billing-sys/src/extars/items.txt";
      // output the user inputs into a specified file
      // std::ios::app, appends next input in file
      std::ofstream items(path, std::ios::app);

      if (!items) {
        std::cout << "\terror: file not found\n";
      } else {
        items << "\t" << b.getItem() << " : " << b.getRate() << " : "
              << b.getQuant() << "\n\n";
      }
      // closes the file, items.txt
      items.close();
      std::cout << "\t"<< item<< " is added to the bill\n";
      sleep(2);  //inputs value is in seconds
    } else if (choice == 2) {
      clearscreen();
      std::cout << "\tback to main menu\n";
      break;
    }
  }
}

int main() {
  bill b;

  while (true) {
    clearscreen();
    std::string input;
    std::cout<< "\n\n";
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
