#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <fstream>
using namespace std;

//These are our global variables (arrays)

string questions[90];
string answers[90];
string selectedAnswers[10];
string selectedQuestions[10];
void getQuestions();
void chooseRandomQuestions(string questarr[90], string ansarr[90]);
int ask_question(string selectedQuest[10], string selectedAns[10]);

/*
function: getQuestions is used to retreive questions and answwers from the TestBank text file.
We have an array for questions and another for answers to read the questions and answers.
If the file is open and while it is not at the end of the file, it will get the questions and answers from the TestBank.
While it is at the end of file -close file
*/

void getQuestions() {
    cout << "hi";
fstream myFile;
myFile.open("TestBank.txt");
if (myFile.is_open()) {
int i = 0;
while (!myFile.eof()) {
getline(myFile, questions[i]);
getline(myFile, answers[i]);
//
i++;
}
}

myFile.close();

}

/*
Function: chooseRandomQuestions is used to get and store 10 random questions and their corresponding answers.
It contains our questions array that holds our 90 questions and our answers array that holds out 90 answers. 
We made two more arrays to contain the selected 10 randomized questions and selected answers.
 While our question count is below 10 we will choose a selected question and answer and store them in quest and ans.
Used Bool statement to check if the question is a repeat; if single quest matches any of selectedQuestions array it will go back to while and choose another question.
If not a repeat, the quest in input into the selectedQuestions array for later; same with its corresponding answer.
This loops until there are 10 random and non repeating questions and answers store in the selectedQuestions array and seletedAnswers array.
*/


void chooseRandomQuestions(string questarr[90], string ansarr[90]) {
srand(time(0));
int questionCount = 0;
//array 3(will hold randomized question  
//array 4(will hold corresponding answers)
 
while (questionCount <= 10) {
int random = rand() % 90;
        //quest and ans store one question and answer at a time
string quest = questarr[random];
string ans = ansarr[random];
bool isRepeat = 0; //false

  //CHECK EVERY QUESTION IN THE SELECTED QUESTIONS AND SEE IF THE NEW QUESTION IS IN THERE - CHECK FOR REPEATING QUESTION
for (int j = 0; j < questionCount; j++) {
        //If a question is a repeat it will enter this if statement 
if (selectedQuestions[j] == quest) {
//YES, QUESTION IS A REPEAT
isRepeat = 1;
//BREAK OUT OF ‘FOR’ LOOP - LEAVES FOR LOOP
break;
}
}


//If there is no repeat enter this if statement
if (!isRepeat) {
selectedQuestions[questionCount] = quest;
selectedAnswers[questionCount] = ans;
questionCount++;
}

}

}

/*
Function: ask_question is used to write in the question and the user’s answer into a text file.
While the loop is less than 10 it will output the question and input their answer. 
If there answer is correct numCorrect will increment to keep track.
If user’s answer is wrong, display correct answer.
Return the correct number at the end
*/

int ask_question(string selectedQuest[10], string selectedAns[10]){
//functions with array inside for questions

int numCorrect = 0;
for (int i = 0; i < 10; i++) {
string answer;
cout << selectedQuest[i];
cin >> answer;
if (selectedAnswers[i] == answer) {
numCorrect++;
}

else {
cout << "The answer is " << selectedAnswers[i];
}

//make file for this - test results

/*a_file << selectedQuestions[i] << endl;
if (a_file << answer == 0){
cout << "False" << endl;
}
else{
cout << "True" << endl;
cout << "Score :" << numCorrect << endl;*/
}

return numCorrect;

}


/*---------------------------------------*/ //the code above this break needs inspected

/*
Open quiz result test file to write into
User is told to enter name and ID so they input their name and ID
It should print into Quiz Results text file 
User must press S to start the quiz and timer.
Do: the 3 functions 
While: time is below 600 seconds(10 mins) if false terminate
Quiz will say Quiz completed when done or terminated 
*/
int main() {

string userName;
int userID;
char start;
double startTime;

    ofstream a_file("QuizResults.txt");
//create text file to hold final results

cout << "Enter your name: ";
cin >> userName;
a_file << userName << endl;
//collect username and store to file (QuizResults.txt)

cout << "Enter student ID: ";
cin >> userID;
a_file << userID << endl;
//collect userID and store to file (QuizResults.txt)

cout << "Enter an S to start the quiz" << endl;
cin >> start;
//quiz start marker

if (start == 'S') {
   startTime=0;
}
getQuestions();
chooseRandomQuestions(questions, answers);
ask_question(selectedQuestions, selectedAnswers);
//
while (startTime <= 600);


cout << "Quiz completed." << endl;


return 0;
}