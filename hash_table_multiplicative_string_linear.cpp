#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

class item{
	
    public:
    string key = "";
	bool empty_since_start = true;
	bool empty_after_removal = false;
};
//Multiplicative string hash function
int initial_value = 3, multiplier = 5; //Provided by instructor
int multiplicative_string_hash(string key, int hash_table_size){
	int pos = initial_value;
    for (int i = 0; i < key.size(); i++)
    {
        pos = (pos * multiplier) + key[i];
    }
    
	return pos % hash_table_size;
}


//Insert using linear probing
bool insert_Item(item hash_table[], string input_value, int hash_table_size)
{
	int position = multiplicative_string_hash(input_value, hash_table_size); //using mid square  base2 hash function
	int check = 0;
	while(check < hash_table_size)
	{
		if(hash_table[position].empty_since_start || hash_table[position].empty_after_removal){
			hash_table[position].key = input_value;
			hash_table[position].empty_since_start = false;
			hash_table[position].empty_after_removal = false;
			return true;
		}else
        {
            cout <<"\nCollision occured performing linear probing.";
        }
        
		check++;
		position = (position + 1 ) % hash_table_size;
	}
	cout <<"\nBucket FULL Press -1 to end insert operation: ";
	return false;
}

void display_hash(item hash_table[], int hash_table_size)
{   cout << endl;
	for(int i=0; i < hash_table_size; i++)
	{
		if(!hash_table[i].empty_since_start && !hash_table[i].empty_after_removal){
            cout << i << " -----> " << hash_table[i].key <<endl;	
		}
		else{
			cout << i << " -----> " << endl;
		}
	}
}

int delete_item(item hash_table[], string delete_value, int hash_table_size)
{
	
	int position = multiplicative_string_hash(delete_value, hash_table_size); // Using mid square base2 hash function
	int bucket_checked = 0;
	while(bucket_checked < hash_table_size &&  !hash_table[position].empty_since_start)
	{
		if(hash_table[position].key == delete_value)
		{
			hash_table[position].key = "";
			hash_table[position].empty_since_start = false;
			hash_table[position].empty_after_removal = true;
			cout << delete_value << " deleted successfully.";
			return true;
		}
		bucket_checked++;
		position = (position + 1) % hash_table_size;
	}
	cout <<delete_value << " not found in the table.";
	return false;
}

void search_item(item hash_table[], string search_value, int hash_table_size)
{
	for(int i=0; i < hash_table_size; i++)
	{
		if(hash_table[i].key == search_value){
			cout << search_value << " was found in the table!" << endl;
			return;
		}
	}
	cout << "Item not found in table." << endl;
	return;
}


int main()
{
    int hash_table_size; 
    string input_value, search_value, delete_value;
    cout <<"Enter the Size of Table: ";
    cin >> hash_table_size;
	item hash_table[hash_table_size];
	//Inserting key in hash table: 
    cout <<"\nEnter the element to insert until -1: ";
    cin >> input_value;
    while((input_value != "-1")){
        if(insert_Item(hash_table, input_value, hash_table_size))
            cout << input_value << " inserted successfully." << endl;
        cin >> input_value;
    }
    
    cout <<"\nEnter value you want to search: ";
    cin >> search_value;
    //searching hash table for search value entered
    search_item(hash_table, search_value, hash_table_size);
    //Deleting value
	cout <<"\nEnter the value you want to delete: ";
	cin >> delete_value;
	delete_item(hash_table, delete_value, hash_table_size);
    //display the hash table
    display_hash(hash_table, hash_table_size);
	return 0;
}