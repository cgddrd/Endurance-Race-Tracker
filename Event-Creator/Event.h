/* 
 * File: Event.h
 * Description: Defines all variables/methods for the Entrant class.
 * Author: Connor Luke Goddard (clg11)
 * Date: March 2013
 * Copyright: Aberystwyth University, Aberystwyth
 */

#ifndef EVENT_H
#define	EVENT_H

#include <string>

/**
 * Event class used to define the data model for a particular event.
 */
class Event {
    
public:
    Event();
    Event(std::string newEventName, std::string newEventDate, std::string newEventTime);
    virtual ~Event();
    void setEventTime(std::string eventTime);
    std::string getEventTime(void) const;
    void setEventDate(std::string eventDate);
    std::string getEventDate(void) const;
    void setEventName(std::string eventName);
    std::string getEventName(void) const;
    
private:
    std::string eventName; /**< The name/description of the event.*/
    std::string eventDate; /**< The date that the event is to take place.*/
    std::string eventTime; /**< The starting time of the event.*/
};

#endif	/* EVENT_H */

