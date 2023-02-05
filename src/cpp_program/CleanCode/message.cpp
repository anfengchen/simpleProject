#include <stdio.h>
#include <string>

using namespace std;

void PrintGuessStatistics(char candidate, int count)
{
    string number;
    string verb;
    string pluraModifier;

    if (count == 0)
    {
        number = "no";
        verb = "are";
        pluraModifier = "s";
    }
    else if (count == 1)
    {
        number = "1";
        verb = "is";
        pluraModifier = "";
    }
    else
    {
        number = to_string(count);
        verb = "are";
        pluraModifier = "s";
    }
    char guessMessage[100];
    snprintf(guessMessage, sizeof(guessMessage), "There %s %s %c%s", verb.c_str(), number.c_str(), candidate, pluraModifier.c_str());
    printf("%s", guessMessage);
}

class GuessStaticsMessage
{
public:
    string make(char candidate, int count)
    {
        CreatePluralDependentPartMessage(count);
        char guessMessage[100];
        snprintf(guessMessage, sizeof(guessMessage), "There %s %s %c%s", verb.c_str(), number.c_str(), candidate, pluraModifier.c_str());
        return guessMessage;
    }

private:
    void CreatePluralDependentPartMessage(int count)
    {
        if (count == 0)
        {
            ThereAreNoLetters();
        }
        else if (count == 1)
        {
            ThereIsOneLetters();
        }
        else
        {
            ThereAreManyLetters(count);
        }
    }
    void ThereAreNoLetters()
    {
        number = "no";
        verb = "are";
        pluraModifier = "s";
    }
    void ThereIsOneLetters()
    {
        number = "1";
        verb = "is";
        pluraModifier = "";
    }
    void ThereAreManyLetters(int count)
    {
        number = to_string(count);
        verb = "are";
        pluraModifier = "s";
    }
    string number;
    string verb;
    string pluraModifier;
};
