#include "ofxJSONElement.h"


ofxJSONElement::ofxJSONElement()
{
}


ofxJSONElement::ofxJSONElement(const Json::Value& v): Json::Value(v)
{
}


ofxJSONElement::ofxJSONElement(const std::string& jsonString)
{
    parse(jsonString);
}


ofxJSONElement::~ofxJSONElement()
{
}


bool ofxJSONElement::parse(const std::string& jsonString)
{
    Json::Reader reader;

    if (!reader.parse( jsonString, *this ))
    {
        ofLogError("ofxJSONElement::parse") << "Unable to parse string: " << reader.getFormattedErrorMessages();
        return false;
    }

    return true;
}


bool ofxJSONElement::open(const std::string& filename)
{
    if (filename.find("http://") == 0 || filename.find("https://") == 0)
    {
        return openRemote(filename);
    }
    else
    {
        return openLocal(filename);
    }
}


bool ofxJSONElement::openLocal(const std::string& filename)
{
    ofBuffer buffer = ofBufferFromFile(filename);

    Json::Reader reader;

    if (!reader.parse(buffer.getText(), *this))
    {
        ofLogError("ofxJSONElement::openLocal") << "Unable to parse " << filename << ": " << reader.getFormattedErrorMessages();
        return false;
    }
    else
    {
        return true;
    }
}


// added by Kajiyu(Yuma Kajihara)
bool ofxJSONElement::openFromBuffer(const ofBuffer& buffer)
{
    Json::Reader reader;
    
    if (!reader.parse(buffer.getText(), *this))
    {
        ofLogError("ofxJSONElement::openLocal") << "Unable to parse "  << ": " << reader.getFormattedErrorMessages();
        return false;
    }
    else
    {
        return true;
    }
}


bool ofxJSONElement::openRemote(const std::string& filename)
{
    std::string result = ofLoadURL(filename).data.getText();

    Json::Reader reader;

    if (!reader.parse(result, *this))
    {
        ofLogError("ofxJSONElement::openRemote") << "Unable to parse " << filename << ": " << reader.getFormattedErrorMessages();
        return false;
    }

    return true;
}


bool ofxJSONElement::save(const std::string& filename, bool pretty) const
{
    ofFile file;

    if (!file.open(filename, ofFile::WriteOnly))
    {
        ofLogError("ofxJSONElement::save") << "Unable to open " << file.getAbsolutePath() << ".";
        return false;
    }

    if (pretty)
    {
        Json::StyledWriter writer;
        file << writer.write( *this ) << std::endl;
    } else {
        Json::FastWriter writer;
        file << writer.write( *this ) << std::endl;
    }

    ofLogVerbose("ofxJSONElement::save") << "JSON saved to " << file.getAbsolutePath() << ".";

    file.close();

    return true;
}


std::string ofxJSONElement::getRawString(bool pretty) const
{
    std::string raw;

    if (pretty)
    {
        Json::StyledWriter writer;
        raw = writer.write(*this);
    }
    else
    {
        Json::FastWriter writer;
        raw = writer.write(*this);
    }

    return raw;
}

std::string ofxJSONElement::toString(Json::ValueType type)
{
    switch (type)
    {
        case Json::nullValue:
            return "null";
        case Json::intValue:
            return "integer";
        case Json::uintValue:
            return "unsigned integer";
        case Json::realValue:
            return "double";
        case Json::stringValue:
            return "string";
        case Json::booleanValue:
            return "boolean";
        case Json::arrayValue:
            return "array";
        case Json::objectValue:
            return "object";
        default:
            ofLogError("ofxJSONElement::toString") << "Unknown Json::ValueType.";
            return "unknown";
    }
}



/* ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| *
 * ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| *
 * |||   Encode Series   ||||||||||||||||||||||||||||||||||||||||| *
 * ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| *
 * ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| */

/* =============================================================== *
 * const ofxJSONElement Encode(const ofPoint &data);              *
 * =============================================================== */
const ofxJSONElement ofxJSONElement :: Encode(const ofPoint& data){
  ofxJSONElement json;

  json["x"] = data.x;
  json["y"] = data.y;
  json["z"] = data.z;

  return json;
}

