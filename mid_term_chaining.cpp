#include <iostream>
#include <string>
#include <vector>

using namespace std;

class item{
    public:
    int key;
};
//Perfect modulo hash functino
int mudolo(int key, int hash_table_size){
    return key % hash_table_size;
}
int insert_item(int key, vector<vector<int>> &hash_table, int hash_table_size){
    int position = mudolo(key, hash_table_size);
    hash_table[position].push_back(key);
    return 0;
}

int delete_item(int delete_key, vector<vector<int>> &hash_table, int hash_table_size){
    int position = mudolo(delete_key, hash_table_size);
    for (int i = 0; i < hash_table[position].size(); i++)
    {
        if(hash_table[position][i] == delete_key){
            hash_table[position][i] = -1;
            cout << delete_key << " successfully deleted.";
            return 0;
        }
    } 
    cout << delete_key <<" not found in the table.";
    return -1;

}
int search_item(int search_key, vector<vector<int>> hash_table, int hash_table_size){
    int position = mudolo(search_key, hash_table_size);
    for (int i = 0; i < hash_table[position].size(); i++)
    {
        if(hash_table[position][i] == search_key){
            cout << search_key << " successfully found in the table.";
            return 0;
        }
    } 
    cout << search_key <<" not found in the table.";
    return -1;
}
void display(vector<vector<int>> hash_table, int hash_table_size)
{
    cout << endl;
    for (int i = 0; i < hash_table_size; i++)
    {   cout << i << "|---> ";
        for (int j = 0; j < hash_table[i].size(); j++)
        {
            if(hash_table[i][j] != -1)
                    cout << hash_table[i][j] <<" --->";
        }
        cout << endl;
    }
}

int main(){
int hash_table_size, key, search_key, delete_key;
cout <<"Enter the size of the table: ";
cin >> hash_table_size;
vector<vector<int>> hash_table(hash_table_size);

cout << "\nEnter the key to insert untill -1: ";
cin >> key;
while( key != -1){
    if(insert_item(key, hash_table, hash_table_size ) == 0)
        cout <<"Insertion successful." << endl;
cin >> key;
}
//Display the table
display(hash_table, hash_table_size);

cout <<"\nEnter value you want to search: ";
cin >> search_key;
//searching hash table for search value entered
search_item(search_key, hash_table, hash_table_size);

//Deleting value
cout <<"\nEnter the value you want to delete: ";
cin >> delete_key;
delete_item(delete_key, hash_table, hash_table_size);

//Display the table
display(hash_table, hash_table_size);
return 0;
}