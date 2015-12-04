/*
   Copyright 2015 Rachael Harding

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#ifndef _VLL_H_
#define _VLL_H_

#include "global.h"
#include "helper.h"
#include "query.h"

class TxnManager;

class TxnQEntry {
public:
	TxnQEntry * prev;
	TxnQEntry * next;
	TxnManager * 	txn;
};

class VLLMan {
public:
	void init();
  void restartQFront(); 
	void vllMainLoop(TxnManager * next_txn, BaseQuery * query);
	// 	 1: txn is blocked
	//	 2: txn is not blocked. Can run.
	//   3: txn_queue is full. 
	RC beginTxn(TxnManager * txn, BaseQuery * query);
	void finishTxn(TxnManager * txn);
	void execute(TxnManager * txn, BaseQuery * query);
private:
    TxnQEntry * 			_txn_queue;
    TxnQEntry * 			_txn_queue_tail;
	int 					_txn_queue_size;
	pthread_mutex_t 		_mutex;

	TxnQEntry * getQEntry();
	void returnQEntry(TxnQEntry * entry);
};

#endif
