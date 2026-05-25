/*************************************************************************************************************/
// Project: prjCampixSystem.cpp 
// Purpose: This program allows the campus community to check for available space.
// Author:  K. Moorning
// Date:    September 17, 2025
// Version: 1
/*************************************************************************************************************/

#include <ctime>
#pragma warning(disable : 4996)


#include "Lot.h";
#include "Lab.h";
#include "Camper.h";
#include "Hall.h";
#include "Windows.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

//Campers
//string email = "skur@gmail.com";
//string password = "test";

/*
1. inheritance
2. pointers
*/

//FUNCTION PROTOTYPES
void welcome();
void login(vector<Camper>& campers, int& liu);
void loadData(vector<Camper>& campers, StudyHall halls[], int hi, Lot lots[], int li, Lab labs[]);
void loadCampers(vector<Camper>& campers);
void loadHalls(StudyHall halls[], int hi);
void loadLots(Lot lots[], int li);
void loadLabs(Lab labs[], int li);
void displayMenu(vector<Camper>& campers, StudyHall halls[], Lot lots[], Lab labs[]);
void viewHalls(StudyHall halls[]);
void viewLots(Lot lots[]);
void viewLabs(Lab labs[]);
void reserveSpot(vector<Camper>& campers, StudyHall halls[], Lot lots[], Lab labs[]);
void changeColors(int color);
string getSystemDate();
void encrypt(string entPwd, vector <Camper> campers);
string decrypt(string entPwd);



/******************MAIN() BEGIN******************************/

int main()
{
    int liu = 0;    //logged in user
    vector<Camper> campers;
    const int hi = 8;
    StudyHall halls[hi];
    const int li = 12;
    Lot lots[li];
    Lab labs[li];


    welcome();
    loadData(campers, halls, hi, lots, li, labs);
    // login(campers, liu);
    displayMenu(campers, halls, lots, labs);

    return 0;
}

/******************MAIN() END*****************************/

/******************MWELCOME() BEGIN******************************/

void welcome()
{
    /* This function displays the welcome banner in purple.*/
    changeColors(13);
    cout << "**********************************************************************" << endl;
    cout << "**********************WELCOME TO CAMPIX SYSTEM************************" << endl;
    cout << "**********************************************************************" << endl;
    changeColors(15);

}
/******************MWELCOME() END******************************/


void loadData(vector<Camper>& campers, StudyHall halls[], int hi, Lot lots[], int li, Lab labs[])
{
    loadCampers(campers);
    loadHalls(halls, hi);
    loadLots(lots, li);
    loadLabs(labs, li);
}

