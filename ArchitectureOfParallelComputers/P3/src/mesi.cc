/************************************************************
 Course		: 	CSC/ECE506
 Source 		:	mesi.cc
 Owner		:	Ed Gehringer
 Email Id	:	efg@ncsu.edu
 ------------------------------------------------------------*
 © Please do not replicate this code without consulting
 the owner & instructor! Thanks!
 *************************************************************/
#include<iostream>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
using namespace std;
#include "cache.h"

#include "main.h"
#include "mesi.h"
//
void MESI::PrRd(ulong addr, int processor_number) {
    // YOUR CODE HERE
    // The below comments are for reference and might not be
    // sufficient to match the debug runs.
    //
    // Update the Per-cache global counter to maintain LRU
    // order among cache ways, updated on every cache access
    // Increment the global read counter.
    // Check whether the line is cached in the processor cache.
    // If not cached, allocate a fresh line and update the state. (M,E,S,I)
    // Check whether the directory entry is updated. If not updated,
    // create a fresh entry in the directory, update the sharer vector or list.
    // Update the directory state (U, EM, S_).
    // Increment the directory operation counter like signalrds,
    // response_replies etc... Invoke the relevant directory
    // signal functions like signalRd or signalRdX etc...
    // If the line is cached in the processor cache, do not forget
    // to update the LRU
    // Do not forget to update miss/hit counter
    current_cycle++;
    reads++;
    cache_line *line = find_line(addr);

    if (NULL == line) {
        // MISS
        cache_line *newline = allocate_line(addr);
        int no_of_sharers = sharers(addr);
        if (1 <= no_of_sharers) {
            newline->set_state(S);
        } else {
            newline->set_state(E);
        }
        signalRd(addr, processor_number);
        read_misses++;
    } else {
        //HIT
        update_LRU(line);
    }
}
//
void MESI::PrWr(ulong addr, int processor_number) {
    // YOUR CODE HERE
    // Refer comments for PrRd
    current_cycle++;
    writes++;
    cache_state state;
    cache_line *line = find_line(addr);

    if (NULL == line) {
        // MISS
        cache_line *newline = allocate_line(addr);
        newline->set_state(M);
        signalRdX(addr, processor_number);
        write_misses++;
    } else {
        //The Block is cached
        state = line->get_state();
        if (M == state || E == state) {
            line->set_state(M);
            update_LRU(line);
        } else if (S == state) {
            line->set_state(M);
            signalUpgr(addr, processor_number);
            update_LRU(line);
        }
    }
}
//
cache_line * MESI::allocate_line(ulong addr) {
    ulong tag;
    cache_state state;

    cache_line *victim = find_line_to_replace(addr);
    assert(victim != 0);
    state = victim->get_state();
    if (state == M)
        write_back(addr);

    ulong victim_tag = victim->get_tag();
    dir_entry* dir_line = directory->find_dir_line(victim_tag);
    if (dir_line != NULL) {
        dir_line->remove_sharer_entry(cache_num);
        int present = 0;
        present = dir_line->is_cached(num_processors);
        if (!present) {
            dir_line->state = U;
            dir_line->tag = 0;
        }
    }

    tag = tag_field(addr);
    victim->set_tag(tag);
    victim->set_state(I);
    return victim;
}
//
void MESI::signalRd(ulong addr, int processor_number) {
    // YOUR CODE HERE
    // The below comments are for reference and might not be
    // sufficient to match the debug runs.
    //
    // Check the directory state and update the cache2cache counter
    // Update the directory state
    // Update the vector/list
    // Send Intervention or Invalidation
    ulong line_tag = 0;
    cache_line *line = find_line(addr);
    line_tag = line->get_tag();
    dir_entry* dir_line = directory->find_dir_line(line_tag);
    if (NULL != dir_line) {
        if (U == dir_line->get_state()) {
            dir_line->set_dir_state(EM);
            dir_line->add_sharer_entry(processor_number);
        } else if (EM == dir_line->get_state()) {
            dir_line->sendInt_to_sharer(addr, num_processors, processor_number);
            dir_line->set_dir_state(S_);
            dir_line->add_sharer_entry(processor_number);
            cache2cache++;
            signal_rds++;
        } else if (S_ == dir_line->get_state()) {
            dir_line->add_sharer_entry(processor_number);
            signal_rds++;
        }
    } else if (NULL == dir_line) {
        dir_line = directory->find_empty_line(line_tag);
        if (NULL != dir_line) {
            dir_line->set_dir_state(EM);
            dir_line->set_dir_tag(line_tag);
            dir_line->add_sharer_entry(processor_number);
        }
    }
}

void MESI::signalRdX(ulong addr, int processor_number) {
    // YOUR CODE HERE
    // Refer signalRd
    ulong line_tag = 0;
    cache_line *line = find_line(addr);
    line_tag = line->get_tag();
    dir_entry* dir_line = directory->find_dir_line(line_tag);
    if (NULL != dir_line) {
        if (U == dir_line->get_state()) {
            dir_line->set_dir_state(EM);
            dir_line->add_sharer_entry(processor_number);
        } else {
            if (EM == dir_line->get_state()) {
                cache2cache++;
            }
            dir_line->set_dir_state(EM);
            dir_line->add_sharer_entry(processor_number);
            dir_line->sendInv_to_sharer(addr, num_processors, processor_number);
            signal_rdxs++;
        }
    } else if (NULL == dir_line) {
        dir_line = directory->find_empty_line(line_tag);
        if (NULL != dir_line) {
            dir_line->set_dir_state(EM);
            dir_line->set_dir_tag(line_tag);
            dir_line->add_sharer_entry(processor_number);
        }
    }
}

void MESI::signalUpgr(ulong addr, int processor_number) {
    // YOUR CODE HERE
    // Refer signalRd
    ulong line_tag = 0;
    cache_line *line = find_line(addr);
    line_tag = line->get_tag();
    dir_entry* dir_line = directory->find_dir_line(line_tag);
    if (NULL != dir_line) {
        if (U == dir_line->get_state()) {
            cout << "ERROR : signalUpgr when directory entry is U" << endl;
        } else if (EM == dir_line->get_state()) {
            cout << "ERROR : signalUpgr when directory entry is EM" << endl;
        } else if (S_ == dir_line->get_state()) {
            dir_line->sendInv_to_sharer(addr, num_processors, processor_number);
            dir_line->set_dir_state(EM);
            signal_upgrs++;
        }
    } else if (NULL == dir_line) {
        cout << "ERROR : signalUpgr when there is no directory entry" << endl;
    }
}

void MESI::Int(ulong addr) {
    // YOUR CODE HERE
    // The below comments are for reference and might not be
    // sufficient to match the debug runs.
    //
    // Update the relevant counter, if the cache copy is dirty,
    // same needs to be written back to main memory. This is
    // achieved by simply updating the writeback counter
    cache_line *line = find_line(addr);
    interventions++;
    if (M == line->get_state() || E == line->get_state()) {
        write_backs++;
    }
    line->set_state(S);
}

void MESI::Inv(ulong addr) {
    // YOUR CODE HERE
    // Refer Int
    cache_line *line = find_line(addr);
    invalidations++;
    if (M == line->get_state()) {
        write_backs++;
    }
    line->set_state(I);
}
