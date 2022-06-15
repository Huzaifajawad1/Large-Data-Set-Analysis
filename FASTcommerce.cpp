#include<bits\stdc++.h>
#include<queue>
#include<stack>
#include <windows.h>
#include<dos.h>
#include<time.h>
#include<conio.h>
#include <stdlib.h>

using namespace std;

# define TABLE_SIZE 1048541

class Node
{
	
	public:
		// DATA MEMBERS
		
		int user_id;
		int pro_id;
		double price;
		string etime;
		string cat_id;
		string cat_code;
		string brand;
		Node* next;
		
		// MEMBER FUNCTIONS
		
			Node()
			{
				user_id=0;
				pro_id=0;
				price=0;
				etime="";
				cat_id="";
				cat_code="";
				brand="";
				next=0;
			}
			
			Node(int u_id, int p_id,double pri,string etim,string c_id,string c_code,string bran)
			{
				user_id=u_id;
				pro_id=p_id;
				price=pri;
				etime=etim;
				cat_id=c_id;
				cat_code=c_code;
				brand=bran;
				next=0;
			}
};

	void Print(Node* node)
	{
		cout << "\t\t\tFor User_ID: " << node->user_id << endl;
		cout << "\t\t\tDate/Time of Purchase: " << node->etime << endl;
		cout << "\t\t\tPrice of Product Purchased: " << node->price << endl;
	    cout<<endl;
	    
	if(node->brand=="")
	{
		cout<<"\t\t\tThis item doesnt belong to any Brand\n";
	}
	
	else
	{
		cout << "\t\t\tName of Product Purchased: " << node->brand << endl;	
	}
		cout << "\t\t\tID of Product Purchased: " << node->pro_id << endl;
	
	if(node->cat_code=="")
	{
			cout<<"\t\t\tThis item doesnt belong to any Catogery\n";
		}
		else
		{
			cout << "\t\t\tName of Category Purchased: " << node->cat_code << endl;
		}
			cout << "\t\t\tID of Category Purchased: " << node->cat_id << endl;
	}

