#include <iostream>
#include "ConfigFile.h"
#include "DataReader.h"
#include "NN.h"
#include "SimulatedAnnealing.h"
#include "Generate.h"
#include "testing.h"

int main() {

    //plik 1
    Config config;
    // Wczytanie konfiguracji
    if (!config.loadConfig("config.txt")) {
        std::cerr << "Nie udało się załadować pliku konfiguracyjnego.\n";
    }
    config.File = "data1.txt";
    config.howBig = 48;
    config.opt = 1776;

    //1. 3opt dla nn, geo, 99
    config.whichOpt = 3;
    config.readyResult = 1;
    config.decreaseType = 0;
    config.Decrease = 0.99;
    doReady(config);


    //2. 3opt dla nn, geo, 90
    config.Decrease = 0.9;
    doReady(config);

    //3. 3opt dla random, geo, 99
    config.readyResult = 0;
    config.Decrease = 0.99;
    doRandom(config);

    //4. 3opt dla random, geo, 90
    config.Decrease = 0.9;
    doRandom(config);

    //5. 2opt dla nn, geo, 99
    config.whichOpt = 2;
    config.readyResult = 1;
    config.Decrease = 0.99;
    doReady(config);

    //6. 2opt dla nn, geo, 90
    config.Decrease = 0.9;
    doReady(config);

    //7. 2opt dla random, geo, 99
    config.readyResult = 0;
    config.Decrease = 0.99;
    doRandom(config);

    //8. 2opt dla random, geo, 90
    config.Decrease = 0.9;
    doRandom(config);

    //9. 3opt, dla nn, log
    config.whichOpt = 3;
    config.readyResult = 1;
    config.decreaseType = 0;
    doReady(config);

    //10. 3opt, dla random, log
    config.readyResult = 0;
    doRandom(config);

    //11. 2opt, dla nn, log
    config.whichOpt = 2;
    config.readyResult = 1;
    doReady(config);

    //12. 2opt, dla random, log
    config.readyResult = 0;
    doRandom(config);



    //plik 2
    config.File = "data2.txt";
    config.howBig = 171;
    config.opt = 2755;


    //1. 3opt dla nn, geo, 99
    config.whichOpt = 3;
    config.readyResult = 1;
    config.decreaseType = 0;
    config.Decrease = 0.99;
    doReady(config);


    //2. 3opt dla nn, geo, 90
    config.Decrease = 0.9;
    doReady(config);

    //3. 3opt dla random, geo, 99
    config.readyResult = 0;
    config.Decrease = 0.99;
    doRandom(config);

    //4. 3opt dla random, geo, 90
    config.Decrease = 0.9;
    doRandom(config);

    //5. 2opt dla nn, geo, 99
    config.whichOpt = 2;
    config.readyResult = 1;
    config.Decrease = 0.99;
    doReady(config);

    //6. 2opt dla nn, geo, 90
    config.Decrease = 0.9;
    doReady(config);

    //7. 2opt dla random, geo, 99
    config.readyResult = 0;
    config.Decrease = 0.99;
    doRandom(config);

    //8. 2opt dla random, geo, 90
    config.Decrease = 0.9;
    doRandom(config);

    //9. 3opt, dla nn, log
    config.whichOpt = 3;
    config.readyResult = 1;
    config.decreaseType = 0;
    doReady(config);

    //10. 3opt, dla random, log
    config.readyResult = 0;
    doRandom(config);

    //11. 2opt, dla nn, log
    config.whichOpt = 2;
    config.readyResult = 1;
    doReady(config);

    //12. 2opt, dla random, log
    config.readyResult = 0;
    doRandom(config);



    //plik 3
    config.File = "data3.txt";
    config.howBig = 403;
    config.opt = 2465;



    //1. 3opt dla nn, geo, 99
    config.whichOpt = 3;
    config.readyResult = 1;
    config.decreaseType = 0;
    config.Decrease = 0.99;
    doReady(config);


    //2. 3opt dla nn, geo, 90
    config.Decrease = 0.9;
    doReady(config);

    //3. 3opt dla random, geo, 99
    config.readyResult = 0;
    config.Decrease = 0.99;
    doRandom(config);

    //4. 3opt dla random, geo, 90
    config.Decrease = 0.9;
    doRandom(config);

    //5. 2opt dla nn, geo, 99
    config.whichOpt = 2;
    config.readyResult = 1;
    config.Decrease = 0.99;
    doReady(config);

    //6. 2opt dla nn, geo, 90
    config.Decrease = 0.9;
    doReady(config);

    //7. 2opt dla random, geo, 99
    config.readyResult = 0;
    config.Decrease = 0.99;
    doRandom(config);

    //8. 2opt dla random, geo, 90
    config.Decrease = 0.9;
    doRandom(config);

    //9. 3opt, dla nn, log
    config.whichOpt = 3;
    config.readyResult = 1;
    config.decreaseType = 0;
    doReady(config);

    //10. 3opt, dla random, log
    config.readyResult = 0;
    doRandom(config);

    //11. 2opt, dla nn, log
    config.whichOpt = 2;
    config.readyResult = 1;
    doReady(config);

    //12. 2opt, dla random, log
    config.readyResult = 0;
    doRandom(config);


    return 0;
}
