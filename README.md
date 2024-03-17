# CSL204 Operating Systems Lab Codes

Welcome to the CSL204 Operating Systems Lab Codes repository! Here you can find my tried-out codes for the BTech Program Course CSL204 Operating Systems Lab.

## About CSL204 Operating Systems Lab

This course focuses on providing practical experience in understanding and implementing various concepts and algorithms in operating systems. From system calls to deadlock avoidance, the course covers a wide range of topics aimed at providing hands-on experience in operating system principles.

## Course Outcomes

1. Understand the use of system calls in operating systems.
2. Apply process creation and inter-process communication concepts.
3. Implement CPU scheduling algorithms including FCFS, SJF, RR, and priority-based scheduling.
4. Apply page replacement algorithms such as FIFO, LRU, and LFU.
5. Apply deadlock detection and avoidance techniques.
6. Apply storage management and disk scheduling techniques.


## Content
  ### Week 0
  Practice Tutorials

  ### Cycle_1
  Shell Programs 
    Questions
      1. Write a shell script to show various system configurations like
        a) your OS and version, release number, kernel version
        b) all available shells
        c) computer CPU information like processor type, speed, etc
        d) memory information
        e) hard disk information like size of hard disk, cache memory, model, etc
        f) File system (Mounted)
      2. Write a shell script to implement a menu-driven calculator with the following functions
        a) Addition
        b) Subtraction
        c) Multiplication
        d) Division
        e) Modulus
      3. Write a shell script to print the n terms in a Fibonacci Series.
      4. Write a shell script to read a file and search for the occurrence of a particular word in it.
      5. Write a shell script that accepts two numbers as command line arguments and prints all the palindrome numbers between the given two numbers

  ### Cycle_2
  System Calls
    Questions
      1. Write a program which creates a child process and the parent process waits for the child process to exit after printing the process id of the child and             parent process. (Use: fork, wait, getpid, getppid, exit System Calls).
      2. Write a program where a parent process creates a child process and then the child process loads another program to add two numbers into its memory space.           The parent process should wait for the child process to exit. (Use: fork, execlp, wait, exit System calls).
      3. Write a program which opens the directory in which it is executed, reads the file contained in it and displays the status of each file contained in                 it(Use: opendir, readdir, closedir and stat System calls)
      4. Write a program to create a file, write some data to it and then read from it. (Use: open, write, read and close System Calls).

  ### Cycle_3
  CPU Scheduling
    Questions
      1. First Come First Serve
      2. Shortest Job First
      3. Priority Scheduling
      4. Round Robin
      
