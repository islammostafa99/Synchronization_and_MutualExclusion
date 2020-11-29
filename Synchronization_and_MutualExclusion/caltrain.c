#include "caltrain.h"

void station_init(struct station *station)
{
    station->waitingRobots = 0;
    station->emptySeats = 0;
    station->leavingRobots = 0;
    pthread_mutex_init(&(station->lock), NULL);
    pthread_cond_init(&(station->launchOnBoard), NULL);
    pthread_cond_init(&(station->trainArrived), NULL);
}

void station_load_train(struct station *station, int count)
{
    pthread_mutex_lock(&(station->lock));
    station->emptySeats = count;
    pthread_cond_broadcast(&(station->trainArrived)); /** to all threads waiting for a train, WAKE UP!*/
    while ((station->waitingRobots > 0 && station-> emptySeats > 0) || station->leavingRobots > 0)
        pthread_cond_wait(&(station->launchOnBoard), &(station->lock)); /**In a train, huh? WAIT for boarding! */
    station->emptySeats = 0;
    pthread_mutex_unlock(&(station->lock));
}

void station_wait_for_train(struct station *station)
{
    pthread_mutex_lock(&(station->lock));
    station->waitingRobots++;
    while(!station->emptySeats)
        pthread_cond_wait(&(station->trainArrived), &(station->lock));
    if(station->emptySeats--)
    {
        station->waitingRobots--;
        station->leavingRobots++;
    }
    pthread_mutex_unlock(&(station->lock));
}

void station_on_board(struct station *station)
{
    pthread_mutex_lock(&(station->lock));
    if(station->leavingRobots--)
        pthread_cond_broadcast(&(station->launchOnBoard));
        /** Now, you can leave, Bye Bye */
    pthread_mutex_unlock(&(station->lock));
}
