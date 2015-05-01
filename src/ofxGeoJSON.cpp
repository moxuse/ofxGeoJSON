//
//  ofxGeoJSON.cpp
//  example-loading
//
//  Created by Koichiro Mori on 2013/10/21.
//
//

#include "ofMain.h"
#include "ofxGeoJSON.h"

ofxGeoJSON::ofxGeoJSON() {
    mode = OFX_GEO_JSON_MERCATROE;
};

bool ofxGeoJSON::load(string _path) {
    
    std::string file = _path;
    
    bool parsingSuccessful = result.open(file);
    
    if (parsingSuccessful) {
        cout  << "parsingSuccessful to parse JSON" << endl;
        
        for (int i = 0; i<result["features"].size(); i++) {
            ofxJSONElement type = result["features"][i]["geometry"]["type"];
            string name = result["features"][i]["properties"]["name"].asString();
            ofxJSONElement coordinates = result["features"][i]["geometry"]["coordinates"];
            ofLog(OF_LOG_NOTICE) << "index: " << i << " " << result["features"][i]["properties"]["name"];
            
            ofxGeoJSONFeature newFeatures;
            newFeatures = ofxGeoJSONFeature();
            newFeatures.name = name;
            
            if ("Polygon" == type.asString()) {
                ofPtr<ofMesh> newMesh = ofPtr<ofMesh>(new ofMesh());
                newMesh->setMode(OF_PRIMITIVE_LINE_STRIP);
                for (int j = 0; j<coordinates[0].size(); j++) {
                    Coodinate coord;
                    coord.latitude = coordinates[0][j][1].asFloat();
                    coord.longtitude = coordinates[0][j][0].asFloat();
                    ofPoint pos = convertToProject(coord);
                    newMesh->addVertex(ofVec3f(pos.x, pos.y, pos.z));
                    newMesh->addColor(ofFloatColor(0.0, 0.0, 0.0));
                    newMesh->addIndex(j);
                }
                newFeatures.meshes.push_back(newMesh);
            } else if ("MultiPolygon" == type.asString()) {
                for (int j = 0; j<coordinates.size(); j++) {
                    ofPtr<ofMesh> newMesh = ofPtr<ofMesh>(new ofMesh());
                    newMesh->setMode(OF_PRIMITIVE_LINE_STRIP);
                    for (int k = 0; k<coordinates[j][0].size(); k++) {
                        Coodinate coord;
                        coord.latitude = coordinates[j][0][k][1].asFloat();
                        coord.longtitude = coordinates[j][0][k][0].asFloat();
                        ofPoint pos = convertToProject(coord);
                        newMesh->addVertex(ofVec3f(pos.x, pos.y, pos.z));
                        newMesh->addColor(ofFloatColor(0.0, 0.0, 0.0));
                        newMesh->addIndex(k);
                    }
                    newFeatures.meshes.push_back(newMesh);
                }
            }
            
            features.insert(map<string, ofxGeoJSONFeature>::value_type(name, newFeatures));
        }
        return true;
    } else {
        ofLog(OF_LOG_WARNING, "Failed to parse JSON");
        return false;
    }
    return false;
};

void ofxGeoJSON::setMode(ofx_geo_json_mode _mode) {
    mode = _mode;
};

ofPoint ofxGeoJSON::convertToProject (Coodinate _coordinate) {
  ofPoint position;
  switch (mode) {
    case OFX_GEO_JSON_EQUIRECTANGULAR:
      position = equirectangular(_coordinate);
      break;
    case OFX_GEO_JSON_MERCATROE:
      position = mercator(_coordinate);
      break;
    case OFX_GEO_JSON_STEREOGRAPHIC:
    case OFX_GEO_JSON_AZIMUTHAL_EQUALAREA:
      position = azimuthal(_coordinate);
      break;
    case OFX_GEO_JSON_SPHERICAL:
      position = spherical(_coordinate);
      break;
    default:
      break;
  }
  return position;
}

ofPoint ofxGeoJSON::mercator(Coodinate _coordinate) {
    ofPoint position;
    position.x = (_coordinate.longtitude / 180.0) * scale + translateX;
    position.y = /*_coordinate.latitude > 85 ? 1 : _coordinate.latitude < -85 ? -1 //<- we should consider about polar regions converting..
    : */ ( log(tan(PI / 4.0 + pvRadians(_coordinate.latitude) / 2.0)) / PI ) * scale - translateY;
    return position;
};

ofPoint ofxGeoJSON::equirectangular(Coodinate _coordinate) {
    ofPoint position;
    position.x = _coordinate.longtitude / 360 * scale + translateX;
    position.y = _coordinate.latitude / 360  * scale - translateY;
    return position;
};

ofPoint ofxGeoJSON::azimuthal(Coodinate _coordinate) {
    ofPoint position;
    float cy0 = cos(pvRadians(0));
    float sy0 = sin(pvRadians(0));
    float radian = PI / 180.0;
    float x1 = _coordinate.longtitude * radian - pvRadians(0);
    float y1 = _coordinate.latitude * radian;
    float cx1 = cos(x1);
    float sx1 = sin(x1);
    float cy1 = cos(y1);
    float sy1 = sin(y1);
    float cc = sy0 * sy1 + cy0 * cy1 * cx1;
    float k;
    switch(mode) {
        case OFX_GEO_JSON_STEREOGRAPHIC:
            k = 1 / (1 + cc);
            break;
        case OFX_GEO_JSON_AZIMUTHAL_EQUALAREA:
            k = sqrt(2 / (1 + cc));
            break;
        default:
            break;
    }
    position.x = k * cy1 * sx1 * scale + translateX;
    position.y = -1 * k * (sy0 * cy1 * cx1 - cy0 * sy1) * scale + translateY;
    return position;
}

ofPoint ofxGeoJSON::spherical(Coodinate _coordinate) {
    ofPoint position;
    float lat = pvRadians(_coordinate.latitude);
    float lon = pvRadians(_coordinate.longtitude);
    position.x = E_R * cosf(lat) * cosf(lon) * scale;
    position.y = E_R * cosf(lat) * sinf(lon) * scale;
    position.z = E_R * sinf(lat) * scale;
    return position;
}

float ofxGeoJSON::pvRadians(float _degrees) {
    float radians = PI / 180.0;
    return radians * _degrees;
};

void ofxGeoJSON::setScale(float _scale) {
    scale = _scale;
};

void ofxGeoJSON::setTranslate(float _transelateX, float _transelateY) {
    translateX = _transelateX;
    translateY = _transelateY;
};

void ofxGeoJSON::draw() {
    map<string, ofxGeoJSONFeature>::iterator it = features.begin();
    while( it != features.end() ) {
        vector< ofPtr<ofMesh> > targets = (it->second).meshes;
        for (int i = 0; i < targets.size(); i++) {
            targets[i]->draw(OF_MESH_FILL);
        }
        ++it;
    }
};

vector< ofPtr<ofMesh> > ofxGeoJSON::getFeature(string name) {
    vector< ofPtr<ofMesh> > meshes;
    map<string, ofxGeoJSONFeature>::iterator it;
    it = features.find(name);
    return (it->second).meshes;
}

