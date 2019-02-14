#include "level_db.hpp"

#include <iostream>
#include <vector>

using namespace std;
using namespace leveldb;

int LevelDBOp::init()
{
	Options options;
	options.create_if_missing = true;
	options.error_if_exists = false;
	Status s= DB::Open(options, db_path.c_str(), &db);
	if (!s.ok()) {
		cout << "Failed to open leveldb, error message:" << s.ToString() << endl;
		return -1;
	}
	return 0;
}

void LevelDBOp::exec()
{
	int r = init();
	if (r < 0) {
		cout << "Failed to init LevelDBOp." << endl;
		return;
	}

	return;
}

void LevelDBOp::help()
{
}

void LevelDBOp::db_write()
{
	string key = "first";
	string value = "I am the first value";
	Status s = db->Put(WriteOptions(), key, value);
	if (!s.ok()) {
		cout << "Failed to put kv to leveldb" << endl;
		return;
	}

	cout << "Put KV to leveldb successfully" << endl;
	return;
}

void LevelDBOp::db_read()
{
	string key = "first";
	string value;
	Status s = db->Get(ReadOptions(), key, &value);
	if (!s.ok()) {
		cout << "Failed to get kv to leveldb" << endl;
		return;
	}

	cout << "Read from leveldb, Key:" << key << ", Value:" << value << endl;
	return;
}

void LevelDBOp::db_delete()
{
	vector<string> keys;
	leveldb::Iterator *it = db->NewIterator(ReadOptions());
	for (it->SeekToFirst(); it->Valid(); it->Next()) {
		keys.push_back(it->key().ToString());
	}

	vector<string>::iterator iter = keys.begin();
	for (iter; iter != keys.end(); iter++) {
		Status s = db->Delete(WriteOptions(), *iter);
		if (!s.ok()) {
			cout << "Failed to delete key from leveldb" << endl;
			return;
		}

		//cout << "Delete key from leveldb successfully" << endl;
	}
	
	return;
}

void LevelDBOp::db_list()
{
	leveldb::Iterator *it = db->NewIterator(ReadOptions());
	for (it->SeekToFirst(); it->Valid(); it->Next()) {
		//cout << "Key:" << it->key().ToString() << ", Value:" << it->value().ToString() << endl;
		cout << "Key:" << it->key().ToString() << endl;
	}
	delete it;
	return;
}