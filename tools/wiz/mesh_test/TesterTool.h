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

#ifndef TESTERTOOL_H
#define TESTERTOOL_H

#include "MeshTesterIncludes.h"
#include <string>
#include <vector>

class TesterTool
{
public:
    TesterTool(const char* actual, const char* actualBinary, const char* expected, const char* expectedBinary);

    void start();

    void printResults();

private:
    int compare(int n, float* array_a, float* array_b, float epsilon=0.0f);
    int compare(int n, unsigned char* array_a, unsigned char* array_b);

    void loadMesh(const std::string& xmlFile,
                  const std::string& binaryFile,
                  std::vector<MeshTester::Attribute>& attribs,
                  std::vector<MeshTester::Group>& m_groupsActual);

    std::vector<MeshTester::Attribute> m_attributesActual;
    std::vector<MeshTester::Attribute> m_attributesExpected;

    std::vector<MeshTester::Group> m_groupsActual;
    std::vector<MeshTester::Group> m_groupsExpected;

    bool m_attribsPass;
    bool m_groupsPass;


};

#endif // TESTERTOOL_H
