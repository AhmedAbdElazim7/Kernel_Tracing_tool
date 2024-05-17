#include <iostream>
#include <cstdlib>
#include <fstream>

void startTrace() {
    system("sudo /usr/bin/trace-cmd record -o /tmp/trace.dat -e 'syscalls:sys_enter_open' -e 'syscalls:sys_exit_open' -e 'syscalls:sys_enter_read' -e 'syscalls:sys_exit_read' -e 'syscalls:sys_enter_write' -e 'syscalls:sys_exit_write' -e 'syscalls:sys_enter_close' -e 'syscalls:sys_exit_close' -e 'sched:sched_switch' -e 'timer:*'");
}

void stopTrace() {
    system("sudo /usr/bin/trace-cmd stop");
}

void processTraceData() {
    system("sudo /usr/bin/trace-cmd report /tmp/trace.dat > /tmp/trace_data.txt");
    system("sudo chown $(whoami):$(whoami) /tmp/trace_data.txt");
    system("mv /tmp/trace_data.txt ./trace_data.txt");
}

int main() {
    std::cout << "Starting trace..." << std::endl;
    startTrace();

    // Perform some operations to generate trace data
    std::cout << "Performing operations..." << std::endl;
    std::ofstream file("test.txt");
    file << "Hello, World!" << std::endl;
    file.close();

    std::ifstream file_read("test.txt");
    std::string content;
    file_read >> content;
    std::cout << "Read content: " << content << std::endl;
    file_read.close();

    std::cout << "Stopping trace..." << std::endl;
    stopTrace();

    std::cout << "Processing trace data..." << std::endl;
    processTraceData();

    std::cout << "Trace data written to trace_data.txt" << std::endl;
    return 0;
}
