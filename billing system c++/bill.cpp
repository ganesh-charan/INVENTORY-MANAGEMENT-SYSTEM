#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <vector>
using namespace std;

class Admin {
    struct Item {
        string name;
        int id;
        int avl_q;
        double price;
    };
    vector<Item> inventory;
    void add_to_files(Item &it)
    {
        fstream file("menu.txt",ios::app);
        if(!file)
        {
            cerr<<"\033[1;36mError opening file\033[0m"<<endl;
            return;
        }
        file<<left<<setw(10)<<it.id<<setw(10)<<it.name<<setw(10)<<it.price<<setw(10)<<it.avl_q<<endl;
        file.close();
    }
    void load_from_file()
    {
        inventory.clear();
        fstream file("menu.txt",ios::in);
        if(!file)
        {
         cerr<<"\033[1;30mError opening file\033[0m"<<endl;
           return;
        }
        Item temp;
        while(file>>temp.id>>temp.name>>temp.price>>temp.avl_q)
        {
            inventory.push_back(temp);
        }
        file.close();
        cout<<"\033[1;36mEXISTING MENU CARD\033[0m"<<endl;
        cout<<left<<setw(26)<<"\033[1;33mitem id\033[0m"
                  <<setw(26)<<"\033[1;33mitem name\033[0m"
                  <<setw(26)<<"\033[1;33mitem price\033[0m"
                  <<setw(26)<<"\033[1;33mitem available quantity\033[0m"<<endl;
        for(int i=0;i<inventory.size();i++)
        {
            cout<<left<<setw(15)<<inventory[i].id
                      <<setw(15)<<inventory[i].name
                      <<setw(15)<<inventory[i].price
                      <<setw(15)<<inventory[i].avl_q
                      <<endl;
        }

    }

public:
    void load()
    {
        load_from_file();
    }
    int update_quantity(string name,int qty)
    {
        int found=0;
        for(int i=0;i<inventory.size();i++)
        {
            if(inventory[i].name==name)
            {
                inventory[i].avl_q-=qty;
                found=1;
                return  inventory[i].avl_q;
                break;
            }
        }
        fstream file("menu.txt",ios::out|ios::trunc);
        file.close();
        for(int i=0;i<inventory.size();i++)
        {
            Item temp;
            temp=inventory[i];
            add_to_files(temp);
        }
        if(found==0){
            cout << "\033[1;36mInvalid Order Name \033[0m"<<endl;
            return -1;
        }
        return 0;
    }

    int get_available(string name) {
        for (auto &i : inventory)
            if (i.name == name) return i.avl_q;
        return 0;
    }

    void add_item() {
        Item new_item;
        string input;
        while (true) {
            cout << "\033[1;36mEnter id no (leave empty to stop): \033[0m";
            getline(cin, input);
            if (input.empty()) break;
            new_item.id = stoi(input);
            cout << "\033[1;36mEnter item name: \033[0m";
            getline(cin, new_item.name);

            cout << "\033[1;36mEnter price of item: \033[0m";
            cin >> new_item.price;

            cout << "\033[1;36mEnter quantity of item available: \033[0m";
            cin >> new_item.avl_q;
            cin.ignore();

            inventory.push_back(new_item);
            add_to_files(new_item);
        }
    }

    int getid(int update_id) {
        for (int i = 0; i < inventory.size(); i++)
            if (inventory[i].id == update_id) return i;
        return -1;
    }

    void search_id() {
        int id;
        cout << "\033[1;33mEnter id_no of item to search: \033[0m";
        cin >> id;
        cin.ignore();
        int result = getid(id);
        if (result == -1) cout << "\033[1;31mItem is not present.\033[0m\n";
        else cout << "\033[1;32m" << inventory[result].name << " item is present.\033[0m\n";
    }

    void delete_list() {
        fstream file("menu.txt", ios::out | ios::trunc);
        file.close();
        int id;
        cout << "\033[1;33mEnter id_no to delete: \033[0m";
        cin >> id;
        cin.ignore();
        int r = getid(id);
        if (r != -1) {
            string confirm;
            cout << "\033[1;31mARE YOU SURE? (yes/no): \033[0m";
            getline(cin, confirm);
            if (confirm == "yes" || confirm == "YES") {
                inventory.erase(inventory.begin() + r);
                cout << "\033[1;32mItem deleted.\033[0m\n";
            } else cout << "\033[1;33mDeletion cancelled.\033[0m\n";
        } else cout << "\033[1;31mItem not found.\033[0m\n";
        for(int i=0;i<inventory.size();i++)
        {
            Item temp;
            temp=inventory[i];
            add_to_files(temp);
        }
    }

