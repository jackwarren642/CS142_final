// A book record database
#include<iostream>
#include<fstream>
#include <limits>
#include<cstdlib>
#include<string>
#include<cmath>
#include <ios>
using namespace std;

typedef struct book_t{
	string book_title;
	string author_name;
	int ISBN_no;
	int availability; // 0 is available; 1 is unavailable
	float price;
}book;

int book_count;

void add_book(book library[]);
void borrow_book(book library[]);
void compare_books(book library[]);
void delete_book(book library[]);
void edit_book(book library[]);
int find_book(book library[], int ISBN_search);
void list_book(book library[]);
void costliest_book(book library[]);
void show_books(book library[]);

int main()
{
	char user_choice;
	book library[100];
	int ISBN_search = 0;

	ifstream input;

	input.open("input.txt");

	input >> book_count;

	for(int i = 0; i < book_count; i++){
		input.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(input, library[i].book_title);
		getline(input, library[i].author_name);
		input >> library[i].ISBN_no;
		input >> library[i].availability;
		input >> library[i].price;
	}

	input.close();

	cout << "\n" << endl;

	for(int i = 0; i < book_count; i++){
		cout << library[i].book_title << endl;
		cout << library[i].author_name << endl;
		cout << library[i].ISBN_no << endl;
		cout << library[i].availability << endl;
		cout << library[i].price << endl;
		cout << "\n";
	}
   
	while (1)
	{
		//prints the user menu
		cout << "\nWelcome to the Library of Haque! Please select an option-" << endl;
		cout << "A- Add a new book to the existing library." << endl;
		cout << "B- Check book availability by title." << endl;
		cout << "C- Compare two books in the library." << endl;
		cout << "D- Delete a book by its ISBN number." << endl;
		cout << "E- Edit a book by its ISBN number." << endl;
		cout << "F- Find a book by its ISBN number." << endl;
		cout << "L- List all books by a given author." << endl;
		cout << "P- Display information of the library's most expensive book." << endl;
		cout << "S- Display information of all books in the library." << endl;
		cout << "X- Exit the library.\n" << endl;

		cin >> user_choice;
		
		//switch branches the user decision
		switch(user_choice)
		{
			case 'a': case 'A': //bobby
				book_count++; //raises book_count to account for new book, and makes sure this is a change in the main function.

				add_book(library);

				break;
	
			case 'b': case 'B':
				
				borrow_book(library);

				break;

			case 'c': case 'C':

				compare_books(library);

				break;

			case 'd': case 'D':

				delete_book(library);

				break;

			case 'e': case 'E':

				edit_book(library);

				break;

			case 'f': case 'F': //bobby

				cout << "\nPlease enter the ISBN number you would like to search for." << endl;
				cin >> ISBN_search;
				//i use 1000000 here because #1 i can't use 0, as library[0] is a valid input, #2 it's unrealistic this will have 1000000 elements, #3 negative value was returning error
				if (find_book(library, ISBN_search) == 1000000){
					cout << "No titles were found for this ISBN number." << endl;
				}
				else{
					int book_number = 0;
					book_number = find_book(library, ISBN_search);
					cout << "\nThe following title is registered to your #- " << library[book_number].book_title << endl;
					cout << "\n" << library[book_number].book_title << endl;
					cout << library[book_number].author_name << endl;
					cout << library[book_number].ISBN_no << endl;
					cout << library[book_number].availability << endl;
					cout << library[book_number].price << endl;
				}
				break;

			case 'l': case 'L':

				list_book(library);

				break;

			case 'p': case 'P': //bobby

				costliest_book(library);

				break;

			case 's':case 'S': //bobby
				
				show_books(library);

				break;

			case 'x':case 'X':

				cout << "\nThanks for visiting, come again!" << endl;
				
				exit(0);	
			
			default:

				cout << "Try again- please enter a valid option!" << endl;
				cout << "\n";

				break;
		}
	}
	
	return 0;
}

void add_book(book library[]){

	cin.ignore(numeric_limits<streamsize>::max(), '\n'); //prompts proper reading of input file

	//obtaining user input for the different parameters for the new book
	//uses [book_count -1] as the final term is one less than the total amount of books (library[7] = the 8th book)
	cout << "\nLet's add a new book! Please enter the name of the new book-" << endl;
	getline(cin, library[book_count - 1].book_title);
	cout << "\nPlease enter the name of the author-" << endl;
	getline(cin, library[book_count - 1].author_name);
	cout << "\nPlease enter the ISBN number of the book-" << endl;
	cin >> library[book_count - 1].ISBN_no;
	cout << "\nPlease enter 0 if the book is available or 1 for unavailable." << endl;
	cin >> library[book_count - 1].availability;
	cout << "\nPlease enter the price of the new book-" << endl;
	cin >> library[book_count - 1].price;
	cout << "\n";
	
	show_books(library);

	return;
}

void borrow_book(book library[]){
	string user_search;

	cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ensures computer allows input of book title

	cout << "\nPlease enter the title of the book that you would like to borrow. (Case Sensitive!)" << endl;
	getline (cin, user_search);

	for (int count = 0; count < book_count; count++){

		if (library[count].book_title == user_search){

			if (library[count].availability == 1){
				cout << "\nThis book is currently checked out or otherwise unavailable. Please try again later!\n" << endl;
			}

			else if(library[count].availability == 0){
				cout << "\nThis book is currently available to be checked out!\n" << endl;
			}

			else{
				cout << "\nThe input availability is invalid! Please contact library help desk.\n" << endl;
			}
		} 
	}

	return;
}

