#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class item{
	
    public:
    int key;
	
};
//Perfect hash fucntion 
int hash_function(int key, int hash_table_size)
{
	return key % hash_table_size;
}

//Insert using chaining
bool insert_Item(vector<vector<int>> &hash_table, int input_value, int hash_table_size)
{	
	int position = hash_function(input_value, hash_table_size); //using perfect modulo  hash function

	hash_table[position].push_back(input_value);
	return true;
}

void display_hash(vector<vector<int>> hash_table, int hash_table_size)
{   cout << endl;
	for(int i=0; i < hash_table_size; i++)
	{	cout << i << " |--> ";
		for(int j = 0; j < hash_table[i].size(); j++){
			if(hash_table[i][j] != -1){
            	cout  << hash_table[i][j] << "--> ";	
			}
		}
		cout <<endl;
	}
		
}

bool delete_item(vector<vector<int>> &hash_table, int delete_value, int hash_table_size)
{
	
	int position = hash_function(delete_value, hash_table_size);
	int bucket_checked = 0;
	for (int i = 0; i < hash_table[position].size(); i++)
	{
		if(hash_table[position][i] == delete_value){
			hash_table[position][i] = -1;
			cout <<delete_value <<" successfully deleted.";
			return true;
		}
	}
	
	cout <<delete_value << " not found in the table.";
	return false;
}

void search_item(vector<vector<int>> hash_table, int search_value, int hash_table_size)
{	int position = hash_function(search_value, hash_table_size);
	int i = 0;
	while(i < hash_table[position].size()) //@Fix me logic error
	{
		if(hash_table[position][i] == search_value){
			cout << search_value << " was found in the table!" << endl;
			return;
		}
		i++;
		
	}
	cout << search_value << " not found in table." << endl;
	return;
}


int main()
{
    int hash_table_size, input_value, search_value, delete_value;
    cout <<"Enter the Size of Table: ";
    cin >> hash_table_size;
	vector<vector<int>> hash_table(hash_table_size);
	
	//Inserting key in hash table: 
    cout <<"\nEnter the element to insert until -1: ";
    cin >> input_value;
    while(input_value != -1){
        if(insert_Item(hash_table, input_value, hash_table_size) == true)
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