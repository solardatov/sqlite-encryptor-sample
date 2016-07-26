# sqlite-encryptor-sample
Injecting custom page encryption to SQLite

This sample is based on SQLite amalgamation version 3.13.0. 
You need to have boost 1.60 in home directory to compile this sample without build file changes. Otherwise, feel free to change CMakeLists.txt and specify boost location.
This sample injects simple xor, but you can take, for example, OpenSSL and use AES or any other block cipher for encryption/decryption.

```
$ git clone https://github.com/solardatov/sqlite-encryptor-sample
$ cd sqlite-encryptor-sample/
$ mkdir build
$ cd build/
$ cmake ../ && make
$ ./SQLiteInjector
```

The correct output should look like 
```
SQLite injecting encryption PoC...
sqlite3_open 0
sqlite3_key 0
sqlite3_exec CREATE 0 
sqlite3_exec INSERT 0 
sqlite3_exec INSERT 0 
sqlite3_exec INSERT 0 
sqlite3_exec INSERT 0 
sqlite3_exec INSERT 0 
sqlite3_exec INSERT 0 
sqlite3_exec INSERT 0 
sqlite3_exec INSERT 0 
sqlite3_exec INSERT 0 
sqlite3_exec INSERT 0 
sqlite3_open 0
sqlite3_key 0
	_id = 0 | _text = Test string #0 | 
	_id = 1 | _text = Test string #1 | 
	_id = 2 | _text = Test string #2 | 
	_id = 3 | _text = Test string #3 | 
	_id = 4 | _text = Test string #4 | 
	_id = 5 | _text = Test string #5 | 
	_id = 6 | _text = Test string #6 | 
	_id = 7 | _text = Test string #7 | 
	_id = 8 | _text = Test string #8 | 
	_id = 9 | _text = Test string #9 | 
sqlite3_exec SELECT 0 
```
