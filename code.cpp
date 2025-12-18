#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

class item {
public:
    string name;
    int price;
    int quantity;

    item(string n, int p, int q)
        : name(n), price(p), quantity(q) {}
};

class list {
public:
    vector<item> items;

    // Read items from a text file
    void load_from_file(istream& in) {
    string line;

    cout << "Reading file...\n";

    while (getline(in, line)) {
        if (line.empty()) continue;

        // Remove UTF-8 BOM if present
        if (line.size() >= 3 &&
            (unsigned char)line[0] == 0xEF &&
            (unsigned char)line[1] == 0xBB &&
            (unsigned char)line[2] == 0xBF) {
            line = line.substr(3);
        }

        string name;
        int price, quantity;

        stringstream ss(line);
        ss >> name >> price >> quantity;

        if (ss.fail()) {
            cout << "Skipped line: [" << line << "]\n";
            continue;
        }

        items.emplace_back(name, price, quantity);
        cout << "Read: " << name << " " << price << " " << quantity << endl;
    }

    cout << "Finished reading. Items loaded: " << items.size() << endl;
}

};

class billing_system {
public:
    int percent_tax;

    void bill_total(const list& item_list, ostream& out) {
        int sum = 0;
        for (const auto& it : item_list.items) {
            sum += it.price * it.quantity;
        }
        sum += (sum * percent_tax) / 100;

        out << "Total bill (including "
            << percent_tax << "% tax): "
            << sum << endl;
    }

    void invoice(const list& item_list, ostream& out) {
        out << "Invoice:\n";
        for (const auto& it : item_list.items) {
            out << it.name << " "
                << it.price << " "
                << it.quantity << endl;
        }
        bill_total(item_list, out);
    }
};

int main() {
    list my_list;

    ifstream inFile("shoppingbag.txt");
    if (!inFile.is_open()) {
        cout << "Could not open input file\n";
        return 1;
    }

    my_list.load_from_file(inFile);
    inFile.close();

    billing_system bs;
    bs.percent_tax = 18;

    ofstream outFile("invoice.txt");
    if (!outFile.is_open()) {
        cout << "Could not open output file\n";
        return 1;
    }

    bs.invoice(my_list, outFile);
    outFile.close();

    return 0;
}
