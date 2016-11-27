/************************************************************
 Course		: 	CSC/ECE506
 Source 		:	ssci.cc
 Owner		:	Ed Gehringer
 Email Id	:	efg@ncsu.edu
 ------------------------------------------------------------*
 � Please do not replicate this code without consulting
 the owner & instructor! Thanks!
 *************************************************************/
#include "ssci.h"

void SSCI::add_sharer_entry(int proc_no) {
    cache_list.push_back(proc_no);
}

void SSCI::remove_sharer_entry(int proc_num) {
    // YOUR CODE HERE
    //
    // Remove the entry from the linked list
    cache_list.remove(proc_num);
}

int SSCI::is_cached(int proc_num) {
    // YOUR CODE HERE
    //
    // Return 1 if the linked list is not empty
    // else return 0
    if (!cache_list.empty())
        return 1;
    return 0; // Returning 0 to avoid compilation error
}

void SSCI::sendInv_to_sharer(ulong addr, int num_proc, int proc_num) {
    // YOUR CODE HERE
    //
    // Erase the entry from the list except for the latest entry
    // The latest entry will be for the processor which is invoking
    // this function
    // Invoke the sendInv function defined in the main function
    for (std::list<int>::iterator item = cache_list.begin(); item != cache_list.end(); item++) {
        if ((*item) != proc_num) {
            sendInv(addr, *item);
        }
    }
    cache_list.clear();
    cache_list.push_back(proc_num);
}

void SSCI::sendInt_to_sharer(ulong addr, int num_proc, int proc_num) {
    // YOUR CODE HERE
    //
    // Invoke the sendInv function defined in the main function
    // for all the entries in the list except for proc_num.
    for (std::list<int>::iterator item = cache_list.begin(); item != cache_list.end(); item++) {
        if ((*item) != proc_num) {
            sendInt(addr, *item);
            cache_list.remove(proc_num);
        }
    }
}
