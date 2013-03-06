/* 
 * File: Event.cpp
 * Description: Provides a data model for a particular event.
 * Author: Connor Luke Goddard (clg11)
 * Date: March 2013
 * Copyright: Aberystwyth University, Aberystwyth
 */

#include "Event.h"

using namespace std;

/**
 * Default constructor for Event.
 */
Event::Event() {
    
}

/**
 * Constructor that allows the characteristics of an event to be specified.
 * @param newEventName The inputted name/description of the event.
 * @param newEventDate The inputted date of the event.
 * @param newEventTime The inputted start time of the event.
 */
Event::Event(string newEventName, string newEventDate, string newEventTime) {
    
    eventName = newEventName;
    eventDate = newEventDate;
    eventTime = newEventTime;
    
}

/**
 * Destructor to be used once object is removed.
 */
Event::~Event() {
}

/**
 * Updates the start time of the event to an inputted value.
 * @param eventTime Recently inputted start time value.
 */
void Event::setEventTime(string eventTime) {
    this->eventTime = eventTime;
}

/**
 * Fetches the start time of the event.
 * @return The value of the 'eventTime' string variable.
 */
string Event::getEventTime(void) const {
    return eventTime;
}

/**
 * Updates the date of the event to an inputted value.
 * @param eventDate Recently inputted event date value.
 */
void Event::setEventDate(string eventDate) {
    this->eventDate = eventDate;
}

/**
 * Fetches the date of the event.
 * @return The value of the 'eventDate' string variable.
 */
string Event::getEventDate(void) const {
    return eventDate;
}

/**
 * Updates the name/description of the event to an inputted value.
 * @param eventTime Recently inputted event name/description..
 */
void Event::setEventName(string eventName) {
    this->eventName = eventName;
}

/**
 * Fetches the name/description of the event.
 * @return The value of the 'eventName' string variable.
 */
string Event::getEventName(void) const {
    return eventName;
}