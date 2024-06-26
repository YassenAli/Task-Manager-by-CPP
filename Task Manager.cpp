// Purpose: Task Manager.
// Author: Yassin Ali Mamdouh
// Date: 6 Dec 2023

#include <bits/stdc++.h>

#ifdef _WIN32
#include <windows.h>
#elif __linux__
#include <cstdlib>
#endif

using namespace std;

// Class representing a process
class Process {
private:
    // Process attributes
    string name;
    string MemoryUsage;
    string Session_Name;
    int PID, Session_Number;
    float CPU, MEM;
    int VSZ, RSS;
    string TTY, STAT, START, TIME, COMMAND;

public:
    // Constructors for different cases
    Process();
    Process(string n, int p, string m);
    Process(string n, int p, string m, string SName, int SNum);
    Process(string n, int p, float cpu, float mem, int vsz, int rss, string tty, string stat, string start,
            string time, string command);

    // Setter methods
    void setName(string n);
    void setPid(int p);
    void setMem(string m);

    // Getter methods
    string getName();
    int getPid();
    int getMem();

    // Methods to print process information
    void printProcess();
    void printProcessWithOtherInfo();
};

// Default constructor
Process::Process() {}

// Constructor for name, PID, and memory usage
Process::Process(string n, int p, string m) : name(n), PID(p), MemoryUsage(m) {}

// Constructor for name, PID, memory usage, session name, and session number
Process::Process(string n, int p, string m, string SName, int SNum) : name(n), PID(p), MemoryUsage(m),
                                                                      Session_Name(SName),
                                                                      Session_Number(SNum) {}

// Constructor for detailed process information
Process::Process(string n, int p, float cpu, float mem, int vsz, int rss, string tty, string stat, string start,
                 string time, string command) : name(n), PID(p), CPU(cpu), MEM(mem), VSZ(vsz), RSS(rss), TTY(tty),
                                                STAT(stat), START(start), TIME(time), COMMAND(command) {}

// Setter for process name
void Process::setName(string n) {
    name = n;
}

// Setter for process PID
void Process::setPid(int p) {
    PID = p;
}

// Setter for process memory usage
void Process::setMem(string m) {
    MemoryUsage = m;
}

// Getter for process name
string Process::getName() {
    return name;
}

// Getter for process memory usage (converted to integer)
int Process::getMem() {
    int mem = 0;
    for (int i = 0; i < MemoryUsage.size(); ++i) {
        if (MemoryUsage[i] == ',') continue;
        mem += (MemoryUsage[i] - '0') * pow(10, MemoryUsage.size() - i);
    }
    return mem;
}

// Getter for process PID
int Process::getPid() {
    return PID;
}

// Method to print basic process information
void Process::printProcess() {
    cout << "Name : " << name << '\t' << "     PID : " << PID << '\t' << '\t' << "MemoryUsage : " << MemoryUsage
         << " k\n";
}

// Method to print detailed process information based on the operating system
void Process::printProcessWithOtherInfo() {
#ifdef _WIN32
    cout << setw(30) << name
         << setw(8) << PID
         << setw(16) << Session_Name
         << setw(12) << Session_Number
         << setw(12) << MemoryUsage << " K"
         << endl;
#elif __linux__
    cout << left << setw(12) << name
          << setw(5) << PID
          << setw(5) << CPU
          << setw(5) << MEM
          << setw(7) << VSZ
          << setw(6) << RSS
          << setw(8) << TTY
          << setw(6) << STAT
          << setw(7) << START
          << setw(5) << TIME
          << setw(15) << COMMAND
          << endl;
#endif
}

// Class representing a list of processes
class ProcessList {
private:
    // Vector to store processes
    vector<Process> processes;

public:
    // Constructors
    ProcessList();
    ProcessList(const string &filename);

    // Method to add a process to the list
    void add_process(const Process &p);

    // Methods to sort the list based on different criteria
    void sort_by_name();
    void sort_by_pid();
    void sort_by_mem();

    // Method to print the list
    void printList();
    void printListFromFile();

    // Method to get the list of processes from the operating system
    void get_from_OS(const string &filename);
};

// Default constructor for ProcessList
ProcessList::ProcessList() {}

// Method to add a process to the list
void ProcessList::add_process(const Process &p) {
    processes.push_back(p);
}

// Method to sort the list of processes by name
void ProcessList::sort_by_name() {
    sort(processes.begin(), processes.end(),
         [](Process first, Process second) { return first.getName() < second.getName(); });
}

// Method to sort the list of processes by PID
void ProcessList::sort_by_pid() {
    sort(processes.begin(), processes.end(),
         [](Process first, Process second) { return first.getPid() < second.getPid(); });
}

