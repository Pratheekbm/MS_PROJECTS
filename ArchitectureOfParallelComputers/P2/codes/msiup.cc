/************************************************************
 Course 		: 	CSC456
 Source 		:	msiup.cc
 Instructor	:	Ed Gehringer
 Email Id	:	efg@ncsu.edu
 ------------------------------------------------------------
 © Please do not replicate this code without consulting
 the owner & instructor! Thanks!
 *************************************************************/

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "cache.h"
#include "main.h"
#include "io_function.h"
#include "msiup.h"
using namespace std;
void MSI_upgrade::PrRd(ulong addr, int processor_number) {
    cache_state state;
    // Per-cache global counter to maintain LRU order among
    // cache ways, updated on every cache access
    current_cycle++;
    reads++;
    cache_line * line = find_line(addr);
    if (line == NULL) {
        // This is a miss
        read_misses++;
        cache_line *newline = allocate_line(addr);
        memory_transactions++;
        // State I --> S
        newline->set_state(S);
        // Read miss --> BusRd
        bus_reads++;
        sendBusRd(addr, processor_number);
    } else {
        // The block is cached
        state = line->get_state();
        if (I == state) {
            // The block is cached, but in invalid state.
            // Hence Read miss
            read_misses++;
            cache_line *newline = allocate_line(addr);
            memory_transactions++;
            // State I --> S
            newline->set_state(S);
            bus_reads++;
            sendBusRd(addr, processor_number);
        } else if ((M == state) || (S == state)) {
            update_LRU(line);
        }
    }
}

void MSI_upgrade::PrWr(ulong addr, int processor_number) {
    current_cycle++;
    writes++;
    cache_line * line = find_line(addr);
    if (line == NULL || line->get_state() == I) {
        /* This is a miss */
        write_misses++;
        cache_line *newline = allocate_line(addr);
        memory_transactions++;
        newline->set_state(M);
        bus_readxs++;
        sendBusRdX(addr, processor_number);
    } else {
        if (M == line->get_state()) {
            /* Since it's a hit, update LRU and update state */
            update_LRU(line);
        } else if (S == line->get_state()) {
            line->set_state(M);
            update_LRU(line);
            bus_upgrades++;
            sendBusRdX(addr, processor_number);
        }

    }
}

cache_line * MSI_upgrade::allocate_line(ulong addr) {
    cache_line *victim = find_line_to_replace(addr);
    assert(victim != 0);
    cache_state state = victim->get_state();
    if (M == state) {
        write_backs++;
        memory_transactions++;
    }
    victim->set_tag(tag_field(addr));
    victim->set_state(I);
    return victim;
}

void MSI_upgrade::BusRd(ulong addr) {
    cache_line * line = find_line(addr);
    if (NULL != line) {
        // If true, it was a hit, so change state appropriately
        if (M == line->get_state()) {
            write_backs++;
            memory_transactions++;
            line->set_state(S);
        } else if (I == line->get_state()) {
            cout << "Error in State - BusRd" << endl;
        }
    }
}

void MSI_upgrade::BusRdX(ulong addr) {
    cache_line * line = find_line(addr);
    if (line != NULL) {
        cache_state state = line->get_state();
        if (state == S || state == I) {
            line->set_state(I);
        } else if (state == M) {
            write_backs++;
            memory_transactions++;
            line->set_state(I);
        }
    }
}

void MSI_upgrade::BusUpgr(ulong addr) {
    cache_line * line = find_line(addr);
    if (line != NULL) {
        cache_state state = line->get_state();
        if (state == S || state == I) {
            line->set_state(I);
        }
    }
}
