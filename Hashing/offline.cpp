#include <bits/stdc++.h>
using namespace std;

const int INITIAL_TABLE_SIZE = 13;
const double MAX_LOAD_FACTOR = 0.5;
const double MIN_LOAD_FACTOR = 0.25;

const int C1 = 1;
const int C2 = 3;

enum EntryType
{
    ACTIVE,
    EMPTY,
    DELETED
};

template <typename KeyType, typename ValueType>
class HashEntry
{
public:
    KeyType key;
    ValueType value;
    EntryType state;

    HashEntry(const KeyType &k = KeyType(), const ValueType &v = ValueType(), const EntryType s = EMPTY) : key(k), value(v), state(s) {}
};

class PrimeClass
{
public:
    static bool isPrime(int n)
    {
        if (n < 2)
            return false;
        if (n == 2)
            return true;
        if (n % 2 == 0)
            return false;

        for (int i = 3; i <= sqrt(n); i += 2)
        {
            if (n % i == 0)
                return false;
        }
        return true;
    }
    static int nextPrime(int n)
    {
        int possible = n + 1;
        while (!isPrime(possible))
        {
            possible++;
        }
        return possible;
    }
    static int prevPrime(int n)
    {
        int possible = n - 1;
        while (possible > 1 && !isPrime(possible))
        {
            possible--;
        }
        return possible > 1 ? possible : 2;
    }
};

class RandomWordGenerator
{
private:
    mt19937 rng;
    unordered_set<string> generatedWords;

public:
    RandomWordGenerator(unsigned int seed = 0) : rng(seed) {}
    string generateWord(int length)
    {
        string word;
        uniform_int_distribution<int> dist('a', 'z');
        do
        {
            word.clear();
            for (int i = 0; i < length; i++)
            {
                word += (char)dist(rng);
            }
        } while (generatedWords.count(word) > 0);
        generatedWords.insert(word);
        return word;
    }
    vector<string> generateUniqueWords(int count, int length)
    {
        vector<string> words;
        for (int i = 0; i < count; i++)
        {
            words.push_back(generateWord(length));
        }
        return words;
    }
};

class HashTableBase
{
protected:
    int tableSize;
    int numElements;
    string hasFuncName;
    int collisionCount;
    int searchHits;
    int searchCount;

    int insertionSinceExpansion;
    int deletionSinceCompaction;

public:
    HashTableBase(const string &hasFunc = "hash1") : tableSize(INITIAL_TABLE_SIZE), numElements(0), hasFuncName(hasFunc), collisionCount(0), searchHits(0), insertionSinceExpansion(0), deletionSinceCompaction(0) {}
    virtual ~HashTableBase() {}
    int hash1(const string &key) const
    {
        long long hashValue = 0;
        const int prime = 37;

        for (char c : key)
        {
            hashValue = (hashValue * prime + c) % tableSize;
        }
        return hashValue;
    }
    int hash2(const string &key) const
    {
        long long hashValue = 0;
        const int prime = 53;

        for (char c : key)
        {
            hashValue = (hashValue * prime + c) % tableSize;
        }
        return hashValue;
    }
    int hash(const string &key) const
    {
        if (hasFuncName == "hash1")
            return hash1(key);
        else
            hash2(key);
    }
    int auxHash(const string &key) const
    {
        long long numericKey = 0;
        for (char c : key)
        {
            numericKey = (numericKey * 31 + c) % tableSize;
        }

        int R = PrimeClass::prevPrime(tableSize);
        if (R < 2)
            R = 2;

        int result = R - (numericKey % R);
        return max(1, result);
    }
    double getLoadFactor() const
    {
        return (double)numElements / tableSize;
    }
    bool shouldExpand() const
    {
        if (getLoadFactor() <= MAX_LOAD_FACTOR)
            return false;
        return insertionSinceExpansion >= numElements / 2;
    }
    bool shouldCompact() const
    {
        if (tableSize == INITIAL_TABLE_SIZE)
            return false;
        if (getLoadFactor() >= MIN_LOAD_FACTOR)
            return false;
        return deletionSinceCompaction >= numElements / 2;
    }
    int getCollisionCount() const
    {
        return collisionCount;
    }
    int getNumElements() const
    {
        return numElements;
    }
    double getAverageSearchHits() const
    {
        if (searchHits == 0)
            return 0.0;
        return (double)searchHits / searchCount;
    }