void login(vector<Camper>& campers, int& liu)
{  //Login
    int numAttempts = 0;
    bool loginOK = false;
    string entUser = "";
    string entPwd = "";
    string decPwd = "";

    cout << campers.size() << endl;
    do {
        //Loop through the Campers vector
        cout << "Enter Your Username: ";
        cin >> entUser;
        cout << "Enter Your Password: ";
        cin >> entPwd;



        for (int i = 0; i < campers.size(); i++)
        {
            decPwd = decrypt(campers.at(i).password);

            if ((entUser == campers.at(i).email) && (entPwd == decPwd))
            {
                changeColors(14);
                cout << "Successful Login!";
                cout << "Welcome, " << campers.at(i).fname << endl;
                changeColors(15);
                loginOK = true;
                liu = i;
            }

        } //end of for loop
        if (!loginOK)
        {
            changeColors(4);
            cout << "Unsuccessful Login, Try Again!" << endl;
            changeColors(15);
            numAttempts++;
        }
    } while ((numAttempts < 3) && (!loginOK));  // end of do loop

    if (!loginOK)
    {
        changeColors(4);
        cout << "Too Many Attempts, Program Terminated!" << endl;
        changeColors(15);
        exit(0);
    }
}
void loadCampers(vector<Camper>& campers)
{
    //Get Campers
    string c, f, l, e, p, p2;
    ifstream campersFile;
    campersFile.open("Campers.dat");
    Camper camper;  //one record
    int ci = 0;

    cout << "Reading from the Campers file" << endl;
    if (!campersFile)
    {
        changeColors(4);
        cout << "Unable to Load Campers Data, Program Terminated!" << endl;
        changeColors(15);
        exit(0);
    }

    while (!campersFile.eof())
    {
        getline(campersFile, c, ',');
        getline(campersFile, f, ',');
        getline(campersFile, l, ',');
        getline(campersFile, e, ',');
        getline(campersFile, p, ',');
        getline(campersFile, p2, '\n');

        //declare the first camper in the array
        camper.campusID = c;
        camper.fname = f;
        camper.lname = l;
        camper.email = e;
        camper.phone = p;
        camper.password = p2;

        campers.push_back(camper); //add to the vector
        ci++;

    }

    campersFile.close();


}
void loadHalls(StudyHall halls[], int hi)
{
    //Get Study Halls
    string b, b2, r, s, a;
    ifstream studyHallsFile;
    studyHallsFile.open("Halls.dat");
    hi = 0;

    cout << "Reading from the Study Halls file" << endl;
    if (!studyHallsFile)
    {
        changeColors(4);
        cout << "Unable to Load Study Hall Data, Program Terminated!" << endl;
        changeColors(15);
        exit(0);
    }

    while (!studyHallsFile.eof())
    {
        getline(studyHallsFile, b, ',');
        getline(studyHallsFile, b2, ',');
        getline(studyHallsFile, r, ',');
        getline(studyHallsFile, s, ',');
        getline(studyHallsFile, a, '\n');

        halls[hi] = { b,b2, stoi(r), stoi(s), stoi(a) };
        hi++;
    }
    studyHallsFile.close();
}
void loadLots(Lot lots[], int li)
{
    //Get Lots
    string l;
    string s;
    string a;
    ifstream lotFile;
    lotFile.open("Lots.dat");
    li = 0;


    cout << "Reading from the Lots file" << endl;
    if (!lotFile)
    {
        cout << "Unable to Load Lot Data, Program Terminated!" << endl;
        exit(0);
    }

    while (!lotFile.eof())
    {
        getline(lotFile, l, ',');
        getline(lotFile, s, ',');
        getline(lotFile, a, '\n');


        lots[li] = { l.at(0), stoi(s), stoi(a) };
        li++;
    }

    lotFile.close();
}
void loadLabs(Lab labs[], int li)
{
    //  labs code   

    string b, b2, r, s, a;
    ifstream labsFile;
    labsFile.open("Labs.dat");
    li = 0;

    cout << "Reading from the Labs file" << endl;

    if (!labsFile)
    {
        changeColors(4);
        cout << "Unable to Load Lab Data, Program Terminated!" << endl;
        changeColors(15);
        exit(0);
    }


    while (!labsFile.eof()) {
        getline(labsFile, b, ',');
        getline(labsFile, b2, ',');
        getline(labsFile, r, ',');
        getline(labsFile, s, ',');
        getline(labsFile, a, '\n');



        labs[li] = { b,b2, stoi(r), stoi(s), stoi(a) };

        li++;

    }

    labsFile.close();

}
void displayMenu(vector<Camper>& campers, StudyHall halls[], Lot lots[], Lab labs[])
{
    cout << "\n\n";
    changeColors(13);
    cout << "**********************************************************************" << endl;
    cout << "**********************CAMPIX SYSTEM: DISPLAY MENU************************" << endl;
    cout << "**********************************************************************" << endl;
    changeColors(15);
    int choice = -1;


    //Validate the user's choice
    do {
        changeColors(14);
        cout << "1. View Study Halls" << endl;
        cout << "2. View Computer Labs" << endl;
        cout << "3. View Parking Lots" << endl;
        cout << "4. Reserve Space" << endl;
        cout << "5. Exit Program" << endl;
        changeColors(15);


        cout << "Enter Choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            viewHalls(halls);
            break;
        }
        case 2:
        {
            viewLabs(labs);
            break;
        }
        case 3:
        {
            viewLots(lots);
            break;
        }
        case 4:
        {
            reserveSpot(campers, halls, lots, labs);
            break;
        }
        case 5:
        {
            cout << "Thank you for using Campix, program terminated!";
            exit(0);
        }
        default:
        {
            changeColors(4);
            cout << "Error, Invalid Choice!" << endl;
            changeColors(15);
        }

        }//end of the switch
    } while (choice != 5);


}
void viewHalls(StudyHall halls[])
{
    changeColors(13);
    cout << "\n\n";
    cout << "**********************************************************************" << endl;
    cout << "******************CAMPIX SYSTEM: DISPLAY STUDY HALLS*****************" << endl;
    cout << "**********************************************************************" << endl;
    changeColors(15);

    //loop through the array to show the study halls.

    for (int i = 0; i < sizeof(halls); i++)
    {
        cout << (i + 1) << "." << "\t" << halls[i].building << "\t" << halls[i].roomnum << "\t" << halls[i].availseats << endl;

    }

}
void viewLabs(Lab labs[])
{
    changeColors(13);
    cout << "\n\n";
    cout << "**********************************************************************" << endl;
    cout << "***********************CAMPIX SYSTEM: DISPLAY LABS*******************" << endl;
    cout << "**********************************************************************" << endl;
    changeColors(15);

    //loop through the array to show the labs

    for (int i = 0; i < sizeof(labs); i++)
    {
        cout << (i + 1) << "." << "\t" << labs[i].building << "\t" << labs[i].roomnum << "\t" << labs[i].availseats << endl;

    }

}
void viewLots(Lot lots[])
{
    changeColors(13);
    cout << "\n\n";
    cout << "**********************************************************************" << endl;
    cout << "***********************CAMPIX SYSTEM: DISPLAY LOTS********************" << endl;
    cout << "**********************************************************************" << endl;
    changeColors(15);

    //loop through the array to show the lots

    for (int i = 0; i < sizeof(lots); i++)
    {
        cout << (i + 1) << "." << "\t" << lots[i].lotcode << "\t" << lots[i].availspots << endl;

    }

}

