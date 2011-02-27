/*
 * Copyright (c) 2011 Peter Vasil
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * Neither the name of the project's author nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef _TOOLMANAGER_H_
#define _TOOLMANAGER_H_

#include "MeshWizIncludes.h"
#include "ConvertTool.h"
#include "TransformTool.h"
#include "AttributeTool.h"

class Mesh;
class ToolManager
{
public:
	ToolManager(Mesh* mesh, bool verbose);
	~ToolManager();
    
    bool convertIndexType(const char* type);
    void translate(float tx, float ty, float tz);
    void rotate(float rangle, float rx, float ry, float rz);
    void scale(float sx, float sy, float sz);
    void resize(float rsx, float rsy, float rsz);
    void resize(const char* axis, float val);
    void center(int axisX, int axisY, int axisZ);
    void generateNormals();
    void removeNormals();
    void generateTangents();
    void removeTangents();
    void generateBitangents();
    void removeBitangents();
    
protected:
private:
    Mesh* m_mesh;
    bool m_verboseOutput;
    
    ConvertTool* m_convertTool;
    TransformTool* m_transformTool;
    AttributeTool* m_attributeTool;
    
};

#endif  // _TOOLMANAGER_H_