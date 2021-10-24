#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

class deckOfCards
{
protected:
    vector <pair<char, string>> deck;
public:
    deckOfCards()
    {
        string x = "A23456789TJQK";
        string y[4] = { "\u2660" , "\u2663" , "\u2665" , "\u2666" };
        pair< char, string > deck1;
        for (int i = 0; i < 13; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                deck1.first = x[i];
                deck1.second = y[j];
                deck.push_back(deck1);
            }
        }
    }
};
class BlackJack : public deckOfCards {
private:
    int score;
    int card;
    int ace;
    char anotherCard;
    int firstCard;
    int cardValue;
public:
    BlackJack()
    {
        score = 0;
    }
    void firstCards()
    {
        for (int i = 1; i <= 2; i++) {
            card = rand() % deck.size();
            if (deck[card].first == 'A')
                firstCard = 11;
            else if (deck[card].first == 'J' || deck[card].first == 'Q' || deck[card].first == 'K' || deck[card].first == 'T')
                firstCard = 10;
            else firstCard = deck[card].first - 48;
            cout << "Your " << i << " card value: " << deck[card].first << deck[card].second << endl;
            score = score + firstCard;
        }
    }
    void takeCard() {
        card = rand() % deck.size();

        if (deck[card].first == 'A')
        {
            cout << "You got A" << deck[card].second << "! Your score: " << score << ". What you choose 1 or 11?" << endl;
            cin >> ace;
            score = score + ace;
        }
        else if (deck[card].first == 'J' || deck[card].first == 'Q' || deck[card].first == 'K' || deck[card].first == 'T')
        {
            score = score + 10;
        }
        else
        {
            score = score + deck[card].first - 48;
        }
        deck.erase(deck.begin() + card);
    }
    void getScore()
    {
        if (score < 21)
        {
            cout << "Your score is " << score << ". Would you like to take another card? (Y/N)" << endl;
            cin >> anotherCard;
            if (anotherCard == 'Y')
            {
                takeCard();
                if (cardValue != 1)
                    cout << "New card value: " << deck[card].first << deck[card].second << endl;
                getScore();

            }
            else cout << "Your score: " << score << endl;
        }
        else if (score == 21)
        {
            cout << "CONGRATS!!! You win!" << endl;
        }
        else cout << "Looser! Score: " << score << endl;
    }
    void computerFirstCards()
    {
        for (int i = 1; i <= 2; i++) {
            card = rand() % deck.size();
            if (deck[card].first == 'A')
                firstCard = 11;
            else if (deck[card].first == 'J' || deck[card].first == 'Q' || deck[card].first == 'K' || deck[card].first == 'T')
                firstCard = 10;
            else firstCard = deck[card].first - 48;
            score = score + firstCard;
        }
    }
    void getDealerScore(BlackJack x)
    {
        card = rand() % deck.size();
        if (deck[card].first == 'A')
        {
            if (x.score > 11 && score + 11 <= 21)
            {
                score += 11;
            }
            else score += 1;
        }
        else if (deck[card].first == 'J' || deck[card].first == 'Q' || deck[card].first == 'K' || deck[card].first == 'T')
        {
            score = score + 10;
        }
        else
        {
            score = score + deck[card].first - 48;
        }
        deck.erase(deck.begin() + card);
    }
    void calculateResults(BlackJack x)
    {
        if (x.score >= score && x.score < 21)
        {
            getDealerScore(x);
            calculateResults(x);
        }
        else if ((score > x.score&& score <= 21) || (x.score > 21))
            cout << "Dealer BLACKJACK! Dealer score: " << score << endl;
        else cout << "Player BLACKJACK! Dealer score " << score << endl;
    }
};

int main()
{
    char start;
    srand(time(0));
    deckOfCards A;

    cout << "***WELCOME TO BLACKJACK!***" << endl;
    cout << "If you want to start the game, press Y, to end the game - press N" << endl;
    cin >> start;
    while (start == 'Y') {
        BlackJack Zaid, Comp;
        Zaid.firstCards();
        Comp.computerFirstCards();
        Zaid.getScore();
        Comp.calculateResults(Zaid);
        cout << "Play again? (Y/N)" << endl;
        cin >> start;
    }
    return 0;
}