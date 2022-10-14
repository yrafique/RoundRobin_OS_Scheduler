#include <iostream>
#include <fstream>
#include <typeinfo>
#include <sstream>
using namespace std;

#define DEBUG_MODE 1

// Process struct to hold an individual process.
typedef struct Process {
	int PID;
	int burst;
	Process *link;

	// Custom Initializer (Constructor)
	Process (int _PID,int _burst){
		burst	= _burst;
		PID		= _PID;
		link	= 0;
	}

	// Default Initializer (Constructor)
	Process (){
		burst	= 0 ;
		PID		= 0 ;
		link	= 0;
	}
};


/*
//	Queue Class implemenetation
*/
class Queue {
private:
	int count;
	Process *head,*tail,*temp;

public:
	Queue(){
		count= 0;
		head = 0;
		tail = 0;
		temp = 0;
	}

//	Enqueue Function
//	Takes a process and FIFO's it into the queue
//	Note: allocated a new temp to NOT mess around with their pointers much.
	void enqueue(Process *p){
		count++;
		if (!head){
			temp = new Process(p->PID,p->burst);
			tail = temp;
			head = temp;
		}
		else {
			temp = new Process(p->PID,p->burst);
			tail->link = temp;
			tail = temp;
		}
	}
	

//	Dequeue Function:
//	takes a reference to a Process as an argument which will be used to store the dequeue'd process.
	bool dequeue (Process* &p){
		if (!head)
			return false;

		else {
			count--;
			temp	= head;
			p->burst= head->burst;
			p->PID	= head->PID;
			head	= head->link;
			delete temp;
			return true;
		}
	}

// Print Queue to file. straight-forward.
	void printQueue(ofstream &output){
		output<<"Printing Queue"<<endl;
		Process *p = new Process();
		Queue q;

		while (dequeue(p)){
			output<<"Process ID = "<<p->PID<<" With CPU Burst = "<<p->burst<<endl;
			q.enqueue(p);
		}
		output<<endl;
		/*bool flag = q.dequeue(p);;
		while (flag == true){
			enqueue(p);
			flag = q.dequeue(p);
		}*/
		while (q.dequeue(p))
			enqueue(p);
		delete p;
	}

	int elementCount(){
		return count;
	}
	
	// Basically, to calculate waiting time, increment every process in the round robin except the currently executing process.
	// Simple and highly ineffecient :)
	void waitingTimeCalculation(int _PID, int waiting[], int quantum){
		Process *p = new Process();
		Queue q;
		while (dequeue(p)){
			if (p->PID != _PID)
				waiting[p->PID]+= quantum;
			q.enqueue(p);
		}

		/*bool flag = q.dequeue(p);;
		while (flag == true){
			enqueue(p);
			flag = q.dequeue(p);
		}*/
		while (q.dequeue(p))
			enqueue(p);
	}


	~Queue(){
		Process *p = new Process();
		int number_of_elements = elementCount();
		for (int i=0; i<number_of_elements; i++)
			dequeue(p);
		delete p;
	}
};


// Function Prototypes
string get_output_name(int, int);
float calcuate_average(int [], float);
void print_output_file(Process *[],int , int [], int [], int [], ofstream &);

