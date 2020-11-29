#include <pthread.h>

/********************************************************************
    S   T   A   T   I   O   N   -   S   T   R   U   C   T
    @param
    lock -> mutex to enforce matual exclusion.
    launchOnBoard, trainArrived -> to ensure train is arrived
    and passengers are boarded.
    waitingRobots -> # of passengers waiting at station
    leavingRobots -> # of passengers boarded and leaving in a train.
    emptySeats -> capacity of the train.
********************************************************************/

struct station
{
    pthread_mutex_t lock;
    pthread_cond_t launchOnBoard, trainArrived;
    int waitingRobots;
    int emptySeats;
    int leavingRobots;
};

/**
 the function station_init, which will be invoked to initialize the
station object when the system boots.
 */
void station_init(struct station *station);

/**
When a train arrives in the station and has opened its doors, it invokes the function
station_load_train(struct station *station, int count), where
count indicates how many seats are available on the train. The function must not
return until the train is satisfactorily loaded (all passengers are in their seats, and
either the train is full or all waiting passengers have boarded).
 */
void station_load_train(struct station *station, int count);

/**
When a passenger robot arrives in a station, it first invokes the function
station_wait_for_train(struct station *station). This function must
not return until a train is in the station (i.e., a call to station_load_train is in progress)
and there are enough free seats on the train for this passenger to sit down. Once this
function returns, the passenger robot will move the passenger on board the train and
into a seat (you do not need to worry about how this mechanism works).
 */
void station_wait_for_train(struct station *station);

/**
Once the passenger is seated, it will call the function station_on_board(struct
station *station) to let the train know that it's on board.
 */
void station_on_board(struct station *station);