    virtual bool insert(const string &key, int value) = 0;
    virtual int search(const string &key) = 0;
    virtual bool remove(const string &key) = 0;
};

class ChainingHashTable : public HashTableBase
{
private:
    vector<list<pair<string, int>>> table;
    void rehash(int newSize)
    {
        vector<list<pair<string, int>>> oldTable = table;
        tableSize = newSize;
        table.clear();
        table.resize(tableSize);

        int oldNumElements = numElements;
        numElements = 0;
        insertionSinceExpansion = 0;
        deletionSinceCompaction = 0;

        for (const auto &chain : oldTable)
        {
            for (const auto &entry : chain)
            {
                int index = hash(entry.first);
                table[index].push_back(entry);
                numElements++;
            }
        }
    }

public:
    ChainingHashTable(const string &hashFunc = "hash1") : HashTableBase(hashFunc)
    {
        table.resize(tableSize);
    }
    bool insert(const string &key, int value) override
    {
        int index = hash(key);

        for (const auto &entry : table[index])
        {
            if (entry.first == key)
            {
                return false;
            }
        }
        if (!table[index].empty())
        {
            collisionCount++;
        }

        table[index].push_front(make_pair(key, value));
        numElements++;
        insertionSinceExpansion++;

        if (shouldExpand())
        {
            rehash(PrimeClass::nextPrime(2 * tableSize));
        }
        return true;
    }

    int search(const string &key) override
    {
        int index = hash(key);
        int hits = 1;

        for (const auto &entry : table[index])
        {
            if (entry.first == key)
            {
                searchHits += hits;
                searchCount++;
                return entry.second;
            }
            hits++;
        }

        searchHits += hits;
        searchCount++;
        return -1;
    }

    bool remove(const string &key) override
    {
        int index = hash(key);

        for (auto it = table[index].begin(); it != table[index].end(); it++)
        {
            if (it->first == key)
            {
                table[index].erase(it);
                numElements--;
                deletionSinceCompaction++;

                if (shouldCompact())
                {
                    rehash(PrimeClass::prevPrime(tableSize / 2));
                }
                return true;
            }
        }
        return false;
    }

    void printStatistics() const
    {
        cout << "Table Size: " << tableSize << endl;
        cout << "Elements: " << numElements << endl;
        cout << "Load Factor (λ): " << fixed << setprecision(2)
             << getLoadFactor() << endl;
        cout << "Collisions: " << collisionCount << endl;
    }
};

class OpenAddressingHashTable : public HashTableBase
{
protected:
    vector<HashEntry<string, int>> table;

    virtual int probe(const string &key, int i) const = 0;

    void rehash(int newSize)
    {
        vector<HashEntry<string, int>> oldTable = table;

        tableSize = newSize;
        table.clear();
        table.resize(tableSize);

        int oldNumElements = numElements;
        numElements = 0;
        insertionSinceExpansion = 0;
        deletionSinceCompaction = 0;

        for (const auto &entry : oldTable)
        {
            if (entry.state == ACTIVE)
            {
                insert(entry.key, entry.value);
            }
        }
    }

public:
    OpenAddressingHashTable(const string &hashFunc = "hash1") : HashTableBase(hashFunc)
    {
        table.resize(tableSize);
    }
    bool insert(const string &key, int value) override
    {
        int i = 0;
        bool collisionOccured = false;

        while (i < tableSize)
        {
            int index = probe(key, i);

            if (table[index].state == EMPTY || table[index].state == DELETED)
            {
                if (i > 0 || table[index].state == DELETED)
                {
                    collisionOccured = true;
                }
                table[index] = HashEntry<string, int>(key, value, ACTIVE);
                numElements++;
                insertionSinceExpansion++;

                if (collisionOccured)
                {
                    collisionCount++;
                }

                if (shouldExpand())
                {
                    rehash(PrimeClass::nextPrime(tableSize * 2));
                }
                return true;
            }
            else if (table[index].state == ACTIVE && table[index].key == key)
            {
                return false;
            }
            else
            {
                if (i == 0)
                {
                    collisionOccured = true;
                }
                i++;
            }
        }
        return false;
    }

