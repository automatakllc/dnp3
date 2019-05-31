/*
 * Copyright 2013-2019 Automatak, LLC
 *
 * Licensed to Green Energy Corp (www.greenenergycorp.com) and Automatak
 * LLC (www.automatak.com) under one or more contributor license agreements.
 * See the NOTICE file distributed with this work for additional information
 * regarding copyright ownership. Green Energy Corp and Automatak LLC license
 * this file to you under the Apache License, Version 2.0 (the "License"); you
 * may not use this file except in compliance with the License. You may obtain
 * a copy of the License at:
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef OPENDNP3_PARSEDEREQUEST_H
#define OPENDNP3_PARSEDEREQUEST_H

#include "app/APDUHeader.h"

#include "opendnp3/link/Addresses.h"

#include <ser4cpp/container/SequenceTypes.h>

namespace opendnp3
{

struct ParsedRequest
{
    ParsedRequest(const Addresses& addresses, const APDUHeader& header, const ser4cpp::rseq_t& objects)
        : addresses(addresses), header(header), objects(objects)
    {
    }

    const Addresses addresses;
    const APDUHeader header;
    const ser4cpp::rseq_t objects;
};

} // namespace opendnp3

#endif
