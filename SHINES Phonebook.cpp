#include <iostream> // for 
#include <fstream> //for file handling

using namespace std;

// the contact class will store the cont
class contact{
private:
	char fName[50], lName[50], address[50], email[50];
	long long phoneNo;

// this functions is a prompt that will be used to create and edit new contacts. 
//It is used with the writeCon and editcon function		
public:
	void createCon() {
		cout<<"Enter first name: ";
		cin>>fName;
		cout<<"Enter last name: ";
		cin>>lName;
		cout<<"Enter address: ";
		cin>>address;
		cout<<"Enter email address: ";
		cin>>email;	
        cout<<"Enter phone number: ";
		cin>>phoneNo;
	}
//this function allows the user to display all contact info in the phonebook		
	void dispCon() {
		cout<<"Name: "<<fName<<" "<<lName<<endl;
        cout<<"Address: "<<address<<endl;
		cout<<"Phone number: "<<phoneNo<<endl;
		cout<<"Email address: "<<email<<endl;	
	}

//this function opens the file and adds new record to the system
	void writeCon() {
		char option;
		ofstream file1;
		file1.open("shines.dat",ios::binary|ios::app);

		do {
			createCon();
			file1.write(reinterpret_cast<char*>(this),sizeof(*this));
			cout<<"Do you want to enter more contacts?(y/n)";
			cin>>option;
		} while(option =='y');

		cout<< "Contact has been sucessfully created!";
		file1.close();
    }
		// this function opens the file and displays all the listed contacts. 
        // It uses the dispCon function
	void readCon() {
		ifstream file2;
		file2.open("shines.dat",ios::binary);

		cout<<"\n ********************************* \n";
		cout<<"LIST OF CONTACTS";
		cout<<" \n ********************************* \n";

		while(!file2.eof()) {
			if(file2.read(reinterpret_cast<char*>(this),sizeof(*this)))
			{
				dispCon();
				cout<<"\n********************************* \n";
			}
		}
		file2.close();
	}
	// this funtion allows the user to search for a contact by using the cell phone number.
    // it opens the phone file and uses the dispCon function	
	void searchCon() {
		ifstream file3;
		long long phone;
		cout<<"Enter phone no.: ";
		cin>>phone;
		file3.open("shines.dat",ios::binary);

		while(!file3.eof()) {
			if(file3.read(reinterpret_cast<char*>(this), sizeof(*this))) {
				if (phone==phoneNo) {
					dispCon();
					return;
				}
			}
		}
		cout<<"\n\n Sorry, we did not find any record";
		file3.close(); 
	}

	//this function deletes a record by searching for the selected phone number 
	void deleteCon() {
		long long delPhoneNo;
		int flag = 0;
        char deloption1, deloption2;
		ofstream file4;
		ifstream file5;
        do{
		file5.open("shines.dat",ios::binary);
		file4.open("shinestemp.dat",ios::binary);

		cout<<"Enter the phone number that you would like to delete: ";
		cin>>delPhoneNo;
        

		while(!file5.eof()) {
            dispCon();
			if(file5.read(reinterpret_cast<char*>(this),sizeof(*this))) {
				if(phoneNo!=delPhoneNo) {
					file4.write(reinterpret_cast<char*>(this),sizeof(*this));
				}
				else 
					flag = 1;
            }
		}
                cout << "Are you sure you want to delete this record? (y/n)";
                 cin>> deloption2;
                if (deloption2 == 'y'){
                file5.close();
		        file4.close();
		        remove("shines.dat");
		        rename("shinestemp.dat","shines.dat");
                
        	    flag==1?
                cout<<endl<<endl<<"\tContact Succesfully Deleted! " :
		        cout<<endl<<endl<<"\t Sorry, we did not find that contact";

                cout<<" \n Do you want to delete another record?(y/n) \n";
                cin >> deloption1;
                }
                if (deloption2 == 'n'){
                cout << " \n No record was deleted! \n";
                cout << "Do you want to delete a record? (y/n)";
                cin >> deloption1;}
             
        }while(deloption1 == 'y');
    
		}
    
		

     
	
