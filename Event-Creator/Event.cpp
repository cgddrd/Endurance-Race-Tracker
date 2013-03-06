/* 
 * File:   Event.cpp
 * Author: connor
 * 
 * Created on March 4, 2013, 10:19 AM
 */

#include "Event.h"

using namespace std;

Event::Event() {
    
}

Event::Event(string newEventName, string newEventDate, string newEventTime) {
    
    eventName = newEventName;
    eventDate = newEventDate;
    eventTime = newEventTime;
    
}

Event::Event(const Event& orig) {
}

Event::~Event() {
}

void Event::setEventTime(string eventTime) {
    this->eventTime = eventTime;
}

std::string Event::getEventTime(void) const {
    return eventTime;
}

void Event::setEventDate(string eventDate) {
    this->eventDate = eventDate;
}

std::string Event::getEventDate(void) const {
    return eventDate;
}

void Event::setEventName(string eventName) {
    this->eventName = eventName;
}

std::string Event::getEventName(void) const {
    return eventName;
}