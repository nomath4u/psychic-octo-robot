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
void play_again(bool*);


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
        int target = rand() % 101;
        return target;
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
    Target target;
    const int max_turns = 5;
    int turn_number;
    int guess;
    bool keepPlaying = true;
    
    while(keepPlaying){
    
        //Retrieve guesses until all guesses are used and compare to target
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
    
    cout << "End Game" << endl;
    play_again(&keepPlaying);
    }
    return 0;
}




int retrieve_guess(int turn_number){
    int guess;
    cout << "Enter your guess. This is turn number " << turn_number<< endl;
    cin >> guess;
    return guess;
    
}

void play_again(bool* keepPlaying)
{
    bool choiceFail = true;
    char selection;
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
        *keepPlaying = true;
    }
    
    else if(selection == 'N' || selection == 'n')
    {
        *keepPlaying = false;
    }
}
       
       
       
       
       
       