/////////////////////////////////	KEY: User_ID	/////////////////////////////////////////////////////////////

	class HashMap
	{	
		public:
		Node** htable;
		Node* minprice;
		Node* maxprice;
		Node *temp1;
		int bestuser;
		
		HashMap()
		{
			htable = new Node*[TABLE_SIZE];
			for (int i = 0; i < TABLE_SIZE; i++)
				htable[i] = NULL;
			minprice=new Node();
			maxprice=new Node();
			minprice->price=INT_MAX;
			temp1=new Node();
        }
        
		~HashMap()
		{
			for (int i = 0; i < TABLE_SIZE; ++i)
			{
				
			Node* entry = htable[i];
			
			while (entry != NULL)
			{
				Node* prev = entry;
				entry = entry->next;
				delete prev;
			}
			
			}
            delete[] htable;
        }

        int HashFunc(int key)
		{
			return key % TABLE_SIZE;
		}
		void Insert(int key, Node* n)
		{
			if(n->price >= maxprice->price)
			{
				maxprice=n;
			}
			
			if(n->price!=0 && n->price <= minprice->price)
			{
				minprice=n;
			}
			
        int hash_val = HashFunc(key);
        Node* prev = NULL;
        Node* entry = htable[hash_val];
        
		while (entry != NULL)
        {
            prev = entry;
            entry = entry->next;
        }
        
        if (entry == NULL)
        {
            entry = n;
            if (prev == NULL)
        	{
                htable[hash_val] = entry;
        	}
        	else
        	{
            	prev->next = entry;
        	}
        }
        
        else
        {
            entry = n;
        }
    }
    
    int Search(int key)
    {
        bool flag = false;
        int hash_val = HashFunc(key);
        Node* entry = htable[hash_val];
    
	while (entry != NULL)
    {
       if (entry->user_id == key)
        {
          flag = true;
        }
    	entry = entry->next;
    }
        if (!flag)
        {
        	cout<<"\t\t\tThis user has not purchased anything from US!\n";
			return -1;
		}
		else
			cout<<"\t\t\tUserId Exists!";
			return flag;
    }
    
	void displayminprice()
	{
		cout<<"\n\t\t\t!!!!!!!!!!!!!!!Details of the Cheaspest Item Sold are!!!!!!!!!!!!!!!\n";
		Print(minprice);
	}
	
	void displaymaxprice()
	{
		cout<<"\n\t\t\t!!!!!!!!!!!!!!!Details of the Most Expensive Item Sold are:!!!!!!!!!!!!!!!\n";
		Print(maxprice);
	}
	
	void displaybestcustomer()
	{	
		int max=INT_MIN;
		
		for(int i=0;i<TABLE_SIZE;i++)
		{
		int c=0;
	 	Node* n=htable[i];
	 	if(n!=0)
	 	{
			while(n!=0)
			{
				if(htable[i]->user_id==n->user_id)
				{
					c++;
				}
					n=n->next;
			}
				if(c>max && c!=0)
				{
					max=c;
					bestuser=htable[i]->user_id;
				}
			}
		}
		cout<<endl;
		cout<<"\t\t\tThe customer with most purchases is: "<<bestuser<<endl<<endl;
		cout<<"\t\t\tTHE TOTAL NUMBER OF PURCHASES MADE BY THIS PERSON IS :"<<max<<endl<<endl;
		cout<<"\t\t\t!!!!!!!!!!!!!!!All his purchasing history!!!!!!!!!!!!!!!\n"<<endl;
		searchuser(bestuser);
	}	
	
	void InsertUid(void)
	{
	int uid;
	int pid;
	double pri;
	string eti;
	string cid;
	string cod;
	string brd;
	
	cout << "\t\t\tInput User_ID: ";
	cin >> uid;
	cout << "\t\t\tInput Product_ID: ";
	cin >> pid;
	cout << "\t\t\tInput Product Price: ";
	cin >> pri;
	cout << "\t\t\tInput Date/Time of User's Activity: ";
	cin >> eti;
	cout << "\t\t\tInput Category_ID: ";
	cin >> cid;
	cout << "\t\t\tInput Category_Code: ";
	cin >> cod;
	cout << "\t\t\tInput Product Brand Name: ";
	cin >> brd;
	Node *n=new Node(uid,pid,pri,eti,cid,cod,brd);
	Insert(uid,n);
	cout<<"\t\t\t!!!!!!!!!!!!Value Inserted!!!!!!!!!!!!\n";
	}
	
	void searchuser(int val)
	{
		if(Search(val)==1)
		{
		int h=HashFunc(val);
		Node *n=htable[h];
		
		queue<Node*> g;
		
			while(n!=0 && htable[h]->user_id==n->user_id)
			{
				g.push(n);
				n=n->next;
			}
			
			while(!g.empty())
			{
				Node *f=g.front();
				g.pop();
				Print(f);
			}
		}
		
		else
		{
			cout<<"\t\t\tNo such element exits!!!!!\n";
		}
	}
	
	void searchforpro()
	{
		int u;
		cout<<"\t\t\tEnter a valid User_id";
		cin>>u;
		int count=0;
		if(Search(u)==1)
		{
		int h=HashFunc(u);
		Node *n=htable[h];
		stack<Node*> s;
			while(n!=0 && htable[h]->user_id==n->user_id)
			{
				s.push(n);
				n=n->next;
			}
			cout<<"\t\t\tThe products purchased by this user are\n";
			while(!s.empty())
			{
				Node *f=s.top();
				s.pop();
				count++;
				cout<<"\t\t\t"<<count<<" : "<<"Product Id : "<<f->pro_id<<"\n";
			}
			cout<<"\t\t\tTOTAL NUMBER OF PRODUCTS BOUGHT BY THIS USER:" <<count<<endl<<endl;
		}
		else
		{
			cout<<"\t\t\tEnter a correct user_id\n";
		}
	}
	
	
	void searchforpri()
	{
		int u,tprice=0;
		cout<<"\n\t\t\tEnter a valid User_id: ";
		cin>>u;
		if(Search(u)==1)
		{
		int h=HashFunc(u);
		Node *n=htable[h]; 
		
		stack<Node*> s;
			
			while(n!=0 && htable[h]->user_id==n->user_id)
			{
				s.push(n);
				n=n->next;
			}
			cout<<"\t\t\tThe price of products purchased by this user are\n";
			while(!s.empty())
			{
				Node *f=s.top();
				s.pop();
				cout<<"Price : "<<f->price<<"\n";
				tprice+=f->price;
			}
				cout<<"\t\t\tThe total money spent by this costumer is : "<<tprice<<endl;
		}
		else
		{
			cout<<"\t\t\tEnter a correct user_id:\n";
		}
	}	
	
	void searchforbrandandcat()
	{
		int u;
		cout<<"\t\t\tEnter a valid User_id: ";
		cin>>u;
		
		if(Search(u)==1)
		{
		int h=HashFunc(u);
		Node *n=htable[h];
		stack<Node*> s;
			
			while(n!=0 && htable[h]->user_id==n->user_id)
			{
				s.push(n);
				n=n->next;
			}
			cout<<"\t\t\tThe brand and catogery purchased by this user are\n";
			while(!s.empty())
			{
				Node *f=s.top();
				s.pop();
				cout<<"\t\t\tThe category id for product is : "<<f->cat_id<<endl;
				cout<<"\t\t\tThe category code for product is : "<<f->cat_code<<endl;
				cout<<"\t\t\tThe Brand for product is : "<<f->brand<<endl;
				cout<<endl;
			}
		}
		else
		{
			cout<<"\t\t\tEnter a correct user_id\n";
		}
	}
			
};


  
/////////////////////////////////	KEY: Product_ID	/////////////////////////////////////////////////////////////

	class HashP
	{	
		public:
		Node** htable;
		Node* minprice;
		Node* maxprice;
		Node *temp1;
		int bestpro;
		HashP()
		{
			htable = new Node*[TABLE_SIZE];
			for (int i = 0; i < TABLE_SIZE; i++)
				htable[i] = NULL;
			minprice=new Node();
			maxprice=new Node();
			minprice->price=1000;
			temp1=new Node();
        }
		~HashP()
		{
			for (int i = 0; i < TABLE_SIZE; ++i)
			{
				
			Node* entry = htable[i];
			
			while (entry != NULL)
			{
				Node* prev = entry;
				entry = entry->next;
				delete prev;
			}
			
			}
            delete[] htable;
        }

        int HashFunc(int key)
		{
			return key % TABLE_SIZE;
		}
		void Insert(int key, Node* n)
		{
			if(n->price >= maxprice->price)
			{
				maxprice=n;
			}
			
			if(n->price!=0 && n->price <= minprice->price)
			{
				minprice=n;
			}
			
        int hash_val = HashFunc(key);
        Node* prev = NULL;
        Node* entry = htable[hash_val];
        while (entry != NULL)
        {
            prev = entry;
            entry = entry->next;
        }
        if (entry == NULL)
        {
            entry = n;
            if (prev == NULL)
        	{
                htable[hash_val] = entry;
        	}
        	else
        	{
            prev->next = entry;
        	}
        }
        else
        {
            entry = n;
        }
    }
    
    int Search(int key)
    {
        bool flag = false;
        int hash_val = HashFunc(key);
        Node* entry = htable[hash_val];
        while (entry != NULL)
    {
       if (entry->pro_id == key)
        {
          flag = true;
        }
    	entry = entry->next;
    }
        if (!flag)
        {
        	cout<<"\t\t\t!!!!!!!!!!!!!!!This Product Has Not Been Purchased!!!!!!!!!!!!!!!!!\n";
		return -1;
		}
		else
		{
		cout<<"\t\t\t!!!!!!!!!!!!!!!This Product Has Been Purchased!!!!!!!!!!!!!!!!!\n";
		return flag;
	    }
    }
    
	void displayminprice()
	{
		cout<<"\n\t\t\t!!!!!!!!!!!!!!!Details of the Cheaspest Item Sold are:!!!!!!!!!!!!!!!\n";
		Print(minprice);
	}
	
		void displaymaxprice()
	{
		cout<<"\n\t\t\t!!!!!!!!!!!!!!!Details of the Most Expensive Item Sold are:!!!!!!!!!!!!!!!\n";
		Print(maxprice);
	}
	
	void displaybestproduct()
	{	
		int max=INT_MIN;
		
		for(int i=0;i<TABLE_SIZE;i++)
		{
		int c=0;
	 	Node* n=htable[i];
	 	
		 if(n!=0)
	 	{
			while(n!=0)
			{
				if(htable[i]->pro_id==n->pro_id)
				{
				    c++;
				}
				n=n->next;
			}
				if(c>max && c!=0)
				{
					max=c;
					bestpro=htable[i]->pro_id;
				}
			}
		}
		cout<<"\t\t\tThe most Selling Product:"<<bestpro<<endl;
		cout<<"\t\t\tThe Total Amount Of this product Sold :"<<max<<endl;
		cout<<"\t\t\t!!!!!!!!!!!!!!!ALL PURCHASING HISTORY OF THIS PROUCT!!!!!!!!!!!!!!! :\n\n";
		searchpro(bestpro);
	}	
	
	
	void searchpro(int val)
	{
		if(Search(val)==1)
		{
		
			int h=HashFunc(val);
			Node *n=htable[h];
			queue<Node*> g;
			while(n!=0 && htable[h]->pro_id==n->pro_id)
			{
				g.push(n);
				n=n->next;
			}
			
			while(!g.empty())
			{
				Node *f=g.front();
				g.pop();
				Print(f);
			}
		}
		
		else
		{
			cout<<"\t\t\tNo such element exits\n";
		}
	}
	
	
	void InsertPid(void)
	{
		
	int uid,pid;
	double pri;
	string eti,cid,cod,brd;
	
		cout << "\t\t\tInput Product_ID: ";
		cin >> pid;
		cout << "\t\t\tInput User_ID: ";
		cin >> uid;
		cout << "\t\t\tInput Product Price: ";
		cin >> pri;
		cout << "\t\t\tInput Date/Time of User's Activity: ";
		cin >> eti;
		cout << "\t\t\tInput Category_ID: ";
		cin >> cid;
		cout << "\t\t\tInput Category_Code: ";
		cin >> cod;
		cout << "\t\t\tInput Product Brand Name: ";
		cin >> brd;
		
		Node *n = new Node(uid,pid,pri,eti,cid,cod,brd);
		Insert(pid,n);
		cout<<"\t\t\t!!!!!!!!!!Value Inserted!!!!!!!!!!!!!!\n";
	}		
	
	void searchforuser()
	{
		int p,count=0;
		cout<<"\t\t\tEnter a valid Product_id";
		cin>>p;
		
		if(Search(p)==1)
		{
		int h=HashFunc(p);
		Node *n=htable[h];
		stack<Node*> s;
			while(n!=0&&htable[h]->pro_id==n->pro_id)
			{
				s.push(n);
				n=n->next;
			}
			cout<<"\t\t\tThe users that purchased this product are :\n";
			
			while(!s.empty())
			{
				Node *f=s.top();
				s.pop();
				count++;
				cout<<"\t\t\t"<<count<<" : "<<"User_Id : "<<f->user_id<<"\n";
			}
			cout<<"\t\t\tThe Total Number of Users Who Bought this Item: "<<count<<endl<<endl;
		}
		else
		{
			cout<<"\t\t\tEnter a correct product_id\n";
		}
	}
	
	void searchforpri()
	{
		int p,tprice=0,c=0;
		cout<<"\t\t\tEnter a valid Product_Id: ";
		cin>>p;
		
		if(Search(p)==1)
		{
		int h=HashFunc(p);
		Node *n=htable[h];
		
		stack<Node*> s;
		
			while(n!=0&&htable[h]->pro_id==n->pro_id)
			{
				s.push(n);
				n=n->next;
				c++;
			}
			Node *g=s.top();
			cout<<"\t\t\tThe price of product is : "<<g->price;
			while(!s.empty())
			{
				Node *f=s.top();
				s.pop();
				tprice+=f->price;
			}
				cout<<"\t\t\tThe total money generated by this product is : "<<tprice<<endl;
				cout<<"\t\t\tIt was bought  "<<c<<" times\n";
		}
		else
		{
			cout<<"\t\t\tEnter a correct Product_id\n";
		}
	}
	
	void searchforbrandandcat()
	{
		int p;
		cout<<"\n\t\t\tEnter a valid Product_Id: ";
		cin>>p;
		
		if(Search(p)==1)
		{
		int h=HashFunc(p);
		Node *n=htable[h];
		cout<<"\t\t\tThe category id for this product is : "<<n->cat_id<<endl;
		cout<<"\t\t\tThe category code for this product is : "<<n->cat_code<<endl;
		cout<<"\t\t\tThe Brand for this product is : "<<n->brand<<endl;
		cout<<endl;
		
		}
		else
		{
			cout<<"\t\t\tEnter a correct Product_id\n";
		}
	}
};
		

