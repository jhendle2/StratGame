#pragma once

#include <item.h>

#include <list>
// #include <tuple>

// typedef std::tuple<Item,int> ItemQuantityPair;
class ItemQuantityPair{
    public:
        int quanity;
        Item item;

        ItemQuantityPair();
        ItemQuantityPair(int quantity, Item item);
        ~ItemQuantityPair();
};

class Inventory{
    private:
        // Actor* owner;
    public:
        std::list<ItemQuantityPair*> items;

        Inventory();
        ~Inventory();

        void add(Item item);
        bool has(const char* name);
        bool has(Item item);
        int find_index(const char* name);
        int find_index(Item item);
        Item find(int index);
        Item find(const char* name);
        ItemQuantityPair find_tup(int index);
        ItemQuantityPair find_tup(const char* name);

        void print(int index);
        void print_all();
};