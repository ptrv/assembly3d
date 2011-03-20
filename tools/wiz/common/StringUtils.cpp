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

#include "StringUtils.h"
#ifdef TARGET_WIN32
#include <direct.h>
#endif
#include <sys/types.h>
#include <sys/stat.h>
#include <cerrno>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>

using namespace WizUtils;

StringUtils::StringUtils()
{
}
StringUtils::~StringUtils()
{
}


void StringUtils::getValuesFromCmdString(const std::string& cmdStr, std::vector<float>& vals)
{
    std::string args = cmdStr;
    
    size_t startIdx = 0;
    size_t endIdx = 0;
    vals.clear();
    while(endIdx != std::string::npos)
    {
        endIdx = args.find("/", startIdx);
        if(endIdx == std::string::npos)
        {
            vals.push_back((float)atof(args.substr(startIdx).c_str()));
            endIdx = -1;
        }
        else
        {
            vals.push_back((float)atof(args.substr(startIdx, endIdx).c_str()));
        }
        startIdx = endIdx+1;
    }

}
void StringUtils::getValueFromCmdString(const std::string& cmdStr, float& val)
{
    val = (float)atof(cmdStr.c_str());
}

int StringUtils::findOccurensesOf(const std::string& cmdStr, const std::string& stringToSearch)
{
    int result = 0;
    for (unsigned int i = 0; i < cmdStr.length(); ++i)
    {
        if(cmdStr[i] == stringToSearch[0])
            ++result;
    }
    return result;
}

