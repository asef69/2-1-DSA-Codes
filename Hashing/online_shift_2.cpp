#include <bits/stdc++.h>
using namespace std;

enum EntryState
{
	EMPTY,
	ACTIVE,
	DELETED
};

struct InnerEntry
{
	string userId;
	string permission;
	EntryState state = EMPTY;
};

struct GroupEntry
{
	string groupId;
	EntryState state = EMPTY;
	vector<InnerEntry> innerTable;
	bool innerInitialized = false;
	vector<string> userOrder;
};

class PermissionDB
{
private:
	int tableSize;
	vector<GroupEntry> outerTable;

	int hash1(const string &key) const
	{
		long long hashValue = 0;
		const int prime = 37;
		for (char c : key)
		{
			hashValue = (hashValue * prime + c) % tableSize;
		}
		return static_cast<int>(hashValue);
	}

	int hash2(const string &key) const
	{
		long long hashValue = 0;
		const int prime = 53;
		for (char c : key)
		{
			hashValue = (hashValue * prime + c) % tableSize;
		}
		return static_cast<int>(hashValue);
	}

	int findGroupIndex(const string &groupId) const
	{
		int base = hash1(groupId);
		for (int i = 0; i < tableSize; i++)
		{
			int index = (base + i) % tableSize;
			if (outerTable[index].state == EMPTY)
			{
				return -1;
			}
			if (outerTable[index].state == ACTIVE && outerTable[index].groupId == groupId)
			{
				return index;
			}
		}
		return -1;
	}

	int findGroupSlotForInsert(const string &groupId)
	{
		int base = hash1(groupId);
		int firstDeleted = -1;

		for (int i = 0; i < tableSize; i++)
		{
			int index = (base + i) % tableSize;
			if (outerTable[index].state == ACTIVE && outerTable[index].groupId == groupId)
			{
				return index;
			}
			if (outerTable[index].state == DELETED && firstDeleted == -1)
			{
				firstDeleted = index;
			}
			if (outerTable[index].state == EMPTY)
			{
				return (firstDeleted != -1) ? firstDeleted : index;
			}
		}
		return firstDeleted;
	}

	InnerEntry *findUserEntry(vector<InnerEntry> &table, const string &userId)
	{
		int base = hash2(userId);
		for (int i = 0; i < tableSize; i++)
		{
			int index = (base + i * i) % tableSize;
			if (table[index].state == EMPTY)
			{
				return nullptr;
			}
			if (table[index].state == ACTIVE && table[index].userId == userId)
			{
				return &table[index];
			}
		}
		return nullptr;
	}

	int findUserSlotForInsert(vector<InnerEntry> &table, const string &userId)
	{
		int base = hash2(userId);
		int firstDeleted = -1;

		for (int i = 0; i < tableSize; i++)
		{
			int index = (base + i * i) % tableSize;
			if (table[index].state == ACTIVE && table[index].userId == userId)
			{
				return index;
			}
			if (table[index].state == DELETED && firstDeleted == -1)
			{
				firstDeleted = index;
			}
			if (table[index].state == EMPTY)
			{
				return (firstDeleted != -1) ? firstDeleted : index;
			}
		}
		return firstDeleted;
	}

public:
	explicit PermissionDB(int n) : tableSize(n), outerTable(n) {}

	void insert(const string &groupId, const string &userId, const string &permission)
	{
		int groupIndex = findGroupSlotForInsert(groupId);
		if (groupIndex == -1)
		{
			return;
		}

		if (outerTable[groupIndex].state != ACTIVE)
		{
			outerTable[groupIndex].groupId = groupId;
			outerTable[groupIndex].state = ACTIVE;
			outerTable[groupIndex].innerTable.assign(tableSize, InnerEntry());
			outerTable[groupIndex].innerInitialized = true;
			outerTable[groupIndex].userOrder.clear();
		}

		vector<InnerEntry> &inner = outerTable[groupIndex].innerTable;
		int userIndex = findUserSlotForInsert(inner, userId);
		if (userIndex == -1)
		{
			return;
		}

		if (inner[userIndex].state == ACTIVE && inner[userIndex].userId == userId)
		{
			inner[userIndex].permission = permission;
			return;
		}

		inner[userIndex].userId = userId;
		inner[userIndex].permission = permission;
		inner[userIndex].state = ACTIVE;
		outerTable[groupIndex].userOrder.push_back(userId);
	}

