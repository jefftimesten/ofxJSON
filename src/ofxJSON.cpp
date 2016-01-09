#include "ofxJSON.h"


ofxJSON::ofxJSON()
{
}


ofxJSON::ofxJSON(const Json::Value& v): Json::Value(v)
{
}


ofxJSON::ofxJSON(const std::string& jsonString)
{
    parse(jsonString);
}


ofxJSON::~ofxJSON()
{
}


bool ofxJSON::parse(const std::string& jsonString)
{
    Json::Reader reader;

    if (!reader.parse( jsonString, *this ))
    {
        ofLogError("ofxJSON") << "parse: Unable to parse string: " << reader.getFormattedErrorMessages();
        return false;
    }

    return true;
}


bool ofxJSON::open(const string& filename)
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


bool ofxJSON::openLocal(const std::string& filename)
{
    ofBuffer buffer = ofBufferFromFile(filename);

    Json::Reader reader;

    if (!reader.parse(buffer.getText(), *this))
    {
        ofLogError("ofxJSON") << "openLocal: Unable to parse " << filename << ": " << reader.getFormattedErrorMessages();
        return false;
    }
    else
    {
        return true;
    }
}


bool ofxJSON::openRemote(const std::string& filename)
{
    std::string result = ofLoadURL(filename).data.getText();

    Json::Reader reader;

    if (!reader.parse(result, *this))
    {
        ofLogError("ofxJSON") << "openRemote: Unable to parse " << filename << ": " << reader.getFormattedErrorMessages();
        return false;
    }

    return true;
}


bool ofxJSON::save(const std::string& filename, bool pretty) const
{
    ofFile file;

    if (!file.open(filename, ofFile::WriteOnly))
    {
        ofLogError("ofxJSON") << "save: Unable to open " << file.getAbsolutePath() << ".";
        return false;
    }

    if (pretty)
    {
        Json::StyledWriter writer;
        file << writer.write( *this ) << endl;
    } else {
        Json::FastWriter writer;
        file << writer.write( *this ) << endl;
    }

    ofLogVerbose("ofxJSON") << "save: JSON saved to " << file.getAbsolutePath() << ".";

    file.close();

    return true;
}


std::string ofxJSON::getRawString(bool pretty) const
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

std::string ofxJSON::toString(Json::ValueType type)
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
            ofLogError("ofxJSON") << "toString: Unknown Json::ValueType.";
            return "unknown";
    }
}
