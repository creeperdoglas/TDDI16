#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <unordered_set>
#include <algorithm>

using std::cout;
using std::endl;
using std::string;
using std::vector;

using namespace std;
struct Node
{
    Node(string const &word)
        : word{word} {}
    Node(string const &word, Node *prev)
        : word{word}, prev{prev} {}
    string word;
    vector<string> neighbors;
    Node *prev;
};

typedef unordered_set<string, hash<string>> Dictionary;
string const alphabet{"abcdefghijklmnopqrstuvwxyz"};

void find_neighbors(const Dictionary &dict, Node &node)
{
    for (int i{}; i < static_cast<int>(node.word.size()); ++i)
    {
        string word = node.word;
        for (const char &c : alphabet)
        {
            word.at(i) = c;
            if (word != node.word)
            {
                auto it = dict.find(word);
                if (it != dict.end())
                    node.neighbors.push_back(word);
            }
        }
    }
}

// Typ som används för ordlistan. Den definieras med en typedef här så att du enkelt kan ändra
// representationen av en ordlista utefter vad din implementation behöver. Funktionen
// "read_questions" skickar ordlistan till "find_shortest" och "find_longest" med hjälp av denna
// typen.
// typedef vector<string> Dictionary;

/**
 * Hitta den kortaste ordkedjan från 'first' till 'second' givet de ord som finns i
 * 'dict'. Returvärdet är den ordkedja som hittats, första elementet ska vara 'from' och sista
 * 'to'. Om ingen ordkedja hittas kan en tom vector returneras.
 */

vector<string> find_shortest(Dictionary dict, const string &from, const string &to)
{
    vector<string> result;
    queue<Node> queue;

    Node begin{from};
    queue.push(begin);
    while (!queue.empty())
    {
        Node curr = queue.front();
        queue.pop();
        find_neighbors(dict, curr);
        for (string neighbor : curr.neighbors)
        {
            if (neighbor == to)
            {
                Node *curr_ptr = new Node(curr);
                result.push_back(to);
                result.push_back(curr_ptr->word);
                while (curr_ptr->word != from)
                {
                    result.push_back(curr_ptr->prev->word);
                    curr_ptr = curr_ptr->prev;
                }
                reverse(result.begin(), result.end());
                return result;
            }
            else
            {
                dict.erase(neighbor);
                queue.push(Node{neighbor, new Node(curr)});
            }
        }
    }
    reverse(result.begin(), result.end());
    return result;
}

/**
 * Hitta den längsta kortaste ordkedjan som slutar i 'word' i ordlistan 'dict'. Returvärdet är den
 * ordkedja som hittats. Det sista elementet ska vara 'word'.
 */
vector<string> find_longest(Dictionary dict, const string &word)
{
    vector<string> result;
    queue<Node> queue;

    Node begin{word};
    queue.push(begin);
    while (true)
    {
        Node curr = queue.front();
        queue.pop();
        find_neighbors(dict, curr);
        for (const string &neighbor : curr.neighbors)
        {
            dict.erase(neighbor);
            queue.push(Node{neighbor, new Node(curr)});
        }
        if (queue.empty())
        {
            if (word != curr.word)
            {
                Node *curr_ptr = new Node(curr);
                result.push_back(curr_ptr->word);
                while (curr_ptr->prev->word != word)
                {
                    result.push_back(curr_ptr->prev->word);
                    curr_ptr = curr_ptr->prev;
                }
            }
            break;
        }
    }
    result.push_back(word);
    return result;
}

/**
 * Läs in ordlistan och returnera den som en vector av orden. Funktionen läser även bort raden med
 * #-tecknet så att resterande kod inte behöver hantera det.
 */
Dictionary read_dictionary()
{
    string line;
    vector<string> result;
    while (std::getline(std::cin, line))
    {
        if (line == "#")
            break;

        result.push_back(line);
    }

    return Dictionary(result.begin(), result.end());
}

/**
 * Skriv ut en ordkedja på en rad.
 */
void print_chain(const vector<string> &chain)
{
    if (chain.empty())
        return;

    vector<string>::const_iterator i = chain.begin();
    cout << *i;

    for (++i; i != chain.end(); ++i)
        cout << " -> " << *i;

    cout << endl;
}

/**
 * Skriv ut ": X ord" och sedan en ordkedja om det behövs. Om ordkedjan är tom, skriv "ingen lösning".
 */
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

/**
 * Läs in alla frågor. Anropar funktionerna "find_shortest" eller "find_longest" ovan när en fråga hittas.
 */
void read_questions(const Dictionary &dict)
{
    string line;
    while (std::getline(std::cin, line))
    {
        size_t space = line.find(' ');
        if (space != string::npos)
        {
            string first = line.substr(0, space);
            string second = line.substr(space + 1);
            vector<string> chain = find_shortest(dict, first, second);

            cout << first << " " << second << ": ";
            print_answer(chain);
        }
        else
        {
            vector<string> chain = find_longest(dict, line);

            cout << line << ": ";
            print_answer(chain);
        }
    }
}

int main()
{
    Dictionary dict = read_dictionary();
    read_questions(dict);

    return 0;
}
