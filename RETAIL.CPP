/**THIS IS A PROGRAM OF RETAIL STORE MANAGEMENT*/


//..............................Header Files...............................

#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<process.h>
#include<fstream.h>
#include<dos.h>

//#define m 30
//#define n 20

class product
{
	int count;
	//char strItm[m][n];
	//int str[m];
	struct storeItems
	{
		int pno,itmCnt;
		char name[10];
		float price;
	}ob;

	//fstream fp;  //Fstream class object.

	/*.........................Member Functions..........................*/

	public:
		void write_product();          //Functions to write in file
		void show_product();           // Function to display one product
		void allProduct();             //Displays list whole inventory
		void display_all();
		void display_sp(int);
		void modify_product();
		void delete_product();
		void menu();
		void place_order();
		void intro();
		void admin_menu();
		void start();
		product();

}pr;    //End of class


//CONSTRUCTOR
product::product()
{
	//fp.open("SHOP.DAT",ios::out|ios::in|ios::binary);   //Global declaration of stream class object
	start();
}


/*
.
Function to write in file
.
*/
void product::write_product()
{
	char tmpNme[10];
	int pno, cnt;
	float price;
	ifstream ifp("SHOP.DAT",ios::binary);
	ob.pno++;
	pno = ob.pno;
	cout<<"\nProduct No. : "<<pno<<endl;
	cout<<"\n\nName of Product :";
	gets(tmpNme);
	cout<<"\n\nNo. of Items :";
	cin>>cnt;
	cout<<"\n\nPrice of each item :";
	cin>>price;
	ifp.seekg(0);
	while(ifp.read((char *)&ob,sizeof(ob)))
		if(strcmp(ob.name,tmpNme)==0)
		{
			ob.itmCnt+=pr.count;
			--ob.pno;
			cout<<"\n\n\tITEM ALREADY EXISTS!!!\n\n";
			cout<<"\n\tMORE "<<pr.count<<" "<<ob.name<<" ARE ACCEPTED"<<endl;
			ifp.close();
			sleep(4);
			return;
		}
	ifp.close();
	ofstream ofp("SHOP.DAT",ios::binary|ios::app);
	strcpy(ob.name,tmpNme);
	ob.itmCnt=cnt;
	ob.pno = pno;
	ob.price = price;
	//ofp.seekp(fp.tellg());
	ofp.write((char *)&ob,sizeof(ob));
	cout<<"\n\n\n\t\tITEM INSERTED SUCCESSFULY !!!";
	ofp.close();
	sleep(2);
}


/*
.
Function to show all records from file
.
*/
void product::display_all()
{
	clrscr();
	ifstream ifp("SHOP.DAT",ios::binary);
	cout<<"\n\n\n\t\tDISPLAY ALL RECORDS !!!\n\n";
	ifp.seekg(0);
	//cout<<"asdsd";
	while(ifp.read((char*)&ob,sizeof(ob)))
	{
		cout<<endl;
		pr.show_product();
		cout<<"\n\n====================================\n";
	}
	//cout<<"cvggch";
	ifp.close();
	getch();
}


/*
.
Display record of one product.
.
*/
void product::show_product()
{
	//ifstream fp("SHOP.DAT",ios::out|ios::in);
	cout<<"\nProduct No. : "<<ob.pno;
	cout<<"\nName of Product : "<<ob.name;
	//puts(ob.name);
	cout<<"\nPrice of Product : "<<ob.price;
}


/*
.
Function to read specific record from file
.
*/
void product::display_sp(int nm)
{
	int flag=0;
	ifstream ifp("SHOP.DAT",ios::binary);
	while(ifp.read((char*)&ob,sizeof(ob)))
	{
		if(ob.pno==nm)
		{
			clrscr();
			pr.show_product();
			flag=1;
		}
	}
	if(flag==0)
		cout<<"\n\n\tRECORD DOES NOT EXIST !!!";
	ifp.close();
	getch();
}


/*
.
Function to modify record of file
.
*/
void product::modify_product()
{
	clrscr();
	int num,found=0;
	ifstream ifp("SHOP.DAT",ios::binary);
	cout<<"\n\n\tTO MODIFY";
	cout<<"\n\n\tEnter The Product No. : ";
	cin>>num;
	while(found == 0 && ifp.read((char*)&ob,sizeof(ob)))
	{
		if(ob.pno==num)
		{
			ifp.close();
			pr.show_product();
			cout<<"\nEnter new details of the Product."<<endl;
			pr.write_product();
			ofstream ofp("SHOP.DAT",ios::binary);
			int pos = -1*sizeof(ob);
			ofp.seekp(pos,ios::cur);
			ofp.write((char*)&ob,sizeof(ob));
			ofp.close();
			cout<<"\n\n\t RECORD UPDATED SUCCESSFULLY !!!";
			found=1;
			//return;
		}
	}
	if(found==0)
	{
		ifp.close();
		cout<<"\n\n RECORD NOT FOUND !!!";
	}
	getch();
}


/*
.
Function to delete a record from file
.
*/
void product::delete_product()
{
	clrscr();
	int num;
	ifstream ifp("SHOP.DAT",ios::binary);
	cout<<"\n\n\n\tDELETE RECORD";
	cout<<"\n\nEnter Product No. of product to DELETE : ";
	cin>>num;
	ofstream ofp("Temp.dat",ios::binary);
	ifp.seekg(0);
	while(ifp.read((char*)&ob,sizeof(ob)))
		if(ob.pno!=num)
			ofp.write((char*)&ob,sizeof(ob));
	ofp.close();
	ifp.close();
	remove("SHOP.dat");
	rename("Temp.dat","SHOP.dat");
	cout<<"\n\n\tRECORD DELETED SUCCESSFULLY !!!";
	getch();
}


