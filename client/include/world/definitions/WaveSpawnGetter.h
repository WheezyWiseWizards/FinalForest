//
// Created by william on 2022-04-04.
//

#ifndef LD50_CLIENT_WAVESPAWNS_H
#define LD50_CLIENT_WAVESPAWNS_H

#include <vector>

struct WaveSpawn {
    unsigned int round;
    unsigned int LumberJacks = 0;
    unsigned int ChainSawLumberJacks = 0;
    unsigned int Bulldozer = 0;
	bool singleDir = false;
};

class WaveSpawnGetter {
    std::vector<WaveSpawn> waveSpawns =
            {{.round=1, .LumberJacks=3, .singleDir=true},
             {.round=2, .LumberJacks=10, .singleDir=true},
             {.round=3, .LumberJacks=5, .ChainSawLumberJacks=1, .singleDir=true},
             {.round=4, .LumberJacks=6, .ChainSawLumberJacks=3, .Bulldozer=1},
             {.round=5, .LumberJacks=6, .ChainSawLumberJacks=6},
             {.round=6, .LumberJacks=10, .ChainSawLumberJacks=10},
             {.round=7, .LumberJacks=5, .ChainSawLumberJacks=1, .Bulldozer=2},
             {.round=8, .LumberJacks=10, .ChainSawLumberJacks=13},
             {.round=9, .LumberJacks=20, .ChainSawLumberJacks=10},
             {.round=10, .LumberJacks=10, .ChainSawLumberJacks=5, .Bulldozer=3},
             {.round=11, .LumberJacks=10, .ChainSawLumberJacks=20},
             {.round=12, .LumberJacks=20, .ChainSawLumberJacks=20, .Bulldozer=4},
             {.round=13, .LumberJacks=20, .ChainSawLumberJacks=30},
             {.round=14, .LumberJacks=5, .ChainSawLumberJacks=20, .Bulldozer=4},
             {.round=15, .LumberJacks=20, .ChainSawLumberJacks=5, .Bulldozer=4},
             {.round=16, .LumberJacks=5, .ChainSawLumberJacks=30, .Bulldozer=4},
             {.round=17, .LumberJacks=5, .ChainSawLumberJacks=10, .Bulldozer=5},
             {.round=18, .LumberJacks=5, .ChainSawLumberJacks=35, .Bulldozer=6},
             {.round=19, .LumberJacks=15, .ChainSawLumberJacks=50, .Bulldozer=6},
             {.round=20, .LumberJacks=5, .ChainSawLumberJacks=10, .Bulldozer=7}};

public:
    ~WaveSpawnGetter() = default;

    std::vector<WaveSpawn>* getWaveSpawn() {
        return &waveSpawns;
    }
};


#endif //LD50_CLIENT_WAVESPAWNS_H
