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
#include <sstream>


using namespace std;


class Target{
    int val;
    
public:
    //Assign target val either random number or injected number
    Target(){
    
        val = generateTarget();
        
    }
    
    Target(int targetValue){
        val = targetValue;
    }
    
    
    //Generate random number 0 - 100
    int generateTarget(){
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
        if(this->isSame(guess)){
            cout << "You win!" << endl;
            won = true;
        }
        
        else if(this->isHigher(guess)){
            cout << "Your guess is too high!" << endl;
            won = false;
        }
        
        else if (this->isLower(guess)){
            cout << "Your guess is too low!" << endl;
            won = false;
        }
        
        else{
            cout << "Error" << endl;
            won = false;
        }
        
        return won;
    }
    
    
    bool isSame(int guess){
        
        return (guess == val);
    }
    
    bool isHigher(int guess){
        return (guess > val);
    }
    
    bool isLower(int guess){
        return (guess < val);
    }
    
};


class Guessing_Game{
    const int max_turns = 5;
    const int statistics_number = 4; // Change this as different statistics are added
    const string rules_flag = "-r";
    const string statistics_flag = "-s";
    
public:
    
    enum Constants{
        TOTAL_PLAYED_LINE = 2,
        WIN_LINE = 3,
        LOSE_LINE = 4,
        AVG_TURNS_LINE = 5
    };
    
    void play(){
        int guess;
        int turn_number;
        bool keepPlaying = true;
        bool won = false;
        
        
        while(keepPlaying){
            
            //Retrieve guesses until all guesses are used and compare to target
            Target target;          
            for(turn_number = 1; turn_number <= max_turns; turn_number++){
                guess = retrieveGuess(turn_number);
                
                //Decide if that was a winning guess
                won = target.compareGuess(guess);
                if (won){
                    break;
                }
            }
            
            
        cout << "The number was ";
        target.display();
        cout << endl << "End Game" << endl;
        statisticsEdit(won, turn_number);
        keepPlaying = playAgain();
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
        int played = 0;
        int wins = 0;
        int losses = 0;
        double average = 0;
        ifstream statisticsfile;
        statisticsfile.open("stats.txt");
        if(statisticsfile.good()){
        }
        else{
            generateStatsFile(wins, losses, average, played);
            cout << "stats.txt generated" << endl;
        }
    }


 
    
    
private:
    int retrieveGuess(int turn_number){
        int guess;
        cout << "Enter your guess. This is turn number " << turn_number << endl;
        cin >> guess;
        return guess;
        
    }
    
    
    //Prompt user for playing again
    bool playAgain(){
        bool choiceFail = true;
        char selection;
        bool keepPlaying;
        while(choiceFail){
            cout << "Would you like to continue playing? (y/n)" << endl;
            cin >> selection;
            if(selection != 'Y' && selection != 'y' && selection != 'N' && selection != 'n'){
                cout << "Invalid selection" << endl;
            }
            
            else{
                choiceFail = false;
            }
        }
        
        if(selection == 'Y' || selection == 'y'){
            
            keepPlaying = true;
        }
        
        else if(selection == 'N' || selection == 'n'){
            keepPlaying = false;
        }
        return keepPlaying;
    }
    
    //Open and read the rules file
    void rulesRead(){
        string line;
        ifstream rulesfile;
        rulesfile.open("rules.txt");
        if(rulesfile.is_open()){
            while(rulesfile.good()){
                getline(rulesfile, line);
                cout << line << endl;
            }
            
            rulesfile.close();
        }
        
        else{
            
            cout << "Unable to open file" << endl;
        }

    }
    //Open and read the statistics file
    void statisticsRead(){
        string line;
        ifstream statisticsfile;
        statisticsfile.open("stats.txt");
        if(statisticsfile.is_open()){
            while(statisticsfile.good()){
                getline(statisticsfile, line);
                cout << line << endl;
            }
            
            statisticsfile.close();
        }
        
        else{
            
            cout << "Unable to find stats.txt. Generating new" << endl;
            statsCheck();
            
        }
    }
    
    void statisticsEdit(bool won, int turns_taken){   
        string line;
        fstream statisticsfile;
        int total_played_old;
        int total_played_new;
        int wins_stat_old;
        int wins_stat_new;
        int losses_stat_old;
        int losses_stat_new;
        string float_string;
        double avg_turns_old;
        double avg_turns_new;
        string trash;
        stringstream *ss;
        
        // correct for loop incrementation without a break;
        if(turns_taken == 6){
            turns_taken = 5;
        }
        
        
        statisticsfile.open("stats.txt");
        if(statisticsfile.is_open()){
            for(int statistics_index = 1; statistics_index <= (1 + statistics_number); statistics_index++){ //The 1 is to counter the first line that doesn't have statistics
                getline(statisticsfile, line);
                ss = new stringstream(line);
                switch(statistics_index){
                    case(TOTAL_PLAYED_LINE):
                        *ss >> trash >>trash >> trash >> total_played_old;
                        total_played_new = total_played_old + 1;  //Always increases
                    case(WIN_LINE):
                        *ss >> trash >> wins_stat_old;
                        wins_stat_new = (won ? wins_stat_old + 1 : wins_stat_old);  //Only increases if you win
                        break;
                        
                    case(LOSE_LINE):
                        *ss >> trash >> losses_stat_old;
                        losses_stat_new = (!won ? losses_stat_old + 1 : losses_stat_old); // Only increases if you lose
                        break;
                    case(AVG_TURNS_LINE):
                        *ss >> trash >> trash >> trash >> trash >> float_string;
                        avg_turns_old = atof(float_string.c_str()); 
                        avg_turns_new = (((avg_turns_old * (double) total_played_old) + (double)turns_taken) / (double) total_played_new);
                        break;
                    default:
                        break;
                }
            }
        }
        statisticsfile.close();
        generateStatsFile(wins_stat_new, losses_stat_new, avg_turns_new, total_played_new);
    }
    
    

    void generateStatsFile(int wins, int losses, double average, int played){
        ofstream statisticsfile;
        statisticsfile.open("stats.txt");
        statisticsfile << "Statistics:" <<endl << "Total Games Played: " << played << endl << "Wins: " << wins << endl << "Losses: " << losses << endl << "Average turns per game: " << average << endl;
        statisticsfile.close();
    }
    
        
};






int main(int argc, const char * argv[]){
    
    Guessing_Game game;
    

    //Decide what, if anything, is being displayed before the game begins
    switch (argc) {
          
        //Regular game run
        case 1:
            break;
        
        
        // Decide which flag was given
        case 2:
            game.flags(argv[1]);
            break;
        
        
        // Too many flags
        default:
            cout << "Too many arguements" << endl;
        
    }
    
    //Generate statistics file if it doens't exist
    game.statsCheck();
        
    
    game.play();    //Start the game
    return 0;
}




       
       
       
       
       