    void update_list() {
      fstream file("menu.txt", ios::out | ios::trunc);
        file.close();
        int id;
        cout << "\033[1;33mEnter id to be updated: \033[0m";
        cin >> id;
        cin.ignore();
        int res = getid(id);
        if (res == -1) {
            cout << "\033[1;31mItem is not present.\033[0m\n";
            return;
        }

        cout << left << setw(10) << "1" << "Update id\n";
        cout << left << setw(10) << "2" << "Update name\n";
        cout << left << setw(10) << "3" << "Update price\n";
        cout << left << setw(10) << "4" << "Update quantity available\n";

        int choice;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                int newid;
                cout << "Enter new id: ";
                cin >> newid;
                cin.ignore();
                inventory[res].id = newid;
                break;
            }
            case 2: {
                string name;
                cout << "Enter new name: ";
                getline(cin, name);
                inventory[res].name = name;
                break;
            }
            case 3: {
                double price;
                cout << "Enter new price: ";
                cin >> price;
                cin.ignore();
                inventory[res].price = price;
                break;
            }
            case 4:
                {
                    int a;
                    cout<<"Enter new available quantity: ";
                    cin>>a;
                    cin.ignore();
                    inventory[res].avl_q = a;
                    break;
                }
            default: cout << "\033[1;31mInvalid choice.\033[0m\n";
        }
         for(int i=0;i<inventory.size();i++)
        {
            Item temp;
            temp=inventory[i];
            add_to_files(temp);
        }
    }

    double getprice(string item) {
        for (auto &i : inventory)
            if (i.name == item) return i.price;
        return 0.0;
    }
};

class billing_system {
protected:
    string item;
    int qty;
public:
    void item_details(string s, int q)
     { item = s; qty = q; }
    string getitem() { return item; }
    int getqty() { return qty; }
};

class show : public billing_system {
public:
    void bill(vector<billing_system> &order, Admin &ad)
     {
        fstream file("bill.txt", ios::app);
        double grandTotal = 0;

        cout << "\033[1;33m";
        cout << left << setw(15) << "Item" << setw(10) << "Qty"
             << setw(10) << "Price" << setw(10) << "Total" << endl;
        cout << "\033[0m";
        file << left << setw(15) << "Item" << setw(10) << "Qty"
             << setw(10) << "Price" << setw(10) << "Total" << endl;

        for (auto &o : order)
        {
            string it = o.getitem();
            int q = o.getqty();
            double price = ad.getprice(it);
            int avl = ad.get_available(it);
            if(price==0) {
                cout<<"item not there"<<endl;
            }
            else if(avl < q) {
                cout << "\033[1;36mItem availability is short \033[0m"<<endl;
            }
            else {
                ad.update_quantity(it,q);
                double total = price * q;
                grandTotal += total;

                cout << left << setw(15) << it << setw(10) << q
                     << setw(10) << price << setw(10) << total << endl;
                file << left << setw(15) << it << setw(10) << q
                     << setw(10) << price << setw(10) << total << endl;
            }
        }

        auto now = chrono::system_clock::now();
        time_t ct = chrono::system_clock::to_time_t(now);

        cout << "---------------------------------------\n";
        cout << left << setw(35) << "Grand Total: " << grandTotal << endl;
        cout << left << setw(35) << "Time: " << put_time(localtime(&ct), "%H:%M:%S") << endl;
        cout << left << setw(35) << "Date: " << put_time(localtime(&ct), "%y-%m-%d") << endl;
        cout << "---------------------------------------\n";

        file << "---------------------------------------\n";
        file << left << setw(35) << "Grand Total: " << grandTotal << endl;
        file << left << setw(35) << "Time: " << put_time(localtime(&ct), "%H:%M:%S") << endl;
        file << left << setw(35) << "Date: " << put_time(localtime(&ct), "%y-%m-%d") << endl;
        file << "---------------------------------------\n";
        file.close();
     }
};

int main() {
    Admin ad;

    while (true) {
            ad.load();
        string user;
        cout << "\033[1;36mEnter username (admin/cashier) or 'exit' to quit: \033[0m";
        cin >> user;
        cin.ignore();
        if (user == "exit") break;

        if (user == "admin") {
                cout << "\n\033[1;34mAdmin Menu:\033[0m\n";
                cout << left << setw(10) << "1." << "Add items to list\n";
                cout << left << setw(10) << "2." << "Update items of list\n";
                cout << left << setw(10) << "3." << "Delete items from list\n";
                cout << left << setw(10) << "4." << "Search items on list\n";
                cout << left << setw(10) << "5." << "Exit admin menu\n";
            while (true) {


                int choice;
                cout << "\033[1;36mEnter choice: \033[0m";
                cin >> choice;
                cin.ignore();

                switch (choice) {
                    case 1: ad.add_item(); break;
                    case 2: ad.update_list(); break;
                    case 3: ad.delete_list(); break;
                    case 4: ad.search_id(); break;
                    case 5: goto end_admin;
                    default: cout << "\033[1;31mInvalid choice.\033[0m\n";
                }
            }
            end_admin:;
        } else if (user == "cashier") {
            vector<billing_system> order;
            string name;
            int q;
            cout << "\033[1;36mEnter your order (type 'done' to finish):\033[0m\n";
            while(true) {
                cout<<"Item name: ";
                cin >> name;
                if(name=="done") break;
                cout<<"Quantity: ";
                cin >> q;
                billing_system o;
                o.item_details(name,q);
                order.push_back(o);
            }
            show s;
            s.bill(order, ad);
        } else {
            cout << "\033[1;31mInvalid user!\033[0m\n";
        }
    }

    return 0;
}
