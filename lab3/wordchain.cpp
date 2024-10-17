#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>

using namespace std;

struct Node
{
    string word;
    Node *prev; // Pekar på föregående nod i ordkedjan
    Node(string const &word, Node *prev = nullptr) : word(word), prev(prev) {}
};

typedef unordered_set<string> Dictionary;
string const alphabet{"abcdefghijklmnopqrstuvwxyz"};

// Hjälpfunktion som hittar grannar till ett ord genom att byta ut varje bokstav och kolla om det nya ordet finns i ordlistan.
void find_neighbors(const Dictionary &dict, Node &node, vector<string> &neighbors)
{
    for (int i = 0; i < static_cast<int>(node.word.size()); ++i)
    {
        string word = node.word;
        for (const char &c : alphabet)
        {
            word[i] = c;
            if (word != node.word && dict.find(word) != dict.end())
            {
                neighbors.push_back(word);
            }
        }
    }
}

// BFS för att hitta den kortaste ordkedjan från 'from' till 'to'
vector<string> find_shortest(Dictionary dict, const string &from, const string &to)
{
    queue<Node *> q;
    q.push(new Node(from)); // Starta från 'from'

    // BFS-loop
    while (!q.empty())
    {
        Node *curr = q.front();
        q.pop();

        // Hitta grannar till nuvarande ord
        vector<string> neighbors;
        find_neighbors(dict, *curr, neighbors);

        for (const string &neighbor : neighbors)
        {
            if (neighbor == to)
            {
                vector<string> result;
                result.push_back(to);
                Node *tmp = curr;

                while (tmp != nullptr)
                {
                    result.push_back(tmp->word);
                    tmp = tmp->prev;
                }

                reverse(result.begin(), result.end());
                return result;
            }
            dict.erase(neighbor);             // Ta bort besökta ord
            q.push(new Node(neighbor, curr)); // Lägg till i kö med länk till föregående nod
        }
    }
    return {}; // Returnera tom vektor om ingen kedja hittades
}

// BFS för att hitta den längsta av alla kortaste ordkedjor som slutar med 'word'
vector<string> find_longest(Dictionary dict, const string &word)
{
    queue<Node *> q;
    q.push(new Node(word)); // Starta från 'word'

    Node *last = nullptr;

    // BFS-loop
    while (!q.empty())
    {
        Node *curr = q.front();
        q.pop();

        // Hitta grannar till nuvarande ord
        vector<string> neighbors;
        find_neighbors(dict, *curr, neighbors);

        for (const string &neighbor : neighbors)
        {
            dict.erase(neighbor); // Ta bort besökta ord
            q.push(new Node(neighbor, curr));
        }

        last = curr; // Håll koll på den sista noden i BFS
    }

    vector<string> result;
    while (last != nullptr)
    {
        result.push_back(last->word);
        last = last->prev;
    }

    reverse(result.begin(), result.end());
    return result;
}

// Läs in ordlistan från standard input
Dictionary read_dictionary()
{
    string line;
    vector<string> result;

    while (getline(cin, line))
    {
        if (line == "#")
            break; // Sluta läsa när vi når '#'
        result.push_back(line);
    }

    return Dictionary(result.begin(), result.end());
}

// Skriv ut en ordkedja
void print_chain(const vector<string> &chain)
{
    if (chain.empty())
        return;

    cout << chain[0];
    for (size_t i = 1; i < chain.size(); ++i)
    {
        cout << " -> " << chain[i];
    }
    cout << endl;
}

// Skriv ut svaret för en fråga
void print_answer(const vector<string> &chain)
{
    if (chain.empty())
    {
        cout << "ingen lösning" << endl;
    }
    else
    {
        cout << chain.size() << " ord" << endl;
        print_chain(chain);
    }
}

// Läs in alla frågor och besvara dem
void read_questions(const Dictionary &dict)
{
    string line;

    while (getline(cin, line))
    {
        size_t space = line.find(' ');
        if (space != string::npos)
        {
            // Fråga: hitta kortaste ordkedjan
            string first = line.substr(0, space);
            string second = line.substr(space + 1);
            vector<string> chain = find_shortest(dict, first, second);

            cout << first << " " << second << ": ";
            print_answer(chain);
        }
        else
        {
            // Fråga: hitta längsta av alla kortaste ordkedjor
            vector<string> chain = find_longest(dict, line);

            cout << line << ": ";
            print_answer(chain);
        }
    }
}

int main()
{
    Dictionary dict = read_dictionary(); // Läs in ordlistan
    read_questions(dict);                // Läs och besvara alla frågor

    return 0;
}
