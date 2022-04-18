#include <bits/stdc++.h>
using namespace std;

class Page
{
public:
    Page(int size);
    bool insert(int record_size, int primary_key);
    int size_of_page;
    int count_of_records;
    int used_space;
    vector<int> primary_keys;
    vector<pair<int, int>> directory;
    int search(int primary_key);
};

Page::Page(int size)
{
    size_of_page = size;
    count_of_records = 0;
    used_space = 16;
}
bool Page::insert(int record_size, int primary_key)
{
    if (size_of_page - used_space < 4 + record_size)
    {
        return 0;
    }
    primary_keys.push_back(primary_key);
    if (directory.size() == 0)
    {
        directory.push_back({0, record_size});
    }
    else
    {
        auto p = directory.back();
        directory.push_back({p.first + p.second, record_size});
    }
    used_space += (4 + record_size);
    count_of_records++;
    return 1;
}
int Page::search(int primary_key)
{
    auto it = find(primary_keys.begin(), primary_keys.end(), primary_key);
    if (it == primary_keys.end())
    {
        return -1;
    }
    return (it - primary_keys.begin());
}

class Heap
{
public:
    Heap(int page_size);
    vector<Page *> pages;
    int page_size;
    void search(int primary_key);
    void status();
    void insert(int record_size, int primary_key);
};
Heap::Heap(int pg_size)
{
    page_size = pg_size;
}
void Heap::insert(int record_size, int primary_key)
{
    bool inserted = 0;
    for (int i = 0; i < pages.size(); i++)
    {
        if (pages[i]->insert(record_size, primary_key))
        {
            inserted = 1;
            break;
        }
    }
    if (!inserted)
    {
        Page *new_page = new Page(page_size);
        pages.push_back(new_page);
        (pages.back())->insert(record_size, primary_key);
    }
}
void Heap::search(int primary_key)
{
    int page_id = -1, record_id = -1;
    for (int i = 0; i < pages.size(); i++)
    {
        if (pages[i]->search(primary_key) != -1)
        {
            page_id = i;
            record_id = pages[i]->search(primary_key);
            break;
        }
    }
    cout << page_id << " " << record_id << endl;
}
void Heap::status()
{
    cout << pages.size() << " ";
    for (auto x : pages)
    {
        cout << x->count_of_records << " ";
    }
    cout << endl;
}
int main()
{

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int page_size;
    cin >> page_size;
    Heap h(page_size);
    int x;
    while (cin >> x)
    {
        if (x == 2)
        {
            h.status();
        }
        else if(x==1){
            int record_size, primary_key;
            cin >> record_size>>primary_key;
            h.insert(record_size, primary_key);
        }
        else if(x==3){
            int primary_key;
            cin >> primary_key;
            h.search(primary_key);
        }
        else{
            break;
        }
    }

    return 0;
}