//
//  psMoveTrackerClass.cpp
//  regMap
//
//  Created by Bryan Dunphy on 02/03/2018.
//

/**
 * PS Move API - An interface for the PS Move Motion Controller
 * Copyright (c) 2012 Thomas Perl <m@thp.io>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *    1. Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *
 *    2. Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 **/

#include "psMoveTrackerClass.hpp"

psMoveTrackerClass::psMoveTrackerClass(){
    
    controllerModelViewMat = NULL;
    m_moves = NULL;
    m_count = psmove_count_connected();
    m_tracker = psmove_tracker_new();
    m_fusion = psmove_fusion_new(m_tracker, 1., 1000.);
    
    printf("### Found %d controllers.\n", m_count);
    if (m_count == 0) {
        return 1;
    }
    
    fprintf(stderr, "Trying to init PSMoveTracker...");
    
    if (!m_tracker)
    {
        fprintf(stderr, "Could not init PSMoveTracker.\n");
        return 1;
    }
    fprintf(stderr, "OK\n");
    
    psmove_tracker_set_mirror(m_tracker, PSMove_True);
    psmove_tracker_set_exposure(m_tracker, Exposure_LOW);
    m_moves = (PSMove**)calloc(m_count, sizeof(PSMove*));
    
    for (int i=0; i<m_count; i++) {
        
        printf("Opening controller %d\n", i);
        m_moves[i] = psmove_connect_by_id(i);
        assert(m_moves[i] != NULL);
        psmove_enable_orientation(m_moves[i], PSMove_True);
        assert(psmove_has_orientation(m_moves[i]));
        while (psmove_tracker_enable(m_tracker, m_moves[i]) != Tracker_CALIBRATED);
        
    }
    
    for (int i = 0; i < 4; i++){
        obj[i] = false;
    }
    
}

psMoveTrackerClass::~psMoveTrackerClass() {
    
    psmove_fusion_free(m_fusion);
    psmove_tracker_free(m_tracker);
    for (int i=0; i<m_count; i++) {
        psmove_disconnect(m_moves[i]);
    }
    free(m_moves);
}

void psMoveTrackerClass::update() {
    
    for (int i=0; i<m_count; i++) {
        
        rand = false;
        drawInterface = false;
        train = false;
    
#ifdef trackerOn
        psmove_fusion_get_position(m_fusion, m_moves[i], &moveXPos, &moveYPos, &moveZPos);
        
        if(moveXPos > 5.0){
            moveXPos = 5.0;
        } else if(moveXPos < -5.0){
            moveXPos = -5.0;
        }
        
        if(moveYPos > 4.0){
            moveYPos = 4.0;
        } else if(moveYPos < -4.0){
            moveYPos = -4.0;
        }
        
        if(moveZPos > -5.0){
            moveZPos = -5.0;
        } else if(moveZPos < -40.0){
            moveZPos = -40.0;
        }
        
#endif
        
#ifdef trackerOff
        psmove_fusion_get_position(m_fusion, m_moves[i], &camXyz.x, &camXyz.y, &camXyz.z);
#endif
        
        psmove_get_orientation(m_moves[i], &wOrientation, &xOrientation, &yOrientation, &zOrientation);
        controllerModelViewMat = psmove_fusion_get_modelview_matrix(m_fusion, m_moves[i]);
        
        while (psmove_poll(m_moves[i])){
        
            unsigned int pressed, released;
            psmove_get_button_events(m_moves[i], &pressed, &released);
            trig = psmove_get_trigger(m_moves[i]);
            if (pressed & Btn_START) {
                psmove_reset_orientation(m_moves[i]);
            }
            if (pressed & Btn_SQUARE) {
                rand = true;
                obj[1] = !obj[1];
            } else if (pressed & Btn_SELECT) {
                drawInterface = true;
            } else if (pressed & Btn_MOVE){
                record = true;
            } else if (released & Btn_MOVE){
                record = false;
            } else if (pressed & Btn_CROSS){
                train = true;
                obj[0] = !obj[0];
            } else if (pressed & Btn_TRIANGLE){
                obj[2] = !obj[2];
            } else if (pressed & Btn_CIRCLE){
                obj[3] = !obj[3];
            }
        }
    }
    
    psmove_tracker_update_image(m_tracker);
    psmove_tracker_update(m_tracker, NULL);
    

}
