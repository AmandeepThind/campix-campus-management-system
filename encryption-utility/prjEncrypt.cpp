// prjEncrypt.cpp : This program encrypts passwords.
//

#include "Camper.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

void loadCampers(vector<Camper>& campers);
void encrypt(vector <Camper> campers);
void writePasswords(vector<string> passwords);



int main()
{
    cout << "**********************************************************************" << endl;
    cout << "***************************ENCRYPT SYSTEM*****************************" << endl;
    cout << "**********************************************************************\n" << endl;


    vector<Camper> campers;

    loadCampers(campers);
    encrypt(campers);

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
        cout << "Unable to Load Campers Data, Program Terminated!" << endl;
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
void encrypt(vector <Camper> campers)
{
    vector <string> passwords;
    string entPwd = "";

    cout << "Encrypting passwords..." << endl;
        char temp;
        string sepwd = "";
        vector <char> vepwd;

        //Loop through vector
        for (int c = 0; c < campers.size(); c++)
        {
            sepwd = "";
            entPwd = campers.at(c).password;
            //Get Password
            for (int i = 0; i < entPwd.length(); i++)
            {
                temp = entPwd.at(i);
                temp += 1;
                vepwd.push_back(temp);
                sepwd = sepwd + temp;

            } // end of password loop
            //store encrypted password in stage file
            passwords.push_back(sepwd);
        }//end of campers loop

    writePasswords(passwords);
}

/**************************************WRITE PASSWORD FUNCTION**********************************/
void writePasswords(vector<string> passwords)
{
    //write log file
    ofstream outfile;
    outfile.open("passwords.dat");

    for (int i = 0; i < passwords.size(); i++)
    {
        // write log data into the file.
        outfile << passwords.at(i) << endl;

    }
    // close the opened file.
    outfile.close();
 
    cout << "Encrypted Passwords file Written!\n";


}
