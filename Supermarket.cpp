// Supermarket.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//Request that please go through all the comments and according to it give the input. 

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

// Here the entire inventory database and customer database are stored with the help of hashing with chaining in an inventory because while searching any particular item or 
// customer from the respective inventory the time taken will be very less compared to that of linked list or any other data structure like hasing with probing,etc.

//Structure of the item in supermarket as item has the attributes like item_id,item_name,rate,available quantity associated with it.
struct item
{
    long int item_id;
    string name;
    float rate;
    int quantity;
    item* next;
};

// This class is the inventory class which does the functions like adding an item to inventory, deleting an item from inventory, updating an item in inventory and getting the 
// information of the product present in inventory.
class Inventory
{
    static item* hash_1[10];
public:

    void make_NULL_hash_1()
    {
        for (int i = 0; i < 10; i++)
            hash_1[i] = NULL;
    }

    void PRINT(long int id)
    {

        int place = id % 10;
        item* temp = hash_1[place];

        while (temp)
        {
            if (temp->item_id == id)
            {
                if (temp->rate / 1000 >= 1)
                    cout << "   " << id << ",       " << temp->name << ",           " << temp->rate << ",            " << temp->quantity << endl;
                else
                    cout << "   " << id << ",       " << temp->name << ",           " << temp->rate << ",             " << temp->quantity << endl;
            }
            temp = temp->next;
        }

    }

protected:
    
    //Subroutine to add the item to an inventory.
    void Add_item(long int id, string name, float rate, int quantity)
    {
        int place = id % 10, flag = 1;
        item* temp = new item;
        item* tmp = hash_1[place], * t = tmp;
        temp->item_id = id;
        temp->name = name;
        temp->rate = rate;
        temp->quantity = quantity;
        //temp->next=NULL;

        if (hash_1[place] == NULL)
        {
            hash_1[place] = temp;
            temp->next = NULL;
        }
        else
        {
            while (tmp)
            {
                if (id >= tmp->item_id)
                {
                    t = tmp;
                    tmp = tmp->next;
                    flag++;
                }
                else
                {
                    if (flag == 1 && id < tmp->item_id)
                    {
                        temp->next = tmp;
                        hash_1[place] = temp;
                        flag++;
                        break;
                    }
                    else
                    {
                        t->next = temp;
                        temp->next = tmp;
                        break;
                    }
                }
            }
            if (tmp == NULL)
            {
                t->next = temp;
                temp->next = NULL;
            }
        }
    }
    
    //Suboutine to delete an item from the inventory.
    void Delete_item(long int id)
    {
        int place = id % 10, flag = 1, tf = 1;
        item* temp = hash_1[place], * tmp = temp;
        while (temp)
        {
            if (temp->item_id == id)
            {
                if (flag == 1)
                {
                    hash_1[place] = temp->next;
                    delete temp;
                    tf = 0;
                    break;
                }
                else
                {
                    tmp->next = temp->next;
                    delete temp;
                    tf = 0;
                    break;
                }
            }
            flag++;
            tmp = temp;
            temp = temp->next;
        }
        if (tf == 1)
            cout << "There is no item having id " << id << " and therefore it cannot be deleted." << endl;
    }

    //Subroutine to update an item from the inventory.
    void Update_item(long int id)
    {
        int place = id % 10;
        item* temp = hash_1[place];
        while (temp)
        {
            if (temp->item_id == id)
            {
                cin >> temp->rate; //Taking rate as input from manager.
                cin >> temp->quantity; //Taking quantity as input from manager.
                break;
            }
            temp = temp->next;
        }
        if (temp == NULL)
            cout << "There is no item with id " << id << " and so it's rate and quantity can't be changed." << endl;
    }
    
    //Subroutine to update the stock of an item in inventory after that item has been purchased.
    int update_stock(long int id, int quantity)
    {
        int place = id % 10;
        item* temp = hash_1[place];
        while (temp)
        {
            if (temp->item_id == id)
            {
                if (temp->quantity >= quantity)
                {
                    temp->quantity = temp->quantity - quantity;
                    return 0;
                }
                else
                {
                    cout << "Sorry there is/are " << temp->quantity << " available number of item/s with id " << id << endl;
                    return 1;
                }
            }
            temp = temp->next;
        }

        return 2;
    }

