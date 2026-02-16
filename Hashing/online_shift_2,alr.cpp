#include <bits/stdc++.h>
using namespace std;

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

    HashEntry(const KeyType &k = KeyType(), const ValueType &v = ValueType(), const EntryType s = EMPTY)
        : key(k), value(v), state(s) {}
};

// Inner hash table for storing (user_id, permission) pairs
class InnerHashTable
{
private:
    int tableSize;
    vector<HashEntry<string, string>> table;
    vector<string> insertionOrder;

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

    int probe(const string &key, int i) const
    {
        // Quadratic probing: (hash2(key) + i^2) mod N
        return (hash2(key) + i * i) % tableSize;
    }

public:
    InnerHashTable(int size) : tableSize(size)
    {
        table.resize(tableSize);
    }

    bool insert(const string &userId, const string &permission)
    {
        int i = 0;
        int firstDeletedIdx = -1;

        while (i < tableSize)
        {
            int index = probe(userId, i);

            if (table[index].state == EMPTY)
            {
                if (firstDeletedIdx != -1)
                {
                    table[firstDeletedIdx] = HashEntry<string, string>(userId, permission, ACTIVE);
                }
                else
                {
                    table[index] = HashEntry<string, string>(userId, permission, ACTIVE);
                }
                insertionOrder.push_back(userId);
                return true;
            }
            else if (table[index].state == DELETED && firstDeletedIdx == -1)
            {
                firstDeletedIdx = index;
            }
            else if (table[index].state == ACTIVE && table[index].key == userId)
            {
                // Update existing user's permission
                table[index].value = permission;
                return true;
            }

            i++;
        }

        // If we found a deleted slot, use it
        if (firstDeletedIdx != -1)
        {
            table[firstDeletedIdx] = HashEntry<string, string>(userId, permission, ACTIVE);
            insertionOrder.push_back(userId);
            return true;
        }

        return false;
    }

    string search(const string &userId) const
    {
        int i = 0;

        while (i < tableSize)
        {
            int index = probe(userId, i);

            if (table[index].state == EMPTY)
            {
                return "";
            }
            else if (table[index].state == ACTIVE && table[index].key == userId)
            {
                return table[index].value;
            }

            i++;
        }

        return "";
    }

    bool remove(const string &userId, string &deletedPermission)
    {
        int i = 0;

        while (i < tableSize)
        {
            int index = probe(userId, i);

            if (table[index].state == EMPTY)
            {
                return false;
            }
            else if (table[index].state == ACTIVE && table[index].key == userId)
            {
                deletedPermission = table[index].value;
                table[index].state = DELETED;

                // Remove from insertion order
                for (auto it = insertionOrder.begin(); it != insertionOrder.end(); ++it)
                {
                    if (*it == userId)
                    {
                        insertionOrder.erase(it);
                        break;
                    }
                }

                return true;
            }

            i++;
        }

        return false;
    }

    vector<pair<string, string>> getAllActive() const
    {
        vector<pair<string, string>> result;

        // Return entries in insertion order
        for (const auto &userId : insertionOrder)
        {
            string permission = search(userId);
            if (!permission.empty())
            {
                result.push_back({userId, permission});
            }
        }

        return result;
    }
};

// Outer hash table for storing (group_id, inner_table) pairs
class PermissionDatabase
{
private:
    int tableSize;
    vector<HashEntry<string, InnerHashTable *>> table;

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

    int probe(const string &key, int i) const
    {
        // Linear probing: (hash1(key) + i) mod N
        return (hash1(key) + i) % tableSize;
    }

    int findGroup(const string &groupId) const
    {
        int i = 0;

        while (i < tableSize)
        {
            int index = probe(groupId, i);

            if (table[index].state == EMPTY)
            {
                return -1;
            }
            else if (table[index].state == ACTIVE && table[index].key == groupId)
            {
                return index;
            }

            i++;
        }

        return -1;
    }

public:
    PermissionDatabase(int size) : tableSize(size)
    {
        table.resize(tableSize);
        for (int i = 0; i < tableSize; i++)
        {
            table[i].value = nullptr;
        }
    }