    int search(const string &key) override
    {
        int i = 0;
        int hits = 0;
        while (i < tableSize)
        {
            int index = probe(key, i);
            hits++;
            if (table[index].state == EMPTY)
            {
                searchHits += hits;
                searchCount++;
                return -1;
            }
            else if (table[index].state == ACTIVE && table[index].key == key)
            {
                searchHits += hits;
                searchCount++;
                return table[index].value;
            }
            else
            {
                i++;
            }
        }
        searchHits += hits;
        searchCount++;
        return -1;
    }

    bool remove(const string &key) override
    {
        int i = 0;

        while (i < tableSize)
        {
            int index = probe(key, i);

            if (table[index].state == EMPTY)
            {
                return false;
            }
            else if (table[index].state == ACTIVE && table[index].key == key)
            {
                table[index].state = DELETED;
                numElements--;
                deletionSinceCompaction++;

                if (shouldCompact())
                {
                    rehash(PrimeClass::prevPrime(tableSize / 2));
                }
                return true;
            }
            else
            {
                i++;
            }
        }
        return false;
    }
    void printStatistics() const
    {
        cout << "Table Size: " << tableSize << endl;
        cout << "Elements: " << numElements << endl;
        cout << "Load Factor (λ): " << fixed << setprecision(2)
             << getLoadFactor() << endl;
        cout << "Collisions: " << collisionCount << endl;
    }
};

class LinearProbingTable : public OpenAddressingHashTable
{
protected:
    int probe(const string &key, int i) const override
    {
        return (hash(key) + i) % tableSize;
    }

public:
    LinearProbingTable(const string &hashFunc = "hash1") : OpenAddressingHashTable(hashFunc) {}
};

class QuadraticProbingTable : public OpenAddressingHashTable
{
protected:
    int probe(const string &key, int i) const override
    {
        return (hash(key) + i * i) % tableSize;
    }

public:
    QuadraticProbingTable(const string &hashFunc = "hash1") : OpenAddressingHashTable(hashFunc) {}
};

class DoubleHashingTable : public OpenAddressingHashTable
{
protected:
    int probe(const string &key, int i) const override
    {
        return (hash(key) + i * auxHash(key)) % tableSize;
    }

public:
    DoubleHashingTable(const string &hashFunc = "hash1") : OpenAddressingHashTable(hashFunc) {}
};

class CustomProbingTable : public OpenAddressingHashTable
{
protected:
    int probe(const string &key, int i) const override
    {
        return (hash(key) + C1 * i * auxHash(key) + C2 * i * i) % tableSize;
    }

public:
    CustomProbingTable(const string &hashFunc = "hash1") : OpenAddressingHashTable(hashFunc) {}
};

void BasicFunctionality()
{
    cout << string(80, '=') << endl;
    cout << "Basic Functionalities" << endl;
    cout << string(80, '=') << endl;

    vector<string> wordsSequence = {"ancient", "puzzled", "benefit", "ancient", "zigzags"};
    cout << "Inserting words in sequence:" << endl;
    cout << "Word Sequence: ";
    for (const auto &word : wordsSequence)
    {
        cout << word << " ";
    }
    cout << endl
         << endl;

    ChainingHashTable ht;
    int sequenceNum = 0;

    for (const string &word : wordsSequence)
    {
        sequenceNum++;
        if (ht.insert(word, sequenceNum))
        {
            cout << "Inserted: (" << word << "," << sequenceNum << ")" << endl;
        }
        else
        {
            cout << "Skipped Duplicates: " << word << endl;
        }
    }

    cout << endl
         << "Searching for words:" << endl;
    vector<string> searchWords = {"ancient", "puzzled", "benefit", "zigzags", "notfound"};
    for (const string &word : searchWords)
    {
        int result = ht.search(word);
        if (result != -1)
        {
            cout << "Found: " << word << "->" << result << endl;
        }
        else
        {
            cout << "Not Found: " << word << endl;
        }
    }
    cout << endl;
}

