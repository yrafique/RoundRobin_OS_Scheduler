
# Round Robin (RR) Scheduling Algorithm

The goal of this project is to explore the relationships between the window size (β), quantum (Ω) and context switching (α) while using a round-robin scheduling algorithm. The round-robin (RR) scheduling algorithm should be examined and understood so that a team can determine how to study the relationships between β, Ω, and α.

The software is coded with capability to read the process-file (PF), which contains a list of processes. Each process has a process identification (PI) and CPU burst time (CBT). All data is stored in a dynamically allocated data structure (program should be able to take in any number of processes with their burst time). The window size (β) is an input integer parameter, which determines the size of the round within RR – the number of processes within a single round. The quantum (Ω) is an input integer parameter, which assigns a time interval to be executed within the CPU. The context switching (α) is a parameter to be estimated during the execution of each window size - the number of context switches occurred during the window size.

The program calculates the turnaround time and waiting time of all finished processes. Data can then be used to analyze the relationships of the following:

1. Window size (x-axis) versus average turnaround time for all quanta.
2. Window size (x-axis) versus average waiting time for all quanta.
3. Window size (x-axis) versus quantum – exploring the context switching.

## What is Round-Robin (RR)?
Round-robin (RR) is a scheduling algorithm for processes in an operating system that handles all processes in a cyclic execution manner without any priority. In order to schedule processes fairly, a round-robin scheduler employs time-sharing, giving each job a time slot or quantum, and interrupting the job if it is not completed by then. The job is resumed next time a time slot is assigned to that process. Having no priority guarantees that any system running this algorithm would be starvation free.

First, a dynamic one-dimensional array will be used to store all the processes, which will be read from a file. Each entry in the array will be of type "Process". Second, a queue will be used to implement the round-robin with each entry of type "Process", and each "Process" will use its pointer to point to the next process using the First in First out (FIFO) criteria. The window size will be defined as the maximum size of the queue and quantum time will be defined as the length a process will "circulate" in the queue before being permanently dequeued and context switching will be defined as the overhead for the enqueue and dequeue operations for each process until no process is left in the array.

The processes will be loaded from the array to the Round-Robin Queue whose size will be the window size. Then, processes will be dequeued and their respective burst times will be deducted by the quantum time, if the process burst is larger than zero, only then will the process be enqueued back to the Round-Robin Queue. After finishing the processes in the queue, the algorithm will go back and reload processes from the array to the queue until no process is left in the array and so on.


## Implementation
Two major data structures are used to implement the RR algorithm. A new type will be defined using structs (typedefs), which will be called a "Process", that will hold the process number (or ID) as an integer, another integer to hold its cycle burst and a pointer to type "Process" which will be discussed later.

### Inputs:
- Number of Processes from file • Process ID from file
- Process Burst from file
- Quantum Size from user
- Window Size from user

### Outputs:
- Average Waiting Time
- Average Turn Around Time
- Average Context Switching
- Waiting Time of each Process
- Turn Around Time of each Process
- Number of Context Switches of each Process

### Data structures: 
- Queue
- Dynamic Arrays
- Structs

