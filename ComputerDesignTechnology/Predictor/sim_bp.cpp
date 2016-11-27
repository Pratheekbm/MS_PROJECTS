/*
 * sim_bp.cpp
 *
 *  Created on: Mar 23, 2015
 *      Author: Pratheek
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include "castTypes.h"
#include "cache.h"
#include "predictor.h"
using namespace std;

int main(int argc, char *argv[]) {

    if (2 <= argc) {
        string bpType = argv[1];

        if ("bimodal" == bpType) {
            if (6 != argc) {
                ERROR_LOG;
                cout << "Input Format" << endl;
                cout << "sim bimodal <M2> <BTB size> <BTB assoc> <tracefile>" << endl;
            } else {
                FILE *myFile;
                char given;
                int totalBrances = 0;
                int totalPredictions = 0;
                int missPredictions = 0;
                int branchMisses = 0;
                SWING swing = MISS;
                int M2 = atoi(argv[2]);
                int BTBSize = atoi(argv[3]);
                int BTBAssos = atoi(argv[4]);

                Cache BTB(CACHE_L1, BTBAssos, BTBSize, 4, LRU, NONINCLUSION);
                Predictor bimodal(M2, 0);

                myFile = fopen((char *) argv[5], "r");
                long int address;
                if (!myFile) {
                    cout << "\n Error in file";
                } else {
                    DECISION predicted;
                    DECISION actual = NOTTAKEN;
                    while (fscanf(myFile, "%lx %c", &address, &given) != EOF) {
                        if ('t' == given) {
                            actual = TAKEN;
                        } else if ('n' == given) {
                            actual = NOTTAKEN;
                        }

                        if ((0 != BTBSize) || (0 != BTBAssos)) {
                            swing = BTB.read(address);
                        } else {
                            swing = HIT;
                        }

                        if (MISS == swing) {
                            if (TAKEN == actual) {
                                branchMisses++;
                            }
                        } else {
                            predicted = bimodal.predict(address);
                            bimodal.updatePTable(address, actual);
                            totalPredictions++;
                            if (actual != predicted) {
                                missPredictions++;
                            }
                        }
                        totalBrances++;
                    }
                    cout << "COMMAND" << endl;
                    cout << "./sim" << " " << argv[1] << " " << argv[2] << " " << argv[4] << " " << argv[5] << endl;
                    cout << "OUTPUT" << endl;
                    if ((0 != BTBSize) || (0 != BTBAssos)) {
                        cout << "size of BTB:\t " << BTBSize << endl;
                        cout << "number of branches:\t" << totalBrances << endl;
                        cout << "number of predictions from branch predictor:\t" << totalPredictions << endl;
                        cout << "number of mispredictions from branch predictor:\t" << missPredictions << endl;
                        cout << "number of branches miss in BTB and taken:\t " << branchMisses << endl;
                        cout << "total mispredictions:\t" << (int) (missPredictions + branchMisses) << endl;
                        if (0 != missPredictions) {
                            cout << fixed << std::setprecision(2) << "misprediction rate:\t"
                                    << (float) (missPredictions + branchMisses) * 100 / (float) (totalBrances) << "%"
                                    << endl;
                        }
                        cout << endl;
                        cout << "FINAL BTB CONTENTS" << endl;
                        BTB.print();
                        cout << endl;
                        cout << "FINAL BIMODAL CONTENTS" << endl;
                        bimodal.print();
                    } else {
                        cout << "number of predictions:\t" << totalPredictions << endl;
                        cout << "number of mispredictions:\t" << missPredictions << endl;
                        if (0 != missPredictions) {
                            cout << fixed << std::setprecision(2) << "misprediction rate:\t"
                                    << (float) missPredictions * 100 / (float) (totalPredictions) << "%" << endl;
                        }
                        cout << "FINAL BIMODAL CONTENTS" << endl;
                        bimodal.print();
                    }
                }

            }
        } else if ("gshare" == bpType) {
            if (7 != argc) {
                ERROR_LOG;
                cout << "Input Format" << endl;
                cout << "sim gshare <M1> <N> <BTB size> <BTB assoc> <tracefile>" << endl;
            } else {
                FILE *myFile;
                char given;
                int totalBrances = 0;
                int totalPredictions = 0;
                int missPredictions = 0;
                int branchMisses = 0;
                SWING swing = MISS;
                int M1 = atoi(argv[2]);
                int N = atoi(argv[3]);
                int BTBSize = atoi(argv[4]);
                int BTBAssos = atoi(argv[5]);

                Cache BTB(CACHE_L1, BTBAssos, BTBSize, 4, LRU, NONINCLUSION);
                Predictor gshareBp(M1, N);

                myFile = fopen((char *) argv[6], "r");
                long int address;
                if (!myFile) {
                    cout << "\n Error in file";
                } else {
                    DECISION predicted;
                    DECISION actual = NOTTAKEN;
                    while (fscanf(myFile, "%lx %c", &address, &given) != EOF) {
                        if ('t' == given) {
                            actual = TAKEN;
                        } else if ('n' == given) {
                            actual = NOTTAKEN;
                        }
                        if ((0 != BTBSize) || (0 != BTBAssos)) {
                            swing = BTB.read(address);
                        } else {
                            swing = HIT;
                        }

                        if (MISS == swing) {
                            if (TAKEN == actual) {
                                branchMisses++;
                            }
                        } else {
                            predicted = gshareBp.predict(address);
                            gshareBp.updatePTable(address, actual);
                            gshareBp.updateHistory(address, actual);
                            totalPredictions++;
                            if (actual != predicted) {
                                missPredictions++;
                            }
                        }
                        totalBrances++;
                    }
                    cout << "COMMAND" << endl;
                    cout << "./sim" << " " << argv[1] << " " << argv[2] << " " << argv[4] << " " << argv[5] << " "
                            << argv[6] << endl;
                    cout << "OUTPUT" << endl;
                    if ((0 != BTBSize) || (0 != BTBAssos)) {
                        cout << "size of BTB:\t " << BTBSize << endl;
                        cout << "number of branches:\t" << totalBrances << endl;
                        cout << "number of predictions from branch predictor:\t" << totalPredictions << endl;
                        cout << "number of mispredictions from branch predictor:\t" << missPredictions << endl;
                        cout << "number of branches miss in BTB and taken:\t " << branchMisses << endl;
                        cout << "total mispredictions:\t" << (int) (missPredictions + branchMisses) << endl;
                        if (0 != missPredictions) {
                            cout << fixed << std::setprecision(2) << "misprediction rate:\t"
                                    << (float) (missPredictions + branchMisses) * 100 / (float) (totalBrances) << "%"
                                    << endl;
                        }
                        cout << endl;
                        cout << "FINAL BTB CONTENTS" << endl;
                        BTB.print();
                        cout << endl;
                        cout << "FINAL GSHARE CONTENTS" << endl;
                        gshareBp.print();
                    } else {
                        cout << "number of predictions:\t" << totalPredictions << endl;
                        cout << "number of mispredictions:\t" << missPredictions << endl;
                        if (0 != missPredictions) {
                            cout << fixed << std::setprecision(2) << "misprediction rate:\t"
                                    << (float) missPredictions * 100 / (float) (totalPredictions) << "%" << endl;
                        }
                        cout << "FINAL GSHARE CONTENTS" << endl;
                        gshareBp.print();
                    }
                }
            }
        } else if ("hybrid" == bpType) {
            if (9 != argc) {
                ERROR_LOG;
                cout << "Input Format" << endl;
                cout << "sim hybrid <K> <M1> <N> <M2> <BTB size> <BTB assoc> <tracefile>" << endl;
            } else {
                FILE *myFile;
                char given;
                int totalBrances = 0;
                int totalPredictions = 0;
                int missPredictions = 0;
                int branchMisses = 0;
                SWING swing = MISS;
                int k = atoi(argv[2]);
                int M1 = atoi(argv[3]);
                int N = atoi(argv[4]);
                int M2 = atoi(argv[5]);
                int BTBSize = atoi(argv[6]);
                int BTBAssos = atoi(argv[7]);

                Cache BTB(CACHE_L1, BTBAssos, BTBSize, 4, LRU, NONINCLUSION);
                Predictor hybrid(k, 0);
                Predictor gshareBp(M1, N);
                Predictor bimodal(M2, 0);

                hybrid.resetPtable(1);

                myFile = fopen((char *) argv[8], "r");
                long int address;
                if (!myFile)
                    cout << "\n Error in file";
                else {
                    DECISION predicted, bimodalPredicted, gsharePredicted;
                    PREDICTOR hybridChoice;
                    DECISION actual = NOTTAKEN;
                    while (fscanf(myFile, "%lx %c", &address, &given) != EOF) {
                        if ('t' == given) {
                            actual = TAKEN;
                        } else if ('n' == given) {
                            actual = NOTTAKEN;
                        }

                        if ((0 != BTBSize) || (0 != BTBAssos)) {
                            swing = BTB.read(address);
                        } else {
                            swing = HIT;
                        }

                        if (MISS == swing) {
                            if (TAKEN == actual) {
                                branchMisses++;
                            }
                        } else {
                            bimodalPredicted = bimodal.predict(address);
                            gsharePredicted = gshareBp.predict(address);

                            hybridChoice = (PREDICTOR) hybrid.predict(address);

                            if (BIMODAL == hybridChoice) {
                                predicted = bimodalPredicted;
                                bimodal.updatePTable(address, actual);
                            } else if (GSHARE == hybridChoice) {
                                predicted = gsharePredicted;
                                gshareBp.updatePTable(address, actual);
                            } else {
                                ERROR_LOG;
                            }
                            gshareBp.updateHistory(address, actual);

                            if (actual == gsharePredicted) {
                                if (actual == bimodalPredicted) {
                                    // Do nothing
                                } else {
                                    hybrid.updatePTable(address, (DECISION) GSHARE);
                                }
                            } else if (actual != gsharePredicted) {
                                if (actual == bimodalPredicted) {
                                    hybrid.updatePTable(address, (DECISION) BIMODAL);
                                } else {
                                    // Do nothing
                                }

                            }
                            totalPredictions++;
                            if (actual != predicted) {
                                missPredictions++;
                            }
                        }
                        totalBrances++;
                    }
                    cout << "COMMAND" << endl;
                    cout << "./sim" << " " << argv[1] << " " << argv[2] << " " << argv[4] << " " << argv[5] << " "
                            << argv[6] << endl;
                    cout << "OUTPUT" << endl;
                    if ((0 != BTBSize) || (0 != BTBAssos)) {
                        cout << "size of BTB:\t " << BTBSize << endl;
                        cout << "number of branches:\t" << totalBrances << endl;
                        cout << "number of predictions from branch predictor:\t" << totalPredictions << endl;
                        cout << "number of mispredictions from branch predictor:\t" << missPredictions << endl;
                        cout << "number of branches miss in BTB and taken:\t " << branchMisses << endl;
                        cout << "total mispredictions:\t" << (int) (missPredictions + branchMisses) << endl;
                        if (0 != missPredictions) {
                            cout << fixed << std::setprecision(2) << "misprediction rate:\t"
                                    << (float) (missPredictions + branchMisses) * 100 / (float) (totalBrances) << "%"
                                    << endl;
                        }
                        cout << endl;
                        cout << "FINAL BTB CONTENTS" << endl;
                        BTB.print();
                        cout << endl;
                        cout << "FINAL CHOOSER CONTENTS" << endl;
                        hybrid.print();
                        cout << "FINAL GSHARE CONTENTS" << endl;
                        gshareBp.print();
                        cout << "FINAL BIMODAL CONTENTS" << endl;
                        bimodal.print();
                    } else {
                        cout << "number of predictions:\t" << totalPredictions << endl;
                        cout << "number of mispredictions:\t" << missPredictions << endl;
                        if (0 != missPredictions) {
                            cout << fixed << std::setprecision(2) << "misprediction rate:\t"
                                    << (float) missPredictions * 100 / (float) (totalPredictions) << "%" << endl;
                        }
                        cout << "FINAL CHOOSER CONTENTS" << endl;
                        hybrid.print();
                        cout << "FINAL GSHARE CONTENTS" << endl;
                        gshareBp.print();
                        cout << "FINAL BIMODAL CONTENTS" << endl;
                        bimodal.print();
                    }
                }
            }
        } else {

        }
    } else {
        ERROR_LOG;
    }

    return 0;
}

