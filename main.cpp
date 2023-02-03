#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <map>
#include <algorithm>

using namespace std;

// class of a single Transaction
class Transaction
{
    // set variables all private
    string payer;
    int points;
    time_t timestamp;

    // use public function to init and get value
public:
    // constructor
    Transaction(string _payer, int _points, string _timestamp);
    // the following functions are provide read-only information of the class
    string get_payer();
    int get_points();
    time_t get_timestamp();
};

Transaction::Transaction(string _payer, int _points, string _timestamp)
{
    payer = _payer.substr(1, _payer.length() - 2); // remove \"
    points = _points;

    // convet string to time_t using std::mktime and std::tm
    std::tm tm = {};
    _timestamp = _timestamp.substr(1, _timestamp.length() - 2); // remove \"
    strptime(_timestamp.c_str(), "%Y-%m-%dT%H:%M:%SZ", &tm);
    timestamp = mktime(&tm);
}

string Transaction::get_payer()
{
    return payer;
}

int Transaction::get_points()
{
    return points;
}

time_t Transaction::get_timestamp()
{
    return timestamp;
}

// compare 2 Transactions by their timestamps
bool compareTimestamp(Transaction &a, Transaction &b)
{
    return a.get_timestamp() < b.get_timestamp();
}

// read the transactions.csv
vector<Transaction> readTransactions(int pointsToSpend, char *fileName)
{
    vector<Transaction> transactions;
    ifstream file(fileName);
    string line;

    // read attributes
    getline(file, line);

    // read the content of .csv file
    while (getline(file, line))
    {
        // if there's an empty line, skip
        if (line == "")
            continue;

        // store the content into lineStream
        stringstream lineStream(line);

        // seperate each element of the line
        string cell;
        vector<string> cells;
        while (getline(lineStream, cell, ','))
        {
            cells.push_back(cell);
        }
        Transaction t(cells[0], std::stoi(cells[1]), cells[2]);
        transactions.push_back(t);
    }
    return transactions;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " ./main <points_to_spend>" << std::endl;
        return 1;
    }
    // get the input points
    int pointsToSpend = stoi(argv[1]);

    // read transactions.csv and store the file in a vector, line by line
    vector<Transaction> transactions = readTransactions(pointsToSpend, "transactions.csv");

    // Sort the transactions by timestamp
    sort(transactions.begin(), transactions.end(), compareTimestamp);

    // compute earning points for each payer
    map<string, int> earningPoints;
    for (int i = 0; i < transactions.size(); i++)
    {
        // add up transactions
        earningPoints[transactions[i].get_payer()] += transactions[i].get_points();

        // check whether the input file is valid
        // e.g. the culminate points will never be smaller than 0
        if (earningPoints[transactions[i].get_payer()] < 0)
        {
            std::cerr << "Invalid transaction file!" << endl;
            return 1;
        }
    }

    // calculate the way to spend the points
    map<string, int> spendPoints;
    for (int i = 0; i < transactions.size(); i++)
    {
        // the amount that can spend in this run
        int amount = transactions[i].get_points();

        if (pointsToSpend == 0)
        {
            break;
        }

        if (amount < pointsToSpend)
        {
            spendPoints[transactions[i].get_payer()] += amount;
            pointsToSpend -= amount;
        }
        else
        {
            spendPoints[transactions[i].get_payer()] += pointsToSpend;
            pointsToSpend = 0;
        }
    }

    // get the Balances for each payer, earn - spend
    map<string, int> payerBalances;
    for (const auto &[key, value] : spendPoints)
    {
        if (earningPoints.count(key) > 0)
        {
            payerBalances[key] = earningPoints[key] - value;
        }
    }

    // print results
    for (const auto &balance : payerBalances)
    {
        std::cout << balance.first << ": " << balance.second << std::endl;
    }
    return 0;
}