COORD coord = {0, 0};
void gotoxy (int x, int y)
{
coord.X = x; coord.Y = y; // X and Y coordinates
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


///////////////////////////////   Login   /////////////////////////////////
void Login()
{
    string userName;
    string userPassword;
    int loginAttempt = 0;

    while (loginAttempt < 5)
    {
    	
    gotoxy(20,9);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2   WELCOME  \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	gotoxy(20,11);
	printf("\xDB\xDB\xDB\xDB\xB2 1. Please enter your user name: ");
	cout<<"\n\n\t\t\t";cin >> userName;
	gotoxy(20,13);
	printf("\xDB\xDB\xDB\xDB\xB2 2. Please enter your user password:");
	cout<<"\n\n\t\t\t";cin >> userPassword;
	gotoxy(20,15);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	gotoxy(20,17);
	
        if (userName == "Umer" && userPassword == "fast")
        {
            break;
        }
        else if (userName == "Huzaifa" && userPassword == "fast")
        {
            break;
        }
        else if (userName == "Usaid" && userPassword == "fast")
        {
            break;
        }
        else
        {
            cout << "\t\t\t\t\tInvalid login attempt. Please try again.\n" << '\n';
            loginAttempt++;
        }
    }
    if (loginAttempt == 5)
    {
            cout << "\t\t\t\t\tToo many login attempts! The program will now terminate.";
            exit(1);
    }

}

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$/
const int BLUE = 1;
const int GREEN = 2;
const int RED = 4;
const int WHITE = 15;

void clearScreen(int characterLength) {
	for (int i = 0; i < characterLength; i++) {
		cout << "\b";
	}
}

void changeColour(int colour) {
	HANDLE hConsole;
	
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, colour);
}

void showLoadingScreen() {
	int i;
	string closed = "..........", open = "..........";
	int colour[] = {RED, GREEN, BLUE};
	
	cout << closed;
	
	for (i = 0; i < 3; i++) {
		Sleep(300);
		
		clearScreen(5);
		changeColour(colour[i]);
		
		cout << open;
		
		Sleep(300);
		
		clearScreen(5);
		changeColour(WHITE);
		
		cout << closed;
	}
	
	clearScreen(5);
	changeColour(WHITE);
}

void showBlinkingLights() {
	changeColour(RED);
	cout << "PLEASE";
	Sleep(300);
	
	changeColour(GREEN);
	cout << "WAIT";
	Sleep(300);
	
	changeColour(WHITE);
}

