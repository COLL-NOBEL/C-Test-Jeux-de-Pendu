#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>


// Function to display underscore "_", for every correctly guessed letter
void afficherMotPartiel(const std::string& mot, const std::vector<bool>& lettresDevinees) {
    for (size_t i = 0; i < mot.size(); ++i) {
        if (lettresDevinees[i]) {
            std::cout << mot[i] << " ";
        }else
        {
            std::cout << "_ ";
        }
        
    }
    std::cout << std::endl;
}

// This function checks whether a certain letter is in the list of already entered letters.
bool lettreDejaDevinee(char lettre, const std:: vector<char>& lettresJouees) {
    return std::find(lettresJouees.begin(), lettresJouees.end(), lettre) != lettresJouees.end();

}

int main() {

    std::cout << "Hi there player. In this game, you guess letters in a word." << std::endl;
    std::cout << "\nWill you play against a frient or against me? " << std::endl;

    const int JustSomeInt = 1;
    char OPPONENT;

    while (JustSomeInt == 1)
    {
        std::cout << "\nEnter \"1\" for FRIEND and \"2\" for COMPUTER or \"0\" to STOP playing : ";
        std::cin >> OPPONENT;

        if (OPPONENT == '1')
        {
            std::string playerWord;
            std::string playerWordDescriptions;

            std::cout << "\nIt's your turn to input a word for your friend to guess : ";
            std::cin >> playerWord;

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clearing input buffer

            std::cout << "\nInput a very short description or summary to help your friend : ";
            std::getline(std::cin, playerWordDescriptions);

            std::cout << "This is the guessing turn" << std::endl;
            std::cout <<"\nHINT : \"" << playerWordDescriptions << "\"" << std::endl;

            std::string motADeviner = playerWord;
            std::vector<bool> lettresDevinees(motADeviner.size(), false);   // Vector that tells wether letter has been guessed or not.
            std::vector<char> lettresJouees;                      // Vector of played letters.

            int tentativesRestantes = 8;
            bool motTrouve = false;
            int SCORE = 10;

            std::cout << "Bienvenus dans le jeu du Pendu !" << std::endl;

            while (tentativesRestantes > 0 && !motTrouve)
            {
                std::cout << "\nMot a deviner : ";

                afficherMotPartiel(motADeviner, lettresDevinees); // Initially, false is the only value in the array "lettresDevinees"

                std::cout << "Tentatives restante : " << tentativesRestantes << std::endl;
                std::cout << "Lettres deJa jouees : ";

                for (char l : lettresJouees)
                { // Display all letters that have been played already
                    std::cout << l << "-";
                }

                std::cout << std::endl;
                std::cout << "Proposez une lettre: ";
                char lettre;
                std::cin >> lettre; // Prompt user to enter input and save the input in the variable "lettre"

                if (!std::isalpha(lettre))
                { // Send error message to user if they don't enter alphabet
                    std::cout << "Erreur : veuillez entrer une lettre valide." << std::endl;
                    continue;
                }

                lettre = std::tolower(lettre);

                if (lettreDejaDevinee(lettre, lettresJouees))
                { // Prompt user to enrter a new letters each time
                    std::cout << "vous avez deja propose cette lettre." << std::endl;
                    continue;
                }

                lettresJouees.push_back(lettre); // Add entered letters to the list of already entered letters

                bool lettreTrouvee = false;

                for (size_t i = 0; i < motADeviner.size(); ++i)
                { // Iterate throught the word to guess

                    if (motADeviner[i] == lettre)
                    {                              // If guessed letter is in real word, add it to guessed letter.
                        lettresDevinees[i] = true; // Putting "true" as value in the position of letter in the array "lettreDevinees"
                        lettreTrouvee = true;
                    }
                }

                if (!lettreTrouvee)
                { // Letter not found error message
                    std::cout << "Mauvaise lettre." << std::endl;

                    for (size_t j = 0; j < motADeviner.size(); j++) // Help player with one letter "for" loop.
                    {
                        if (lettresDevinees[j])
                        {
                            continue;
                        }
                        else
                        {
                            lettresDevinees[j] = true;
                            break;
                        }
                    }

                    std::cout << "You have been assisted with 1 letters" << std::endl;

                    --tentativesRestantes; // Number of trials reduces when player inputs wrong letter
                    --SCORE;
                }

                motTrouve = std::all_of(lettresDevinees.begin(), lettresDevinees.end(), [](bool b){ return b; });
            }

            if (motTrouve)
            {
                std::cout << "\nFelicitation ! vous avez devine le mot : " << motADeviner << std::endl;
                std::cout << "Your score is : " << SCORE << " Points." << std::endl;
            }
            else
            {
                std::cout << "\nDommage vous avez perdu. le mot etai : " << motADeviner << std::endl;
            }


        }else if (OPPONENT == '2')
        {

            std::ifstream fichier("mots.txt");
            if (!fichier)
            {
                std::cerr << "Erreur: impossible de lire le fichier des mots." << std::endl;

                return 1;
            }
            std::vector<std::string> mots;
            std::string mot;

            // Adding words to our words vector
            while (fichier >> mot)
            {
                mots.push_back(mot);
            }

            if (mots.empty())
            {
                std::cerr << "Erreur: le fichier des mots est vide." << std::endl;

                return 1;
            }

            // Initializing Long and short words list
            std::vector<std::string> longWords;
            std::vector<std::string> shortWords;

            for (const auto &word : mots)
            {
                if (word.length() > 8)
                {
                    longWords.push_back(word); // Separating long words from list of words
                }
                else
                {
                    shortWords.push_back(word); // Separating short words from list of words
                }
            }

            const int unknownInt = 1; // Just some interger to keep the loop below running until user wants to break it.
            char DIFFICULTY;

            while (unknownInt == 1)
            {
                std::cout << "\nEnter \"1\" for EASY or \"2\" for HARD or \"0\" to stop playing : ";
                std::cin >> DIFFICULTY;

                /* CODE FOR EASY DIFFICULTY  */

                if (DIFFICULTY == '1')
                {

                    // Initailzing some important variables
                    std::srand(std::time(0));                          // Initializing random function with current time
                    std::string motADeviner = shortWords[std::rand() % shortWords.size()]; // Choosing random word to be guessed, from list of words
                    std::vector<bool> lettresDevinees(motADeviner.size(), false);  // Vector that tells wether letter has been guessed or not.
                    std::vector<char> lettresJouees;                           // Vector of played letters.

                    int tentativesRestantes = 8;
                    bool motTrouve = false;
                    int SCORE = 10;

                    std::cout << "Bienvenus dans le jeu du Pendu !" << std::endl;

                    while (tentativesRestantes > 0 && !motTrouve)
                    {
                        std::cout << "\nMot a deviner : ";

                        afficherMotPartiel(motADeviner, lettresDevinees); // Initially, false is the only value in the array "lettresDevinees"

                        std::cout << "Tentatives restante : " << tentativesRestantes << std::endl;
                        std::cout << "Lettres deJa jouees : ";

                        for (char l : lettresJouees)
                        { // Display all letters that have been played already
                            std::cout << l << "-";
                        }

                        std::cout << std::endl;
                        std::cout << "Proposez une lettre: ";
                        char lettre;
                        std::cin >> lettre; // Prompt user to enter input and save the input in the variable "lettre"

                        if (!std::isalpha(lettre))
                        { // Send error message to user if they don't enter alphabet
                            std::cout << "Erreur : veuillez entrer une lettre valide." << std::endl;
                            continue;
                        }

                        lettre = std::tolower(lettre);

                        if (lettreDejaDevinee(lettre, lettresJouees))
                        { // Prompt user to enrter a new letters each time
                            std::cout << "vous avez deja propose cette lettre." << std::endl;
                            continue;
                        }

                        lettresJouees.push_back(lettre); // Add entered letters to the list of already entered letters

                        bool lettreTrouvee = false;

                        for (size_t i = 0; i < motADeviner.size(); ++i)
                        { // Iterate throught the word to guess

                            if (motADeviner[i] == lettre)
                            {                              // If guessed letter is in real word, add it to guessed letter.
                                lettresDevinees[i] = true; // Putting "true" as value in the position of letter in the array "lettreDevinees"
                                lettreTrouvee = true;
                            }
                        }

                        if (!lettreTrouvee)
                        { // Letter not found error message
                            std::cout << "Mauvaise lettre." << std::endl;

                            for (size_t j = 0; j < motADeviner.size(); j++) // Help player with one letter "for" loop.
                            {
                                if (lettresDevinees[j])
                                {
                                    continue;
                                }
                                else
                                {
                                    lettresDevinees[j] = true;
                                    break;
                                }
                            }

                            std::cout << "You have been assisted with 1 letters" << std::endl;

                            --tentativesRestantes; // Number of trials reduces when player inputs wrong letter
                            --SCORE;
                        }

                        motTrouve = std::all_of(lettresDevinees.begin(), lettresDevinees.end(), [](bool b){ return b; });
                    }

                    if (motTrouve)
                    {
                        std::cout << "\nFelicitation ! vous avez devine le mot : " << motADeviner << std::endl;
                        std::cout << "Your score is : " << SCORE << " Points." << std::endl;
                    }
                    else
                    {
                        std::cout << "\nDommage vous avez perdu. le mot etai : " << motADeviner << std::endl;
                    }

                    /* CODE FOR HARD DIFFICULTY  */
                }
                else if (DIFFICULTY == '2')
                {

                    // Initailzing some important variables
                    std::srand(std::time(0));                            // Initializing random function with current time
                    std::string motADeviner = longWords[std::rand() % longWords.size()]; // Choosing random word to be guessed, from list of words
                    std::vector<bool> lettresDevinees(motADeviner.size(), false);  // Vector that tells wether letter has been guessed or not.
                    std::vector<char> lettresJouees;                    // Vector of played letters.

                    int tentativesRestantes = 6;
                    bool motTrouve = false;
                    int SCORE = 10;

                    std::cout << "Bienvenus dans le jeu du Pendu !" << std::endl;

                    while (tentativesRestantes > 0 && !motTrouve)
                    {
                        std::cout << "\nMot a deviner : ";

                        afficherMotPartiel(motADeviner, lettresDevinees); // Initially, false is the only value in the array "lettresDevinees"

                        std::cout << "Tentatives restante : " << tentativesRestantes << std::endl;
                        std::cout << "Lettres deJa jouees : ";

                        for (char l : lettresJouees)
                        { // Display all letters that have been played already
                            std::cout << l << "-";
                        }

                        std::cout << std::endl;
                        std::cout << "Proposez une lettre: ";
                        char lettre;
                        std::cin >> lettre; // Prompt user to enter input and save the input in the variable "lettre"

                        if (!std::isalpha(lettre))
                        { // Send error message to user if they don't enter alphabet
                            std::cout << "Erreur : veuillez entrer une lettre valide." << std::endl;
                            continue;
                        }

                        lettre = std::tolower(lettre);

                        if (lettreDejaDevinee(lettre, lettresJouees))
                        { // Prompt user to enrter a new letters each time
                            std::cout << "vous avez deja propose cette lettre." << std::endl;
                            continue;
                        }

                        lettresJouees.push_back(lettre); // Add entered letters to the list of already entered letters

                        bool lettreTrouvee = false;

                        for (size_t i = 0; i < motADeviner.size(); ++i)
                        { // Iterate throught the word to guess

                            if (motADeviner[i] == lettre)
                            {                              // If guessed letter is in real word, add it to guessed letter.
                                lettresDevinees[i] = true; // Putting "true" as value in the position of letter in the array "lettreDevinees"
                                lettreTrouvee = true;
                            }
                        }

                        if (!lettreTrouvee)
                        { // Letter not found error message
                            std::cout << "Mauvaise lettre." << std::endl;

                            --tentativesRestantes; // Number of trials reduces when player inputs wrong letter
                            --SCORE;
                        }

                        motTrouve = std::all_of(lettresDevinees.begin(), lettresDevinees.end(), [](bool b){ return b; });
                    }

                    if (motTrouve)
                    {
                        std::cout << "\nFelicitation ! vous avez devine le mot : " << motADeviner << std::endl;
                        std::cout << "Your score is : " << SCORE << " Points." << std::endl;
                    }
                    else
                    {
                        std::cout << "\nDommage vous avez perdu. le mot etai : " << motADeviner << std::endl;
                    }
                }
                else if (DIFFICULTY == '0')
                {
                    std::cout << "\nThank you for your time. I hope you enjoyed the game";

                    break;
                }
                else
                {
                    std::cout << "Invalid input" << std::endl;
                    continue;
                }
            }

        }else if (OPPONENT == '0')
        {

            std::cout << "\nTry the game more next time!!";
            break;

        }else
        {
            std::cout << "\nInvalid input" << std::endl;
            continue;
        }

    }

    return 0;

}