void runPerformanceEvaluation()
{
    cout << string(80, '=') << endl;
    cout << "Hash Table Performance Evaluation" << endl;
    cout << string(80, '=') << endl
         << endl;

    cout << "Generating 10,000 unique words of length 10..." << endl;
    RandomWordGenerator generator(42);
    vector<string> words = generator.generateUniqueWords(10000, 10);
    cout << "Generated " << words.size() << " unique words" << endl
         << endl;

    vector<string> searchWords;
    random_device rd;
    mt19937 rng(42);
    uniform_int_distribution<int> dist(0, words.size() - 1);
    unordered_set<int> selectedIndices;

    while (searchWords.size() < 1000)
    {
        int idx = dist(rng);
        if (selectedIndices.insert(idx).second)
        {
            searchWords.push_back(words[idx]);
        }
    }

    vector<string> hashFunctions = {"hash1", "hash2"};

    struct MethodInfo
    {
        string name;
        function<unique_ptr<HashTableBase>(const string &)> factory;
    };

    vector<MethodInfo> methods = {
        {"Chaining Method", [](const string &h)
         {
             return unique_ptr<HashTableBase>(new ChainingHashTable(h));
         }},
        {"Linear Probing", [](const string &h)
         {
             return unique_ptr<HashTableBase>(new LinearProbingTable(h));
         }},
        {"Quadratic Probing", [](const string &h)
         {
             return unique_ptr<HashTableBase>(new QuadraticProbingTable(h));
         }},
        {"Double Hashing", [](const string &h)
         {
             return unique_ptr<HashTableBase>(new DoubleHashingTable(h));
         }},
        {"Custom Probing", [](const string &h)
         {
             return unique_ptr<HashTableBase>(new CustomProbingTable(h));
         }}};

    struct Result
    {
        int collisions;
        double avgHits;
    };

    map<string, map<string, Result>> results;

    for (const auto &method : methods)
    {
        cout << "Testing " << method.name << "..." << endl;

        for (const string &hashFunc : hashFunctions)
        {
            auto ht = method.factory(hashFunc);

            for (size_t i = 0; i < words.size(); i++)
            {
                ht->insert(words[i], i + 1);
            }

            int collisions = ht->getCollisionCount();

            for (const string &word : searchWords)
            {
                ht->search(word);
            }

            double avgHits = ht->getAverageSearchHits();

            results[method.name][hashFunc] = {collisions, avgHits};

            cout << "  " << hashFunc << ": Collisions = " << collisions
                 << ", Avg Hits = " << fixed << setprecision(2) << avgHits << endl;
        }

        cout << endl;
    }

    cout << string(80, '=') << endl;
    cout << "PERFORMANCE EVALUATION RESULTS" << endl;
    cout << string(80, '=') << endl
         << endl;

    cout << left << setw(30) << ""
         << right << setw(22) << "Hash1"
         << setw(22) << "Hash2" << endl;
    cout << left << setw(30) << ""
         << right << setw(11) << "Collisions"
         << setw(11) << "Avg Hits"
         << setw(11) << "Collisions"
         << setw(11) << "Avg Hits" << endl;
    cout << string(80, '-') << endl;

    for (const auto &method : methods)
    {
        const auto &h1 = results[method.name]["hash1"];
        const auto &h2 = results[method.name]["hash2"];

        cout << left << setw(30) << method.name
             << right << setw(11) << h1.collisions
             << setw(11) << fixed << setprecision(2) << h1.avgHits
             << setw(11) << h2.collisions
             << setw(11) << fixed << setprecision(2) << h2.avgHits << endl;
    }

    cout << string(80, '=') << endl;
}

int main()
{
    BasicFunctionality();
    cout << endl;

    runPerformanceEvaluation();
}