void ascii_art()
{
    string input;
    input="FAST COMMERCE";
    //loop will print first layer
    for (int i=0; i < input.size(); i++)
    {
        if (input[i] == 'A' || input[i]== 'a')
            cout<<"  ___   ";
        if (input[i] == 'B' || input[i] == 'b')
            cout<<" _____  ";
        if (input[i] == 'C' || input[i] == 'c')
            cout<<" _____  ";
        if (input[i] == 'D' || input[i] == 'd')
            cout<<" _____  ";
        if (input[i] == 'E' || input[i] == 'e')
            cout<<" _____  ";
        if (input[i] == 'F' || input[i] == 'f')
            cout<<" _____  ";
        if (input[i] == 'G' || input[i] == 'g')
            cout<<" _____  ";
        if (input[i] == 'H' || input[i] == 'h')
            cout<<" _   _  ";
        if (input[i] == 'I' || input[i] == 'i')
            cout<<" _____  ";
        if (input[i] == 'J' || input[i] == 'j')
            cout<<"   ___  ";
        if (input[i] == 'K' || input[i] == 'k')
            cout<<" _   __ ";
        if (input[i] == 'L' || input[i] == 'l')
            cout<<" _      ";
        if (input[i] == 'M' || input[i] == 'm')
            cout<<" __  __  ";
        if (input[i] == 'N' || input[i] == 'n')
            cout<<" _   _  ";
        if (input[i] == 'O' || input[i] == 'o')
            cout<<" _____  ";
        if (input[i] == 'P' || input[i] == 'p')
            cout<<" _____  ";
        if (input[i] == 'Q' || input[i] == 'q')
            cout<<" _____  ";
        if (input[i] == 'R' || input[i] == 'r')
            cout<<" _____  ";
        if (input[i] == 'S' || input[i] == 's')
            cout<<" _____  ";
        if (input[i] == 'T' || input[i] == 't')
            cout<<" _____  ";
        if (input[i] == 'U' || input[i] == 'u')
            cout<<" _   _  ";
        if (input[i] == 'V' || input[i] == 'v')
            cout<<" _   _  ";
        if (input[i] == 'W' || input[i] == 'w')
            cout<<" _    _  ";
        if (input[i] == 'X' || input[i] == 'x')
            cout<<"__   __ ";
        if (input[i] == 'Y' || input[i] == 'y')
            cout<<"__   __ ";
        if (input[i] == 'Z' || input[i]== 'z')
            cout<<" ______ ";
        if (input[i] == ' ')
            cout<<"  ";
        if (input[i] == '`')
            cout<<" _  ";
        if (input[i] == '~')
            cout<<"      ";
        if (input[i] == '1')
            cout<<" __   ";
        if (input[i]== '2')
            cout<<" _____  ";
        if (input[i]== '3')
            cout<<" _____  ";
        if (input[i] == '4')
            cout<<"   ___  ";
        if (input[i] == '5')
            cout<<" _____  ";
        if (input[i] == '6')
            cout<<"  ____  ";
        if (input[i] == '7')
            cout<<" ______ ";
        if(input[i] == '.')
            cout<<"    ";
        if (input[i] == '8')
            cout<<" _____  ";
        if (input[i] == '9')
            cout<<" _____  ";
        if (input[i] == '0')
            cout<<" _____  ";
        if (input[i] == '!')
            cout<<" _  ";
        if (input[i] == '@')
            cout<<"   ____   ";
        if (input[i] == '#')
            cout<<"   _  _    ";
        if (input[i] == '$')
            cout<<"  _   ";
        if (input[i] == '%')
            cout<<" _   __ ";
        if (input[i] == '^')
            cout<<" /\\  ";
        if (input[i] == '&')
            cout<<"         ";
        if (input[i] == '*')
            cout<<"    _     ";
        if (input[i] == '(')
            cout<<"  __ ";
        if (input[i] == ')')
            cout<<"__   ";
        if (input[i] == '-')
            cout<<"         ";
        if (input[i] == '_')
            cout<<"         ";
        if (input[i] == '=')
            cout<<"         ";
        if (input[i] == '+')
            cout<<"        ";
        if (input[i] == '[')
            cout<<" ___  ";
        if (input[i] == '{')
            cout<<"   __ ";
        if (input[i]== ']')
            cout<<" ___  ";
        if (input[i] == '}')
            cout<<"__    ";
        if (input[i] == '|')
            cout<<" _  ";
        if (input[i] == '\\')
            cout<<"__      ";
        if (input[i] == ';')
            cout<<" _  ";
        if (input[i] == ':')
            cout<<"    ";
        if (input[i] == '\'')
            cout<<" _  ";
        if (input[i] == '"')
            cout<<" _ _  ";
        if (input[i] == '<')
            cout<<"   __ ";
        if (input[i] == ',')
            cout<<"    ";
        if (input[i] == '>')
            cout<<"__    ";
        if (input[i] == '/')
            cout<<"     __ ";
        if (input[i] == '?')
            cout<<" ___   ";
    }
    cout<<endl;
    //loop will print second layer
    for (int i=0; i < input.size(); i++)
    {
        if (input[i] == 'A' || input[i]== 'a')
            cout<<" / _ \\  ";
        if (input[i] == 'B' || input[i] == 'b')
            cout<<"| ___ \\ ";
        if (input[i] == 'C' || input[i] == 'c')
            cout<<"/  __ \\ ";
        if (input[i] == 'D' || input[i] == 'd')
            cout<<"|  _  \\ ";
        if (input[i] == 'E' || input[i] == 'e')
            cout<<"|  ___| ";
        if (input[i] == 'F' || input[i] == 'f')
            cout<<"|  ___| ";
        if (input[i] == 'G' || input[i] == 'g')
            cout<<"|  __ \\ ";
        if (input[i] == 'H' || input[i] == 'h')
            cout<<"| | | | ";
        if (input[i] == 'I' || input[i] == 'i')
            cout<<"|_   _| ";
        if (input[i] == 'J' || input[i] == 'j')
            cout<<"  |_  | ";
        if (input[i] == 'K' || input[i] == 'k')
            cout<<"| | / / ";
        if (input[i] == 'L' || input[i] == 'l')
            cout<<"| |     ";
        if (input[i] == 'M' || input[i] == 'm')
            cout<<"|  \\/  | ";
        if (input[i] == 'N' || input[i] == 'n')
            cout<<"| \\ | | ";
        if (input[i] == 'O' || input[i] == 'o')
            cout<<"|  _  | ";
        if (input[i] == 'P' || input[i] == 'p')
            cout<<"| ___ \\ ";
        if (input[i] == 'Q' || input[i] == 'q')
            cout<<"|  _  | ";
        if (input[i] == 'R' || input[i] == 'r')
            cout<<"| ___ \\ ";
        if (input[i] == 'S' || input[i] == 's')
            cout<<"/  ___| ";
        if (input[i] == 'T' || input[i] == 't')
            cout<<"|_   _| ";
        if (input[i] == 'U' || input[i] == 'u')
            cout<<"| | | | ";
        if (input[i] == 'V' || input[i] == 'v')
            cout<<"| | | | ";
        if (input[i] == 'W' || input[i] == 'w')
            cout<<"| |  | | ";
        if (input[i] == 'X' || input[i] == 'x')
            cout<<"\\ \\ / / ";
        if (input[i] == 'Y' || input[i] == 'y')
            cout<<"\\ \\ / / ";
        if (input[i] == 'Z' || input[i]== 'z')
            cout<<"|___  / ";
        if (input[i] == ' ')
            cout<<"  ";
        if (input[i] == '`')
            cout<<"( ) ";
        if (input[i] == '~')
            cout<<"      ";
        if (input[i] == '1')
            cout<<"/  |  ";
        if (input[i]== '2')
            cout<<"/ __  \\ ";
        if (input[i]== '3')
            cout<<"|____ | ";
        if (input[i] == '4')
            cout<<"  /   | ";
        if (input[i] == '5')
            cout<<"|  ___| ";
        if (input[i] == '6')
            cout<<" / ___| ";
        if (input[i] == '7')
            cout<<"|___  / ";
        if(input[i] == '.')
            cout<<"    ";
        if (input[i] == '8')
            cout<<"|  _  | ";
        if (input[i] == '9')
            cout<<"|  _  | ";
        if (input[i] == '0')
            cout<<"|  _  | ";
        if (input[i] == '!')
            cout<<"| | ";
        if (input[i] == '@')
            cout<<"  / __ \\  ";
        if (input[i] == '#')
            cout<<" _| || |_  ";
        if (input[i] == '$')
            cout<<" | |  ";
        if (input[i] == '%')
            cout<<"(_) / / ";
        if (input[i] == '^')
            cout<<"|/\\| ";
        if (input[i] == '&')
            cout<<"  ___    ";
        if (input[i] == '*')
            cout<<" /\\| |/\\  ";
        if (input[i] == '(')
            cout<<" / / ";
        if (input[i] == ')')
            cout<<"\\ \\  ";
        if (input[i] == '-')
            cout<<"         ";
        if (input[i] == '_')
            cout<<"         ";
        if (input[i] == '=')
            cout<<" ______  ";
        if (input[i] == '+')
            cout<<"   _    ";
        if (input[i] == '[')
            cout<<"|  _| ";
        if (input[i] == '{')
            cout<<"  / / ";
        if (input[i]== ']')
            cout<<"|_  | ";
        if (input[i] == '}')
            cout<<"\\ \\   ";
        if (input[i] == '|')
            cout<<"| | ";
        if (input[i] == '\\')
            cout<<"\\ \\     ";
        if (input[i] == ';')
            cout<<"(_) ";
        if (input[i] == ':')
            cout<<" _  ";
        if (input[i] == '\'')
            cout<<"( ) ";
        if (input[i] == '"')
            cout<<"( | ) ";
        if (input[i] == '<')
            cout<<"  / / ";
        if (input[i] == ',')
            cout<<"    ";
        if (input[i] == '>')
            cout<<"\\ \\   ";
        if (input[i] == '/')
            cout<<"    / / ";
        if (input[i] == '?')
            cout<<"|__ \\  ";
    }
    cout<<endl;
    //loop will print third layer
    for (int i=0; i < input.size(); i++)
    {
        if (input[i] == 'A' || input[i]== 'a')
            cout<<"/ /_\\ \\ ";
        if (input[i] == 'B' || input[i] == 'b')
            cout<<"| |_/ / ";
        if (input[i] == 'C' || input[i] == 'c')
            cout<<"| /  \\/ ";
        if (input[i] == 'D' || input[i] == 'd')
            cout<<"| | | | ";
        if (input[i] == 'E' || input[i] == 'e')
            cout<<"| |__   ";
        if (input[i] == 'F' || input[i] == 'f')
            cout<<"| |_    ";
        if (input[i] == 'G' || input[i] == 'g')
            cout<<"| |  \\/ ";
        if (input[i] == 'H' || input[i] == 'h')
            cout<<"| |_| | ";
        if (input[i] == 'I' || input[i] == 'i')
            cout<<"  | |   ";
        if (input[i] == 'J' || input[i] == 'j')
            cout<<"    | | ";
        if (input[i] == 'K' || input[i] == 'k')
            cout<<"| |/ /  ";
        if (input[i] == 'L' || input[i] == 'l')
            cout<<"| |     ";
        if (input[i] == 'M' || input[i] == 'm')
            cout<<"| .  . | ";
        if (input[i] == 'N' || input[i] == 'n')
            cout<<"|  \\| | ";
        if (input[i] == 'O' || input[i] == 'o')
            cout<<"| | | | ";
        if (input[i] == 'P' || input[i] == 'p')
            cout<<"| |_/ / ";
        if (input[i] == 'Q' || input[i] == 'q')
            cout<<"| | | | ";
        if (input[i] == 'R' || input[i] == 'r')
            cout<<"| |_/ / ";
        if (input[i] == 'S' || input[i] == 's')
            cout<<"\\ `--.  ";
        if (input[i] == 'T' || input[i] == 't')
            cout<<"  | |   ";
        if (input[i] == 'U' || input[i] == 'u')
            cout<<"| | | | ";
        if (input[i] == 'V' || input[i] == 'v')
            cout<<"| | | | ";
        if (input[i] == 'W' || input[i] == 'w')
            cout<<"| |  | | ";
        if (input[i] == 'X' || input[i] == 'x')
            cout<<" \\ V /  ";
        if (input[i] == 'Y' || input[i] == 'y')
            cout<<" \\ V /  ";
        if (input[i] == 'Z' || input[i]== 'z')
            cout<<"   / /  ";
        if (input[i] == ' ')
            cout<<"  ";
        if (input[i] == '`')
            cout<<" \\| ";
        if (input[i] == '~')
            cout<<" /\\/| ";
        if (input[i] == '1')
            cout<<"`| |  ";
        if (input[i]== '2')
            cout<<"`' / /' ";
        if (input[i]== '3')
            cout<<"    / / ";
        if (input[i] == '4')
            cout<<" / /| | ";
        if (input[i] == '5')
            cout<<"|___ \\  ";
        if (input[i] == '6')
            cout<<"/ /___  ";
        if (input[i] == '7')
            cout<<"   / /  ";
        if(input[i] == '.')
            cout<<"    ";
        if (input[i] == '8')
            cout<<" \\ V /  ";
        if (input[i] == '9')
            cout<<"| |_| | ";
        if (input[i] == '0')
            cout<<"| |/' | ";
        if (input[i] == '!')
            cout<<"| | ";
        if (input[i] == '@')
            cout<<" / / _` | ";
        if (input[i] == '#')
            cout<<"|_  __  _| ";
        if (input[i] == '$')
            cout<<"/ __) ";
        if (input[i] == '%')
            cout<<"   / /  ";
        if (input[i] == '^')
            cout<<"     ";
        if (input[i] == '&')
            cout<<" ( _ )   ";
        if (input[i] == '*')
            cout<<" \\ ` ' /  ";
        if (input[i] == '(')
            cout<<"| |  ";
        if (input[i] == ')')
            cout<<" | | ";
        if (input[i] == '-')
            cout<<" ______  ";
        if (input[i] == '_')
            cout<<"         ";
        if (input[i] == '=')
            cout<<"|______| ";
        if (input[i] == '+')
            cout<<" _| |_  ";
        if (input[i] == '[')
            cout<<"| |   ";
        if (input[i] == '{')
            cout<<" | |  ";
        if (input[i]== ']')
            cout<<"  | | ";
        if (input[i] == '}')
            cout<<" | |  ";
        if (input[i] == '|')
            cout<<"| | ";
        if (input[i] == '\\')
            cout<<" \\ \\    ";
        if (input[i] == ';')
            cout<<"    ";
        if (input[i] == ':')
            cout<<"(_) ";
        if (input[i] == '\'')
            cout<<"|/  ";
        if (input[i] == '"')
            cout<<" V V  ";
        if (input[i] == '<')
            cout<<" / /  ";
        if (input[i] == ',')
            cout<<"    ";
        if (input[i] == '>')
            cout<<" \\ \\  ";
        if (input[i] == '/')
            cout<<"   / /  ";
        if (input[i] == '?')
            cout<<"   ) | ";
    }
    cout<<endl;
    //loop will print fourth layer
    for (int i=0; i < input.size(); i++)
    {
        if (input[i] == 'A' || input[i]== 'a')
            cout<<"|  _  | ";
        if (input[i] == 'B' || input[i] == 'b')
            cout<<"| ___ \\ ";
        if (input[i] == 'C' || input[i] == 'c')
            cout<<"| |     ";
        if (input[i] == 'D' || input[i] == 'd')
            cout<<"| | | | ";
        if (input[i] == 'E' || input[i] == 'e')
            cout<<"|  __|  ";
        if (input[i] == 'F' || input[i] == 'f')
            cout<<"|  _|   ";
        if (input[i] == 'G' || input[i] == 'g')
            cout<<"| | __  ";
        if (input[i] == 'H' || input[i] == 'h')
            cout<<"|  _  | ";
        if (input[i] == 'I' || input[i] == 'i')
            cout<<"  | |   ";
        if (input[i] == 'J' || input[i] == 'j')
            cout<<"    | | ";
        if (input[i] == 'K' || input[i] == 'k')
            cout<<"|    \\  ";
        if (input[i] == 'L' || input[i] == 'l')
            cout<<"| |     ";
        if (input[i] == 'M' || input[i] == 'm')
            cout<<"| |\\/| | ";
        if (input[i] == 'N' || input[i] == 'n')
            cout<<"| . ` | ";
        if (input[i] == 'O' || input[i] == 'o')
            cout<<"| | | | ";
        if (input[i] == 'P' || input[i] == 'p')
            cout<<"|  __/  ";
        if (input[i] == 'Q' || input[i] == 'q')
            cout<<"| | | | ";
        if (input[i] == 'R' || input[i] == 'r')
            cout<<"|    /  ";
        if (input[i] == 'S' || input[i] == 's')
            cout<<" `--. \\ ";
        if (input[i] == 'T' || input[i] == 't')
            cout<<"  | |   ";
        if (input[i] == 'U' || input[i] == 'u')
            cout<<"| | | | ";
        if (input[i] == 'V' || input[i] == 'v')
            cout<<"| | | | ";
        if (input[i] == 'W' || input[i] == 'w')
            cout<<"| |/\\| | ";
        if (input[i] == 'X' || input[i] == 'x')
            cout<<" / ^ \\  ";
        if (input[i] == 'Y' || input[i] == 'y')
            cout<<"  \\ /   ";
        if (input[i] == 'Z' || input[i]== 'z')
            cout<<"  / /   ";
        if (input[i] == ' ')
            cout<<"  ";
        if (input[i] == '`')
            cout<<"    ";
        if (input[i] == '~')
            cout<<"|/\\/  ";
        if (input[i] == '1')
            cout<<" | |  ";
        if (input[i]== '2')
            cout<<"  / /   ";
        if (input[i]== '3')
            cout<<"    \\ \\ ";
        if (input[i] == '4')
            cout<<"/ /_| | ";
        if (input[i] == '5')
            cout<<"    \\ \\ ";
        if (input[i] == '6')
            cout<<"| ___ \\ ";
        if (input[i] == '7')
            cout<<"  / /   ";
        if(input[i] == '.')
            cout<<"    ";
        if (input[i] == '8')
            cout<<" / _ \\  ";
        if (input[i] == '9')
            cout<<"\\____ | ";
        if (input[i] == '0')
            cout<<"|  /| | ";
        if (input[i] == '!')
            cout<<"| | ";
        if (input[i] == '@')
            cout<<"| | (_| | ";
        if (input[i] == '#')
            cout<<" _| || |_  ";
        if (input[i] == '$')
            cout<<"\\__ \\ ";
        if (input[i] == '%')
            cout<<"  / /   ";
        if (input[i] == '^')
            cout<<"     ";
        if (input[i] == '&')
            cout<<" / _ \\/\\ ";
        if (input[i] == '*')
            cout<<"|_     _| ";
        if (input[i] == '(')
            cout<<"| |  ";
        if (input[i] == ')')
            cout<<" | | ";
        if (input[i] == '-')
            cout<<"|______| ";
        if (input[i] == '_')
            cout<<"         ";
        if (input[i] == '=')
            cout<<" ______  ";
        if (input[i] == '+')
            cout<<"|_   _| ";
        if (input[i] == '[')
            cout<<"| |   ";
        if (input[i] == '{')
            cout<<"< <   ";
        if (input[i]== ']')
            cout<<"  | | ";
        if (input[i] == '}')
            cout<<"  > > ";
        if (input[i] == '|')
            cout<<"| | ";
        if (input[i] == '\\')
            cout<<"  \\ \\   ";
        if (input[i] == ';')
            cout<<" _  ";
        if (input[i] == ':')
            cout<<"    ";
        if (input[i] == '\'')
            cout<<"    ";
        if (input[i] == '"')
            cout<<"      ";
        if (input[i] == '<')
            cout<<"< <   ";
        if (input[i] == ',')
            cout<<" _  ";
        if (input[i] == '>')
            cout<<"  > > ";
        if (input[i] == '/')
            cout<<"  / /   ";
        if (input[i] == '?')
            cout<<"  / /  ";
    }
    cout<<endl;
    //loop will print fifth layer
    for (int i=0; i < input.size(); i++)
    {
        if (input[i] == 'A' || input[i]== 'a')
            cout<<"| | | | ";
        if (input[i] == 'B' || input[i] == 'b')
            cout<<"| |_/ / ";
        if (input[i] == 'C' || input[i] == 'c')
            cout<<"| \\__/\\ ";
        if (input[i] == 'D' || input[i] == 'd')
            cout<<"| |/ /  ";
        if (input[i] == 'E' || input[i] == 'e')
            cout<<"| |___  ";
        if (input[i] == 'F' || input[i] == 'f')
            cout<<"| |     ";
        if (input[i] == 'G' || input[i] == 'g')
            cout<<"| |_\\ \\ ";
        if (input[i] == 'H' || input[i] == 'h')
            cout<<"| | | | ";
        if (input[i] == 'I' || input[i] == 'i')
            cout<<" _| |_  ";
        if (input[i] == 'J' || input[i] == 'j')
            cout<<"/\\__/ / ";
        if (input[i] == 'K' || input[i] == 'k')
            cout<<"| |\\  \\ ";
        if (input[i] == 'L' || input[i] == 'l')
            cout<<"| |____ ";
        if (input[i] == 'M' || input[i] == 'm')
            cout<<"| |  | | ";
        if (input[i] == 'N' || input[i] == 'n')
            cout<<"| |\\  | ";
        if (input[i] == 'O' || input[i] == 'o')
            cout<<"\\ \\_/ / ";
        if (input[i] == 'P' || input[i] == 'p')
            cout<<"| |     ";
        if (input[i] == 'Q' || input[i] == 'q')
            cout<<"\\ \\/' / ";
        if (input[i] == 'R' || input[i] == 'r')
            cout<<"| |\\ \\  ";
        if (input[i] == 'S' || input[i] == 's')
            cout<<"/\\__/ / ";
        if (input[i] == 'T' || input[i] == 't')
            cout<<"  | |   ";
        if (input[i] == 'U' || input[i] == 'u')
            cout<<"| |_| | ";
        if (input[i] == 'V' || input[i] == 'v')
            cout<<"\\ \\_/ / ";
        if (input[i] == 'W' || input[i] == 'w')
            cout<<"\\  /\\  / ";
        if (input[i] == 'X' || input[i] == 'x')
            cout<<"/ / \\ \\ ";
        if (input[i] == 'Y' || input[i] == 'y')
            cout<<"  | |   ";
        if (input[i] == 'Z' || input[i]== 'z')
            cout<<"./ /___ ";
        if (input[i] == ' ')
            cout<<"  ";
        if (input[i] == '`')
            cout<<"    ";
        if (input[i] == '~')
            cout<<"      ";
        if (input[i] == '1')
            cout<<"_| |_ ";
        if (input[i]== '2')
            cout<<"./ /___ ";
        if (input[i]== '3')
            cout<<".___/ / ";
        if (input[i] == '4')
            cout<<"\\___  | ";
        if (input[i] == '5')
            cout<<"/\\__/ / ";
        if (input[i] == '6')
            cout<<"| \\_/ | ";
        if (input[i] == '7')
            cout<<"./ /    ";
        if(input[i] == '.')
            cout<<" _  ";
        if (input[i] == '8')
            cout<<"| |_| | ";
        if (input[i] == '9')
            cout<<".___/ / ";
        if (input[i] == '0')
            cout<<"\\ |_/ / ";
        if (input[i] == '!')
            cout<<"|_| ";
        if (input[i] == '@')
            cout<<" \\ \\__,_| ";
        if (input[i] == '#')
            cout<<"|_  __  _| ";
        if (input[i] == '$')
            cout<<"(   / ";
        if (input[i] == '%')
            cout<<" / / _  ";
        if (input[i] == '^')
            cout<<"     ";
        if (input[i] == '&')
            cout<<"| (_>  < ";
        if (input[i] == '*')
            cout<<" / , . \\  ";
        if (input[i] == '(')
            cout<<"| |  ";
        if (input[i] == ')')
            cout<<" | | ";
        if (input[i] == '-')
            cout<<"         ";
        if (input[i] == '_')
            cout<<" ______  ";
        if (input[i] == '=')
            cout<<"|______| ";
        if (input[i] == '+')
            cout<<"  |_|   ";
        if (input[i] == '[')
            cout<<"| |_  ";
        if (input[i] == '{')
            cout<<" | |  ";
        if (input[i]== ']')
            cout<<" _| | ";
        if (input[i] == '}')
            cout<<" | |  ";
        if (input[i] == '|')
            cout<<"| | ";
        if (input[i] == '\\')
            cout<<"   \\ \\  ";
        if (input[i] == ';')
            cout<<"( ) ";
        if (input[i] == ':')
            cout<<" _  ";
        if (input[i] == '\'')
            cout<<"    ";
        if (input[i] == '"')
            cout<<"      ";
        if (input[i] == '<')
            cout<<" \\ \\  ";
        if (input[i] == ',')
            cout<<"( ) ";
        if (input[i] == '>')
            cout<<" / /  ";
        if (input[i] == '/')
            cout<<" / /    ";
        if (input[i] == '?')
            cout<<" |_|   ";
    }
    cout<<endl;
    //loop will print sixth layer
    for (int i=0; i < input.size(); i++)
    {
        if (input[i] == 'A' || input[i]== 'a')
            cout<<"\\_| |_/ ";
        if (input[i] == 'B' || input[i] == 'b')
            cout<<"\\____/  ";
        if (input[i] == 'C' || input[i] == 'c')
            cout<<" \\____/ ";
        if (input[i] == 'D' || input[i] == 'd')
            cout<<"|___/   ";
        if (input[i] == 'E' || input[i] == 'e')
            cout<<"\\____/  ";
        if (input[i] == 'F' || input[i] == 'f')
            cout<<"\\_|     ";
        if (input[i] == 'G' || input[i] == 'g')
            cout<<" \\____/ ";
        if (input[i] == 'H' || input[i] == 'h')
            cout<<"\\_| |_/ ";
        if (input[i] == 'I' || input[i] == 'i')
            cout<<" \\___/  ";
        if (input[i] == 'J' || input[i] == 'j')
            cout<<"\\____/  ";
        if (input[i] == 'K' || input[i] == 'k')
            cout<<"\\_| \\_/ ";
        if (input[i] == 'L' || input[i] == 'l')
            cout<<"\\_____/ ";
        if (input[i] == 'M' || input[i] == 'm')
            cout<<"\\_|  |_/ ";
        if (input[i] == 'N' || input[i] == 'n')
            cout<<"\\_| \\_/ ";
        if (input[i] == 'O' || input[i] == 'o')
            cout<<" \\___/  ";
        if (input[i] == 'P' || input[i] == 'p')
            cout<<"\\_|     ";
        if (input[i] == 'Q' || input[i] == 'q')
            cout<<" \\_/\\_\\ ";
        if (input[i] == 'R' || input[i] == 'r')
            cout<<"\\_| \\_| ";
        if (input[i] == 'S' || input[i] == 's')
            cout<<"\\____/  ";
        if (input[i] == 'T' || input[i] == 't')
            cout<<"  \\_/   ";
        if (input[i] == 'U' || input[i] == 'u')
            cout<<" \\___/  ";
        if (input[i] == 'V' || input[i] == 'v')
            cout<<" \\___/  ";
        if (input[i] == 'W' || input[i] == 'w')
            cout<<" \\/  \\/  ";
        if (input[i] == 'X' || input[i] == 'x')
            cout<<"\\/   \\/ ";
        if (input[i] == 'Y'  || input[i] == 'y')
            cout<<"  \\_/   ";
        if (input[i] == 'Z' || input[i]== 'z')
            cout<<"\\_____/ ";
        if (input[i] == ' ')
            cout<<"  ";
        if (input[i] == '`')
            cout<<"    ";
        if (input[i] == '~')
            cout<<"      ";
        if (input[i] == '1')
            cout<<"\\___/ ";
        if (input[i]== '2')
            cout<<"\\_____/ ";
        if (input[i]== '3')
            cout<<"\\____/  ";
        if (input[i] == '4')
            cout<<"    |_/ ";
        if (input[i] == '5')
            cout<<"\\____/  ";
        if (input[i] == '6')
            cout<<"\\_____/ ";
        if (input[i] == '7')
            cout<<"\\_/     ";
        if(input[i] == '.')
            cout<<"(_) ";
        if (input[i] == '8')
            cout<<"\\_____/ ";
        if (input[i] == '9')
            cout<<"\\____/  ";
        if (input[i] == '0')
            cout<<" \\___/  ";
        if (input[i] == '!')
            cout<<"(_) ";
        if (input[i] == '@')
            cout<<"  \\____/  ";
        if (input[i] == '#')
            cout<<"  |_||_|   ";
        if (input[i] == '$')
            cout<<" |_|  ";
        if (input[i] == '%')
            cout<<"/_/ (_) ";
        if (input[i] == '^')
            cout<<"     ";
        if (input[i] == '&')
            cout<<" \\___/\\/ ";
        if (input[i] == '*')
            cout<<" \\/|_|\\/  ";
        if (input[i] == '(')
            cout<<" \\_\\ ";
        if (input[i] == ')')
            cout<<"/_/  ";
        if (input[i] == '-')
            cout<<"         ";
        if (input[i] == '_')
            cout<<"|______| ";
        if (input[i] == '=')
            cout<<"         ";
        if (input[i] == '+')
            cout<<"        ";
        if (input[i] == '[')
            cout<<"|___| ";
        if (input[i] == '{')
            cout<<"  \\_\\ ";
        if (input[i]== ']')
            cout<<"|___| ";
        if (input[i] == '}')
            cout<<"/_/   ";
        if (input[i] == '|')
            cout<<"|_| ";
        if (input[i] == '\\')
            cout<<"    \\_\\ ";
        if (input[i] == ';')
            cout<<"|/  ";
        if (input[i] == ':')
            cout<<"(_) ";
        if (input[i] == '\'')
            cout<<"    ";
        if (input[i] == '"')
            cout<<"      ";
        if (input[i] == '<')
            cout<<"  \\_\\ ";
        if (input[i] == ',')
            cout<<"|/  ";
        if (input[i] == '>')
            cout<<"/_/   ";
        if (input[i] == '/')
            cout<<"/_/     ";
        if (input[i] == '?')
            cout<<" (_)   ";
    }
    cout<<endl;
}