    //Subroutine to ge the iformation of an item like it's rate, name, id, quantity present in inventory.
    int Get_Product_Info(long int id, int q)
    {
        int place = id % 10;
        item* temp = hash_1[place];
        while (temp)
        {
            if (temp->item_id == id)
            {

                if ((temp->rate / 1000) >= 1)
                {
                    cout << "   " << id << ",       " << temp->name << ",           " << temp->rate << ",             " << q << ",              " << temp->rate * q << endl;
                }
                else
                {
                    cout << "   " << id << ",       " << temp->name << ",            " << temp->rate << ",             " << q << ",              " << temp->rate * q << endl;
                }
                break;
            }
            temp = temp->next;
        }

        if (temp == NULL)
            cout << "There is no item with id " << id << " and so it's information can't be obtained." << endl;
        return temp->rate * q;
    }

    void display()
    {
        for (int i = 0; i < 10; i++)
        {
            item* temp = hash_1[i];
            cout << i;
            while (temp)
            {
                cout << "-->" << temp->quantity;
                temp = temp->next;
            }
            cout << endl;
        }
    }


};

//Scope resolution for the hash table. 
item* Inventory::hash_1[10];

// Class for the manager which includes the fuctions manager can perform.
class Manager :public Inventory
{
    long int id;
    string name;
public:
    void setId(long int i)
    {
        id = i;
    }
    long int getId()
    {
        return id;
    }

    void setName(string n)
    {
        name = n;
    }
    string getName()
    {
        return name;
    }
    
    // Manager is having access to perform all the below operations.
    using Inventory::Add_item; // Adding item to inventory
    using Inventory::Delete_item; //Deleting item from inventory.
    using Inventory::Update_item; //Updating item in inventory.
    using Inventory::update_stock; //Updating stock of an item in inventory.
    using Inventory::Get_Product_Info; //Getting the details of the particulat item present in inventory.
    using Inventory::display;
};

struct i
{
    long int it;
    string na;
    float ra;
    int quantit;
};

//This is the inventory dataset which includes the item's id,name,quantity and rate respectively.
i INVENTORY_DATASET[100] = {
{111100000001,"1",100,20},{111100000002,"2",110,20},{111100000003,"3",120,20},{111100000004,"4",130,20},{111100000005,"5",140,20},{111100000006,"6",150,20},{111100000007,"7",160,20},{111100000008,"8",170,20},{111100000009,"9",180,20},{111100000010,"10",190,20},{111100000011,"11",200,20},{111100000012,"12",210,20},{111100000013,"13",220,20},{111100000014,"14",230,20},{111100000015,"15",240,20},{111100000016,"16",250,20},{111100000017,"17",260,20},{111100000018,"18",270,20},{111100000019,"19",280,20},{111100000020,"20",290,20},{111100000021,"21",300,20},{111100000022,"22",310,20} ,{111100000023,"23",320,20},{111100000024,"24",330,20},{111100000025,"25",340,20},{111100000026,"26",350,20},{111100000027,"27",360,20},{111100000028,"28",370,20},{111100000029,"29",380,20},{111100000030,"30",390,20},
{111100000031,"31",400,20},{111100000032,"32",410,20},{111100000033,"33",420,20},{111100000034,"34",430,20},{111100000035,"35",440,20},{111100000036,"36",450,20},{111100000037,"37",460,20},{111100000038,"38",470,20},{111100000039,"39",480,20},{111100000040,"40",490,20},{111100000041,"41",500,20},{111100000042,"42",510,20},{111100000043,"43",520,20},{111100000044,"44",530,20},{111100000045,"45",540,20},{111100000046,"46",550,20},{111100000047,"47",560,20},{111100000048,"48",570,20},{111100000049,"49",580,20},{222200001111,"50",590,20},{222200001114,"51",600,20},{222200001117,"52",610,20},{222200001120,"53",620,20},{222200001123,"54",630,20},{222200001126,"55",640,20},{222200001129,"56",650,20},{222200001132,"57",660,20},{222200001135,"58",670,20},{222200001138,"59",680,20},{222200001141,"60",690,20},{222200001144,"61",700,20},{222200001147,"62",710,20},{222200001150,"63",720,20},{222200001153,"64",730,20},{222200001156,"65",740,20},{222200001159,"66",750,20},{222200001162,"67",760,20},{222200001165,"68",770,20},{222200001168,"69",780,20},{222200001171,"70",790,20},{222200001174,"71",800,20},{222200001177,"72",810,20},{222200001180,"73",820,20},{222200001183,"74",830,20},{222200001186,"75",840,20},{222200001189,"76",850,20},{222200001192,"77",860,20},{222200001195,"78",870,20},{222200001198,"79",880,20},{222200001201,"80",890,20},{222200001204,"81",900,20},{222200001207,"82",910,20},{222200001210,"83",920,20},{222200001213,"84",930,20},{222200001216,"85",940,20},{222200001219,"86",950,20},{222200001222,"87",960,20},{222200001225,"88",970,20},{222200001228,"89",980,20},{222200001231,"90",990,20},{222200001234,"91",1000,20},{222200001237,"92",1010,20},{222200001240,"93",1020,20},{222200001243,"94",1030,20},{222200001246,"95",1040,20},{222200001249,"96",1050,20},{222200001252,"97",1060,20},{222200001255,"98",1070,20},{222200001258,"99",1080,20},{222200001261,"100",1090,20},
};

