#include <iostream>
#include <fstream> // For file operations
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

class item{
public:
    string name;
    int price;
    int quantity;
    item(string n, int p, int q): name(n), price(p), quantity(q) {
    }
};


class list{
public:
    vector<item> items;
    void add(item ITEM){
        items.push_back(ITEM);
    }
    void remove(item ITEM){
        if(items.empty()){
            cout << "List is empty" << endl;
            return;
        }
        for(int i=0;i<items.size();i++){
            if(items[i].name==ITEM.name){
                items.erase(items.begin()+i);
                return;
        }
    }
    cout << "Item not found" << endl;
    }


};

class billing_system{
    private:
        list item_list;
    public:
        int percent_tax;
        void bill_total(list item_list,ostream& out){
            int sum=0;
            for (auto item : item_list.items){
                sum+=item.price*item.quantity;
            }
            sum=sum + (sum*percent_tax)/100;
            out << "Total bill (including " << percent_tax << "% tax): " << sum << endl;
        }

        void invoice(list item_list,ostream& out){
            out << "Invoice:" << endl;
            for (auto item : item_list.items){
                out << item.name << ": " << item.price << " "<< item.quantity<< endl;
            }
            bill_total(item_list, out);
        }

};

int main(){
    list my_list;
    my_list.add(item("Apple", 100, 2));
    my_list.add(item("Banana", 50, 5));
    my_list.add(item("Orange", 80, 3));

    billing_system bs;
    bs.percent_tax = 18; // Setting tax percentage

    fstream myFile;
    myFile.open("invoice.txt", ios::out);
    if(myFile.is_open()){
        bs.invoice(my_list,myFile);    
    }
    myFile.close();


    return 0;
}