/*
.
Function to display price list of all products
.
*/
void product::menu()
{
	clrscr();
	ifstream ifp("SHOP.DAT",ios::binary);
	if(!ifp)
	{
		cout<<"STOCK IS EMPTY";
		cout<<"\n\n\n Program is closing ....";
		ifp.close();
		delay(2700);
		exit(0);
	}
	cout<<"\n\n\t\t\tPRODUCTS IN STOCK\n\n";
	cout<<"====================================================\n";
	cout<<"P.NO.\t\tNAME\t\tPRICE\n";
	cout<<"====================================================\n";
	while(ifp.read((char*)&ob,sizeof(ob)))
	{
		cout<<ob.pno<<"\t\t"<<ob.name<<"\t\t"<<ob.price<<endl;
	}
	ifp.close();
}


/*
.
Function to PLACE ORDER and GENERATE BILL of products
.
*/
void product::place_order()
{
	int order_arr[50],quan[50],x,c=0;
	float amt,/*damt,*/total=0;
	char ch='Y';
	menu();
	ifstream ifp("SHOP.DAT",ios::binary);
	cout<<"\n\n\n\n\t\t\t==================";
	cout<<"\n\t\t\t PLACE YOUR ORDER";
	cout<<"\n\t\t\t==================\n";
	do
	{
		cout<<"\n\nEnter The Product No. of the product : ";
		cin>>order_arr[c];
		cout<<"\nWant to shop more ?  ...(y/n)";
		cin>>ch;
	}while(ch=='y'|| ch=='Y');
	cout<<"\n\nThank You for Shopping";
	sleep(2);
	clrscr();
	cout<<"\n\n********************************INVOICE************************\n";
	cout<<"\nPr No.\tPr Name\tQuantity \tPrice \tAmount\n";
	for(x=0;x<c;x++)
	{
		//fp.seekg(order_arr[x]);
		while(ifp.read((char*)&ob,sizeof(ob)))
			if(ob.pno==order_arr[x])
			{
				amt=ob.price*quan[x];
				//damt=amt-(amt*ob.dis/100);
				cout<<"\n"<<order_arr[x]<<"\t"<<ob.name<<"\t"<<quan[x]<<"\t\t"
				<<ob.price<<"\t"<<amt;
				total+=amt;
			}
	}
	cout<<"\n\n\t\t\t\t\tTOTAL = "<<total;
	ifp.close();
	getch();
}


/**
   INTRODUCTION FUNCTIO
*/
void product::intro()
{
	clrscr();
	gotoxy(25,7);
	cout<<"********************************";
	gotoxy(29,9);
	cout<<" STORE MANAGEMENT SYSTEM";
	gotoxy(25,11);
	cout<<"********************************";
	gotoxy(10,14);
	cout<<"\n\n\t\t     DEVELOPED BY: AKASH GUPTA &\n\t\t\t\t   KALLAL BHAKTA";
	cout<<"\n\n\t\t     STUDENTS OF: ARMY PUBLIC SCHOOL BENGDUBI ";
	sleep(3);
}


/**
   ADMINSTRATOR MENU FUNCTION
*/
void product::admin_menu()
{
	clrscr();
	char ch2;
	cout<<"\n\n\n\n\t\t\t\tADMIN MENU";
	cout<<"\n\n\t1.CREATE PRODUCT";
	cout<<"\n\n\t2.DISPLAY ALL PRODUCTS";
	cout<<"\n\n\t3.QUERY ";
	cout<<"\n\n\t4.MODIFY PRODUCT";
	cout<<"\n\n\t5.DELETE PRODUCT";
	cout<<"\n\n\t6.VIEW PRODUCT MENU";
	cout<<"\n\n\t7.BACK TO MAIN MENU";
	cout<<"\n\n\tPlease Enter Your Choice (1-7) ";
	ch2=getche();
	switch(ch2)
	{
		case '1':
			clrscr();
			write_product();
			break;
		case '2':
			display_all();
			break;
		case '3':
			int num;
			clrscr();
			cout<<"\n\n\tEnter Product No. ";
			cin>>num;
			display_sp(num);
			break;
		case '4':
			modify_product();
			break;
		case '5':
			delete_product();
			break;
		case '6':
			menu();
			getch();
		case '7':
			break;
		default:
			admin_menu();
	}
}


/*
.
Start the working
.
*/
void product::start()
{
	char ch;
	intro();
	do
	{
		clrscr();
		gotoxy(20,8);
		cout<<"\t\t\t\t\t\t\t\t\t\t\t=============MAIN MENU============";
		cout<<"\n\n\n\n\t\t\t1. CUSTOMER"<<endl;
		cout<<"\n\t\t\t2. ADMINISTRATOR"<<endl;
		cout<<"\n\t\t\t3. EXIT"<<endl;
		cout<<"\n\n\t\t\tSelect Your Option (1-3) ";
		ch=getche();
		switch(ch)
		{
			case '1':
				clrscr();
				place_order();
				getch();
				break;
			case '2':
				admin_menu();
				break;
			case '3':
				exit(0);
		}
	}while(1);
}

/**
   THE MAIN FUNCTION OF PROGRAM
*/
int main()
{
	product pr;
	return 0;
}
//Main function ends

//===============================PROGRAM ENDS=================================