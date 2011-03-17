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

#include "MeshTesterIncludes.h"
#include <tclap/CmdLine.h>
#include "TesterTool.h"


int main (int argc, char* argv[])
{
    try {
        TCLAP::CmdLine cmd("MeshTester - Utility for comparing Assembly3D mesh files.",
                           '=',
                           ProjectInfo::versionString);

        TCLAP::ValueArg<std::string> actualArg("a", "actual", "Actual file.", true, "", "file-path");
        TCLAP::ValueArg<std::string> actualBinaryArg("b", "actual-binary", "Actual input binary file.", true, "", "file-path");
        TCLAP::ValueArg<std::string> expectedArg("e", "expected", "Expected file.", true, "", "file-path");
        TCLAP::ValueArg<std::string> expectedBinaryArg("f", "expected-binary", "Expected binary file.", true, "", "file-path");
        TCLAP::ValueArg<float> epsilonArg("", "epsilon", "Compares attribute values with a deviation epsilon (default 0.0).", false, 0.0f, "val");

//        TCLAP::SwitchArg ignoreOrderAttributes("", "ignore-order-attributes", "Ignore attribute order");
//        TCLAP::SwitchArg ignoreOrderGroups("", "ignore-order-groups", "Ignore group order");

//        cmd.add(ignoreOrderAttributes);
//        cmd.add(ignoreOrderGroups);
        cmd.add(epsilonArg);
        cmd.add(expectedBinaryArg);
        cmd.add(expectedArg);
        cmd.add(actualBinaryArg);
        cmd.add(actualArg);

        // Parse the argv array.
        cmd.parse( argc, argv );

        const char* actualFile = actualArg.getValue().c_str();
        const char* actualBinaryFile = actualBinaryArg.getValue().c_str();
        const char* expectedFile = expectedArg.getValue().c_str();
        const char* expectedBinaryFile = expectedBinaryArg.getValue().c_str();
        float eps = epsilonArg.getValue();

        TesterTool tester;

        tester.compare(actualFile, actualBinaryFile, expectedFile, expectedBinaryFile, eps);

    } catch (TCLAP::ArgException &e)  // catch any exceptions
    { std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl; }

    return 0;
}