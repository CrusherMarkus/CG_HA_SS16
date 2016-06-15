//
//  Exception.hpp
//  CG_HA_SS16
//
//  Created by Markus Klemann on 15.06.16.
//  Copyright © 2016 Markus Klemann. All rights reserved.
//

#ifndef Exception_h
#define Exception_h

#include <exception>


class Exception : public std::exception {
private:
    const char *message;
    
public:
    Exception(const char *message) { this->message = strdup(message); }
    virtual const char *what() const throw() {
        return this->message;
    }
};

#endif /* Exception_h */
