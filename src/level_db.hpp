#ifndef _SONGZI_LEVEL_DB_H_
#define _SONGZI_LEVEL_DB_H_

#include "op/op.hpp"
#include <string>
#include <leveldb/db.h>

class LevelDBOp : public Op {
private:
	leveldb::DB *db;
	std::string db_path;
public:
	LevelDBOp(Argument *argument):Op(argument, "leveldb", "test leveldb operation"),db(NULL) {
		db_path = "/home/songzi/store.db-error";
		//db_path = "/home/songzi/program/src/leveldb";
	}
	~LevelDBOp(){
		if (db) {
			delete db;
			db = NULL;
		}
	}
	virtual void exec();
	virtual void help();
	int init();
	void db_write();
	void db_read();
	void db_delete();
	void db_list();
};

#endif