// Method to sort the list of processes by memory usage
void ProcessList::sort_by_mem() {
    sort(processes.begin(), processes.end(),
         [](Process first, Process second) { return first.getMem() < second.getMem(); });
}

// Method to print the list of processes
void ProcessList::printList() {
    for (auto &process: processes)
        process.printProcess();
}

// Method to print the list of processes with additional information based on the operating system
void ProcessList::printListFromFile() {
#ifdef _WIN32
    cout << left << setw(30) << "Image Name"
         << setw(8) << "PID"
         << setw(16) << "Session Name"
         << setw(12) << "Session#"
         << setw(12) << "Mem Usage"
         << endl << "========================= ======== ================ =========== ============\n";
#elif __linux__
    cout << left << setw(12) << "USER"
          << setw(5) << "PID"
          << setw(5) << "%CPU"
          << setw(5) << "%MEM"
          << setw(7) << "VSZ"
          << setw(6) << "RSS"
          << setw(8) << "TTY"
          << setw(6) << "STAT"
          << setw(7) << "START"
          << setw(5) << "TIME"
          << setw(15) << "COMMAND"
          << endl;
#endif
    for (auto &process: processes)
        process.printProcessWithOtherInfo();
}

// Method to get the list of processes from the operating system
void ProcessList::get_from_OS(const string &filename) {
    string command;
#ifdef _WIN32
    command = "tasklist > " + filename;
#elif __linux__
    command = "ps aux > " + filename;
#endif
    system(command.c_str());
}

// Constructor that initializes the ProcessList by getting the list of processes from the OS
ProcessList::ProcessList(const string &filename) {
    // Get the list of processes from the OS
    get_from_OS(filename);
    ifstream file(filename);
    string line;
    string Name;
    string Mem_Usage;
    string Session_Name;
    int PID, Session_Num;
    float CPU, MEM;
    int VSZ, RSS;
    string TTY, STAT, START, TIME, COMMAND;

#ifdef _WIN32
    // Skip header lines in the Windows output(new line)
    getline(file, line);
#endif
    getline(file, line); // Skip another line
    getline(file, line); // Skip another line
    getline(file, line); // Skip the line of System Idle Process

    // Add a special process to represent "System Idle Process" with PID 0 and default memory usage
    add_process(Process("System Idle Process", 0, "8", "Services", 0));

    // Read the file line by line and create Process objects
    while (getline(file, line)) {
        istringstream iss(line);
#ifdef _WIN32
        iss >> Name >> PID >> Session_Name >> Session_Num >> Mem_Usage;
        add_process(Process(Name, PID, Mem_Usage, Session_Name, Session_Num));
#elif __linux__
        // Read process information from the Linux output
        iss >> Name >> PID >> CPU >> MEM >> VSZ >> RSS >> TTY >> STAT >> START >> TIME >> COMMAND;
        add_process(Process(Name, PID, CPU, MEM, VSZ, RSS, TTY, STAT, START, TIME, COMMAND));
#endif
    }

    file.close();
}

// Main function
int main() {
    // Create an instance of ProcessList
    ProcessList taskManager;

    // Add processes to the list
    taskManager.add_process(Process("cProcess1", 1234, "1024"));
    taskManager.add_process(Process("bProcess2", 5678, "208"));
    taskManager.add_process(Process("aProcess3", 11, "4096"));

    // Print the unsorted list
    cout << "Unsorted List:\n";
    taskManager.printList();

    // Sort and print the list by name
    taskManager.sort_by_name();
    cout << "\nSorted by Name:\n";
    taskManager.printList();

    // Sort and print the list by PID
    taskManager.sort_by_pid();
    cout << "\nSorted by PID:\n";
    taskManager.printList();

    // Sort and print the list by memory usage
    taskManager.sort_by_mem();
    cout << "\nSorted by Memory Usage:\n";
    taskManager.printList();

    // Take a file from the OS and print the list with additional information
    cout << "Please input the file name to write the task manager output: ";
    string fileName;
    cin >> fileName;
    ProcessList taskManagerOnWindows(fileName);

    // Print the unsorted list with additional information
    cout << "Unsorted List:\n";
    taskManagerOnWindows.printListFromFile();

    // Sort and print the list by name with additional information
    taskManagerOnWindows.sort_by_name();
    cout << "\nSorted by Name:\n";
    taskManagerOnWindows.printListFromFile();

    // Sort and print the list by PID with additional information
    taskManagerOnWindows.sort_by_pid();
    cout << "\nSorted by PID:\n";
    taskManagerOnWindows.printListFromFile();

    // Sort and print the list by memory usage with additional information
    taskManagerOnWindows.sort_by_mem();
    cout << "\nSorted by Memory Usage:\n";
    taskManagerOnWindows.printListFromFile();

    return 0;
}