// The customer's structure will contain it's id, name of the customer and points won.
struct customer
{
    long int customer_ID;
    string Name;
    float Points;
    customer* nex;
};

customer* hash_2[10];

void make_NULL_hash_2()
{
    for (int i = 0; i < 10; i++)
        hash_2[i] = NULL;
}

// This is the customer class which includes the functions the customer as well as manager wil have access.
class Customer
{
public:
    
    // Subroutine to add the customer to the customer database.
    void Add_customer(long int id, string name, float point)
    {
        int place = id % 10, flag = 1;
        customer* temp = new customer, * tmp = hash_2[place], * t = tmp;
        temp->customer_ID = id;
        temp->Name = name;
        temp->Points = point;

        if (hash_2[place] == NULL)
        {
            hash_2[place] = temp;
            temp->nex = NULL;
        }
        else
        {
            while (tmp)
            {
                if (id >= tmp->customer_ID)
                {
                    t = tmp;
                    tmp = tmp->nex;
                    flag++;
                }
                else
                {
                    if (flag == 1 && id < tmp->customer_ID)
                    {
                        temp->nex = tmp;
                        hash_2[place] = temp;
                        flag++;
                        break;
                    }
                    else
                    {
                        t->nex = temp;
                        temp->nex = tmp;
                        break;
                    }
                }
            }
            if (tmp == NULL)
            {
                t->nex = temp;
                temp->nex = NULL;
            }
        }
    }
    
    //Subroutine to update the points of the customer after the customermakes the purchase. For the first time the customer's points is 0.
    void Update_points(long int id, int amt)
    {
        int place = id % 10, tfl = 0;
        customer* temp = hash_2[place];
        while (temp)
        {
            if (temp->customer_ID == id)
            {
                temp->Points += amt;
                tfl = 1;
                break;
            }
            temp = temp->nex;
        }
        if (tfl == 0)
            cout << "There is no customer with id " << id << " and so it's points can't be updated." << endl;
    }
};

struct c
{
    long int ID;
    string ame;
    float oints;
};

