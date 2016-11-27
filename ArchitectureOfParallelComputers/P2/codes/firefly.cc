/************************************************************
 Course         :   CSC456
 Source         :   firefly.cc
 Instructor :   Ed Gehringer
 Email Id   :   efg@ncsu.edu
 ------------------------------------------------------------
 © Please do not replicate this code without consulting
 the owner & instructor! Thanks!
 *************************************************************/
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "main.h"
#include "firefly.h"
using namespace std;

void Firefly::PrRd(ulong addr, int processor_number) {
    current_cycle++;
    reads++;
    cache_line * line = find_line(addr);
    if (line == NULL) {
        read_misses++;
        bus_reads++;
        cache_line *newline = allocate_line(addr);
        if (0 == sharers(addr)) {
            memory_transactions++;
            newline->set_state(V);
        } else {
            cache2cache++;
            newline->set_state(S);
        }
        sendBusRd(addr, processor_number);
    } else {
        update_LRU(line);
    }
}

void Firefly::PrWr(ulong addr, int processor_number) {
    cache_state state;
    current_cycle++;
    writes++;
    cache_line * line = find_line(addr);
    if (line == NULL) {
        /* This is a miss */
        write_misses++;
        bus_reads++;
        memory_transactions++;
        cache_line *newline = allocate_line(addr);
        if (0 == sharers(addr)) {
            newline->set_state(D);
        } else {
            cache2cache++;
            newline->set_state(S);
            bus_writes++;
        }
        sendBusWr(addr, processor_number);
    } else {
        update_LRU(line);
        state = line->get_state();
        if (V == state) {
            line->set_state(D);
        } else if (S == state) {
            memory_transactions++;
            bus_writes++;
            if (1 == sharers(addr)) {
                line->set_state(V);
                sendBusWr(addr, processor_number);
            } else if (0 == sharers(addr)) {
                cout << "This Cannot be happening" << endl;
            } else {
                //DO nothing
            }
        }

    }
}

cache_line * Firefly::allocate_line(ulong addr) {
    cache_line *victim = find_line_to_replace(addr);
    assert(victim != 0);
    cache_state state = victim->get_state();
    if (D == state) {
        write_backs++;
        memory_transactions++;
    }
    victim->set_tag(tag_field(addr));
    victim->set_state(I);
    return victim;
}

void Firefly::BusRd(ulong addr) {
    cache_line * line = find_line(addr);
    if (NULL != line) {
        cache_state state = line->get_state();
        if (V == state) {
            line->set_state(S);
        } else if (D == state) {
            memory_transactions++;
            write_backs++;
            line->set_state(S);
        } else {
            // Do nothing
        }
    }
}

void Firefly::BusWr(ulong addr) {
    cache_line * line = find_line(addr);
    if (NULL != line) {
        cache_state state = line->get_state();
        if (V == state) {
            line->set_state(S);
        } else if (D == state) {
            memory_transactions++;
            line->set_state(S);
        } else {
            line->set_state(S);
        }
    }
}