    ~PermissionDatabase()
    {
        for (int i = 0; i < tableSize; i++)
        {
            if (table[i].value != nullptr)
            {
                delete table[i].value;
            }
        }
    }

    void insert(const string &groupId, const string &userId, const string &permission)
    {
        int i = 0;
        int firstDeletedIdx = -1;

        while (i < tableSize)
        {
            int index = probe(groupId, i);

            if (table[index].state == EMPTY)
            {
                if (firstDeletedIdx != -1)
                {
                    table[firstDeletedIdx].key = groupId;
                    table[firstDeletedIdx].value = new InnerHashTable(tableSize);
                    table[firstDeletedIdx].state = ACTIVE;
                    table[firstDeletedIdx].value->insert(userId, permission);
                }
                else
                {
                    table[index].key = groupId;
                    table[index].value = new InnerHashTable(tableSize);
                    table[index].state = ACTIVE;
                    table[index].value->insert(userId, permission);
                }
                return;
            }
            else if (table[index].state == DELETED && firstDeletedIdx == -1)
            {
                firstDeletedIdx = index;
            }
            else if (table[index].state == ACTIVE && table[index].key == groupId)
            {
                // Group exists, insert user into inner table
                table[index].value->insert(userId, permission);
                return;
            }

            i++;
        }

        // Use deleted slot if found
        if (firstDeletedIdx != -1)
        {
            table[firstDeletedIdx].key = groupId;
            table[firstDeletedIdx].value = new InnerHashTable(tableSize);
            table[firstDeletedIdx].state = ACTIVE;
            table[firstDeletedIdx].value->insert(userId, permission);
        }
    }

    void searchUser(const string &groupId, const string &userId) const
    {
        int groupIdx = findGroup(groupId);

        if (groupIdx == -1)
        {
            cout << "Group not found" << endl;
            return;
        }

        string permission = table[groupIdx].value->search(userId);
        if (permission.empty())
        {
            cout << "User not found in group " << groupId << endl;
        }
        else
        {
            cout << permission << endl;
        }
    }

    void searchGroup(const string &groupId) const
    {
        int groupIdx = findGroup(groupId);

        if (groupIdx == -1)
        {
            cout << "Group not found" << endl;
            return;
        }

        vector<pair<string, string>> entries = table[groupIdx].value->getAllActive();

        for (size_t i = 0; i < entries.size(); i++)
        {
            cout << "(" << entries[i].first << ", " << entries[i].second << ")";
            if (i < entries.size() - 1)
            {
                cout << ", ";
            }
        }
        cout << endl;
    }

    void deleteUser(const string &groupId, const string &userId)
    {
        int groupIdx = findGroup(groupId);

        if (groupIdx == -1)
        {
            cout << "Group not found" << endl;
            return;
        }

        string deletedPermission;
        if (table[groupIdx].value->remove(userId, deletedPermission))
        {
            cout << "(" << userId << ", " << deletedPermission << ") deleted" << endl;
        }
        else
        {
            cout << "User not found in group " << groupId << endl;
        }
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    cin.ignore();

    PermissionDatabase db(n);

    for (int i = 0; i < q; i++)
    {
        string line;
        if (!getline(cin, line))
            break;

        if (line.empty())
        {
            i--;
            continue;
        }

        stringstream ss(line);
        string operation;
        ss >> operation;

        if (operation == "INSERT")
        {
            string groupId, userId, permission;
            ss >> groupId >> userId >> permission;
            db.insert(groupId, userId, permission);
        }
        else if (operation == "SEARCH")
        {
            string groupId, userId;
            ss >> groupId;

            if (ss >> userId)
            {
                db.searchUser(groupId, userId);
            }
            else
            {
                db.searchGroup(groupId);
            }
        }
        else if (operation == "DELETE")
        {
            string groupId, userId;
            ss >> groupId >> userId;
            db.deleteUser(groupId, userId);
        }
    }

    return 0;
}
