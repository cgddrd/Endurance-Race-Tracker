/* 
 * File:   Event.h
 * Author: connor
 *
 * Created on March 4, 2013, 10:19 AM
 */

#ifndef EVENT_H
#define	EVENT_H

#include <string>

class Event {
public:
    Event();
    Event(const Event& orig);
    Event(std::string newEventName, std::string newEventDate, std::string newEventTime);
    virtual ~Event();
    void setEventTime(std::string eventTime);
    std::string getEventTime(void) const;
    void setEventDate(std::string eventDate);
    std::string getEventDate(void) const;
    void setEventName(std::string eventName);
    std::string getEventName(void) const;
private:
    std::string eventName;
    std::string eventDate;
    std::string eventTime;
};

#endif	/* EVENT_H */