// This is the customer dataset which is already present.
c CUSTOMER_DATASET[100] = {
{9400000001,"1",0},{9400000002,"2",0},{9400000003,"3",0},{9400000004,"4",0},{9400000005,"5",0},{9400000006,"6",0},{9400000007,"7",0},{9400000008,"8",0},{9400000009,"9",0},{9400000010,"10",0},
{9400000011,"11",0},{9400000012,"12",0},{9400000013,"13",0},{9400000014,"14",0},{9400000015,"15",0},{9400000016,"16",0},{9400000017,"17",0},{9400000018,"18",0},{9400000019,"19",0},{9400000020,"20",0},{9400000021,"21",0},{9400000022,"22",0},{9400000023,"23",0},{9400000024,"24",0},{9400000025,"25",0},{9400000026,"26",0},{9400000027,"27",0},{9400000028,"28",0},{9400000029,"29",0},{9400000030,"30",0},{9400000031,"31",0},{9400000032,"32",0},{9400000033,"33",0},{9400000034,"34",0},{9400000035,"35",0},{9400000036,"36",0},{9400000037,"37",0},{9400000038,"38",0},{9400000039,"39",0},{9400000040,"40",0},{9400000041,"41",0},{9400000042,"42",0},{9400000043,"43",0},{9400000044,"44",0},{9400000045,"45",0},{9400000046,"46",0},{9400000047,"47",0},{9400000048,"48",0},{9400000049,"49",0},{9400000050,"50",0},{9400000051,"51",0},{9400000052,"52",0},{9400000053,"53",0},{9400000054,"54",0},{9400000055,"55",0},{9400000056,"56",0},{9400000057,"57",0},{9400000058,"58",0},{9400000059,"59",0},{9400000060,"60",0},{9400000061,"61",0},{9400000062,"62",0},{9400000063,"63",0},{9400000064,"64",0},{9400000065,"65",0},{9400000066,"66",0},{9400000067,"67",0},{9400000068,"68",0},{9400000069,"69",0},{9400000070,"70",0},{9400000071,"71",0},{9400000072,"72",0},{9400000073,"73",0},{9400000074,"74",0},{9400000075,"75",0},{9400000076,"76",0},{9400000077,"77",0},{9400000078,"78",0},{9400000079,"79",0},{9400000080,"80",0},{9400000081,"81",0},{9400000082,"82",0},{9400000083,"83",0},{9400000084,"84",0},{9400000085,"85",0},{9400000086,"86",0},{9400000087,"87",0},{9400000088,"88",0},{9400000089,"89",0},{9400000090,"90",0},{9400000091,"91",0},{9400000092,"92",0},{9400000093,"93",0},{9400000094,"94",0},{9400000095,"95",0},{9400000096,"96",0},{9400000097,"97",0},{9400000098,"98",0},{9400000099,"99",0},{9400000100,"100",0},
};

struct node
{
    long int id;
    int quan;
    node* next;
};

// This is the class billing and it includes only those functions which can be accessed during generating the bill like updating stock of item, updating the points of customer,
// getting the product info about the item that the customer is going to buy, updating the stock of the item purchased ,etc.Moreover here i had inherited the inventory and 
// customer classes because the functions mentioned above are defined in those classes.
class Billing :public Inventory, public Customer
{
    node* head;
public:

    Billing()
    {
        head = NULL;
    }

    using Inventory::update_stock;
    using Inventory::Get_Product_Info;
    using Inventory::display;

    //Subroutine to display name of the customer.
    void display_customer()
    {
        for (int i = 0; i < 10; i++)
        {
            customer* temp = hash_2[i];
            cout << i;
            while (temp)
            {
                cout << "-->" << temp->Name;
                temp = temp->nex;
            }
            cout << endl;
        }
    }

    //Subroutine to buy item. Here the different items that customer wants to purchase are stored in the form of link list by this subroutine.    
    void Buy_item(long int id, int quantity)
    {
        node* temp = new node;
        temp->id = id;
        temp->quan = quantity;
        temp->next = NULL;

        if (head == NULL)
            head = temp;
        else
        {
            node* tmp = head;
            while (tmp->next)
                tmp = tmp->next;

            tmp->next = temp;
        }
    }

    //Subroutine to cancel any item ifthe customer doesn't wants to purchase.
    void Cancel_item(long int id)
    {
        node* temp = head, * tmp = temp;
        int flag = 1, tf = 0;
        while (temp)
        {
            if (temp->id == id)
            {
                if (flag == 1)
                {
                    head = temp->next;
                    delete temp;
                    tf = 0;
                    break;
                }
                else
                {
                    tmp->next = temp->next;
                    delete temp;
                    tf = 0;
                    break;
                }
                flag++;
                tmp = temp;
                temp = temp->next;
            }
        }
        if (tf == 1)
            cout << "There is no item with id " << id << " that you have purchased so you cannot cancel that item." << endl;
    }