void reserveSpot(vector<Camper>& campers, StudyHall halls[], Lot lots[], Lab labs[]) {
    changeColors(13);
    cout << "\n\n";
    cout << "**********************************************************************" << endl;
    cout << "***********************CAMPIX SYSTEM: RESERVE SPACE*******************" << endl;
    cout << "**********************************************************************" << endl;
    changeColors(15);
    int space = -1, choice = -1;

    //show the availability
    cout << " Select the space type!" << endl;
    cout << "1. Study Hall" << endl;
    cout << "2. Computer Lab" << endl;
    cout << "3. Parking Lot" << endl;
    cout << "Enter space type: ";
    cin >> space;
    if (space < 1 || space > 3)
    {
        changeColors(4);
        cout << "Invalid space type!" << endl;
        changeColors(15);
    }

    switch (space)
    {
    case 1:
    {
        viewHalls(halls);
        cout << "Enter room #: ";
        cin >> choice;
        //subtract one from availseats
        halls[choice - 1].availseats--;
        changeColors(14);
        cout << "You have reserved a seat in " << halls[choice - 1].bldginitials << " " << halls[choice - 1].roomnum << endl;
        changeColors(15);
        break;
    }
    case 2:
    {
        viewLabs(labs);
        cout << "Enter room #: ";
        cin >> choice;
        //subtract one from availseats
        labs[choice - 1].availseats--;
        changeColors(14);
        cout << "You have reserved a seat in " << labs[choice - 1].bldginitials << " " << labs[choice - 1].roomnum << endl;
        changeColors(15);
        break;
    }
    case 3:
    {
        viewLots(lots);
        cout << "Enter lot#: ";
        cin >> choice;
        //subtract one from availseats
        lots[choice - 1].availspots--;
        changeColors(14);
        cout << "You have reserved a parking spot in Lot " << lots[choice - 1].lotcode << endl;
        changeColors(15);

        break;
    } //end of switch


    }

  
    /**************************************WRITE LOGS FUNCTION**********************************
    void writeLogs(vector<Log>& logs)
    {
        //write log file
        ofstream outfile;
        outfile.open("logs.dat", ios::app);

        for (int i = 0; i < logs.size(); i++)
        {
            // write log data into the file.
            outfile << logs.at(i).accountnum << "," << logs.at(i).transactionTime << "," << logs.at(i).transactionType << endl;

        }
        // close the opened file.
        outfile.close();
        changeColors(11);//cyan
        cout << "Logs File Updated!\n";
        changeColors(15);//white

    }*/
}
/**************************************CHANGE COLORS FUNCTION***********************************/
void changeColors(int color)
{
    static const HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, color);
    /*********************************COLOR CODES***************************

    black,          //  0 text color - multiply by 16, for background colors
    dark_blue,      //  1
    dark_green,     //  2
    dark_cyan,      //  3
    dark_red,       //  4
    dark_magenta,   //  5
    dark_yellow,    //  6
    light_gray,     //  7
    dark_gray,      //  8
    light_blue,     //  9
    light_green,    // 10
    light_cyan,     // 11
    light_red,      // 12
    light_magenta,  // 13
    light_yellow,   // 14
    white           // 15
*/
/****************************END OF COLOR CODES***************************/
}
/***************************************GET SYSTEM DATE FUNCTION***********************************/
string getSystemDate()
{
    time_t now = time(0); //system time
    char* dt = ctime(&now);
    return dt;
}




void encrypt(string entPwd, vector <Camper> campers)
{
    vector <string> passwords;
    for (int i = 0; i < sizeof(campers); i++)
    {

        //*Encrypt / Decrypt variables
        //* sepwd (string encrypted pwd) 
        //* sdpwd (string decrypted pwd) 
        //* vepwd (vector encrypted pwd)
        char temp;
        string sepwd = "";
        vector <char> vepwd;

        //Get Password
        for (int i = 0; i < entPwd.length(); i++)
        {
            temp = entPwd.at(i);
            temp += 1;
            vepwd.push_back(temp);
            sepwd = sepwd + temp;
            passwords.push_back(sepwd);
            //store encrypted password in stage file


        }
        // writePasswords(passwords);

    } //end of for loop
}
string decrypt(string entPwd)
{
    char temp;
    string sdpwd = "";
    vector <char> vdpwd;



    //Decrypt

    for (int i = 0; i < entPwd.length(); i++) {


        temp = entPwd.at(i);
        temp -= 1;
        vdpwd.push_back(temp);
        sdpwd = sdpwd + temp;

    }
    //use sdpwd compare to entPwd for authentication
    return sdpwd;
}


