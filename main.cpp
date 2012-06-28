//
//  main.cpp
//  Guessing Game
//
//  Created by Christopher Harper on 6/26/12.
//  Copyright (c) 2012 Christopher Harper. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;


class Target{
    int val;
    
public:
    //Assign target val either random number or injected number
    Target()
    {
        val = generate_target();
        
    }
    
    Target(int targetValue)
    {
        val = targetValue;
    }
    
    
    //Generate random number 0 - 100
    int generate_target(){
        srand( (unsigned int)time(NULL) );
        int target = (rand() % 101);
        return target;
    }
    
    void display(){
        cout << val;
    }
    
    
    
    
    //Compare target val to guess
    bool compareGuess(int guess){
        bool won;
        if(this->isSame(guess))
        {
            cout << "You win!" << endl;
            won = true;
        }
        
        else if(this->isHigher(guess))
        {
            cout << "Your guess is too high!" << endl;
            won = false;
        }
        
        else if (this->isLower(guess))
        {
            cout << "Your guess is too low!" << endl;
            won = false;
        }
        
        else
        {
            cout << "Error" << endl;
            won = false;
        }
        
        return won;
    }
    
    
    bool isSame(int guess)
    {
        
        return (guess == val);
    }
    
    bool isHigher(int guess)
    {
        return (guess > val);
    }
    
    bool isLower(int guess)
    {
        return (guess < val);
    }
    
};


class Guessing_game{
    const int max_turns = 5;
    const string rules_flag = ("-r");
    const string statistics_flag = ("-s");
    
public:
    void play(){
        int guess;
        bool keepPlaying = true;
        bool won = false;
        
        
        while(keepPlaying){
            
            //Retrieve guesses until all guesses are used and compare to target
            Target target;          
            for(int turn_number = 1; turn_number <= max_turns; turn_number++)
            {
                guess = retrieve_guess(turn_number);
                
                //Decide if that was a winning guess
                won = target.compareGuess(guess);
                if (won){
                    break;
                }
            }
            
            
        cout << "The number was ";
        target.display();
        cout << endl << "End Game" << endl;
        keepPlaying = play_again();
        }
    }
    
    
    
    //Deal with commandline flags
    void flags(string flag){
        if (flag.compare(rules_flag) == 0){
            rulesRead();
        }
        
        else if (flag.compare(statistics_flag) == 0){
            statisticsRead();
        }
        else {
            cout << "Invalid flag" << endl;
        }
    }
    
    void statsCheck (){
        ifstream statisticsfile;
        statisticsfile.open("stats.txt");
        if(statisticsfile.good()){
        }
        else{
            generateStatsFile();
            cout << "stats.txt generated" << endl;
        }
    }

 
    
    
private:
    int retrieve_guess(int turn_number){
        int guess;
        cout << "Enter your guess. This is turn number " << turn_number << endl;
        cin >> guess;
        return guess;
        
    }
    
    
    //Prompt user for playing again
    bool play_again()
    {
        bool choiceFail = true;
        char selection;
        bool keepPlaying;
        while(choiceFail)
        {
            cout << "Would you like to continue playing? (y/n)" << endl;
            cin >> selection;
            if(selection != 'Y' && selection != 'y' && selection != 'N' && selection != 'n')
            {
                cout << "Invalid selection" << endl;
            }
            
            else
            {
                choiceFail = false;
            }
        }
        
        if(selection == 'Y' || selection == 'y')
        {
            keepPlaying = true;
        }
        
        else if(selection == 'N' || selection == 'n')
        {
            keepPlaying = false;
        }
        return keepPlaying;
    }
    
    //Open and read the rules file
    void rulesRead(){
        string line;
        ifstream rulesfile;
        rulesfile.open("rules.txt");
        if(rulesfile.is_open())
        {
            while(rulesfile.good())
            {
                getline(rulesfile, line);
                cout << line << endl;
            }
            
            rulesfile.close();
        }
        
        else
        {
            cout << "Unable to open file" << endl;
        }

    }
    //Open and read the statistics file
    void statisticsRead(){
        string line;
        ifstream statisticsfile;
        statisticsfile.open("stats.txt");
        if(statisticsfile.is_open())
        {
            while(statisticsfile.good())
            {
                getline(statisticsfile, line);
                cout << line << endl;
            }
            
            statisticsfile.close();
        }
        
        else
        {
            cout << "Unable to find stats.txt. Generating new" << endl;
            generateStatsFile();
            
        }
    }
    
    void generateStatsFile(){
        ofstream statisticsfile;
        statisticsfile.open("stats.txt");
        statisticsfile << "Statistics:" <<endl << "Wins: " << endl << "Losses: " << endl << "Average turns per game: " << endl;
        statisticsfile.close();
    }
    
        
};






int main(int argc, const char * argv[])
{
    Guessing_game game;
    

    //Decide what, if anything, is being displayed before the game begins
    switch (argc) {
          
        //Regular game run
        case 1: {
            break;
        }
        
        // Decide which flag was given
        case 2: {
            game.flags(argv[1]);
            break;
        }
        
        // Too many flags
        default:{
            cout << "Too many arguements" << endl;
        }
    }
    
    //Generate statistics file if it doens't exist
    game.statsCheck();
            
    
    
    game.play();    //Start the game
    return 0;
}




       
       
       
       
       