    //Subroutine to generate the bill and to make payment.
    int make_payment(long int id)
    {
        int total = 0;
        cout << "Transaction_ID:      ABCDEFGH" << endl;
        cout << "   Customer_ID:      " << id << endl;
        cout << "   Product ID,        Name,          Rate,          Quantity,        Amount," << endl;
        node* temp = head;

        while (temp)
        {
            total += Get_Product_Info(temp->id, temp->quan);
            temp = temp->next;
        }
        cout << "                                                               Total : " << total;
        return total;
    }

    //Subroutine to display the details of the customer after he/she has purchased any item from the supermarket.
    void customer_details(long int id)
    {
        int place = id % 10;
        customer* temp = hash_2[place];
        while (temp)
        {
            if (temp->customer_ID == id)
            {
                cout << "   " << temp->customer_ID << ",            " << temp->Name << ",            " << temp->Points << endl;
            }
            temp = temp->nex;
        }
    }

    //SSubroutine to check whether the customer is present in the customer datadet or not and if customer is not present then add that customer to the customer dataset.
    void check_customer(long int c_id)
    {
        int place = c_id % 10, flag = 0;
        customer* temp = hash_2[place];
        while (temp)
        {
            if (temp->customer_ID == c_id)
            {
                flag = 1;
                break;
            }
            temp = temp->nex;
        }
        if (flag == 0)
        {
            string name;
            cin >> name; //Taking the name of the customer as input
            Add_customer(c_id, name, 0);
        }
    }
};

