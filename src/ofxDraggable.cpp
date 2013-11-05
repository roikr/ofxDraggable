//
//  ofxDraggable.cpp
//  imageLoaderExample
//
//  Created by Roee Kremer on 6/14/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "ofxDraggable.h"

void ofxDraggable::setup(ofMatrix4x4 mat) {
    
   
    this->mat = mat;
    imat = mat.getInverse();
    
};


void ofxDraggable::begin() {
    ofPushMatrix();
    ofMultMatrix(mat);
    
};

void ofxDraggable::end() {
    ofPopMatrix();
};



void ofxDraggable::touchDown(ofTouchEventArgs &touch) {
    if (touches.empty()) {
       
        touches.push_back(touch);
    } else {
        touches.push_back(touch);
    }
    
};

void ofxDraggable::touchMoved(ofTouchEventArgs &touch) {
    if (!touches.empty()) {
        vector<ofTouchEventArgs>::iterator iter;
        for (iter=touches.begin(); iter!=touches.end(); iter++) {
            if (iter->id == touch.id) {
                break;
            }
        }
        
        
        if (iter==touches.end()) {
            cout << "ofxDraggable::touchMoved - can't find touch" << endl;
        } else {
            switch (touches.size()) {
                case 1:
                    //mat.preMult(ofMatrix4x4::newTranslationMatrix(ofVec2f(iter->x,iter->y)-ofVec2f(touch.x,touch.y)));
                    mat.postMult(ofMatrix4x4::newTranslationMatrix(ofVec2f(touch.x,touch.y)-ofVec2f(iter->x,iter->y)));
                    *iter = touch;
                    break;
                case 2: {
                    ofVec2f p2(touch.x,touch.y);
                    ofVec2f p1(iter->x,iter->y);
                    *iter = touch;
                    ofTouchEventArgs &second = touches[1-distance(touches.begin(), iter)];
                    ofVec2f q(second.x,second.y);
                    ofVec2f qp1 = q-p1;
                    ofVec2f qp2 = q-p2;
                    
                                        
                    ofVec2f trans(0.5*(qp1-qp2));
                    float scl = qp2.length()/qp1.length();
                    float rot = (atan2(qp2.y, qp2.x)-atan2(qp1.y, qp1.x))*180.0f/PI;
                    
                    ofVec2f anchor = mat.getInverse().preMult(ofVec3f(0.5*(p1+q)));
                    
                    ofMatrix4x4 temp(mat);
                    temp.preMult(ofMatrix4x4::newScaleMatrix(scl, scl, 1.0));  
                    temp.preMult(ofMatrix4x4::newRotationMatrix(rot, ofVec3f(0,0,1.0)));
                    
                    ofVec2f vec = temp.preMult(ofVec3f(anchor))-mat.preMult(ofVec3f(anchor));
                    //    cout << anchor <<"\t" << vec << "\t" << scl << endl;
                    
                    temp.postMult(ofMatrix4x4::newTranslationMatrix(trans-vec));
                    mat=temp;
                    
                } break;
                default:
                    break;
            }
            imat = mat.getInverse(); // mat had benn change, need to update its inverse
        }
        
        
    }
};

void ofxDraggable::touchUp(ofTouchEventArgs &touch) {
    if (!touches.empty()) {
        vector<ofTouchEventArgs>::iterator iter;
        for (iter=touches.begin(); iter!=touches.end(); iter++) {
            if (iter->id == touch.id) {
                touches.erase(iter);
                break;
            }
        }
    }
};

void ofxDraggable::touchDoubleTap(ofTouchEventArgs &touch) {
    
};

void ofxDraggable::touchCancelled(ofTouchEventArgs &touch) {
    
};

