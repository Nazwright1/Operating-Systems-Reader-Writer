# Operating-Systems-Reader-Writer
Reader-Writer is a classic synchronization problem where a data structure, database or files are being read and or written to by concurrent processes or threads.
There are some constraints for this problem:
1. Any number of readers can be in the critical section executing code simultaneously.
2. The writer threads must have exclusive access in the critical section.
