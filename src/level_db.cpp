#include <leveldb/slice.h>
#include <leveldb/options.h>
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

	db_path = "/root/.hqx01_kv";
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

	string marker;
	bool truncated = true;
	while (truncated) {
		
	}

	return;
}

void LevelDBOp::help()
{
	cout << "Support Commands:" << endl;
	cout << " test       test leveldb interfaces" << endl;
}

int LevelDBOp::db_write(string key, string value)
{
	Status s = db->Put(WriteOptions(), key, value);
	if (!s.ok()) {
		cout << "Failed to put kv to leveldb" << endl;
		return -1;
	}
	return 0;
}

int LevelDBOp::db_read(string key, string &value)
{
	Status s = db->Get(ReadOptions(), key, &value);
	if (!s.ok()) {
		cout << "Failed to get kv to leveldb" << endl;
		return -1;
	}
	return 0;
}

int LevelDBOp::db_delete()
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
			return -1;
		}

		//cout << "Delete key from leveldb successfully" << endl;
	}
	
	return 0;
}

void LevelDBOp::db_list(string marker)
{
	leveldb::Iterator *it = db->NewIterator(ReadOptions());
	if (marker.empty()) {
		it->SeekToFirst();
	} else {
		it->Seek(Slice(marker));
	}

	for (; it->Valid(); it->Next()) {
		//cout << "Key:" << it->key().ToString() << ", Value:" << it->value().ToString() << endl;
		cout << "Key:" << it->key().ToString() << endl;
	}
	delete it;
	return;
}

void LevelDBOp::db_list(map<string, string > &out, int max, string &marker, bool &truncated)
{
	int cnt = 0;
	leveldb::Iterator *it = db->NewIterator(ReadOptions());
	if(marker.empty()) {
		it->SeekToFirst();
	} else {
		it->Seek(Slice(marker));
	}
	
	while (it->Valid() && cnt < max) {
		out[it->key().ToString()] = it->value().ToString();

		it->Next();
		cnt++;

		if (cnt == max) {
			if (it->Valid()) {
				marker = it->key().ToString();
				truncated = true;
			} else {
				truncated = false;
			}
			break;
		}

		if (!it->Valid()) {
			truncated = false;
			break;
		}
	}

	delete it;
	it = NULL;
}