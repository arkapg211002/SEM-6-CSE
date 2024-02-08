1. Not using `typedef` when dealing with message queue is a better option
2. Using `ftok()` to generate key can lead to errors. Use `(key_t)1234` as key in `msgget()`
