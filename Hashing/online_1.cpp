#include <bits/stdc++.h>
using namespace std;
enum EntryType
{
    EMPTY,
    OCCUPIED,
    DELETED
};
struct Slot
{
    int process_id;
    EntryType entry;
    Slot() : process_id(-1), entry(EMPTY) {}
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
        for (int i = 3; i <= sqrt(n); i++)
        {
            if (n % i == 0)
                return false;
        }
        return true;
    }
    static int nextPrime(int n)
    {
        int candidate = n + 1;
        while (!isPrime(candidate))
        {
            candidate++;
        }
        return candidate;
    }
    static int prevPrim(int n)
    {
        int candidate = n - 1;
        while (!isPrime(candidate) && candidate > 1)
        {
            candidate--;
        }
        return candidate;
    }
};
class MemoryManager
{
    vector<Slot> table;
    int tableSize;
    int initialSize;
    int occupiedCount;
    int maxProbeCount;
    int pMax;
    int deletionSinceLastCheck;
    int hash(int process_id)
    {
        return process_id % tableSize;
    }
    int probe(int process_id, int j)
    {
        return (hash(process_id) + j * j) % tableSize;
    }
    double getLoadFactor()
    {
        return (double)occupiedCount / tableSize;
    }
    void printRehashBefore()
    {
        cout << "--- Rehash Triggered: BEFORE ---" << endl;
        cout << "Table Size: " << tableSize << endl;
        cout << "Active Processes: " << occupiedCount << endl;
        cout << "Load Factor: " << fixed << setprecision(2) << getLoadFactor() << endl;
        cout << "Max Probe Sequence: " << maxProbeCount << endl;
    }

    void printRehashAfter()
    {
        cout << "--- Rehash Triggered: AFTER ---" << endl;
        cout << "Table Size: " << tableSize << endl;
        cout << "Active Processes: " << occupiedCount << endl;
        cout << "Load Factor: " << fixed << setprecision(2) << getLoadFactor() << endl;
        cout << "Max Probe Sequence: " << maxProbeCount << endl;
    }
    void rehash(int newSize)
    {
        vector<Slot> oldTable = table;
        int oldSize = tableSize;

        tableSize = newSize;
        table.clear();
        table.resize(tableSize);
        occupiedCount = 0;
        maxProbeCount = 0;
        deletionSinceLastCheck = 0;

        for (const auto &prev_slot : oldTable)
        {
            if (prev_slot.entry == OCCUPIED)
            {
                int j = 0;
                int probeCount = 0;
                while (j < tableSize)
                {
                    int index = probe(prev_slot.process_id, j);
                    probeCount++;

                    if (table[index].entry == EMPTY || table[index].entry == DELETED)
                    {
                        table[index].process_id = prev_slot.process_id;
                        table[index].entry = OCCUPIED;
                        occupiedCount++;
                        maxProbeCount = max(maxProbeCount, probeCount);
                        break;
                    }
                    j++;
                }
            }
        }
    }
    void scaleUp()
    {
        printRehashBefore();
        int newSize = PrimeClass::nextPrime(2 * tableSize);
        rehash(newSize);
        printRehashAfter();
    }
    void scaleDown()
    {
        if (tableSize <= initialSize)
            return;

        int targetSize = tableSize / 2;
        int newSize;
        if (PrimeClass::isPrime(targetSize))
        {
            newSize = targetSize;
        }
        else
        {
            newSize = PrimeClass::prevPrim(targetSize);
        }
        if (newSize < initialSize)
            return;

        maxProbeCount = 0;

        for (int i = 0; i < tableSize; i++)
        {
            if (table[i].entry == OCCUPIED)
            {
                int process_id = table[i].process_id;
                int j = 0;
                int probeCount = 0;

                while (j < tableSize)
                {
                    int index = probe(process_id, j);
                    probeCount++;

                    if (table[index].entry == OCCUPIED && table[i].process_id == process_id)
                    {
                        maxProbeCount = max(maxProbeCount, probeCount);
                        break;
                    }
                    j++;
                }
            }
        }
        printRehashBefore();
        rehash(newSize);
        printRehashAfter();
    }

public:
    MemoryManager(int n, int p_max) : initialSize(n), tableSize(n), pMax(p_max), occupiedCount(0), deletionSinceLastCheck(0), maxProbeCount(0)
    {
        table.resize(tableSize);
    }
    void allocate(int process_id)
    {
        int j = 0;
        int probeCount = 0;
        int insertIndex = -1;

        while (j < tableSize)
        {
            int index = probe(process_id, j);
            probeCount++;
            if (table[index].entry == EMPTY || table[index].entry == DELETED)
            {
                insertIndex = index;
                break;
            }
            if (probeCount >= pMax && insertIndex == -1)
            {
                scaleUp();
                j = 0;
                probeCount = 0;
                continue;
            }
            j++;
        }
        if (insertIndex != -1)
        {
            table[insertIndex].process_id = process_id;
            table[insertIndex].entry = OCCUPIED;
            occupiedCount++;
            maxProbeCount = max(maxProbeCount, probeCount);
            cout << "ALLOCATE " << process_id << ": Inserted at index "
                 << insertIndex << " (probes: " << probeCount << ")" << endl;
        }
    }
    void free(int process_id)
    {
        int j = 0;
        int freeIndex = -1;
        while (j < tableSize)
        {
            int index = probe(process_id, j);
            if (table[index].entry == EMPTY)
                break;

            if (table[index].entry == OCCUPIED && table[index].process_id == process_id)
            {
                freeIndex = index;
                break;
            }
            j++;
        }
        if (freeIndex != -1)
        {
            table[freeIndex].entry = DELETED;
            occupiedCount--;
            deletionSinceLastCheck++;
            cout << "FREE " << process_id << ": Freed from index " << freeIndex << endl;
            if (deletionSinceLastCheck >= 5)
            {
                deletionSinceLastCheck = 0;
                if (getLoadFactor() < 0.2)
                {
                    scaleDown();
                }
            }
        }
    }
};
int main()
{
    int N, P_MAX, Q;
    cin >> N >> P_MAX >> Q;

    MemoryManager manager(N, P_MAX);

    for (int i = 0; i < Q; i++)
    {
        string operation;
        cin >> operation;

        if (operation == "ALLOCATE")
        {
            int process_id;
            cin >> process_id;
            manager.allocate(process_id);
        }
        else if (operation == "FREE")
        {
            int process_id;
            cin >> process_id;
            manager.free(process_id);
        }
    }
}