
#include <iostream> // for cin and cout
#include <string>
#include <fstream>
#include<vector>
#include<algorithm>

using namespace std;

const string rule_msg_1 = "The selected password must be at least eight characters long.";
const string rule_msg_2 = "The selected password must have at least one uppercase letter.";
const string rule_msg_3 = "The selected password must have at least one lowercase letter.";
const string rule_msg_4 = "The selected password must have at least one digit.";
const string rule_msg_5 = "The selected password must have at least one of special characters: [@,!,#,^,&,*,$]";
const string rule_msg_6 = "The selected password has been leaked.";
const string rule_msg_7 = "The selected password cannot contain a dictionary word.";


/****
 * Called within binary search of leaked passwords file and compares leaked passwords to password, getting rid of just special characters and comparing
// ****/
void comparegmailword(string & allegedPassword){
    string stringtemp="";
    for (int i=0; i<allegedPassword.size();i++){
        if (allegedPassword[i]!='@'&& allegedPassword[i]!='!'&& allegedPassword[i]!='#'&&allegedPassword[i]!='^'&&allegedPassword[i]!='&'&&allegedPassword[i]!='*'&& allegedPassword[i]!='$'){
            stringtemp+=tolower(allegedPassword[i]);

        }

    }
    allegedPassword=stringtemp;


}
/****
 * Called within binary search of english word file and compares english words to passwords, getting rid of special characters and numbers and comparing
// ****/

void compareenglishword(string & allegedPassword){
    string stringtemp="";
    for (int i=0; i<allegedPassword.size();i++){
        if (allegedPassword[i]!='@'&& allegedPassword[i]!='!'&& allegedPassword[i]!='#'&&allegedPassword[i]!='^'&&allegedPassword[i]!='&'&&allegedPassword[i]!='*'&& allegedPassword[i]!='$'){
            if (isdigit(allegedPassword[i])==false) {
                stringtemp += tolower(allegedPassword[i]);
            }

        }

    }
    allegedPassword=stringtemp;


}
/****
 * Does the binary search of the english word files
// ****/

int binarySearchenlgishword(vector<string> passwordList, string password){
    int low = 0;
    int high =passwordList.size()-1;
    compareenglishword(password);
    while (low<=high) {

        int mid = (low + high) / 2;
        passwordList[mid];
        compareenglishword(passwordList[mid]);
        if (password > passwordList[mid]) {
            low = mid + 1;
        } else if (password < passwordList[mid]) {
            high = mid - 1;
        } else {
            return mid;
        }
    }
    return -1;
}

/****
 * Does the binary search of the leaked passwords
// ****/
int binarySearchgmailword(vector<string> passwordList, string password){
    int low = 0;
    int high =passwordList.size()-1;
    comparegmailword(password);
    while (low<=high) {

        int mid = (low + high) / 2;
        passwordList[mid];
        comparegmailword(passwordList[mid]);
        if (password > passwordList[mid]) {
            low = mid + 1;
        } else if (password < passwordList[mid]) {
            high = mid - 1;
        } else {
            return mid;
        }
    }
    return -1;
}
/****
 * Checks to see if password contains a dictionary word
// ****/

bool notEnglishword(string password, int &acceptcondition){
    ifstream passwordList;
    passwordList.open("words_5.txt");
    vector<string> previousPassword;
    string potentialPassword;
    while (!passwordList.eof()){
        passwordList >> potentialPassword;
        previousPassword.push_back(potentialPassword);
    }
    if(binarySearchenlgishword(previousPassword,password)!=-1){
        cout << rule_msg_7 << endl;
        cout << "Password rejected!";
    }
    else{
        acceptcondition=2;
    }

}


/****
 * Checks to see if password has been leaked
// ****/
bool passLeaked(string password, int &acceptcondition){
    ifstream passwordList;
    passwordList.open("alleged-gmail-passwords.txt");
    vector<string> previousPassword;
    string potentialPassword;



    while (!passwordList.eof()){
        passwordList >> potentialPassword;
        previousPassword.push_back(potentialPassword);
    }
    if(binarySearchgmailword(previousPassword,password)!=-1){
        cout << rule_msg_6 << endl;
        cout << "Password rejected!";
    }
    else{
        acceptcondition=1;
    }



}



/****
 * Runs the main part of the program and sees if rules 1-5 are true and if they are checks rules 6-7 and if they are true outputs password accepted and if any rules aren't then passwords rejected
// ****/
int run(string leaked_password_file, string english_word_file){
    cout << "Enter password: ";
    string password;
    cin >> password;
//    vector<string> word, alleged;
//    fileRead(word,english_word_file);
//    fileRead(alleged,leaked_password_file);
    int passwordUpper=0;
    int passwordLower=0;
    int passwordDigit=0;
    int passwordSpecialChar=0;
    int passwordLength=0;
    int passwordRejected=0;
    int passwordAccepted=0;
    if (password.length()>=8) {
        passwordLength = 1;
    }
    for (int i = 0; i < password.size(); i++) {
        if (isupper(password.at(i))) {
            passwordUpper = 1;
        }

        if (islower((password.at(i)))) {
            passwordLower = 1;
        }

        if (isdigit(password.at(i))) {
            passwordDigit = 1;
        }

        if (password.at(i)=='@'|| password.at(i)=='!'||password.at(i)=='#'||password.at(i)=='^'||password.at(i)=='&'||password.at(i)=='*'|| password.at(i)=='$') {
            passwordSpecialChar = 1;
        }

    }
    //Checks if rules 1-5 are false and return error message
    if (passwordLength==0){ // Rule 1
        passwordRejected=1;
        cout << rule_msg_1<<endl;
    }
    if (passwordUpper==0){ // Rule 2
        passwordRejected=1;
        cout << rule_msg_2<<endl;
    }
    if (passwordLower==0){ // Rule 3
        passwordRejected=1;
        cout << rule_msg_3<<endl;
    }
    if (passwordDigit==0){ // Rule 4
        passwordRejected=1;
        cout << rule_msg_4<<endl;
    }
    if (passwordSpecialChar==0){ // Rule 5
        passwordRejected=1;
        cout << rule_msg_5<<endl;
    }
    if (passwordRejected==1){
        cout << "Password rejected!";
    }



    //If rules 1-5 are true then checks if password is leaked
    if (passwordRejected==0){
        passLeaked(password, passwordAccepted);
        notEnglishword(password, passwordAccepted);
    }
    if (passwordAccepted==2){
        cout << "Password accepted!" << endl;
    }

}





int main() {
    /** Change the address of the files appropriatly based on your local machine.
     * This main function will be replaced during testing. Do not add any line of code to the main function
     **/
    string leaked_password_file = "alleged-gmail-passwords.txt"; //change this based on the location of the file on your machine
    string english_word_file = "words_5.txt"; //change this based on the location of the file on your machine
    run(leaked_password_file, english_word_file);
    return 0;
}