/* =============================================================== *
 * const ofxJSONElement Encode(const ofVec2f &data);              *
 * =============================================================== */
const ofxJSONElement ofxJSONElement :: Encode(const ofVec2f& data){
  ofxJSONElement json;

  json["x"] = data.x;
  json["y"] = data.y;

  return json;
}

/* =============================================================== *
 * const ofxJSONElement Encode(const ofRectangle &data);          *
 * =============================================================== */
const ofxJSONElement ofxJSONElement :: Encode(const ofRectangle& data){
  ofxJSONElement json;

  json["x"]      = data.x;
  json["y"]      = data.y;
  json["width"]  = data.width;
  json["height"] = data.height;

  return json;
}

/* ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| *
 * ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| *
 * |||   Decode Series   ||||||||||||||||||||||||||||||||||||||||||| *
 * ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| *
 * ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| */

/* ================================================================= *
 * const T Decode(const ofxJSONElement& json);                       *
 * ================================================================= */
template<typename T>
const T ofxJSONElement :: Decode(const ofxJSONElement& json){
  
  T data;

  data = static_cast<T>(
      json.isNull  () ? 0 :
      json.isArray () ? 0 :
      json.isObject() ? 0 :
      json.isString() ? 0 : json.asInt()
  );
  
  return data;
}


/* ================================================================= *
 * const ofPoint Decode<ofPoint>(const ofxJSONElement& json);        *
 * ================================================================= */
template<>
const ofPoint ofxJSONElement :: Decode<ofPoint>(const ofxJSONElement& json){
  ofPoint data;

  data.x = json["x"].isNull  () ? 0 :
           json["x"].isArray () ? 0 :
           json["x"].isObject() ? 0 :
           json["x"].isString() ? 0 : json["x"].asFloat();

  data.y = json["y"].isNull  () ? 0 :
           json["y"].isArray () ? 0 :
           json["y"].isObject() ? 0 :
           json["y"].isString() ? 0 : json["y"].asFloat();

  data.z = json["z"].isNull  () ? 0 :
           json["z"].isArray () ? 0 :
           json["z"].isObject() ? 0 :
           json["z"].isString() ? 0 : json["z"].asFloat();

  return data;
}

/* ================================================================= *
 * const ofVec2f Decode<ofVec2f>(const ofxJSONElement& json);        *
 * ================================================================= */
template<>
const ofVec2f ofxJSONElement :: Decode<ofVec2f>(const ofxJSONElement& json){
  
  ofVec2f data;

  data.x = json["x"].isNull  () ? 0 :
           json["x"].isArray () ? 0 :
           json["x"].isObject() ? 0 :
           json["x"].isString() ? 0 : json["x"].asFloat();

  data.y = json["y"].isNull  () ? 0 :
           json["y"].isArray () ? 0 :
           json["y"].isObject() ? 0 :
           json["y"].isString() ? 0 : json["y"].asFloat();

  return data;

}

/* ================================================================= *
 * const ofRectangle Decode<ofRectangle(const ofxJSONElement& json); *
 * ================================================================= */
template<>
const ofRectangle ofxJSONElement :: Decode<ofRectangle>(const ofxJSONElement& json){

  ofRectangle data;

  data.x = json["x"].isNull  () ? 0 :
           json["x"].isArray () ? 0 :
           json["x"].isObject() ? 0 :
           json["x"].isString() ? 0 : json["x"].asFloat();

  data.y = json["y"].isNull  () ? 0 :
           json["y"].isArray () ? 0 :
           json["y"].isObject() ? 0 :
           json["y"].isString() ? 0 : json["y"].asFloat();

  data.width = json["width"].isNull  () ? 0 :
               json["width"].isArray () ? 0 :
               json["width"].isObject() ? 0 :
               json["width"].isString() ? 0 : json["width"].asFloat();

  data.height = json["height"].isNull  () ? 0 :
                json["height"].isArray () ? 0 :
                json["height"].isObject() ? 0 :
                json["height"].isString() ? 0 : json["height"].asFloat();

  return data;

}