/*
//	Main.cpp
*/
int main(){

	ifstream fin("PF.txt");
	Process **processes_array;	// An dyarray of type _Process_.
	int *waiting_time, *turnaround_time, *context_switch_counter;

	ofstream fout;
	ofstream summary_output;
	summary_output.open("Summary.txt");

	// Read number of process and allocate array memory for the processes./
	float   number_of_processes;
	fin >>  number_of_processes;

	processes_array			= new Process *[number_of_processes]  ;
	turnaround_time			= new int	   [number_of_processes]  ;

	int id,burst;
	Process *temp;

	//	Store processes into the array
	for (int i=0; i<number_of_processes; i++){
		fin>>id>>burst;
		temp = new Process(id,burst);
		processes_array[i] = temp;
	}

	int window_size;
	cout<<"Enter Window Size:"<<endl;
	cin >>window_size;

	int quantum_time;
	cout<<"Enter Quantum Time:"<<endl;
	cin >>quantum_time;


	for (; window_size<100; window_size+=10)
	{
		string output_name = get_output_name(window_size,quantum_time); 
		fout.open(output_name.c_str());
		fout<<"Number Of Processes: "<<number_of_processes<<endl;
		fout<<"Window Size: "		 <<window_size		  <<endl;
		fout<<"Quantum Time: "		 <<quantum_time		  <<endl;
		fout<<"Press Ctrl + End to jump to time calculations"	<<endl;
		fout<<"================================================"<<endl;

		int counter = 0;
		int time	= 0;
		Queue *q	= new Queue();
		context_switch_counter
					= new int [number_of_processes]();
		waiting_time= new int [number_of_processes]();

		cout<<"***	Writing To File!	***"<<endl;

		// Begin scheduling.
		while (counter < number_of_processes)
		{
			//cout<<" type of array = "<< typeid(p).name();
			if (DEBUG_MODE)
				fout<<"======= New Batch at time = "<<time<<" ========"<<endl;

			// Insert elements into the round robin queue.
			for (int i=0; i<window_size; i++){
				q->enqueue(processes_array[counter]);
				counter++;
				if (counter == number_of_processes)
					break;	// No more processes to execute the array.
			}

			if (DEBUG_MODE)
				q->printQueue(fout);

			Process *p = new Process();

			while (q->elementCount() > 0){
				if (DEBUG_MODE)
					fout<<"Queue size = "<<q->elementCount()<<endl;

				q->dequeue(p);
				context_switch_counter[p->PID]++;
				/*if (p->burst == processes_array[p->PID]->burst)
					waiting_time[p->PID] = time;*/
				q->waitingTimeCalculation(p->PID,waiting_time,quantum_time);

				p->burst -= quantum_time;
				time	 += quantum_time;
				if (DEBUG_MODE)
					fout<<"At time = "<<time<<" With id = "<<p->PID<<" and burst = "<<p->burst<<endl<<endl;

				if (p->burst > 0)
					q->enqueue(p);
				else
					turnaround_time[p->PID] = time;
			}
		}

		if (DEBUG_MODE){
			fout<<"Average Waiting Time = "     <<calcuate_average(waiting_time,number_of_processes)		  <<endl;
			fout<<"Average Turn-around Time = " <<calcuate_average(turnaround_time,number_of_processes)		  <<endl;
			fout<<"Average Context Switching = "<<calcuate_average(context_switch_counter,number_of_processes)<<endl;
		}
		else
			print_output_file(processes_array, number_of_processes, waiting_time, turnaround_time, context_switch_counter, fout);

		cout<<"***	 Done	***"<<endl;
		fout.close();

		summary_output<<"For window size = "<<window_size<<" and quantum time = "<<quantum_time<<endl;
		summary_output<<"Average Waiting Time = "    <<calcuate_average(waiting_time,number_of_processes)			<<endl;
		summary_output<<"Average Turn-around Time = "<<calcuate_average(turnaround_time,number_of_processes)		<<endl;
		summary_output<<"Average Context Switching = "<<calcuate_average(context_switch_counter,number_of_processes)<<endl;
		summary_output<<"========================================================"<<endl;

		// Quick Clean-up, return malloc'd space
		q->~Queue();
		delete context_switch_counter;
	} // For loop

	delete temp;
	summary_output.close();
	return 0;
}


//	get_output_name
//	Function to calculate a unique file name using the window_size and quantum_time
//  return: output filename string
string get_output_name(int ws, int qt){

	string window_size_string, quantum_time_string;
	stringstream out1,out2;
	out1 << ws;
	window_size_string = out1.str();
	
	out2 << qt;
	quantum_time_string = out2.str();
	
	string output_file_name = "";
	output_file_name += "window=";
	output_file_name += window_size_string;
	output_file_name += ", quantum=";
	output_file_name += quantum_time_string;
	output_file_name += ".txt";
	
	return output_file_name;
}

float calcuate_average(int arr[],float total)
{
	float sumation = 0;
	for (int i=0; i<total; i++)
		sumation += arr[i];
	return sumation/(float)total;
}

// Prints each process with its various attributes
void print_output_file(Process *p_array[],int number, int wait[], int turnaround[], int context[], ofstream &output)
{
	for (int i=0; i<number; i++){
		output<<"Process id = "<<p_array[i]->PID<<", Burst = "<<p_array[i]->burst<<", Waiting time = "
		<<wait[i]<<", Turnaround time = "<<turnaround[i]<<" and Number of context switches = "<<context[i]<<endl;
	}
}