	void searchUser(const string &groupId, const string &userId) const
	{
		int groupIndex = findGroupIndex(groupId);
		if (groupIndex == -1)
		{
			cout << "Group not found" << '\n';
			return;
		}

		const vector<InnerEntry> &inner = outerTable[groupIndex].innerTable;
		int base = hash2(userId);
		for (int i = 0; i < tableSize; i++)
		{
			int index = (base + i * i) % tableSize;
			if (inner[index].state == EMPTY)
			{
				cout << "User not found in group " << groupId << '\n';
				return;
			}
			if (inner[index].state == ACTIVE && inner[index].userId == userId)
			{
				cout << inner[index].permission << '\n';
				return;
			}
		}
		cout << "User not found in group " << groupId << '\n';
	}

	void searchGroup(const string &groupId) const
	{
		int groupIndex = findGroupIndex(groupId);
		if (groupIndex == -1)
		{
			cout << "Group not found" << '\n';
			return;
		}

		const GroupEntry &group = outerTable[groupIndex];
		bool firstPrinted = true;

		for (const auto &userId : group.userOrder)
		{
			int base = hash2(userId);
			for (int i = 0; i < tableSize; i++)
			{
				int index = (base + i * i) % tableSize;
				if (group.innerTable[index].state == EMPTY)
				{
					break;
				}
				if (group.innerTable[index].state == ACTIVE && group.innerTable[index].userId == userId)
				{
					if (!firstPrinted)
					{
						cout << ", ";
					}
					cout << '(' << userId << ", " << group.innerTable[index].permission << ')';
					firstPrinted = false;
					break;
				}
			}
		}

		cout << '\n';
	}

	void removeUser(const string &groupId, const string &userId)
	{
		int groupIndex = findGroupIndex(groupId);
		if (groupIndex == -1)
		{
			cout << "Group not found" << '\n';
			return;
		}

		vector<InnerEntry> &inner = outerTable[groupIndex].innerTable;
		int base = hash2(userId);
		for (int i = 0; i < tableSize; i++)
		{
			int index = (base + i * i) % tableSize;
			if (inner[index].state == EMPTY)
			{
				cout << "User not found in group " << groupId << '\n';
				return;
			}
			if (inner[index].state == ACTIVE && inner[index].userId == userId)
			{
				cout << '(' << inner[index].userId << ", " << inner[index].permission << ") deleted" << '\n';
				inner[index].state = DELETED;
				vector<string> &order = outerTable[groupIndex].userOrder;
				for (size_t j = 0; j < order.size(); j++)
				{
					if (order[j] == userId)
					{
						order.erase(order.begin() + static_cast<long long>(j));
						break;
					}
				}
				return;
			}
		}
		cout << "User not found in group " << groupId << '\n';
	}
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n = 0;
	int q = 0;
	if (!(cin >> n >> q))
	{
		return 0;
	}

	PermissionDB db(n);
	string line;
	getline(cin, line);

	for (int i = 0; i < q; i++)
	{
		if (!getline(cin, line))
		{
			break;
		}
		if (line.empty())
		{
			i--;
			continue;
		}

		stringstream ss(line);
		string op;
		ss >> op;

		if (op == "INSERT")
		{
			string groupId, userId, permission;
			ss >> groupId >> userId >> permission;
			db.insert(groupId, userId, permission);
		}
		else if (op == "SEARCH")
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
		else if (op == "DELETE")
		{
			string groupId, userId;
			ss >> groupId >> userId;
			db.removeUser(groupId, userId);
		}
	}

	return 0;
}
