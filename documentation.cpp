#include<iostream>         //header files required for code
#include<conio.h>           //header file for getch() function
#include<fstream>           //header file required for file handling
#include<windows.h>         //header file is used for sleep and clear erminal screen function
using namespace std;        //for standard namespace

class bus                   // basic class named bus
{
    private:
        string b_no,from,to,via;        // strings for bus number,source,destination and route
        int b_seats;                    // integer for number of seats in bus
    public:
        void menu1();                   //function for admin/employee menu
        void menu2();                   //function for customer menu
        void new_bus();                 //function for adding new bus
        void single_bus_view();         //function for single bus details
        void all_bus_view();            //function for all bus details
        void del_bus();                 //function fr deleting a bus
        void ticket_booking();          //function for booking tickets
        void seat_details();            //function for searching seat details
        void del_seat();                //funcction to delete booking 
        void booking_record();           //booking histry
};

    void bus::menu1()
    {
        a:
        system("cls");                  //clears terminal window
        int choice;
        cout<<"\n\t\t\t ------- Welcome to Pune Shuttle Line -------";
        cout<<"\n\n\n\t\t\t\t\t  * Main Menu * ";
        cout<<"\n\n\n\t\t 1. Add Bus Details";
        cout<<"\n\n\t\t 2. Delete Bus Details";
        cout<<"\n\n\t\t 3. Exit";
        cout<<"\n\n\t\t\tEnter your Choice : ";
        cin>>choice;

        switch(choice)                  //switch case for selecting perticular function
        {
        case 1:
            new_bus();
            break;
        case 2:
            del_bus();
            break;
        case 3:
            break;
        default:
            cout<<"\n\n\n Invalid Choice...Try Again...";
            getch();
            goto a;
        }
    }

    void bus::menu2()
    {
        b:
        int choice;
        system("cls");
        cout<<"\n\t\t\t ------- Welcome to Pune Shuttle Line -------";
        cout<<"\n\n\n\t\t\t\t\t  * Main Menu * ";
        cout<<"\n\n\n\t\t 1.View all Bus details";
        cout<<"\n\t\t 2.Serach Bus";
        cout<<"\n\t\t 3.Booking Ticket Now";
        cout<<"\n\t\t 4.Seat Record";
        cout<<"\n\t\t 5.Delete Booking Record";
        cout<<"\n\t\t 6.Search Booking Record";
        cout<<"\n\t\t 7.Exit";
        cout<<"\n\n\n\t\t\t Enter your Choice : ";
        cin>>choice;
        
        switch(choice)                  //switch case for selecting perticular function
        {
            case 1:
                all_bus_view();
                break;
            case 2:
                single_bus_view();
                break;
            case 3: 
                ticket_booking();
                break;
            case 4:
                seat_details();
                break;
            case 5:
                del_seat();
                break;
            case 6:
                booking_record();
                break;
            case 7:
                cout<<"\n\n\t\t\t\t ---Thank you for visiting---";
                break;
            default:
                cout<<"\n\n Invalid Choice...Try Again...";
                getch();
                goto b;
        }      
    }

    void bus::new_bus()
    { 
        c:
        system("cls");
        fstream file;
        string t_no,t_from,t_to,t_via;              //strings to add new bus in file
        int t_seat,found=0;                         //integer to say number of seats in bus
        cout<<"\n\t\t\t ------- Welcome to Pune Shuttle Line -------";
        cout<<"\n\n\n\t\t Bus No : ";
        cin>> b_no;
        cout<<"\n\t\t Total Seats : ";
        cin>>b_seats;
        cout<<"\n\t\t From : ";
        cin>>from;
        cout<<"\n\t\t To : ";
        cin>>to;
        cout<<"\n\t\t Via : ";
        cin>>via;

        file.open("bus.txt",ios::in);               //opening file 'bus.txt' using file handling
        if(!file)
        {
            file.open("bus.txt",ios::app);                             //creating file if does not exist
            file<<b_no<<" "<< b_seats<<" "<<from<<" "<<to<<" "<<via<<"\n";      //writing in text file
            file.close();                                                       //closing text file
            cout<<"\n\n Bus Added Successfully...";
        }
        else
        {
            file>>t_no>>t_seat>>t_from>>t_to>>t_via;                            //writing details in text file
            while(!file.eof())                                                  //reading text file untill it ends
            {
                if(b_no==t_no)
                {
                    found++;
                }
                file>>t_no>>t_seat>>t_from>>t_to>>t_via;
            }
            file.close();                                                       //closes file
            if(found==0)
            {
                file.open("bus.txt",ios::app);                                  //opens file in append mode
                file<<b_no<<" "<< b_seats<<" "<<from<<" "<<to<<" "<<via<<"\n";  //writes data in file
                file.close();                                                   //closes file
                cout<<"\n\n Bus Added Successfully...";
            }
            else
            {
                cout<<"\n\n Duplicate Record Found... ";
                getch();
                goto c;                                       //to move at start of function i.e. executing function again
            }
        }
        cout<<"\n\n Press any key to return Main Menu";
        getch();
        menu1();                                               // to execute admin menu again
    }

    void bus::single_bus_view()
    {
        d:
        system("cls");                                  //clears terminal window
        string t_from,t_to;
        fstream file;
        int found=0;
        cout<<"\n\t\t\t ------- Welcome to Pune Shuttle Line -------";
        file.open("bus.txt",ios::in);                   // file opening in read mode
        if(!file)                                       //if file not found, show error
        {
            cout<<"\n\n File opening error...";
        }
        else
        {
            cout<<"\n\n\n\t\t\t From : ";               //ask source
            cin>>t_from;
            cout<<"\n\t\t\t To : ";                     //ask destination
            cin>>t_to;
            file>>b_no>>b_seats>>from>>to>>via;         //extract data from bus.txt
            while(!file.eof())                          //read file until it ends
            {
                if((t_from==from && t_to==to) || (t_from==to && t_to==from))        //compare source and destination in bus.txt
                {
                    cout<<"\n\n Bus no : "<<b_no<<"\t\t Total seats : "<<b_seats<<"\t\tRoute : "<<t_from<<"\t to\t"<<t_to<<"\t\t via : "<<via;
                    found++;
                }
                file>>b_no>>b_seats>>from>>to>>via;
            }
            file.close();                                                           //close file
            if(found==0)
            {
                cout<<"\n\n Sorry!!! No Bus found on the Route... ";                //print if no bus found
                getch();
                goto d;                                                             //go to start of function
            }
        }
        cout<<"\n\n Press enter to return Main Menu...";
        getch();
        menu2();                                                                    //at end, move to customer menu
    }

    void bus::all_bus_view()
    {
        system("cls");                                                          //clears terminal window
        fstream file;
        cout<<"\n\t\t\t ------- Welcome to Pune Shuttle Line -------";
        file.open("bus.txt",ios::in);                                           //open fie in read mode
        if(!file)
        {
            cout<<"\n\n File opening error...";                                 //if 'bus.txt' not found, show file opening error
        }
        else
        {
            file>>b_no>>b_seats>>from>>to>>via;                                 //extract this data from text file
            while(!file.eof())                                                  //read text file upto its end
            {
                cout<<"\n\n Bus no : "<<b_no<<"\t\t Total seats : "<<b_seats<<"\t\tRoute : "<<from<<"\t to\t"<<to<<"\t\t via : "<<via<<"\n\t\t\t\t\t\t\t\t"<<to<<"\t to\t"<<from<<"\t\t via : "<<via<<"\n";
                file>>b_no>>b_seats>>from>>to>>via;             
            }                                                                   //print all buses details which are in datasheet
            file.close();                                                       //close datasheet
        }
        cout<<"\n\n\t Press Enter to return Main Mainu...";
        getch();                                                                //'press any key to continue' command function
        menu2();                                                                //move to customer menu
    }

    void bus::del_bus()
    {
        system("cls");                                                          //clears terminal window
        fstream file,file1;
        string t_no;
        int found=0,n;
        cout<<"\n\t\t\t ------- Welcome to Pune Shuttle Line -------";
        system("cls");
        file.open("bus.txt",ios::in);                                           //open 'bus.txt' in read mode
        if(!file)
        {
            cout<<"\n\n File opening error...";                                 //if file not found, show error
        }

        else
        {
            cout<<"\n\n Bus No : ";
            cin>>t_no;
            file1.open("bus-temp.txt",ios::app|ios::out);                       //create a new text file
            file>>b_no>>b_seats>>from>>to>>via;                                 //extract this data frim text file
            while(!file.eof())                                                  //execute until end of file
            {
                if(t_no==b_no)
                {
                    cout<<"\n\n\n Bus record deleted succesfully";              //if bus no. entered and bus no. from file matches, print this
                    cout<<"\n\n Press enter to return main menu";
                    found++;
                }
                else
                {
                    file1<<b_no<<" "<<b_seats<<" "<<from<<" "<<to<<" "<<via<<"\n";
                }
                file>>b_no>>b_seats>>from>>to>>via;                             //data is written in temperory text file without the data with deletin bus
            }
            file.close();                                                       //close bus.txt
            file1.close();                                                      //close bus-temp.txt
            remove("bus.txt");                                                  //delete bus.txt
            rename("bus-temp.txt","bus.txt");                                   //rename bus-temp.txt to bus.txt
            if(found==0)
            {
                cout<<"\n\n Please enter valid Bus Number...";
            }
        }
        getch();                                                                //'enter any key to continue' function
        menu1();                                                                //move to admin menu
    }

    void bus::seat_details()
    {
        system("cls");                                                      //clears terminal sreen
        fstream file2,file;
        string t_no,s_no,s_b_no;
        int count=0,found=0;
        cout<<"\n\t\t\t ------- Welcome to Pune Shuttle Line -------";
        file.open("bus.txt",ios::in);                                       //opening bus.txt in read mode
        file2.open("seat.txt",ios::in);                                     //opening seat.txt in read mode
        if(!file2 || !file)
        {
            cout<<"\n\n\t\t File opening Error!!!";
            cout<<"\n\n \t\t\t Press enter to Main Menu...";
        }
        else
        {
            cout<<"\n\n\n\t\t Bus no. : ";
            cin>>t_no;
            file2>>s_b_no>>s_no;
            while(!file2.eof())                                             //execute untill end of file 
            {
                if(t_no == s_b_no)
                {
                    count++;
                }
                file2>>s_b_no>>s_no;
            }
            file2.close();                                                  //close seat.txt
            file>>b_no>>b_seats>>from>>to>>via;

            while(!file.eof())                                              //execute untill end of file
            {
                if(t_no == b_no)
                {
                    system("cls");
                    cout<<"\n\t\t\t ------- Welcome to Pune Shuttle Line -------";
                    cout<<"\n\n\n\t\t Total seats : " << b_seats;
                    cout<<"\n\n\t\t Reserved seats :" << count;
                    cout<<"\n\n\t\t Empty Seats :" << b_seats-count;
                    cout<<"\n\n\n\t Press Enter to return Main Menu...";
                    found++;
                }
                file>>b_no>>b_seats>>from>>to>>via;
            }
            
            file.close();                                                   //closes bus.txt
            if(found==0)
            {
                cout<<"\n\nNo Bus Found!!! ";
            } 
        }
        getch();
        menu2();                                                            //execute customer menu again

    }

    void bus::ticket_booking()
    {
        p:
        system("cls");                                                      //clears terminal screen
        fstream file2,file;
        string t_no,s_b_no,cust_name1,cust_name2,aadhar_no,ch;
        int found=0,seats=36,count=0,s_s_no,s_no,i=0,x;
        cout<<"\n\t\t\t ------- Welcome to Pune Shuttle Line -------";
        file.open("bus.txt",ios::in);                                       //opening bus.txt in read mode
        if(!file)
        {
            cout<<"\n\n File opening error...";
        }
        else
        {
            cout<<"\n\n\n\t\t Bus no : ";
            cin>>t_no;
            file.close();                                                   //close bus.txt
            file2.open("seat.txt",ios::in);                                 //open seat.txt in read mode
            if(file2)
            {
                file2>>s_b_no>>s_s_no;
                while(!file2.eof())                                         //execute untill end of file
                {
                    if(t_no == s_b_no)
                    {
                        count++;
                    }
                    file2>>s_b_no>>s_s_no;
                }
                file2.close();                                              //close seat.txt file
            }
            file.open("bus.txt",ios::in);                                   //opening bus.txt in read mode
            file>>b_no>>b_seats>>from>>to>>via;
            while(!file.eof())                                              //execute untll end of file
            {
                if(t_no ==b_no)
                {
                    seats = b_seats;
                    found++;
                }
                file>>b_no>>b_seats>>from>>to>>via;
            }
            file.close();                                                   //close bus.txt
            if(seats-count==0)
            {
                cout<<"\n\n\n\t\t\t All seats are reserved...";
            }
            else if(found == 1)
            {
                do
                {
                    a:
                    cout<<"\n\n\t\t Seat no : ";
                    cin>>s_no;
                    if(s_no > seats || s_no < 1)
                    {
                        cout<<"\n\n Plese Enter valid Seat Number...";
                        goto a;
                    }
                    file2.open("seat.txt",ios::in);                         //open seat.txt in read mode
                    if(!file2)
                    {
                        file2.open("seat.txt",ios::app);           //open seat.txt in append mode
                        file2<<t_no<<" "<<s_no<<"\n";
                        file2.close();                             //close seat.txt file
                    }
                    else
                    {
                        file2>>s_b_no>>s_s_no;
                        while(!file2.eof())                        //execute untill end of file
                        {
                            if(t_no == s_b_no && s_no == s_s_no)
                            {
                                cout<<"\n\n\t\t\t Seat is already reserved...";
                                goto a;
                            }
                            file2>>s_b_no>>s_s_no;
                        }
                        file2.close();                              // close seat.txt
                        file2.open("seat.txt",ios::app);            //open seat.txt in append mode   
                        file2<<t_no<<" "<<s_no<<"\n";
                        file2.close();                              // close seat.txt file
                    }
                    cout<<"\n\n\t\t\t Your seat has been booked...";
                    cout<<"\n\n\t\t Customer First name : ";
                    cin>>cust_name1;
                    cout<<"\n\n\t\t Customer Last name : ";
                    cin>>cust_name2;
                    cout<<"\n\n\t\t Aadhar no (last 4 digit) : ";
                    
                    for(int i=0;i<4;i++)
                    {
                        ch = getch();
                        aadhar_no+=ch;
                        cout<<aadhar_no[i];
                        Sleep(750);                                 
                    }

                    file.open("customer.txt",ios::app);                                        //open file in append mode
                    file<<cust_name1<<" "<<cust_name2<<" "<<t_no<<" "<<s_no<<" "<<aadhar_no<<"\n";
                    file.close();                                                              //close customer.txt file
                    cout<<"\n\n\t\t\t Your seat has been booked";
                    cout<<"\n\n\t\t Your booking details are in progress, please wait";
                    cout<<"\n\n\n\t\t\t\t\t Loading...";
                    Sleep(1000);
                    system("cls");                                                             //clears terminal screen
                    cout<<"\n\t\t   ------- Welcome to Pune Shuttle Line -------";
                    cout<<"\n\n\n\t\t   ********************************************************";
                    cout<<"\n\n\t\t\t ------------- Booking Details -------------";
                    cout<<"\n\n\t\t   ********************************************************";
                    cout<<"\n\n\t\t   Name    : "<<cust_name1<<" "<<cust_name2;
                    cout<<"\n\t\t   Bus no  : "<<t_no;
                    cout<<"\n\t\t   Seat id : "<<aadhar_no<<"_"<<s_no;
                    cout<<"\n\n\t\t   ********************************************************";
                    cout<<"\n\n\t\t   ********************************************************";
                    cout<<"\n\n\n\t\t # Do you want to book book another seat \n\n\t\t\t Yes=1 \t no=2 \n\n\t\t Enter your choice : ";
                    cin>>x;
                }while(x == 1);
                system("cls");                      
                menu2();                                                                        //execute customer menu
                
            }
            else
            {
                cout<<"\n\n Please Enter valid Bus Number...";
            }
            getch();
            goto p;
        }
    }

    void bus::del_seat()
    {
        system("cls");                                                          //clears terminal
        cout<<"\n\t\t\t ------- Welcome to Pune Shuttle Line -------";
        cout<<"\n\n\n\t\t\t\t\t Loading...";
        Sleep(750);
        f:
        system("cls");                                                          //clears terminal
        fstream file2,file1,file;
        string t_no,s_t_no,s_b_no,s_s_no,cust_name1,cust_name2,aadhar_no,aadharcard_no,ch;
        int found=0;
        cout<<"\n\t\t\t ------- Welcome to Pune Shuttle Line -------";
        cout<<"\n\n\n\t\t Aadhar no : ";
        for(int i=0;i<4;i++)
        {
            ch = getch();
            aadharcard_no += ch;
            cout<<aadharcard_no[i];
            Sleep(750);
        }
        cout<<"\n\n\t\t Bus No : ";
        cin>>t_no;
        cout<<"\n\n\t\t Seat no : ";
        cin>>s_t_no;

        file.open("customer.txt",ios::in);                                  //opens file in read mode
        {
        if(!file)
        {
            cout<<"\n\n File opening error...";
        }

        else
        {
            file1.open("customer-temp.txt",ios::app);                          //opens file in append mode
            file>>cust_name1>>cust_name2>>s_b_no>>s_s_no>>aadhar_no;
            while(!file.eof())                                             //read file until it ends
            {
                if(aadharcard_no==aadhar_no && t_no==s_b_no &&s_t_no==s_s_no)
                {
                    found++;
                }
                else
                {
                    file1<<cust_name1<<" "<<cust_name2<<" "<<s_b_no<<" "<<s_s_no<<" "<<aadhar_no<<"\n";
                }
                file>>cust_name1>>cust_name2>>s_b_no>>s_s_no>>aadhar_no;
            }
            file.close();                   //closes file
            file1.close();                  //closes file
            remove("customer.txt");         //deletes customer.txt
            rename("customer-temp.txt","customer.txt");     //renames customer-temp.txt to customer.txt
            if(found==0)
            {
                cout<<"\n\n Invalid input...plese try again...";
                getch();
                goto f;
            }
        }
        }

        file2.open("seat.txt",ios::in);                 //opens file in read mode
        {
        if(!file2)
        {
            cout<<"\n\n File opening error...";
        }

        else
        {
            file1.open("seat2.txt",ios::app);           //opens file in append mode
            file2>>s_b_no>>s_s_no;
            while(!file2.eof())
            {
                if(t_no==s_b_no && s_t_no==s_s_no)
                {
                    cout<<"\n\n\n Booking details deleted succesfully...";
                    found++;
                }
                else
                {
                    file1<<s_b_no<<" "<<s_s_no<<"\n";
                }
                file2>>s_b_no>>s_s_no;
            }
            file2.close();                          //closes file
            file1.close();                          //closes file
            remove("seat.txt");                     //deletes set.txt
            rename("seat2.txt","seat.txt");         //renames seat-temp.txt as seat.txt
            if(found==1)
            {
                getch();
                goto f;
            }
        }
        }
        cout<<"\n\n Press enter to return main menu...";
        getch();
        system("cls");                              //clears terminal screen
        cout<<"\n\t\t\t ------- Welcome to Pune Shuttle Line -------";
        cout<<"\n\n\n\t\t\t\t\t Loading...";
        Sleep(750);
        menu2();                                    //executes customer menu
    }

    void bus::booking_record()
        {
            system("cls");                                                                  //clears terminal screen
            cout<<"\n\t\t\t ------- Welcome to Pune Shuttle Line -------";
            cout<<"\n\n\n\t\t\t\t\t Loading...";
            Sleep(750);
            e:
            system("cls");                                                                  //clears terminal screen
            fstream file;
            string cust_name1,cust_name2,s_b_no,s_s_no,aadhar_no,aadharcard_no,ch;
            int found=0;
            cout<<"\n\t\t\t ------- Welcome to Pune Shuttle Line -------";

            file.open("customer.txt",ios::in);
            if(!file)
            {
                cout<<"\n\n File opening error...";
            }
            else
            {
                cout<<"\n\n\n\t\t Aadhar no (last 4 digit) : ";

                for(int i=0;i<4;i++)
                {
                    ch = getch();
                    aadharcard_no += ch;
                    cout<<aadharcard_no[i];
                    Sleep(750);
                }

                file>>cust_name1>>cust_name2>>s_b_no>>s_s_no>>aadhar_no;
                while(!file.eof())                                              //executes untill end of file
                {
                    if(aadharcard_no==aadhar_no)
                    {
                        system("cls");                                          //clears terminal screen
                        cout<<"\n\t\t\t ------- Welcome to Pune Shuttle Line -------";
                        cout<<"\n\n\n\t\t\t\t\t Loading...";
                        Sleep(750);
                        system("cls");                                          //clears terminal screen
                        cout<<"\n\t\t\t\t --------- Welcome to Pune Shuttle Line ---------";
                        cout<<"\n\n\n\t\t   ********************************************************";
                        cout<<"\n\n\t\t\t ------------- Booking Details -------------";
                        cout<<"\n\n\t\t   ********************************************************";
                        cout<<"\n\n\t\t   Name    : "<<cust_name1<<" "<<cust_name2;
                        cout<<"\n\t\t   Bus no  : "<<s_b_no;
                        cout<<"\n\t\t   Seat id : "<<aadhar_no<<"_"<<s_s_no;
                        cout<<"\n\n\t\t   ********************************************************";
                        cout<<"\n\n\t\t   ********************************************************";
                        found++;
                    }
                    file>>cust_name1>>cust_name2>>s_b_no>>s_s_no>>aadhar_no;
                }
                file.close();                                //closes customer.txt
                if(found==0)
                {
                    cout<<"\n\n\t\t Invalid aadhar no...try again...";
                    getch();
                    goto e;
                }
            }
            cout<<"\n\n\n\n\t\t Press Enter for main menu...";
            getch();
            system("cls");                                  //clears terminal screen
            cout<<"\n\t\t\t ------- Welcome to PMPML Bus Reservation system -------";
            cout<<"\n\n\n\t\t\t\t\t Loading...";
            Sleep(750);
            menu2();                                        //executes customer menu
        }

