//
// Created by james on 20/08/17.
//

#ifndef LOGGINGMONGO_JSONWRITER_H
#define LOGGINGMONGO_JSONWRITER_H

#include "../../mongo/bson/bsonobjbuilder.h"
#include "../../mongo/bson/bsonobj.h"
#include "JSONType.h"
#include "JsonEntity.h"

using namespace std;
using namespace mongo;

typedef std::stringstream StringStream;

class ObjectType: public JSONType {
private:
    BSONObj *object;
    BSONObj reference;

public:
    ObjectType(std::list<JsonEntity> dataMap) {
        BSONObjBuilder builder;
        for (auto item = dataMap.begin(); item != dataMap.end(); ++item) {
            string key = item->first;
            JSONType* data = item->second;
            data->put(&builder, key);
        }
        reference = builder.obj();
        object = &reference;
    }

    ObjectType(BSONObj data) {
        reference = data;
        object = &reference;
    }


    ObjectType(const BSONObj *data) {
        reference = data->copy();
        object = &reference;
    }

    void log(ostream *stream) {
        StringStream out;
        out << object->jsonString() << endl;
        (*stream) << out.str();
    }

    void put(BSONObjBuilder *map, string key) {
        (*map).append(convert(key), object);
    }
};
#endif //LOGGINGMONGO_JSONWRITER_H
