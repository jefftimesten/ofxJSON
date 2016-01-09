/*
 *  ofxJSON.h
 *  ofxJSON
 *
 *  Created by Jeffrey Crouse on 12/17/10.
 *  Copyright 2010 Eyebeam. All rights reserved.
 *
 *  Updates by Christopher Baker 2012 - 2014
 *  http://christopherbaker.net
 *
 */


#pragma once

#include <string>
#include "json/json.h"
#include "ofLog.h"
#include "ofURLFileLoader.h"

// Add a typedef for backward compatibility
class ofxJSON;
typedef ofxJSON ofxJSONElement;

class ofxJSON: public Json::Value
{
public:
    ofxJSON();
    ofxJSON(const std::string& jsonString);
    ofxJSON(const Json::Value& v);

    virtual ~ofxJSON();

    bool parse(const std::string& jsonString);
    bool open(const std::string& filename);
    bool openLocal(const std::string& filename);
    bool openRemote(const std::string& filename);
    bool save(const std::string& filename, bool pretty = false) const;
    std::string getRawString(bool pretty = true) const;

    static std::string toString(Json::ValueType type);

};