	//this function allows the user to search for a record by phone number.
    // the user can update the fileusing the createCon function	
	void editCon() {
		long long editPhoneNo;
		fstream file6;

		cout<<"Edit contact";
		cout<<"\n*******************************n\n";
		cout<<"Enter the phone number you would like to edit: ";
		cin>>editPhoneNo;

		file6.open("shines.dat",ios::binary|ios::out|ios::in);

		while(!file6.eof()) {
			if(file6.read(reinterpret_cast<char*>(this),sizeof(*this))) {
				if (phoneNo == editPhoneNo) {
					cout<< " \n Update your contact information \n";
					createCon();
					long long pos=-1*sizeof(*this);
					file6.seekp(pos,ios::cur);
					file6.write(reinterpret_cast<char*>(this),sizeof(*this));
					cout<<endl<<endl<<"\t Contact Successfully Updated !";
					return;
				}
			}
		}
		cout<<"\n\n Sorry, we could not find any records.";
		file6.close(); 
	}
};

int main() {
	system("cls"); // clear system
	system("Color 3F"); // 

	cout<<"\n\n\n\n\n\n\n\n\t\t\t ************* WELCOME TO SHINES PHONEBOOK *************  ";

    // this while loop allows the user to be directed to the Main Menu
    //by selecting 1. If the user selects 0, the user will exit the program 
	while(1) {
		contact c1; //create an object from the contact class
		int option2;
        char exitOpt, exitOpt2;


		system("cls"); // clears the screen
		system("Color 03"); //customized color for system

        //main menu displaying options for the user to enter
		cout<<"\n \n *** SHINES PHONEBOOK *** ";
        cout<<"\n\n *** MAIN MENU *** ";
		cout<<"\n ************************ \n";
        cout<<"[1] Add a new Contact\n";
        cout<<"[2] Display all Contacts\n";
        cout<<"[3] Search for contact\n";
        cout<<"[4] Edit a Contact \n";
        cout<<"[5] Delete a Contact \n";
        cout<<"[0] Exit \n ";
		cout<<"\n ************************ \n";
        cout<<"What would you like to do? : ";
        cin>>option2;


        //switch case allowing user to choose each option
        switch(option2) { //Create contact option
        	case 1:
        		system("cls");
        		c1.writeCon();
        		break;

        	case 2: //display all contacts
				system("cls");
        		c1.readCon();
        		break;

			case 3: //
        		system("cls");
        		c1.searchCon();
        		break;

        	case 4: //update and edits the selected record
				system("cls");
        		c1.editCon();
        		break;

        	case 5: //deletes the selected record
			    system("cls");
        		c1.deleteCon();
        		break;

        	case 0: //option to exit the progran
        		system("cls");
                cout<<"Are you sure you would like to exit?(y/n)";
			    cin>>exitOpt;
                if(exitOpt == 'y')
                {
        		cout<<"\n\n\n\t\t\tThank you for using SHINES PHONEBOOK."<<endl<<endl;
        		exit(0);}
        		break;

        	default:
				continue;	
		}

        // option to return to the main menu or exit th e program use a switch case.
		int option3;
		cout<<"\n\n What would you like to do? :\n[1] Go to the Main Menu\t\t[0] Exit\n";
		cin>>option3;

		switch (option3) {
			case 0:
                char finalexit;
        		system("cls");
                cout<<"Are you sure you would like to exit?(y/n)";
			    cin>>finalexit;
                
		        if (finalexit =='y')
                {
                    cout<<"\n\n\n\t\t\tThank you for using SHINES PHONEBOOK."<<endl<<endl;
        		    exit(0);
                }
                break;
               default:
				continue;	
        		

			
		}
	}


}