void compare_books(book library[]){

	int ISBN_search1 = 0, ISBN_search2 = 0;
	int book_number1 = 0, book_number2 = 0;

	cout << "\nPlease enter the ISBN number of the first book you would like to compare." << endl;
	cin >> ISBN_search1;
	book_number1 = find_book(library, ISBN_search1);

	cout << "\nPlease enter the ISBN number to compare to " << library[book_number1].book_title << ":\n";
	cin >> ISBN_search2;
	book_number2 = find_book(library, ISBN_search2);
	cout << "\n Comparison of " << library[book_number1].book_title << " and " << library[book_number2].book_title << "-\n";

	cout << "\n" << library[book_number1].book_title << endl;
	cout << library[book_number1].author_name << endl;
	cout << library[book_number1].ISBN_no << endl;
	cout << library[book_number1].availability << endl;
	cout << library[book_number1].price << endl;
	cout << "\n";

	cout << library[book_number2].book_title << endl;
	cout << library[book_number2].author_name << endl;
	cout << library[book_number2].ISBN_no << endl;
	cout << library[book_number2].availability << endl;
	cout << library[book_number2].price << endl;
	cout << "\n";

	return;
}

void delete_book(book library[]){

	int book_to_delete = 0;
	int ISBN_search = 0;
	char user_selection;

	cout << "\nPlease enter the ISBN number of the book you'd like to delete." << endl;
	cin >> ISBN_search;

	if (find_book(library, ISBN_search) == 1000000){
		cout << "There are no titles registered under this ISBN." << endl;
	}

	else{
		cout << "\nWould you like to delete " << library[find_book(library, ISBN_search)].book_title << "? (Y/N)" << endl;
		cin >> user_selection;

		if (user_selection == 'Y' || user_selection == 'y'){
			for (int count = find_book(library, ISBN_search); count < book_count; count++){
				library[count] = library[count + 1];
			}
			book_count--;
			show_books(library);
		}
		if (user_selection == 'N' || user_selection == 'n'){
			cout << "\nDeletion canceled!" << endl;
		}
	} 

	return;
}

void edit_book(book library[]){
	int ISBN_search = 0;
	char user_selection;
	string new_title;
	string new_author;
	int new_ISBN = 0;
	int new_availability = 0;
	float new_price = 0.0;

	cout << "\nPlease enter the ISBN number of the book you'd like to edit." << endl;
	cin >> ISBN_search;

	if (find_book(library, ISBN_search) == 1000000){
		cout << "\nThere are no titles registered under this ISBN." << endl;
	}

	else{
		int book_number = find_book(library, ISBN_search);

		cout << "\nWould you like to edit " << library[book_number].book_title << "? (Y/N)" << endl;
		cin >> user_selection;

		if (user_selection == 'Y' || user_selection == 'y'){

			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\nPlease enter the new title." << endl;
			getline(cin, new_title);
			cout << "\nPlease enter the new author." << endl;
			getline(cin, new_author);
			cout << "\nPlease enter the new ISBN number." << endl;
			cin >> new_ISBN;
			cout << "\nPlease enter 0 if available and 1 if unavailable." << endl;
			cin >> new_availability;
			cout << "\nPlease enter the new price." << endl;
			cin >> new_price;
		
		
			library[book_number].book_title = new_title;
			
			library[book_number].author_name = new_author;
			
			library[book_number].ISBN_no = new_ISBN;
		
			library[book_number].availability = new_availability;
			
			library[book_number].price = new_price;
			
			show_books(library);
		}

		if (user_selection == 'N' || user_selection == 'n'){
			cout << "\nEdit canceled!" << endl;
		}
	}
}

int find_book(book library[], int ISBN_search){
	int found_book = 1000000;

	for(int count = 0; count < book_count; count++){
		if(library[count].ISBN_no == ISBN_search){
			found_book = count;
		}
	}

	return found_book;
}

void list_book(book library[]){
	string user_search;
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ensures computer allows input of book title

	cout << "\nPlease enter the author name (case sensitive) that you would like to check the works of." << endl;
	getline(cin, user_search);
	cout << "\nThe following books were found for the entered author-" << endl;
	cout << "\n";

	for(int count = 0; count < book_count; count++){
		if (library[count].author_name == user_search){
			cout << library[count].book_title << endl;
			cout << library[count].author_name << endl;
			cout << library[count].ISBN_no << endl;
			cout << library[count].availability << endl;
			cout << library[count].price << endl;
			cout << "\n";
		}
	}

	return;
}

void costliest_book(book library[]){
	int book_cost_max = 0;

	for (int count = 1; count < book_count; count++){
		if (library[count].price > library[book_cost_max].price){
			book_cost_max = count;
		}
	}

	cout << "\nThe most expensive book in this library is " << library[book_cost_max].book_title << "!\n";
	cout << "\n" << library[book_cost_max].book_title << endl;
	cout << library[book_cost_max].author_name << endl;
	cout << library[book_cost_max].ISBN_no << endl;
	cout << library[book_cost_max].availability << endl;
	cout << library[book_cost_max].price << endl;
	cout << "\n";

	return;
}

void show_books(book library[]){
	//for loop prints the new library accounting for the new book and the raised count
	cout << "\n";

	for(int count = 0; count < book_count; count++){
		cout << library[count].book_title << endl;
		cout << library[count].author_name << endl;
		cout << library[count].ISBN_no << endl;
		cout << library[count].availability << endl;
		cout << library[count].price << endl;
		cout << "\n";
	}

	return;/**/
}