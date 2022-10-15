
# Round Robin (RR) Scheduling Algorithm

Modern Operating Systems are moving towards multitasking environments, which mainly depends on the CPU scheduling algorithm since the CPU is the most effective or essential part of the computer. The objective of this project is to examine and understand the round robin scheduling algorithm. We will compare the relationships between the window size (β), quantum (Ω) and context switching (α). The window size (β) is an input integer parameter, which determines the size of the round within RR that is, the number of processes within a single round. The quantum (Ω) is an input integer parameter, which assigns a time interval to be executed within the CPU. The context switching (α) is a parameter to be estimated during the execution of each window size - the number of context switches occurred during the window size.

## Project Goal
Given a set of processes the goal of this project is to implement the round-robin (RR) scheduling algorithm to determine the relationships window size (β), quantum (Ω) and context switching (α) by an extensive study.

The processes will be read from a Process File (PF) where each entry in this file consists of a Process Identification (PID) and CPU Burst Time (CBT). When the algorithm executes the user is promoted to specify the window size and the time quantum. A record of the number of context switches and the total waiting time associated with each process is saved. The turn-around time is then computed using this formula: Turn Around Time = Total waiting time + Burst Time.

The total waiting time is the amount of time the process spends in the queue waiting to be served because it’s time quantum has expired or it still hasn’t reached it turn yet. Context switching is done by enqueuing and denqueuing the processes from the queue. Then the number of contexts is saved using a counter. A process’s CPU burst time might be larger than the quantum, therefore a number of context switches will be required to apply the round robin algorithm. Waiting time will be calculated using counters and saved into a waiting time array having entries for each process. Finally, the turn-around time of each process is saved and outputted to a file. The results are then plotted on a graph. The graph will help us visualize the relationship between quantum size and window size and the turn-around time.

## What is Round-Robin (RR)?
Round-robin (RR) is a scheduling algorithm for processes in an operating system that handles all processes in a cyclic execution manner without any priority. In order to schedule processes fairly, a round-robin scheduler employs time-sharing, giving each job a time slot or quantum, and interrupting the job if it is not completed by then. The job is resumed next time a time slot is assigned to that process. Having no priority guarantees that any system running this algorithm would be starvation free.

<center><img width="226" alt="image" src="https://user-images.githubusercontent.com/2394751/195959545-cd45812f-881a-4f9a-a57a-9c1aca3d76c5.png"></center>

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

![image](https://user-images.githubusercontent.com/2394751/195959840-9f7e38d3-3e90-4a6d-b220-e65f055850b9.png)


