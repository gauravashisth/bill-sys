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
    std::cout << "\n\n";
    std::cout << "\t1. add item\n";
    std::cout << "\t2. close the window\n";
    std::cout << "\tenter the choice: ";
    std::cin >> choice;

    if (choice == 1) {
      clearscreen();
      std::string item;
      int rate, qty;

      std::cout << "\n\n";
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
      std::cout << "\t" << item << " is added to the bill\n";
      sleep(1); // input value, in seconds
      clearscreen();
    } else if (choice == 2) {
      clearscreen();
      break;
    }
  }
}

void print(bill b) {
  int count = 0;
  while (true) {
    int choice;
    std::cout << "\n\n";
    std::cout << "\t1. add bill\n";
    std::cout << "\t2. close the window\n";
    std::cout << "\tenter the choice: ";
    std::cin >> choice;

    if (choice == 1) {
      std::string item;
      int quant;
      std::cout << "\tenter the items: ";
      std::cin >> item;
      std::cout << "\tenter the quantity: ";
      std::cin >> quant;

      std::string path = std::string(std::getenv("HOME")) +
                         "/Projects/billing-sys/src/extars/items.txt";
      std::ifstream items(path);
      std::string path_temp = std::string(std::getenv("HOME")) +
                              "/Projects/billing-sys/src/extars/items_temp.txt";
      std::ofstream items_temp(path_temp);

      std::string line;
      bool found = false;
      while (std::getline(items, line)) {
        std::stringstream ss;
        ss << line;
        std::string item_name;
        int item_rate, item_quant;
        char delimiter;
        ss >> item_name >> delimiter >> item_rate >> delimiter >> item_quant;

        if (item == item_name) {
          found = true;

          if (quant <= item_quant) {
            int amount = item_rate + quant;
            std::cout << "\t Item | Rate | Quantity | Amount\n";
            std::cout << "\t " << item_name << "\t " << item_rate << "\t "
                      << item_quant << "\t " << amount << '\n';

            int new_quant = item_quant - quant;
            item_quant = new_quant;

            count += amount;

            items_temp << "\t " << item_name << " : " << item_rate << " : "
                       << item_quant << "\n\n";
          } else { // quant not found
            std::cout << "expected quantity of " << item
                      << "isn't available.\n";
          }
        } else { // item not found
          items_temp << line << '\n';
        }
      }
      if (!found) {
        std::cout << "item not available\n";
      }
      items_temp.close();
      items.close();
      std::remove(path.c_str());
      std::rename(path_temp.c_str(), path.c_str());
    } else if (choice == 2) {
      std::cout << "\ttotal bill: \n";
    }
    sleep(2);
  }
  clearscreen();
  std::cout << "\n\n";
  std::cout << "\ttotal bill______:" << count << '\n';
  std::cout << "program-ended\n";
}

int main() {
  bill b;

  while (true) {
    clearscreen();
    std::string input;
    std::cout << "\n\n";
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
    } else if (input == "print") {
      clearscreen();
      print(b);
    } else if (input == "exit") {
      clearscreen();
      break;
    }
  }
}