int main()
{
    bus b;
    int n;
    string pass,user_id,ch;
    p:
    system("cls");                                                      //clears terminal screen
    cout<<"\n\t\t\t ------- Welcome to Pune Shuttle Line -------";
    cout<<"\n\n\n\t\t\t\t Employee = 1 \t\t costomer = 2";
    cout<<"\n\n\n\t\t\tEnter your Choice : ";
    cin>>n;
    if (n==1)
    {
        q:
        system("cls");                                                  //clears terminal screen
        cout<<"\n\t\t\t ------- Welcome to Pune Shuttle Line -------";
        cout<<"\n\n\n\t\t\t\t\t >>> Sign in <<<";
        cout<<"\n\n\t\t User Id : ";
        cin>>user_id;
        cout<<"\n\n\t\t Password : ";
        for(int i=1;i<10;i++)
        {
            ch = getch();
            pass += ch;
            cout<<"*";
        }

        if((user_id=="aditya16" && pass=="aditya285") || (user_id=="atharv17" && pass=="atharv317"))
        {
            system("cls");
            cout<<"\n\t\t\t ------- Welcome to Pune Shuttle Line -------";
            cout<<"\n\n\n\t\t\t\t\t Loading...";
            Sleep(750);
            b.menu1();                                  //executes admin menu
        }

        else
        {
            cout<<"\n Invalid User Id or password";
            getch();
            goto q;
        }
    }

    else
    {
        system("cls");
        cout<<"\n\t\t\t ------- Welcome to Pune Shuttle Line -------";
        cout<<"\n\n\n\t\t\t\t\t Loading...";
        Sleep(750);
        b.menu2();                                      //executes customer menu
    }
    return 0;
}