int main()
{

    make_NULL_hash_2();
    Manager a;
    a.setId(201901416);
    a.setName("HNS");
    cout << "Manager's ID:" << a.getId() << endl;
    cout << "Manager's Name:" << a.getName() << endl;
    a.make_NULL_hash_1();

    for (int i = 0; i < 100; i++)
        a.Add_item(INVENTORY_DATASET[i].it, INVENTORY_DATASET[i].na, INVENTORY_DATASET[i].ra, INVENTORY_DATASET[i].quantit);
    char g;

    cin >> g; //Taking input as Y or N from the manager to know whether manager wants to Delete any item in the Inventory Database

    if (g == 'Y' || g == 'y')
    {
        long int cid; // Taking the id of item as input manager wants to update.
        cin >> cid;
        a.Delete_item(cid);
    }

    cin >> g; //Taking input as Y or N from the manager to know whether manager wants to Update any item in the Inventory Database.

    if (g == 'Y' || g == 'y')
    {
        long int cid; // Taking the id of item as input manager wants to update.
        cin >> cid;
        a.Update_item(cid);
    }
    Billing b;

    cout << endl;
    for (int i = 0; i < 100; i++)
        b.Add_customer(CUSTOMER_DATASET[i].ID, CUSTOMER_DATASET[i].ame, CUSTOMER_DATASET[i].oints);

    long int c_id;
    int num;
    cin >> num;// Taking input from customer that how many items with different id he/she wants to buy.
    long int arr[num];
    cin >> c_id;//Taking customer's id as input.
    b.check_customer(c_id);

    for (int i = 0; i < num; i++)
    {
        long int i_id; int quantity;
        cin >> i_id; //Taking id as input of item customer wants to purchased.
        arr[i] = i_id;
        cin >> quantity; //Taking input quantity of that item.
        int j = b.update_stock(i_id, quantity);
        if (j == 2)
        {
            cout << endl << "There is no item with id " << i_id << " and so it can't be purchased.";
            continue;
        }
        while (j)
        {
            cin >> quantity; // Taking quantity as input again due to less number of available items;
            j = b.update_stock(i_id, quantity);
        }
        b.Buy_item(i_id, quantity);
    }

    cout << endl << "BILL" << endl;
    int amt = b.make_payment(c_id);
    b.Update_points(c_id, amt);

    cout << endl;
    cout << endl << "Update in quantity of purhased item:";
    cout << endl;
    cout << endl;
    cout << "   Product ID,        Name,          Rate,          Quantity" << endl;

    for (int i = 0; i < num; i++)
        a.PRINT(arr[i]);

    cout << endl << "Update in points of customer who has done shopping" << endl << endl;
    cout << "   Customer ID,        Name,          Points" << endl;

    b.customer_details(c_id);

    /* Test Case 1. Here customer who is shopping is already in the customer dataset.

    N(N means manager doesn't want to delete any item from inventory database.)
    N(N means manager doesn't want to update any item from inventory database.)
    3(Taking input from customer that how many items with different id he/she wants to buy.)
    9400000011(Taking customer's id as input.)
    111100000011(Taking id as input of item customer wants to purchased.)
    3(Taking input quantity of that item.)
    222200001114(Taking id as input of item customer wants to purchased.)
    1(Taking input quantity of that item.)
    222200001234(Taking id as input of item customer wants to purchased.)
    2(Taking input quantity of that item.)
    */

    /* Test Case 2. Here customer who is shopping is already in the customer dataset but the quantity of item customer is purchasing is more then the quantity which is/are in the stock.

    N(N means manager doesn't want to delete any item from inventory database.)
    N(N means manager doesn't want to update any item from inventory database.)
    3(Taking input from customer that how many items with different id he/she wants to buy.)
    9400000011(Taking customer's id as input.)
    111100000011(Taking id as input of item customer wants to purchased.)
    23(Taking input quantity of that item.)
    3(Taking quantity as input again due to less number of available items.)
    222200001114(Taking id as input of item customer wants to purchased.)
    1(Taking input quantity of that item.)
    222200001234(Taking id as input of item customer wants to purchased.)
    2(Taking input quantity of that item.)
    */

    /* Test Case 3.Here the customer who is shoppng is not present in the customer dataset.

    N(N means manager doesn't want to delete any item from inventory database.)
    N(N means manager doesn't want to update any item from inventory database.)
    3(Taking input from customer that how many items with different id he/she wants to buy.)
    20190141234(Taking customer's id as input.)
    XYZ(As customer is not present i customer dataset so taking customer's name to add him/her.)
    111100000011(Taking id as input of item customer wants to purchased.)
    3(Taking input quantity of that item.)
    222200001114(Taking id as input of item customer wants to purchased.)
    1(Taking input quantity of that item.)
    222200001234(Taking id as input of item customer wants to purchased.)
    2(Taking input quantity of that item.)
    */

    /* Test Case 4.If manager wants to update any item in Inventory.

    N
    Y(Taking input as Y or N from the manager to know whether manager wants to Update any item in the Inventory Database.)
    222200001114(Taking the id of item as input manager wants to update.)
    5555(Taking rate as input from manager.)
    15(Taking quantity as input from manager.)
    3(Taking input from customer that how many items with different id he/she wants to buy.)
    9400000011(Taking customer's id as input.)
    111100000012(Taking id as input of item customer wants to purchased.)
    3(Taking input quantity of that item.)
    222200001114(Taking id as input of item customer wants to purchased.)
    1(Taking input quantity of that item.)
    222200001234(Taking id as input of item customer wants to purchased.)
    2(Taking input quantity of that item.)
    */

    /* Test Case 5. Similarly manager can delete and update an item from inventory.

    Y(Taking input as Y or N from the manager to know whether manager wants to Delete any item in the Inventory Database.)
    111100000011(Taking the id of item as input manager wants to delete.)
    Y(Taking input as Y or N from the manager to know whether manager wants to Update any item in the Inventory Database.)
    222200001114(Taking the id of item as input manager wants to update.)
    5555(Taking rate as input from manager.)
    15(Taking quantity as input from manager.)
    3(Taking input from customer that how many items with different id he/she wants to buy.)
    9400000011(Taking customer's id as input.)
    111100000012(Taking id as input of item customer wants to purchased.)
    3(Taking input quantity of that item.)
    222200001114(Taking id as input of item customer wants to purchased.)
    1(Taking input quantity of that item.)
    222200001234(Taking id as input of item customer wants to purchased.)
    2(Taking input quantity of that item.)
    */

    //Similarly one can make combinations like manager wants to update and not delete an item or vice versa.

    return 0;
}

