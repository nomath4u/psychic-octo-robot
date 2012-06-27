//
//  main.cpp
//  Guessing Game
//
//  Created by Christopher Harper on 6/26/12.
//  Copyright (c) 2012 Christopher Harper. All rights reserved.
//

#include <iostream>
#include <cstdlib>

void initialization();
int generate_target();
int retrieve_guess(int);
bool play_again();


using namespace std;

class Target{
    int val;
    
public:
    Target()
    {
        val = generate_target();
    
    }
    
    Target(int targetValue)
    {
        val = targetValue;
    }
    
    int generate_target(){
        srand( (unsigned int)time(NULL) );
        int target = (rand() % 101);
        return target;
    }
    
    void display(){
        cout << val;
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



int main(int argc, const char * argv[])
{

    // insert code here...
    
    //initialization
    
    //Target target;             Target initialization was here
    
    const int max_turns = 5;
    int turn_number;
    int guess;
    bool keepPlaying = true;
    
    while(keepPlaying){
    
        //Retrieve guesses until all guesses are used and compare to target
        Target target;           //Target initialization moved inside of keep playing loop to get a new target every playthrough does old target get destroyed?
        for(turn_number = 1; turn_number <= max_turns; turn_number++)
        {
            guess = retrieve_guess(turn_number);
            if(target.isSame(guess))
            {
                cout << "You win!" << endl;
                break;
            }
        
            else if(target.isHigher(guess))
            {
                cout << "Your guess is too high!" << endl;
            }
        
            else if (target.isLower(guess))
            {
                cout << "Your guess is too low!" << endl;
            }
            
            else
            {
                cout << "Error" << endl;
            }
        }
    cout << "The number was ";
    target.display();
    cout << endl << "End Game" << endl;
    keepPlaying = play_again();
    }
    return 0;
}




int retrieve_guess(int turn_number){
    int guess;
    cout << "Enter your guess. This is turn number " << turn_number<< endl;
    cin >> guess;
    return guess;
    
}

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
       
       
       
       
       
       