int main()
{
	//////Art/////////
        _getch();
        ascii_art();
        cout<<endl;
    //////////////////
    
	Login();
	HashMap user;
	HashP product;
	int y,x;
	
	L3:
	system("cls");
	gotoxy(20,3);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2   WELCOME  \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	gotoxy(20,5);
	printf("\xDB\xDB\xDB\xDB\xB2 1. SELECT USER ID AS KEY ");
	gotoxy(20,7);
	printf("\xDB\xDB\xDB\xDB\xB2 2. SELECT PRODUCT ID AS KEY");
	gotoxy(20,9);
	printf("\xDB\xDB\xDB\xDB\xB2 3. EXIT!");
	gotoxy(20,11);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	gotoxy(20,13);
	cin>>y;
	
	cout << "\n\n\n";  cout << "      ";
	showBlinkingLights();
	showLoadingScreen();
	cout << "\n\n\n";
	
	vector<string> row;
	string line;
	string word;
    int i,j;
	double k;
	fstream file;
	file.open("2019-Oct.csv",ios::in);
	if(file.is_open())
	{
		
		getline(file, line);
		
		while(getline(file, line))
		{
			row.clear();
 
			stringstream str(line);
 
			while(getline(str, word, ','))
			      row.push_back(word);
		
    
    	  istringstream(row[0])>>i;
    	  istringstream(row[1])>>j;
    	  istringstream(row[2])>>k;
		    
          Node * n=new Node(i,j,k,row[3],row[4],row[5],row[6]);
          
		  switch(y)
		  {
		  	case 1:
		      user.Insert(i,n);
		      break;
		    case 2:
			  product.Insert(j,n);
			  break;
			default:
				exit(1);
	      }
		}
	}
	
    if(y==1)
	{
				
	L1:	
	system("cls");
	gotoxy(20,3);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	gotoxy(20,5);
	printf("\xDB\xDB\xDB\xDB\xB2 1.	Who viewed Most Products   ");
	gotoxy(20,7);
	printf("\xDB\xDB\xDB\xDB\xB2 2. Who viewed the Most expensive product");
	gotoxy(20,9);
	printf("\xDB\xDB\xDB\xDB\xB2 3. Who viewed the least expensive product");
	gotoxy(20,11);
	printf("\xDB\xDB\xDB\xDB\xB2 4. Search User");
	gotoxy(20,13);
	printf("\xDB\xDB\xDB\xDB\xB2 5. Display User Information");
	gotoxy(20,15);
	printf("\xDB\xDB\xDB\xDB\xB2 6. Add Information");
	gotoxy(20,17);
	printf("\xDB\xDB\xDB\xDB\xB2 7. THE PRODUCTS VIEWED BY THIS CUSTOMER");
	gotoxy(20,19);
	printf("\xDB\xDB\xDB\xDB\xB2 8. PRODUCT TRANSACTION AMOUNT BY THE CUSTOMER");
	gotoxy(20,21);
	printf("\xDB\xDB\xDB\xDB\xB2 9. Search For Brand And Category Of The Product Bought By The Customer");
	gotoxy(20,23);
	printf("\xDB\xDB\xDB\xDB\xB2 10. EXIT!");
	gotoxy(20,25);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	gotoxy(20,27);
    
	cin >> x;
	
	switch(x)
	{
		case 1:
					user.displaybestcustomer();
					system("Pause");
					goto L1;
		case 2:
			
					user.displaymaxprice();
					system("Pause");
					goto L1;
		case 3:
			
					user.displayminprice();
					system("Pause");
					goto L1;
		
		case 4:
		
		            int uid;
		            cout<< "\t\t\t\t\tENTER USER ID TO SEARCH:\n";
					cout<<"\t\t\t";cin>>uid;
					user.Search(uid);
					system("Pause");
					goto L1;
		case 5:
		
		            cout<<"\t\t\t\t\tENTER USER ID TO SEARCH:\n";
					cin>>uid;
					user.searchuser(uid);
					system("Pause");
					goto L1;
		case 6:
			        user.InsertUid();
					system("Pause");
					goto L1;
				
		case 7:
			        user.searchforpro();
			        system("Pause");
					goto L1;
		case 8:
			        user.searchforpri();
			        system("Pause");
					goto L1;
		case 9:
			        user.searchforbrandandcat();
			        system("Pause");
					goto L1;
		
		case 10:
					system("Pause");
					goto L3;	
		default:
			cout<<"Invalid";
			system("Pause");
					goto L1;
	}
 }
 
 else if (y==2)
 {
 	L2:
	system("cls");
	gotoxy(20,3);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	gotoxy(20,5);
	printf("\xDB\xDB\xDB\xDB\xB2 1. Most Products Listed   ");
	gotoxy(20,7);
	printf("\xDB\xDB\xDB\xDB\xB2 2. Most Expensive Product");
	gotoxy(20,9);
	printf("\xDB\xDB\xDB\xDB\xB2 3. Least Expensive Product");
	gotoxy(20,11);
	printf("\xDB\xDB\xDB\xDB\xB2 4. Search Product");
	gotoxy(20,13);
	printf("\xDB\xDB\xDB\xDB\xB2 5. Display Product Information");
	gotoxy(20,15);
	printf("\xDB\xDB\xDB\xDB\xB2 6. Add Information");
	gotoxy(20,17);
	printf("\xDB\xDB\xDB\xDB\xB2 7. The Users Who Bought This Product");
	gotoxy(20,19);
	printf("\xDB\xDB\xDB\xDB\xB2 8. Revenue Generated By This Product");
	gotoxy(20,21);
	printf("\xDB\xDB\xDB\xDB\xB2 9. Search For Brand And Category Of The Product Bought");
	gotoxy(20,23);
	printf("\xDB\xDB\xDB\xDB\xB2 10. EXIT!");
	gotoxy(20,25);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	gotoxy(20,27);
    cout<<endl;
    
	cin >> x;
	switch(x)
	{
		case 1:
					product.displaybestproduct();
					system("Pause");
					goto L2;
		case 2:
			
					product.displaymaxprice();
					system("Pause");
					goto L2;
		case 3:
			
					product.displayminprice();
					system("Pause");
					goto L2;	
		case 4:
		
		            int pid;
		            cout<<"\t\t\t\tENTER PRODUCT ID"<<endl;
					cout<<"\t\t\t";cin>>pid;
					product.Search(pid);
					system("Pause");
					goto L2;
		case 5:
					
		            cout<<"\t\t\t\tENTER PRODUCT ID"<<endl;
		            cin>>pid;
					product.searchpro(pid);
					system("Pause");
					goto L2;
		
		case 6:
					cout<<"\t\t\t\tENTER DATA TO ADD"<<endl;
		            product.InsertPid();
		            system("Pause");
					goto L2;
		case 7:
			   		product.InsertPid();
					system("Pause");
					goto L2;
		
		case 8:
			   		product.searchforpri();
					system("Pause");
					goto L2;
		case 9:
			   		product.searchforbrandandcat();
					system("Pause");
					goto L2;
		
		case 10:
			        product.searchforuser();
		            system("Pause");
					goto L3;	
		default:
					cout<<"\t\t\t\tInvalid";
					system("Pause");
					goto L2;
	}
 }
 
 else
 {
     exit(1);
 }
 
}
